/* \file
 *
 * UART Console
 */
 
#ifndef _UART_CONSOLE_H_
#define _UART_CONSOLE_H_

#include <stdlib.h>
#include "PM.h"
#include "DAC.h"
#include "Dataflash.h"
#include "RRAM.h"
#include "Demos.h"

#define PROMPT "ICSRL>\0"
#define HEADER "<< RRAM Terminal >>\r\n"
#define COMMAND_BUFFER_SIZE 32 
#define TEMP_BUFFER_SIZE 32 

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

/*
* 
*/
void Serial_TxString(const char* StringPtr)
{
  LEDs_TurnOnLEDs(LEDMASK_RX);
  while(*StringPtr != '\0')
    Serial_TxByte(*(StringPtr++));
  LEDs_TurnOffLEDs(LEDMASK_RX);
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

  /* Power Management (PM) */
  if(strcmp("PM", parameter[0]) == 0){
    if(strcmp("list", parameter[1]) == 0){
      regulator_structure_t *regulator = regulators_map;
      while(regulator->name) {
        memset(buffer, 0, TEMP_BUFFER_SIZE);
        sprintf(buffer, " - %10s(%3s): %4d mV\r\n", regulator->name, PM_Is_Enabled(regulator->name)?"on":"off", PM_Read_Voltage(regulator->name));
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        regulator++;
      }
    }
    else if(strcmp("clear", parameter[1]) == 0)
      PM_ClearIRQ();
    else if(strcmp("status", parameter[1]) == 0){
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Status: 0x%02X\r\n",  PM_ReadIRQ());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(strcmp("save", parameter[1]) == 0)
      PM_Save();
    else if(strcmp("load", parameter[1]) == 0)
      PM_Load();
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
      sprintf(buffer, " - %10s(%3s): %4d mV\r\n", parameter[1], PM_Is_Enabled(parameter[1])?"on":"off", PM_Read_Voltage(parameter[1]));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
  }

  /* Digital Analog Converter (DAC) */
  else if(strcmp("DAC", parameter[0]) == 0){
    if(strcmp("list", parameter[1]) == 0){
      dac_structure_t *channel = dacs_map;
      while(channel->name) {
        memset(buffer, 0, TEMP_BUFFER_SIZE);
        sprintf(buffer, " - %10s: %4d mV\r\n", channel->name, DAC_Read_Voltage(channel->name));
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        channel++;
      }
    }
    else if(parameter[2][0] == '+' && parameter[2][1] == '+')
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
      sprintf(buffer, " - %10s: %4d mV\r\n", parameter[1], DAC_Read_Voltage(parameter[1]));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
  }

  /* Data Flash (DF) */
  else if(strcmp("DF", parameter[0]) == 0){
    Dataflash_SelectChip(DATAFLASH_CHIP1);
    if(strcmp("status", parameter[1]) == 0){
      Dataflash_SendByte(DF_CMD_GETSTATUS);
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Byte 1: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "Byte 2: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    //else if(strcmp("id", parameter[1]) == 0){
    //  Dataflash_SendByte(DF_CMD_READMANUFACTURERDEVICEINFO);
    //  memset(buffer, 0, TEMP_BUFFER_SIZE);
    //  sprintf(buffer, "Manufacturer ID : 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
    //  CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //  memset(buffer, 0, TEMP_BUFFER_SIZE);
    //  sprintf(buffer, "Device ID Byte 1: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
    //  CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //  memset(buffer, 0, TEMP_BUFFER_SIZE);
    //  sprintf(buffer, "Device ID Byte 2: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
    //  CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //}
    else if(strcmp("reset", parameter[1]) == 0){
      for(uint8_t i=0;i<sizeof(DF_CMD_SOFTWARERESET)/sizeof(DF_CMD_SOFTWARERESET[0]);i++)
        Dataflash_SendByte(DF_CMD_SOFTWARERESET[i]);
    }
    else if(strcmp("read", parameter[1]) == 0){
      uint32_t address;
      uint32_t count;
      if(strcmp("chip", parameter[2]) == 0){
        address = 0;
        count   = (uint32_t)DATAFLASH_PAGES*(uint32_t)DATAFLASH_PAGE_SIZE;
      }
      else if(strcmp("sector", parameter[2]) == 0){
        if(strcmp("0a", parameter[3]) == 0){
          address = 0;
          count   = 1*(uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
        }
        else if(strcmp("0b", parameter[3]) == 0){
          address =                                   1*(uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
          count   = ((uint32_t)DATAFLASH_SECTOR_SIZE-1)*(uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
        }
        else{
          address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_SECTOR_SIZE*(uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
          count   =                              (uint32_t)DATAFLASH_SECTOR_SIZE*(uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
        }
      }
      else if(strcmp("block", parameter[2]) == 0){
        address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
        count   =                              (uint32_t)DATAFLASH_BLOCK_SIZE*(uint32_t)DATAFLASH_PAGE_SIZE;
      }
      else if(strcmp("page", parameter[2]) == 0){
        address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_PAGE_SIZE;
        count   =                              (uint32_t)DATAFLASH_PAGE_SIZE;
      }
      else{ // Reading only 1 Byte
        // Parse the address
        if(strchr(parameter[3], '.')){ // [Page].[Offset] format
          parameter[3] = strtok(parameter[3], ". ");
          address  = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_PAGE_SIZE;
          parameter[3] = strtok(NULL, ". ");
          address += (uint32_t)atoi(parameter[3]);
        }
        else if(parameter[3][0] == '0' && parameter[3][1] == 'x') // Hex format
          address = strtol(parameter[3]+2, NULL, 16);
        else // Integer format
          address = (uint32_t)atoi(parameter[3]);
        count = 1;
      }

      // Start reading and printing
      Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, address);
      for(uint32_t i = 0; i<count;i++){
        if(i%16 == 0){
          memset(buffer, 0, TEMP_BUFFER_SIZE);
          sprintf(buffer, "DF[0x%04lX]: 0x", i);
          CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        }
        memset(buffer, 0, TEMP_BUFFER_SIZE);
        sprintf(buffer, "%02X", (uint8_t)Dataflash_ReceiveByte());
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        if(i%16 == 15 || i == count - 1){
          CDC_Device_SendByte(&VirtualSerial_CDC_Interface, LF);
          CDC_Device_SendByte(&VirtualSerial_CDC_Interface, CR);
        }
      }
    }
    else if(strcmp("write", parameter[1]) == 0){
      // Parse the address
      uint32_t address;
      if(strchr(parameter[2], '.')){
        parameter[2] = strtok(parameter[2], ". ");
        address  = (uint32_t)atoi(parameter[2])*(uint32_t)DATAFLASH_PAGE_SIZE;
        parameter[2] = strtok(NULL, ". ");
        address += (uint32_t)atoi(parameter[2]);
      }
      else if(parameter[2][0] == '0' && parameter[2][1] == 'x')
        address = strtol(parameter[2]+2, NULL, 16);
      else
        address = (uint32_t)atoi(parameter[2]);

      // Parse the value
      uint8_t value;
      if(parameter[3][0] == '0' && parameter[3][1] == 'x')
        value = strtol(parameter[3]+2, NULL, 16);
      else
        value = (uint32_t)atoi(parameter[3]);

      Dataflash_Configure_Write_Address(DF_CMD_RMWTHROUGHBUFF1, address);
      Dataflash_SendByte(value);
    }
    else if(strcmp("erase", parameter[1]) == 0){
      if(strcmp("chip", parameter[2]) == 0){
        for(uint8_t i=0;i<sizeof(DF_CMD_CHIPERASE)/sizeof(DF_CMD_CHIPERASE[0]);i++)
          Dataflash_SendByte(DF_CMD_CHIPERASE[i]);
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
      else if(strcmp("sector", parameter[2]) == 0){
        if(strcmp("0a", parameter[3]) == 0)
          Dataflash_Configure_Write_Address(DF_CMD_SECTORERASE,                            0 << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH));
        else if(strcmp("0b", parameter[3]) == 0)
          Dataflash_Configure_Write_Address(DF_CMD_SECTORERASE,                            1 << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH));
        else
          Dataflash_Configure_Write_Address(DF_CMD_SECTORERASE, (uint32_t)atoi(parameter[3]) << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_SECTOR_ADDR_WIDTH));
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
      else if(strcmp("block", parameter[2]) == 0){
        Dataflash_Configure_Write_Address(DF_CMD_BLOCKERASE, (uint32_t)atoi(parameter[3]) << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH));
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
      else if(strcmp("page", parameter[2]) == 0){
        Dataflash_Configure_Write_Address(DF_CMD_PAGEERASE, (uint32_t)atoi(parameter[3]) << (uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH);
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
    }
    else if(strcmp("protect", parameter[1]) == 0){
      if(strcmp("on", parameter[2]) == 0){
        // Enable Sector Protection
        for(uint8_t i=0;i<sizeof(DF_CMD_ENABLESECTORPROTECTION)/sizeof(DF_CMD_ENABLESECTORPROTECTION[0]);i++)
          Dataflash_SendByte(DF_CMD_ENABLESECTORPROTECTION[i]);
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
      else if(strcmp("off", parameter[2]) == 0){
        for(uint8_t i=0;i<sizeof(DF_CMD_DISABLESECTORPROTECTION)/sizeof(DF_CMD_DISABLESECTORPROTECTION[0]);i++)
          Dataflash_SendByte(DF_CMD_DISABLESECTORPROTECTION[i]);
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
      else if(strcmp("status", parameter[2]) == 0){
        for(uint8_t i=0;i<sizeof(DF_CMD_READSECTORPROTECTIONREG)/sizeof(DF_CMD_READSECTORPROTECTIONREG[0]);i++)
          Dataflash_SendByte(DF_CMD_READSECTORPROTECTIONREG[i]);
        for(uint16_t i=0;i<DATAFLASH_SECTORS;i++){
          memset(buffer, 0, TEMP_BUFFER_SIZE);
          sprintf(buffer, "Sector[%u]: %02X\r\n", i, (uint8_t)Dataflash_ReceiveByte());
          CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        }
      }
      else{
        uint8_t  value;
        if(strcmp("all", parameter[2]) == 0){
          for(uint8_t i = 0;i<DATAFLASH_SECTORS;i++){
            eeprom_write_byte(&DF_Sector_Protection[i], DF_SECTORPROTECTIONREG_PROTECTED);
            eeprom_busy_wait();
          }
        }
        else if(strcmp("none", parameter[2]) == 0){
          for(uint8_t i = 0;i<DATAFLASH_SECTORS;i++){
            eeprom_write_byte(&DF_Sector_Protection[i], DF_SECTORPROTECTIONREG_UNPROTECTED);
            eeprom_busy_wait();
          }
        }
        else if(strcmp("0a", parameter[2]+1) == 0){
          value = eeprom_read_byte(&DF_Sector_Protection[0]);
          if(parameter[2][0] == '+')
            value |= DF_SECTORPROTECTIONREG_0A_PROTECTED;
          if(parameter[2][0] == '-')
            value &= ~DF_SECTORPROTECTIONREG_0A_PROTECTED;
          eeprom_write_byte(&DF_Sector_Protection[0], value);
          eeprom_busy_wait();
        }
        else if(strcmp("0b", parameter[2]+1) == 0){
          value = eeprom_read_byte(&DF_Sector_Protection[0]);
          if(parameter[2][0] == '+')
            value |= DF_SECTORPROTECTIONREG_0B_PROTECTED;
          else if(parameter[2][0] == '-')
            value &= ~DF_SECTORPROTECTIONREG_0B_PROTECTED;
          eeprom_write_byte(&DF_Sector_Protection[0], value);
          eeprom_busy_wait();
        }
        else{
          if(parameter[2][0] == '+')
            value = DF_SECTORPROTECTIONREG_PROTECTED;
          else if(parameter[2][0] == '-')
            value = DF_SECTORPROTECTIONREG_UNPROTECTED;
          else
            value = DF_SECTORPROTECTIONREG_PROTECTED;
          eeprom_write_byte(&DF_Sector_Protection[atoi(parameter[2]+1)], value);
          eeprom_busy_wait();
        }

        // Erase first
        for(uint8_t i=0;i<sizeof(DF_CMD_ERASESECTORPROTECTIONREG)/sizeof(DF_CMD_ERASESECTORPROTECTIONREG[0]);i++)
          Dataflash_SendByte(DF_CMD_ERASESECTORPROTECTIONREG[i]);
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();

        // Update Sector Protection Register
        for(uint8_t i=0;i<sizeof(DF_CMD_PROGRAMSECTORPROTECTIONREG)/sizeof(DF_CMD_PROGRAMSECTORPROTECTIONREG[0]);i++)
          Dataflash_SendByte(DF_CMD_PROGRAMSECTORPROTECTIONREG[i]);
        for(uint8_t i=0;i<DATAFLASH_SECTORS;i++)
          Dataflash_SendByte(eeprom_read_byte(&DF_Sector_Protection[i]));
        Dataflash_ToggleSelectedChipCS();
        Dataflash_WaitWhileBusy();
      }
    }
    else if(strcmp("blankcheck", parameter[1]) == 0){
      uint32_t i;
      Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, 0);
      for(i = 0; i<(uint32_t)DATAFLASH_PAGES*(uint32_t)DATAFLASH_PAGE_SIZE;i++){
        uint8_t temp = Dataflash_ReceiveByte();
        if(temp != 255){
          memset(buffer, 0, TEMP_BUFFER_SIZE);
          sprintf(buffer, "0x%02lX value %d\r\n", i, temp);
          CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
          break;
        }
      }
      if(i == (uint32_t)DATAFLASH_PAGES*(uint32_t)DATAFLASH_PAGE_SIZE){
        memset(buffer, 0, TEMP_BUFFER_SIZE);
        sprintf(buffer, "Dataflash blank\r\n");
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
    }
    Dataflash_DeselectChip();
  }

  /* EEPROM */
  else if(strcmp("EEPROM", parameter[0]) == 0){
    if(strcmp("read", parameter[1]) == 0){
      uint16_t address = (uint8_t)atoi(parameter[2]);
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "EEPROM[%u]: 0x%02X\r\n", address, eeprom_read_byte((uint8_t*)address));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(strcmp("write", parameter[1]) == 0){
      uint16_t address = (uint8_t)atoi(parameter[2]);
      uint8_t value;
      if(parameter[3][0] == '0' && parameter[3][1] == 'x')
        value = strtol(parameter[3]+2, NULL, 16);
      else
        value = (uint32_t)atoi(parameter[3]);
      eeprom_write_byte((uint8_t*)address, value);
      eeprom_busy_wait();
    }

  }

  /* LED */
  else if(strcmp("LED", parameter[0]) == 0){
    if(strcmp("TX", parameter[1]) == 0){
      if(strcmp("on", parameter[2]) == 0)
        LEDs_TurnOnLEDs(LEDMASK_TX);
      else if(strcmp("off", parameter[2]) == 0)
        LEDs_TurnOffLEDs(LEDMASK_TX);
      else
        LEDs_ToggleLEDs(LEDMASK_TX);
    }
    else if(strcmp("RX", parameter[1]) == 0){
      if(strcmp("on", parameter[2]) == 0)
        LEDs_TurnOnLEDs(LEDMASK_RX);
      else if(strcmp("off", parameter[2]) == 0)
        LEDs_TurnOffLEDs(LEDMASK_RX);
      else
        LEDs_ToggleLEDs(LEDMASK_RX);
    }
  }

  /* RRAM */
  else if(strcmp("RRAM", parameter[0]) == 0){
    if(strcmp("linereset", parameter[1]) == 0){
      SW_LineReset();
    }
    else if(strcmp("jtagtosw", parameter[1]) == 0){
      SW_JTAGToSW();
    }
    else if(strcmp("connect", parameter[1]) == 0){
      SW_Connect();
    }
    else if(strcmp("powerup", parameter[1]) == 0){
      SW_DAPPowerUp();
    }
    //else if(strcmp("write", parameter[1]) == 0){
    //  SW_WriteMem();
    //}
    //else if(strcmp("read", parameter[1]) == 0){
    //  SW_WriteMem();
    //}
    else if(strcmp("halt", parameter[1]) == 0){
      SW_HaltCore();
    }
    else if(strcmp("resetcore", parameter[1]) == 0){
      SW_ResetCore();
    }
  }

  /* Demos */
  else if(strcmp("DEMO", parameter[0]) == 0){
    if(strcmp("list", parameter[1]) == 0){
      for(uint8_t i=0;i<sizeof(demos_map)/sizeof(demos_structure_t);i++){
        memset(buffer, 0, TEMP_BUFFER_SIZE);
        sprintf(buffer, "%u - %s\r\n",  i, demos_map[i].name);
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
    }
    else if(strcmp("load", parameter[1]) == 0){
      // Print out the demo being loaded
      uint8_t index = atoi(parameter[2]);
      memset(buffer, 0, TEMP_BUFFER_SIZE);
      sprintf(buffer, "\"%s\" from sector %u\r\n", demos_map[index].name, demos_map[index].sector_number);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));

      //// Prepare RRAM testchip for programming
      //SW_JTAGToSW();
      //SW_Connect();
      //SW_DAPPowerUp();
      //SW_HaltCore();

      //// Start reading from the Dataflash sequentially and Write to the RRAM testchip
      //Dataflash_SelectChip(DATAFLASH_CHIP1);
      //Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LF, 0);
      //for(uint32_t i=0; i < RRAM_ROM_SIZE; i++){
      //  SW_WriteMem(SW_ROM_ADDR + i, SW_REG_AP_CSW_SIZE_BYTE_MASK, Dataflash_ReceiveByte());
      //}
      //Dataflash_DeselectChip();
    }
    else if(strcmp("run", parameter[1]) == 0){
      SPI_ShutDown();
      RRAM_Reset();
    }
  }

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
           if(_char2 == 0x41){ // Up 
      }
      else if(_char2 == 0x42){ // Down 
      }
      if(_char2 == 0x43){ // Right
        UARTConsole_MoveForward(1);
      }
      else if(_char2 == 0x44){ // Left
        UARTConsole_MoveBackward(1);
      }
    }
  }
  else if(_char == 0x02) // Ctrl + B
    UARTConsole_MoveBackward(position);
  else if(_char == 0x03) // Ctrl + C
    UARTConsole_MoveForward(count-position);
  else
    UARTConsole_CommandInsert(_char);
}

#endif
