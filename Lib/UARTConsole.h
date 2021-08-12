/* \file
 *
 * UART Console
 */
 
#ifndef _UART_CONSOLE_H_
#define _UART_CONSOLE_H_

#include "PM.h"
#include "DAC.h"
#include "Dataflash.h"
#include "RRAM.h"
#include <stdlib.h>

#define PROMPT "ICSRL>"
#define HEADER "<< RRAM Terminal >>\r\n"
#define COMMAND_BUFFER_SIZE 32 
#define TEMP_BUFFER_SIZE 16 

#define NUL 0x00 // Ctrl-@
#define SOH 0x01 // Ctrl-A
#define STX 0x02 // Ctrl-B
#define ETX 0x03 // Ctrl-C
#define EOT 0x04 // Ctrl-D
#define ENQ 0x05 // Ctrl-E
#define ACK 0x06 // Ctrl-F
#define BEL 0x07 // Ctrl-G
#define  BS 0x08 // Ctrl-H
#define  HT 0x09 // Ctrl-I
#define  LF 0x0A // Ctrl-J
#define  VT 0x0B // Ctrl-K
#define  FF 0x0C // Ctrl-L
#define  CR 0x0D // Ctrl-M
#define  SO 0x0E // Ctrl-N
#define  SI 0x0F // Ctrl-O

#define DLE 0x10 // Ctrl-P
#define DC1 0x11 // Ctrl-Q
#define DC2 0x12 // Ctrl-R
#define DC3 0x13 // Ctrl-S
#define DC4 0x14 // Ctrl-T
#define NAK 0x15 // Ctrl-U
#define SYN 0x16 // Ctrl-V
#define ETB 0x17 // Ctrl-W
#define CAN 0x18 // Ctrl-X
#define  EM 0x19 // Ctrl-Y
#define SUB 0x1A // Ctrl-Z
#define ESC 0x1B // Ctrl-[
#define  FS 0x1C // Ctrl-'\'
#define  GS 0x1D // Ctrl-]
#define  RS 0x1E // Ctrl-^
#define  US 0x1F // Ctrl-_

#define SPACE 0x20 //

/* char array for storing the command */
char command[COMMAND_BUFFER_SIZE];
uint8_t count = 0;
uint8_t position = 0;

/* Temp char array for any purpose */
char buffer[TEMP_BUFFER_SIZE];

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
void Write_Program(void);

/*
* 
*/
void Serial_TxString(const char* StringPtr)
{
  //LEDs_TurnOnLEDs(LEDMASK_RX);
  while(*StringPtr != '\0')
    Serial_TxByte(*(StringPtr++));
  //LEDs_TurnOffLEDs(LEDMASK_RX);
}

/*
 * 
 */
static inline void UARTConsole_PrintHeader(void)
{
  CDC_Device_SendString(&VirtualSerial_CDC_Interface, HEADER, strlen(HEADER));
}

/*
 * 
 */
static inline void UARTConsole_PrintPrompt(void)
{
  CDC_Device_SendString(&VirtualSerial_CDC_Interface, PROMPT, strlen(PROMPT));
}

/*
 * 
 */
static inline void UARTConsole_PrintNewLine(void)
{
  CDC_Device_SendByte(&VirtualSerial_CDC_Interface, LF);
  CDC_Device_SendByte(&VirtualSerial_CDC_Interface, CR);
}

/*
 * 
 */
static inline void UARTConsole_MoveBackward(uint8_t _num){
  for(uint8_t i=0;position > 0 && i<_num;i++){
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ESC);
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, 0x5B);
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, 0x44);
    position--;
  }
}

/*
 * 
 */
static inline void UARTConsole_MoveForward(uint8_t _num){
  for(uint8_t i=0;position < count && i<_num;i++){
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ESC);
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, 0x5B);
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, 0x43);
    position++;
  }
}

/*
 * 
 */
static inline void UARTConsole_Backspace(uint8_t _num){
  for(uint8_t i=0;count > 0 && i<_num;i++){
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, BS);
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, SPACE);
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, BS);
    count--;
    position--;
  }
}

/*
 * 
 */
static inline void UARTConsole_CommandInsert(uint8_t _char){
  
  uint8_t tmp;
  uint8_t rollBack = count - position;

  count++;
  while(position < count){
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, _char);
    tmp = command[position];
    command[position] = _char;
    _char = tmp;
    position++;
  }
  UARTConsole_MoveBackward(rollBack);
}

/*
 * 
 */
