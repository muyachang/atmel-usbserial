/** \file
 *
 *  Header file for rram-usbserial.c.
 */

#ifndef _RRAM_USBSERIAL_H_
#define _RRAM_USBSERIAL_H_

#include <avr/wdt.h>

/* USB Descripto */
#include "Descriptors.h"

/* LUFA Components */
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Board/Dataflash.h>
#include <LUFA/Drivers/Peripheral/Serial.h>

/* Board Components */
#include "PM.h"

/* Libs */
#include "RingBuffer.h"
#include "UARTConsole.h"

void SetupHardware(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_UnhandledControlRequest(void);

void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);    

#endif /* _RRAM_USBSERIAL_H_ */
