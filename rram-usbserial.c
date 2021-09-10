/** \file
 *
 *  Main source file for the rram-usbserial project. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "rram-usbserial.h"

RingBuff_t USARTtoUSB_Buffer;

/*
 *  LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
{
  .Config = 
  {
    .ControlInterfaceNumber         = 0,

    .DataINEndpointNumber           = CDC_TX_EPNUM,
    .DataINEndpointSize             = CDC_TXRX_EPSIZE,
    .DataINEndpointDoubleBank       = false,

    .DataOUTEndpointNumber          = CDC_RX_EPNUM,
    .DataOUTEndpointSize            = CDC_TXRX_EPSIZE,
    .DataOUTEndpointDoubleBank      = false,

    .NotificationEndpointNumber     = CDC_NOTIFICATION_EPNUM,
    .NotificationEndpointSize       = CDC_NOTIFICATION_EPSIZE,
    .NotificationEndpointDoubleBank = false,
  },
};

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
  SetupHardware();
  
  /* Infinite Loop */
  for (;;)
  {
    /* Read bytes from the USB OUT endpoint into the UART Console */
    int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
    if (!(ReceivedByte < 0))
      UARTConsole_InsertChar(ReceivedByte);
    
    /* Check if the UART receive buffer flush timer has expired or the buffer is nearly full */
    RingBuff_Count_t BufferCount = RingBuffer_GetCount(&USARTtoUSB_Buffer);
    if ((TIFR0 & (1 << TOV0)) || (BufferCount > BUFFER_NEARLY_FULL))
    {
      TIFR0 |= (1 << TOV0);

      if (USARTtoUSB_Buffer.Count) {
        LEDs_TurnOnLEDs(LEDMASK_TX);
        TxLEDPulse = LEDS_PULSE_MS;
      }

      /* Read bytes from the USART receive buffer into the USB IN endpoint */
      while (BufferCount--)
        CDC_Device_SendByte(&VirtualSerial_CDC_Interface, RingBuffer_Remove(&USARTtoUSB_Buffer));
        
      /* Turn off TX LED(s) once the TX pulse period has elapsed */
      if (TxLEDPulse && !(--TxLEDPulse))
        LEDs_TurnOffLEDs(LEDMASK_TX);
    }
    
    CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
  }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
  /* Disable watchdog if enabled by bootloader/fuses */
  MCUSR &= ~_BV(WDRF); // Clear Watchdog Reset Flag
  wdt_disable(); // Disable Watchdog Timer

  /* Enable Global Interrupt */
  sei();

  /* Start the flush timer so that overflows occur rapidly to push received bytes to the USB interface */
  TCCR0B = (1 << CS02);
  
  /* UART Buffer Initialization*/
  RingBuffer_InitBuffer(&USARTtoUSB_Buffer);

  /* Protocol Initialization */
  USB_Init();
  Serial_Init(115200, false);

  /* Power Initialization */
  PM_Init();
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
  CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
  CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/* 
 * Event handler for the CDC Class driver Line Encoding Changed event.
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
  /* Must turn off USART before reconfiguring it, otherwise incorrect operation may occur */
  UCSR1B = 0;

  /* Reconfigure USART Baud Rate Registers */
  UBRR1 = SERIAL_2X_UBBRVAL(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS);  

  /* Reconfigure UCSRnC – USART Control and Status Register C */
  {
    uint8_t ConfigMask = 0;

    // Bits 5:4 – UPMn1:0: Parity Mode
    switch (CDCInterfaceInfo->State.LineEncoding.ParityType) {
      case CDC_PARITY_Odd:  ConfigMask = (_BV(UPM11) | _BV(UPM10));    break;
      case CDC_PARITY_Even: ConfigMask =  _BV(UPM11);                  break;
    }

    // Bit 3 – USBSn: Stop Bit Select
    if (CDCInterfaceInfo->State.LineEncoding.CharFormat == CDC_LINEENCODING_TwoStopBits)
      ConfigMask |= _BV(USBS1);

    // Bit 2:1 – UCSZn1:0: Character Size
    switch (CDCInterfaceInfo->State.LineEncoding.DataBits) {
      case 6: ConfigMask |=                _BV(UCSZ10) ; break;
      case 7: ConfigMask |=  _BV(UCSZ11);                break;
      case 8: ConfigMask |= (_BV(UCSZ11) | _BV(UCSZ10)); break;
    }

    UCSR1C = ConfigMask;
  }

  /* Reconfigure UCSRnA – USART Control and Status Register A */
  UCSR1A = _BV(U2X1);

  /* Reconfigure UCSRnB – USART Control and Status Register B */
  UCSR1B = _BV(RXCIE1) | _BV(RXEN1) | _BV(TXEN1);
}

/* Event handler for the CDC Class driver control line state change event.
 *
 * \param[in] CDCInterfaceInfo Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
  bool DataTerminalReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR);

  // Data Terminal Ready (DTR)
  if (DataTerminalReady){
  }
  else{
  }
}

/* 
 * ISR to manage the reception of data from the serial port placing received bytes into a circular buffer for later
 * transmission to the host.
 */
ISR(USART1_RX_vect, ISR_BLOCK)
{
  static bool TC_Commanding = false;

  /* USART -> Buffer */
  uint8_t temp = UDR1;

  if(temp == ESC) // A command from Testchip about to come
    TC_Commanding = !TC_Commanding;
  else if(TC_Commanding) // Receiving the command from the testchip
    UARTConsole_InsertChar(temp);
  else
    RingBuffer_Insert(&USARTtoUSB_Buffer, temp);
}
