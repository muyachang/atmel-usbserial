/* \file
 *
 * UART Console
 */
 
#ifndef _UART_CONSOLE_H_
#define _UART_CONSOLE_H_

#define UART_HEADER         "ICSRL>"
#define COMMAND_BUFFER_SIZE 64 

char command[COMMAND_BUFFER_SIZE];
uint8_t count = 0;

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;

/*
 * 
 */
static inline void UARTConsole_PrintHeader()
{
  for(uint8_t i=0;i<6;i++)
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, UART_HEADER[i]);
}

#endif