static inline void UARTConsole_ProcessCommand(void)
{
  /* Insert the null termination */
  command[count] = '\0';

  /* Process the command */
  char *token;
  char *parameter[4];

  token = strtok(command, " ");
  for(uint8_t i=0;i<4;i++){
    parameter[i] = token;
    token = strtok(NULL, " ");
  }

  /* Release the hardware */
  if(strcmp("run", parameter[0]) == 0){
    /* Protocols shutdown */
    SPI_ShutDown();

    /* Reset RRAM testchip */
    RRAM_Reset();
  }

  /* Power Management (PM) */
  else if(strcmp("PM", parameter[0]) == 0){
    if(strcmp("clear", parameter[1]) == 0)
      PM_ClearIRQ();
    else if(strcmp("status", parameter[1]) == 0){
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Status: 0x%02x\r\n",  PM_ReadIRQ());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(strcmp("allon", parameter[1]) == 0)
      PM_EnableAll();
    else if(strcmp("alloff", parameter[1]) == 0)
      PM_DisableAll();
    else if(strcmp("reset", parameter[1]) == 0)
      PM_Reset();
    else if(strcmp("on", parameter[2]) == 0)
      PM_Enable(parameter[1]);
    else if(strcmp("off", parameter[2]) == 0)
      PM_Disable(parameter[1]);
    else if(parameter[2][0] == '+' && parameter[2][1] == '+')
      PM_Adjust(parameter[1], 0, PM_ADJUST_MODE_INCREMENT);
    else if(parameter[2][0] == '-' && parameter[2][1] == '-')
      PM_Adjust(parameter[1], 0, PM_ADJUST_MODE_DECREMENT);
    else if(parameter[2][0] == '+')
      PM_Adjust(parameter[1],atof(parameter[2]+1), PM_ADJUST_MODE_PLUS);
    else if(parameter[2][0] == '-')
      PM_Adjust(parameter[1],atof(parameter[2]+1), PM_ADJUST_MODE_MINUS);
    else if(parameter[2] != NULL)
      PM_Adjust(parameter[1],atof(parameter[2]), PM_ADJUST_MODE_ABSOLUTE);
    else{
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Value: %4d\r\n",  PM_Read(parameter[1]));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
  }

  /* Digital Analog Converter (DAC) */
  else if(strcmp("DAC", parameter[0]) == 0){
    if(parameter[2][0] == '+' && parameter[2][1] == '+')
      DAC_Configure_DAC(parameter[1], 0, DAC_ADJUST_MODE_INCREMENT); 
    else if(parameter[2][0] == '-' && parameter[2][1] == '-')
      DAC_Configure_DAC(parameter[1], 0, DAC_ADJUST_MODE_DECREMENT); 
     else if(parameter[2][0] == '+')
      DAC_Configure_DAC(parameter[1], atoi(parameter[2]+1), DAC_ADJUST_MODE_PLUS); 
    else if(parameter[2][0] == '-')
      DAC_Configure_DAC(parameter[1], atoi(parameter[2]+1), DAC_ADJUST_MODE_MINUS); 
    else if(parameter[2] != NULL)
      DAC_Configure_DAC(parameter[1], atoi(parameter[2]), DAC_ADJUST_MODE_ABSOLUTE); 
    else{
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Value: %4d\r\n",  DAC_Read(parameter[1]));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
  }

  /* Data Flash (DF) */
  else if(strcmp("DF", parameter[0]) == 0){
    // Parse the address
    uint32_t address;
    if(strchr(parameter[2], '.')){
      parameter[2] = strtok(parameter[2], ". ");
      address  = atoi(parameter[2])*DATAFLASH_PAGE_SIZE;
      parameter[2] = strtok(NULL, ". ");
      address += atoi(parameter[2]);
    }
    else if(parameter[2][0] == '0' && parameter[2][1] == 'x')
      address = strtol(parameter[2]+2, NULL, 16);
    else
      address = atoi(parameter[2]);

    // Parse the value
    uint8_t value;
    if(parameter[3][0] == '0' && parameter[3][1] == 'x')
      value = strtol(parameter[3]+2, NULL, 16);
    else
      value = atoi(parameter[3]);

    if(strcmp("upload", parameter[1]) == 0){
      Write_Program();
    }
    else if(strcmp("read", parameter[1]) == 0){
      Dataflash_SelectChip(DATAFLASH_CHIP1);
      Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LF, address);
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Value: 0x%02x\r\n",  (uint8_t)Dataflash_ReceiveByte());
      Dataflash_DeselectChip();
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(strcmp("write", parameter[1]) == 0){
      Dataflash_SelectChip(DATAFLASH_CHIP1);
      Dataflash_Configure_Write_Address(DF_CMD_RMWTHROUGHBUFF1, address);
      Dataflash_SendByte(value);
      Dataflash_DeselectChip();
    }
  }

  /* LED */
  if(strcmp("LED", parameter[0]) == 0)
    if(strcmp("TX", parameter[1]) == 0)
      LEDs_ToggleLEDs(LEDMASK_TX);
    else if(strcmp("RX", parameter[1]) == 0)
      LEDs_ToggleLEDs(LEDMASK_RX);

  /* Unknown command, loop it back to the CDC */
  else if(count !=0){ 
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Unknown Command: ", 17);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, command, count);
    UARTConsole_PrintNewLine();
  }
  
  /* Send it to the RRAM chip */
  Serial_TxString(command);
  
  /* Clear the counter and the position */
  memset(command, 0, COMMAND_BUFFER_SIZE);
  count = 0;
  position = 0;
}

/*
 * 
 */
static inline void UARTConsole_InsertChar(uint8_t _char)
{
       if(_char == BS) // Backspace
    UARTConsole_Backspace(1);
  else if(_char == CR || _char == LF){ // Carriage Return (CR) || New line (LF)
    UARTConsole_PrintNewLine();
    UARTConsole_ProcessCommand();
    UARTConsole_PrintPrompt();
  }
  else if(_char == ESC) { // ESC (Special keys)
    char _char1 = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
    char _char2 = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

    if(_char1 == 0x5B){
      //     if(_char2 == 0x41){ // Up 
      //}
      //else if(_char2 == 0x42){ // Down 
      //}
      if(_char2 == 0x43){ // Right
        UARTConsole_MoveForward(1);
      }
      else if(_char2 == 0x44){ // Left
        UARTConsole_MoveBackward(1);
      }
    }
  }
  //else if(_char == 0x02) // Ctrl + B
  //  UARTConsole_MoveBackward(position);
  //else if(_char == 0x03) // Ctrl + C
  //  UARTConsole_MoveForward(count-position);
  else
    UARTConsole_CommandInsert(_char);
}

#endif
