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
#include "TC.h"
#include "Demos.h"
#include "ASCII.h"

#define PROMPT "ICSRL>\0"
#define HEADER "<< TC Terminal >>\r\n"

/* char array for storing the command */
char command[32];
uint8_t count = 0;
uint8_t position = 0;

/* Temp char array for any purpose */
char buffer[32];

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
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, " - %10s(%3s): %4d mV\r\n", regulator->name, PM_Is_Enabled(regulator->name)?"on":"off", PM_Read_Voltage(regulator->name));
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        regulator++;
      }
    }
    else if(strcmp("clear", parameter[1]) == 0)
      PM_ClearIRQ();
    else if(strcmp("status", parameter[1]) == 0){
        memset(buffer, 0, sizeof(buffer));
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
      //memset(buffer, 0, sizeof(buffer));
      //sprintf(buffer, " - %10s(%3s): %4d mV\r\n", parameter[1], PM_Is_Enabled(parameter[1])?"on":"off", PM_Read_Voltage(parameter[1]));
      //CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
  }

  /* Digital Analog Converter (DAC) */
  else if(strcmp("DAC", parameter[0]) == 0){
    if(strcmp("list", parameter[1]) == 0){
      dac_structure_t *channel = dacs_map;
      while(channel->name) {
        memset(buffer, 0, sizeof(buffer));
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
      //memset(buffer, 0, sizeof(buffer));
      //sprintf(buffer, " - %10s: %4d mV\r\n", parameter[1], DAC_Read_Voltage(parameter[1]));
      //CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
  }

  /* Data Flash (DF) */
  else if(strcmp("DF", parameter[0]) == 0){
    Dataflash_SelectChip(DATAFLASH_CHIP1);
    if(strcmp("status", parameter[1]) == 0){
      Dataflash_SendByte(DF_CMD_GETSTATUS);
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "Byte 1: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "Byte 2: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    //else if(strcmp("id", parameter[1]) == 0){
    //  Dataflash_SendByte(DF_CMD_READMANUFACTURERDEVICEINFO);
    //  memset(buffer, 0, sizeof(buffer));
    //  sprintf(buffer, "Manufacturer ID : 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
    //  CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //  memset(buffer, 0, sizeof(buffer));
    //  sprintf(buffer, "Device ID Byte 1: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
    //  CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //  memset(buffer, 0, sizeof(buffer));
    //  sprintf(buffer, "Device ID Byte 2: 0x%02X\r\n",  (uint8_t)Dataflash_ReceiveByte());
    //  CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //}
    else if(strcmp("reset", parameter[1]) == 0)
      Dataflash_Reset();
    else if(strcmp("read", parameter[1]) == 0){
      uint32_t address;
      uint32_t count;
      if(strcmp("chip", parameter[2]) == 0){
        address = 0;
        count   = (uint32_t)DATAFLASH_SIZE;
      }
      else if(strcmp("sector", parameter[2]) == 0){
        if(strcmp("0a", parameter[3]) == 0){
          address = 0*(uint32_t)DATAFLASH_BLOCK_SIZE;
          count   = 1*(uint32_t)DATAFLASH_BLOCK_SIZE;
        }
        else if(strcmp("0b", parameter[3]) == 0){
          address =  1*(uint32_t)DATAFLASH_BLOCK_SIZE;
          count   = 15*(uint32_t)DATAFLASH_BLOCK_SIZE;
        }
        else{
          address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_SECTOR_SIZE;
          count   =                              (uint32_t)DATAFLASH_SECTOR_SIZE;
        }
      }
      else if(strcmp("block", parameter[2]) == 0){
        address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_BLOCK_SIZE;
        count   =                              (uint32_t)DATAFLASH_BLOCK_SIZE;
      }
      else if(strcmp("page", parameter[2]) == 0){
        address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_PAGE_SIZE;
        count   =                              (uint32_t)DATAFLASH_PAGE_SIZE;
      }
      else{ // Reading only 1 Byte
        // Parse the address
        if(strchr(parameter[2], '.')){ // [Page].[Offset] format
          parameter[2] = strtok(parameter[2], ". ");
          address  = (uint32_t)atoi(parameter[2])*(uint32_t)DATAFLASH_PAGE_SIZE;
          parameter[2] = strtok(NULL, ". ");
          address += (uint32_t)atoi(parameter[2]);
        }
        else if(parameter[2][0] == '0' && parameter[2][1] == 'x') // Hex format
          address = strtol(parameter[2]+2, NULL, 16);
        else // Integer format
          address = (uint32_t)atoi(parameter[2]);
        count = 1;
      }

      // Start reading and printing
      Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, address);
      for(uint32_t i = 0; i<count;i++){
        if(i%16 == 0){
          memset(buffer, 0, sizeof(buffer));
          sprintf(buffer, "DF[0x%04lX]: 0x", i + address);
          CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        }
        memset(buffer, 0, sizeof(buffer));
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
      uint32_t address;
      if(strcmp("chip", parameter[2]) == 0)
        Dataflash_Erase(DATAFLASH_LEVEL_CHIP, 0);
      else if(strcmp("sector", parameter[2]) == 0){
        if(strcmp("0a", parameter[3]) == 0)
          address =                             0 << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH);
        else if(strcmp("0b", parameter[3]) == 0)
          address =                             1 << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH);
        else
          address =  (uint32_t)atoi(parameter[3]) << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_SECTOR_ADDR_WIDTH);
        Dataflash_Erase(DATAFLASH_LEVEL_SECTOR, address);
      }
      else if(strcmp("block", parameter[2]) == 0){
        address = (uint32_t)atoi(parameter[3]) << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH);
        Dataflash_Erase(DATAFLASH_LEVEL_BLOCK, address);
      }
      else if(strcmp("page", parameter[2]) == 0){
        address = (uint32_t)atoi(parameter[3]) << (uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH;
        Dataflash_Erase(DATAFLASH_LEVEL_PAGE, address);
      }
    }
    //else if(strcmp("protect", parameter[1]) == 0){
    //  if(strcmp("on", parameter[2]) == 0)
    //    Dataflash_Enable_Sector_Protection();
    //  else if(strcmp("off", parameter[2]) == 0)
    //    Dataflash_Disable_Sector_Protection();
    //  else if(strcmp("status", parameter[2]) == 0){
    //    // Print whether protection is enabled
    //    Dataflash_SendByte(DF_CMD_GETSTATUS);
    //    memset(buffer, 0, sizeof(buffer));
    //    if(Dataflash_ReceiveByte() & DF_STATUSREG_BYTE1_SECTORPROTECTION_ON)
    //      sprintf(buffer, "Sector Protection On\r\n");
    //    else
    //      sprintf(buffer, "Sector Protection Off\r\n");
    //    CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //    Dataflash_ToggleSelectedChipCS();

    //    // Print protection register for each sector
    //    for(uint8_t i=0;i<sizeof(DF_CMD_READSECTORPROTECTIONREG)/sizeof(DF_CMD_READSECTORPROTECTIONREG[0]);i++)
    //      Dataflash_SendByte(DF_CMD_READSECTORPROTECTIONREG[i]);
    //    for(uint16_t i=0;i<DATAFLASH_SECTORS;i++){
    //      memset(buffer, 0, sizeof(buffer));
    //      sprintf(buffer, "Sector[%u]: %02X\r\n", i, (uint8_t)Dataflash_ReceiveByte());
    //      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    //    }
    //  }
    //  else{
    //    uint8_t  value;
    //    if(strcmp("all", parameter[2]) == 0){
    //      for(uint8_t i = 0;i<DATAFLASH_SECTORS;i++){
    //        eeprom_write_byte(&DF_Sector_Protection[i], DF_SECTORPROTECTIONREG_PROTECTED);
    //        eeprom_busy_wait();
    //      }
    //    }
    //    else if(strcmp("none", parameter[2]) == 0){
    //      for(uint8_t i = 0;i<DATAFLASH_SECTORS;i++){
    //        eeprom_write_byte(&DF_Sector_Protection[i], DF_SECTORPROTECTIONREG_UNPROTECTED);
    //        eeprom_busy_wait();
    //      }
    //    }
    //    else if(strcmp("0a", parameter[2]+1) == 0){
    //      value = eeprom_read_byte(&DF_Sector_Protection[0]);
    //      if(parameter[2][0] == '+')
    //        value |= DF_SECTORPROTECTIONREG_0A_PROTECTED;
    //      if(parameter[2][0] == '-')
    //        value &= ~DF_SECTORPROTECTIONREG_0A_PROTECTED;
    //      eeprom_write_byte(&DF_Sector_Protection[0], value);
    //      eeprom_busy_wait();
    //    }
    //    else if(strcmp("0b", parameter[2]+1) == 0){
    //      value = eeprom_read_byte(&DF_Sector_Protection[0]);
    //      if(parameter[2][0] == '+')
    //        value |= DF_SECTORPROTECTIONREG_0B_PROTECTED;
    //      else if(parameter[2][0] == '-')
    //        value &= ~DF_SECTORPROTECTIONREG_0B_PROTECTED;
    //      eeprom_write_byte(&DF_Sector_Protection[0], value);
    //      eeprom_busy_wait();
    //    }
    //    else{
    //      if(parameter[2][0] == '+')
    //        value = DF_SECTORPROTECTIONREG_PROTECTED;
    //      else if(parameter[2][0] == '-')
    //        value = DF_SECTORPROTECTIONREG_UNPROTECTED;
    //      else
    //        value = DF_SECTORPROTECTIONREG_PROTECTED;
    //      eeprom_write_byte(&DF_Sector_Protection[atoi(parameter[2]+1)], value);
    //      eeprom_busy_wait();
    //    }

    //    // Erase first
    //    Dataflash_Erase_Sector_Protection_Registor();

    //    // Update Sector Protection Register
    //    Dataflash_Update_Sector_Protection_Registor();
    //  }
    //}
    else if(strcmp("blankcheck", parameter[1]) == 0){
      uint32_t firstNonBlank = Dataflash_BlankCheck();
      if(firstNonBlank == (uint32_t)DATAFLASH_SIZE){
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "Dataflash blank\r\n");
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
      else{
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "0x%02lX not blank\r\n", firstNonBlank);
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
    }
    Dataflash_DeselectChip();
  }

  /* EEPROM */
  //else if(strcmp("EEPROM", parameter[0]) == 0){
  //  if(strcmp("read", parameter[1]) == 0){
  //    uint16_t address = (uint8_t)atoi(parameter[2]);
  //    memset(buffer, 0, sizeof(buffer));
  //    sprintf(buffer, "EEPROM[%u]: 0x%02X\r\n", address, eeprom_read_byte((uint8_t*)address));
  //    CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
  //  }
  //  else if(strcmp("write", parameter[1]) == 0){
  //    uint16_t address = (uint8_t)atoi(parameter[2]);
  //    uint8_t value;
  //    if(parameter[3][0] == '0' && parameter[3][1] == 'x')
  //      value = strtol(parameter[3]+2, NULL, 16);
  //    else
  //      value = (uint32_t)atoi(parameter[3]);
  //    eeprom_write_byte((uint8_t*)address, value);
  //    eeprom_busy_wait();
  //  }
  //}

  /* LED */
  //else if(strcmp("LED", parameter[0]) == 0){
  //  if(strcmp("TX", parameter[1]) == 0){
  //    if(strcmp("on", parameter[2]) == 0)
  //      LEDs_TurnOnLEDs(LEDMASK_TX);
  //    else if(strcmp("off", parameter[2]) == 0)
  //      LEDs_TurnOffLEDs(LEDMASK_TX);
  //    else
  //      LEDs_ToggleLEDs(LEDMASK_TX);
  //  }
  //  else if(strcmp("RX", parameter[1]) == 0){
  //    if(strcmp("on", parameter[2]) == 0)
  //      LEDs_TurnOnLEDs(LEDMASK_RX);
  //    else if(strcmp("off", parameter[2]) == 0)
  //      LEDs_TurnOffLEDs(LEDMASK_RX);
  //    else
  //      LEDs_ToggleLEDs(LEDMASK_RX);
  //  }
  //}

  /* RRAM Testchip (TC) */
  else if(strcmp("TC", parameter[0]) == 0){
    if(strcmp("connect", parameter[1]) == 0){
      // Enable SW Mode
      SW_LineReset();
      SW_JTAGToSW();
      SW_LineReset();

      // Connect to the device
      uint32_t id = SW_Connect();
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "Device ID: 0x%08lX\r\n", id);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      
      // Power up the DAP
      SW_DAPPowerUp();

      // Halt the core
      SW_HaltCore();
    }
    else if(strcmp("read", parameter[1]) == 0){
      uint32_t address = atoi(parameter[2]);
      uint32_t value = SW_ReadMem(address, SW_REG_AP_CSW_SIZE_WORD_MASK);
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "[%lu] = 0x%08lX\r\n", address, value);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(strcmp("write", parameter[1]) == 0){
      uint32_t address = atoi(parameter[2]);
      uint32_t value = atoi(parameter[3]);
      SW_WriteMem(address, SW_REG_AP_CSW_SIZE_WORD_MASK, value);
    }
    else{ // Unknow command here, forward to RRAM testchip
      for(uint8_t i=1;i<=3;i++)
        if(parameter[i]){
          Serial_TxString(parameter[i]);
          Serial_TxString(" ");
        }
      Serial_TxString("\n");
    }
  }

  /* Demos */
  else if(strcmp("DEMO", parameter[0]) == 0){
    if(strcmp("list", parameter[1]) == 0){
      for(uint8_t i=0;i<sizeof(demos_map)/sizeof(demos_structure_t);i++){
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%u - %s\r\n",  i, demos_map[i].name);
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
    }
    else if(strcmp("load", parameter[1]) == 0){
      // Print out the demo being loaded
      uint8_t index = atoi(parameter[2]);
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "\"%s\" from sector %u\r\n", demos_map[index].name, demos_map[index].sector_number);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      CDC_Device_USBTask(&VirtualSerial_CDC_Interface);

      // Prepare RRAM testchip for programming
      SW_LineReset();
      SW_JTAGToSW();
      SW_LineReset();
      SW_Connect();
      SW_DAPPowerUp();
      SW_HaltCore();
      CDC_Device_USBTask(&VirtualSerial_CDC_Interface);

      // Print the progress bar
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, '[');
      for(uint8_t i=0; i<16; i++)
        CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ' ');
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ']');
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, CR);
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, '[');
      CDC_Device_USBTask(&VirtualSerial_CDC_Interface);

      // Start reading from the Dataflash sequentially and Write to the RRAM testchip
      Dataflash_SelectChip(DATAFLASH_CHIP1);
      Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, demos_map[index].sector_number*(uint32_t)DATAFLASH_SECTOR_SIZE);
      uint32_t step = TC_ROM_SIZE/16;
      for(uint32_t i=0; i < TC_ROM_SIZE; i+=4){
        uint32_t word = 0;
        word |= (uint32_t) Dataflash_ReceiveByte();
        word |= (uint32_t) Dataflash_ReceiveByte() << 8;
        word |= (uint32_t) Dataflash_ReceiveByte() << 16;
        word |= (uint32_t) Dataflash_ReceiveByte() << 24;
        SW_WriteMem((uint32_t)SW_ROM_ADDR + i, SW_REG_AP_CSW_SIZE_WORD_MASK, word);
        if(i%step == 0){
          CDC_Device_SendByte(&VirtualSerial_CDC_Interface, '>');
          CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
        }
      }
      Dataflash_DeselectChip();

      UARTConsole_PrintNewLine();
    }
    else if(strcmp("run", parameter[1]) == 0){
      //SPI_ShutDown();
      SW_ResetCore();
    }
    else if(strcmp("stop", parameter[1]) == 0){
      SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING | SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
    }
  }

  /* Unknown command, loop it back to the CDC */
  else if(count !=0){ 
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Unknown Command: ", 17);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, command, count);
    UARTConsole_PrintNewLine();
  }
  
  /* Clear the counter and the position */
  memset(command, 0, sizeof(command));
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
      else if(_char2 == 0x43){ // Right
        UARTConsole_MoveForward(1);
      }
      else if(_char2 == 0x44){ // Left
        UARTConsole_MoveBackward(1);
      }
    }
  }
  else
    UARTConsole_CommandInsert(_char);
}

#endif
