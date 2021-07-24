/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for rram-usbserial.c.
 */

#ifndef _RRAM_USBSERIAL_H_
#define _RRAM_USBSERIAL_H_

#include <avr/wdt.h>

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Board/Dataflash.h>
#include <LUFA/Drivers/Peripheral/Serial.h>

#include "Descriptors.h"

/* Libs */
#include "RingBuffer.h"
#include "UARTConsole.h"
#include "SWD.h"

/* Board Components */
#include "DAC.h"
#include "PM.h"
#include "RRAM.h"

void SetupHardware(void);
void Write_Program(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_UnhandledControlRequest(void);

void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);    

#endif /* _RRAM_USBSERIAL_H_ */
