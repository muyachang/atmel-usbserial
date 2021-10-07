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
#include "CommandMap.h"

/* char array for storing the command */
char command[64];
uint8_t count = 0;

/* Temp char array for any purpose */
char buffer[64];

/* Extern variables */
extern bool TC_Commanding;
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
static inline void UARTConsole_CommandInsert(uint8_t _char){
  // Insert the new _char
  command[count++] = _char;
}

/*
 * 
 */
static inline void UARTConsole_ProcessCommand(void)
{
  /* Whether we want to wait for EOT or not */
  bool waitForEOT = false;

  /* Insert the null termination */
  command[count] = '\0';

  /* Process the command */
  char *token;
  char *parameter[16];

  token = strtok(command, " ");
  for(uint8_t i=0;i<16;i++){
    parameter[i] = token;
    token = strtok(NULL, " ");
  }

  /* Power Management (PM) */
  if(*parameter[0] == CM_PM){
    if(*parameter[1] == CM_PM_CLEAR)
      PM_ClearIRQ();
    else if(*parameter[1] == CM_PM_STATUS){
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "0x%02X\n",  PM_ReadIRQ());
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(*parameter[1] == CM_PM_SAVE)
      PM_Save();
    else if(*parameter[1] == CM_PM_LOAD)
      PM_Load();
    else if(*parameter[1] == CM_PM_RESET)
      PM_Reset();
    else if(*parameter[1] == CM_PM_ENABLE)
      PM_Enable(*parameter[2]);
    else if(*parameter[1] == CM_PM_DISABLE)
      PM_Disable(*parameter[2]);
    else if(*parameter[1] == CM_PM_INCR)
      PM_Adjust(*parameter[2], 0, PM_ADJUST_MODE_INCREMENT);
    else if(*parameter[1] == CM_PM_DECR)
      PM_Adjust(*parameter[2], 0, PM_ADJUST_MODE_DECREMENT);
    else if(*parameter[1] == CM_PM_PLUS)
      PM_Adjust(*parameter[3],atof(parameter[2]), PM_ADJUST_MODE_PLUS);
    else if(*parameter[1] == CM_PM_MINUS)
      PM_Adjust(*parameter[3],atof(parameter[2]), PM_ADJUST_MODE_MINUS);
    else if(*parameter[1] == CM_PM_SET)
      PM_Adjust(*parameter[3],atof(parameter[2]), PM_ADJUST_MODE_ABSOLUTE);
    else if(*parameter[1] == CM_PM_GET){
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "%d %d\n", PM_Is_Enabled(*parameter[2]), PM_Read_Voltage(*parameter[2]));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else
      goto UNKNOW_COMMAN;
  }

  /* Digital Analog Converter (DAC) */
  else if(*parameter[0] == CM_DAC){
    if(*parameter[1] == CM_DAC_INCR)
      DAC_Configure_DAC(*parameter[2], 0, DAC_ADJUST_MODE_INCREMENT); 
    else if(*parameter[1] == CM_DAC_DECR)
      DAC_Configure_DAC(*parameter[2], 0, DAC_ADJUST_MODE_DECREMENT); 
    else if(*parameter[1] == CM_DAC_PLUS)
      DAC_Configure_DAC(*parameter[3], atoi(parameter[2]), DAC_ADJUST_MODE_PLUS); 
    else if(*parameter[1] == CM_DAC_MINUS)
      DAC_Configure_DAC(*parameter[3], atoi(parameter[2]), DAC_ADJUST_MODE_MINUS); 
    else if(*parameter[1] == CM_DAC_SET)
      DAC_Configure_DAC(*parameter[3], atoi(parameter[2]), DAC_ADJUST_MODE_ABSOLUTE); 
    else if(*parameter[1] == CM_DAC_GET){
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "%d\n", DAC_Read_Voltage(*parameter[2]));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else
      goto UNKNOW_COMMAN;
  }

  /* Data Flash (DF) */
  else if(*parameter[0] == CM_DF){
    Dataflash_SelectChip(DATAFLASH_CHIP1);
    if(*parameter[1] == CM_DF_STATUS){
      Dataflash_SendByte(DF_CMD_GETSTATUS);
      uint8_t status[2];
      status[0] = (uint8_t)Dataflash_ReceiveByte();
      status[1] = (uint8_t)Dataflash_ReceiveByte();
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "0x%02X 0x%02X\n", status[0], status[1]);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(*parameter[1] == CM_DF_ID){
      Dataflash_SendByte(DF_CMD_READMANUFACTURERDEVICEINFO);
      uint8_t id[3];
      id[0] = (uint8_t)Dataflash_ReceiveByte();
      id[1] = (uint8_t)Dataflash_ReceiveByte();
      id[2] = (uint8_t)Dataflash_ReceiveByte();
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "0x%02X 0x%02X 0x%02X\n", id[0], id[1], id[2]);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(*parameter[1] == CM_DF_RESET)
      Dataflash_Reset();
    else if(*parameter[1] == CM_DF_READ){
      uint32_t address = (uint32_t)atoi(parameter[2]);
      uint32_t count = 1;
      if(*parameter[2] == DATAFLASH_LEVEL_SECTOR){
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
      else if(*parameter[2] == DATAFLASH_LEVEL_BLOCK){
        address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_BLOCK_SIZE;
        count   =                              (uint32_t)DATAFLASH_BLOCK_SIZE;
      }
      else if(*parameter[2] == DATAFLASH_LEVEL_PAGE){
        address = (uint32_t)atoi(parameter[3])*(uint32_t)DATAFLASH_PAGE_SIZE;
        count   =                              (uint32_t)DATAFLASH_PAGE_SIZE;
      }
      else if(*parameter[2] == DATAFLASH_LEVEL_BYTE){
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
        }
      }
    }
    else if(*parameter[1] == CM_DF_WRITE){
      // Parse the address/value
      uint32_t address = (uint32_t)atoi(parameter[2]);
      uint8_t  value   = (uint8_t)atoi(parameter[3]);

      Dataflash_Configure_Write_Address(DF_CMD_RMWTHROUGHBUFF1, address);
      Dataflash_SendByte(value);
    }
    else if(*parameter[1] == CM_DF_ERASE){
      uint32_t address;
      if(*parameter[2] == DATAFLASH_LEVEL_CHIP)
        Dataflash_Erase(DATAFLASH_LEVEL_CHIP, 0);
      else if(*parameter[2] == DATAFLASH_LEVEL_SECTOR){
        if(strcmp("0a", parameter[3]) == 0)
          address =                             0 << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH);
        else if(strcmp("0b", parameter[3]) == 0)
          address =                             1 << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH);
        else
          address =  (uint32_t)atoi(parameter[3]) << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_SECTOR_ADDR_WIDTH);
        Dataflash_Erase(DATAFLASH_LEVEL_SECTOR, address);
      }
      else if(*parameter[2] == DATAFLASH_LEVEL_BLOCK){
        address = (uint32_t)atoi(parameter[3]) << ((uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH + (uint32_t)DATAFLASH_PAGE_ADDR_WIDTH - (uint32_t)DATAFLASH_BLOCK_ADDR_WIDTH);
        Dataflash_Erase(DATAFLASH_LEVEL_BLOCK, address);
      }
      else if(*parameter[2] == DATAFLASH_LEVEL_PAGE){
        address = (uint32_t)atoi(parameter[3]) << (uint32_t)DATAFLASH_OFFSET_ADDR_WIDTH;
        Dataflash_Erase(DATAFLASH_LEVEL_PAGE, address);
      }
      else
        goto UNKNOW_COMMAN;
    }
    else if(*parameter[1] == CM_DF_PROTECT){
      if(*parameter[2] == CM_DF_PROTECT_ENABLE)
        Dataflash_Enable_Sector_Protection();
      else if(*parameter[2] == CM_DF_PROTECT_DISABLE)
        Dataflash_Disable_Sector_Protection();
      else if(*parameter[2] == CM_DF_PROTECT_STATUS){
        // Print whether protection is enabled
        Dataflash_SendByte(DF_CMD_GETSTATUS);
        memset(buffer, 0, sizeof(buffer));
        if(Dataflash_ReceiveByte() & DF_STATUSREG_BYTE1_SECTORPROTECTION_ON)
          sprintf(buffer, "Sector Protection Enabled\n");
        else
          sprintf(buffer, "Sector Protection Disabled\n");
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        Dataflash_ToggleSelectedChipCS();

        // Print protection register for each sector
        for(uint8_t i=0;i<sizeof(DF_CMD_READSECTORPROTECTIONREG)/sizeof(DF_CMD_READSECTORPROTECTIONREG[0]);i++)
          Dataflash_SendByte(DF_CMD_READSECTORPROTECTIONREG[i]);
        for(uint16_t i=0;i<DATAFLASH_SECTORS;i+=8){
          memset(buffer, 0, sizeof(buffer));
          sprintf(buffer, "Sector[%2u~%2u]: ", i, i+8-1);
          CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
          for(uint16_t j=0;j<8;j++){
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "%02X ", (uint8_t)Dataflash_ReceiveByte());
            CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
          }
          CDC_Device_SendByte(&VirtualSerial_CDC_Interface, LF);
        }
      }
      else{
        if(strcmp("0a", parameter[3]) == 0){
          uint8_t value = eeprom_read_byte(&DF_Sector_Protection[0]);
          if(*parameter[2] == CM_DF_PROTECT_ADD)
            value |= DF_SECTORPROTECTIONREG_0A_PROTECTED;
          else if(*parameter[2] == CM_DF_PROTECT_REMOVE)
            value &= ~DF_SECTORPROTECTIONREG_0A_PROTECTED;
          eeprom_write_byte(&DF_Sector_Protection[0], value);
          eeprom_busy_wait();
        }
        else if(strcmp("0b", parameter[3]) == 0){
          uint8_t value = eeprom_read_byte(&DF_Sector_Protection[0]);
          if(*parameter[2] == CM_DF_PROTECT_ADD)
            value |= DF_SECTORPROTECTIONREG_0B_PROTECTED;
          else if(*parameter[2] == CM_DF_PROTECT_REMOVE)
            value &= ~DF_SECTORPROTECTIONREG_0B_PROTECTED;
          eeprom_write_byte(&DF_Sector_Protection[0], value);
          eeprom_busy_wait();
        }
        else{
          uint8_t value = eeprom_read_byte(&DF_Sector_Protection[atoi(parameter[3])]);
          if(*parameter[2] == CM_DF_PROTECT_ADD)
            value = DF_SECTORPROTECTIONREG_PROTECTED;
          else if(*parameter[2] == CM_DF_PROTECT_REMOVE)
            value = DF_SECTORPROTECTIONREG_UNPROTECTED;
          eeprom_write_byte(&DF_Sector_Protection[atoi(parameter[3])], value);
          eeprom_busy_wait();
        }

        // Erase first
        Dataflash_Erase_Sector_Protection_Registor();

        // Update Sector Protection Register
        Dataflash_Update_Sector_Protection_Registor();
      }
    }
    else if(*parameter[1] == CM_DF_BLANKCHECK){
      int32_t firstNonBlank = Dataflash_BlankCheck();
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "%ld\n", firstNonBlank);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else
      goto UNKNOW_COMMAN;
    Dataflash_DeselectChip();
  }

  /* EEPROM */
  else if(*parameter[0] == CM_EEPROM){
    if(*parameter[1] == CM_EEPROM_READ){
      uint16_t address = (uint8_t)atoi(parameter[2]);
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "%d\n", eeprom_read_byte((uint8_t*)address));
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(*parameter[1] == CM_EEPROM_WRITE){
      uint16_t address = (uint8_t)atoi(parameter[2]);
      uint8_t value = (uint32_t)atoi(parameter[3]);
      eeprom_write_byte((uint8_t*)address, value);
      eeprom_busy_wait();
    }
    else
      goto UNKNOW_COMMAN;
  }

  /* LED */
  else if(*parameter[0] == CM_LED){
    if(*parameter[1] == CM_LED_ENABLE){
      if(strcmp("TX", parameter[2]) == 0)
        LEDs_TurnOnLEDs(LEDMASK_TX);
      else
        LEDs_TurnOnLEDs(LEDMASK_RX);
    }
    else if(*parameter[1] == CM_LED_DISABLE){
      if(strcmp("TX", parameter[2]) == 0)
        LEDs_TurnOffLEDs(LEDMASK_TX);
      else
        LEDs_TurnOffLEDs(LEDMASK_RX);
    }
    else if(*parameter[1] == CM_LED_TOGGLE){
      if(strcmp("TX", parameter[2]) == 0)
        LEDs_ToggleLEDs(LEDMASK_TX);
      else
        LEDs_ToggleLEDs(LEDMASK_RX);
    }
    else
      goto UNKNOW_COMMAN;
  }

  /* RRAM Testchip (TC) */
  else if(*parameter[0] == CM_TC){
    if(*parameter[1] == CM_TC_CONNECT){
      // Enable SW Mode
      SW_LineReset();
      SW_JTAGToSW();
      SW_LineReset();

      // Connect to the device
      uint32_t id = SW_Connect();
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "0x%08lX\n", id);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      
      // Power up the DAP
      SW_DAPPowerUp();

      // Halt the core
      SW_HaltCore();
    }
    else if(*parameter[1] == CM_TC_READ){
      uint32_t address = atoi(parameter[2]);
      uint32_t value = SW_ReadMem(address, SW_REG_AP_CSW_SIZE_WORD_MASK);
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "0x%08lX\n", value);
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
    }
    else if(*parameter[1] == CM_TC_WRITE){
      uint32_t address = atoi(parameter[2]);
      uint32_t value = atoi(parameter[3]);
      SW_WriteMem(address, SW_REG_AP_CSW_SIZE_WORD_MASK, value);
    }
    else
      goto UNKNOW_COMMAN;
  }

  /* Demos */
  else if(*parameter[0] == CM_DEMO){
    if(*parameter[1] == CM_DEMO_LIST){
      for(uint8_t i=0;i<sizeof(demos_map)/sizeof(demos_structure_t);i++){
        char demo_name[24];
        memset(demo_name, 0, sizeof(demo_name));
        eeprom_read_block(demo_name, demos_map[i].name, sizeof(demo_name));

        uint8_t sector_number = eeprom_read_byte(&demos_map[i].sector_number);
        uint8_t size = eeprom_read_byte(&demos_map[i].size);

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%2u - %-24s @ sector %2u (%3u KB)\n",  i, demo_name, sector_number, size);
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
    }
    else if(*parameter[1] == CM_DEMO_LOAD){
      // Check if 3.3V, VDD, AVDD_SRAM are on
      if(!(PM_Is_Enabled(PM_3V3) && PM_Is_Enabled(PM_VDD) && PM_Is_Enabled(PM_AVDD_SRAM))){
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "3.3V, VDD, and AVDD_SRAM are not all enabled, skipping ...\n");
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
        CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
        return;
      }

      // Retrieve the demo information
      uint8_t index = atoi(parameter[2]);

      char demo_name[24];
      memset(demo_name, 0, sizeof(demo_name));
      eeprom_read_block(demo_name, demos_map[index].name, sizeof(demo_name));

      uint8_t sector_number = eeprom_read_byte(&demos_map[index].sector_number);
      uint8_t size = eeprom_read_byte(&demos_map[index].size);

      // Print out the demo being loaded
      memset(buffer, 0, sizeof(buffer));
      sprintf(buffer, "Loading \"%s\" from sector %2u (%3u KB)\n", demo_name, sector_number, size);
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
      Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, (uint32_t)sector_number*(uint32_t)DATAFLASH_SECTOR_SIZE);
      uint32_t step = (uint32_t)size*1024/16;
      for(uint32_t i=0; i < (uint32_t)size*1024; i+=4){
        uint32_t word = 0;
        word |= (uint32_t) Dataflash_ReceiveByte();
        word |= (uint32_t) Dataflash_ReceiveByte() << 8;
        word |= (uint32_t) Dataflash_ReceiveByte() << 16;
        word |= (uint32_t) Dataflash_ReceiveByte() << 24;
        SW_WriteMem((uint32_t)SW_ROM_ADDR + i, SW_REG_AP_CSW_SIZE_WORD_MASK, word);

        // Print the status of progress bar
        if(i%step == 0){
          CDC_Device_SendByte(&VirtualSerial_CDC_Interface, '>');
          CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
        }

        if(i%(DATAFLASH_PAGE_SIZE/2) == 0)
          LEDs_ToggleLEDs(LEDMASK_RX);
      }
      Dataflash_DeselectChip();

      // Print the end of progress bar
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ']');
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, LF);
      CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
    }
    else if(*parameter[1] == CM_DEMO_RUN){
      waitForEOT = true;
      TC_Reset();
    }
    else if(*parameter[1] == CM_DEMO_ANALYZE){
      for(uint8_t i=0;i<sizeof(demos_map)/sizeof(demos_structure_t);i++){

        // Retrieve the demo information
        char demo_name[24];
        memset(demo_name, 0, sizeof(demo_name));
        eeprom_read_block(demo_name, demos_map[i].name, sizeof(demo_name));

        uint8_t sector_number = eeprom_read_byte(&demos_map[i].sector_number);
        uint8_t size = eeprom_read_byte(&demos_map[i].size); // KB

        // Start reading from the Dataflash sequentially and check if it's blank 
        uint32_t start_addr = (uint32_t)sector_number*(uint32_t)DATAFLASH_SECTOR_SIZE;
        Dataflash_SelectChip(DATAFLASH_CHIP1);
        Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, start_addr);
        uint16_t page;
        for(page=0; page<256; page+=2){ // Step 1KB
          uint16_t j;
          for(j=0; j<(uint16_t)DATAFLASH_PAGE_SIZE*2; j++)
            if(Dataflash_ReceiveByte()!=255){ // Not empty, we go to next 1KB page
              Dataflash_ToggleSelectedChipCS();
              Dataflash_Configure_Read_Address(DF_CMD_CONTARRAYREAD_LP, start_addr + page*DATAFLASH_PAGE_SIZE);
              break;
            }

          if(j==(uint16_t)DATAFLASH_PAGE_SIZE*2) // The whole 1KB is blank, i.e. reached the end of the demo size
            break;
        }
        Dataflash_DeselectChip();

        // Save and print the updated size
        eeprom_write_byte(&demos_map[i].size, page/2); // Page # -> size (KB)
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "Updating \"%-24s\" from %3u KB -> %3u KB\n", demo_name, size, page/2);
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, buffer, strlen(buffer));
      }
    }
    else
      goto UNKNOW_COMMAN;
  }

  /* Forwarding other commands to the testchip */
  else if(*parameter[0] == CM_RRAM || *parameter[0] == CM_VECTOR){
    waitForEOT = true;
    for(uint8_t i=0;i<16;i++){
      if(parameter[i]){
        Serial_TxString(parameter[i]);
        Serial_TxString(" ");
      }
    }
    Serial_TxString("\n");
  }

  /* Unknown command */
  else
    goto UNKNOW_COMMAN;

/* Clear the counter and the position */
CLEAN_UP:
  if(!waitForEOT && !TC_Commanding)
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, EOT);
  memset(command, 0, sizeof(command));
  count = 0;
  return;

/* Unknown command, loop it back to the CDC */
UNKNOW_COMMAN:
  CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Unknown Command: ", 17);
  for(uint8_t i=0;i<5;i++){
    if(parameter[i]){
      CDC_Device_SendString(&VirtualSerial_CDC_Interface, parameter[i], strlen(parameter[i]));
      CDC_Device_SendByte(&VirtualSerial_CDC_Interface, SPACE);
    }
  }
  CDC_Device_SendString(&VirtualSerial_CDC_Interface, "(From Atmel)", 12);
  CDC_Device_SendByte(&VirtualSerial_CDC_Interface, LF);
  goto CLEAN_UP;
}

/*
 * 
 */
static inline void UARTConsole_InsertChar(uint8_t _char)
{
  if(_char == LF) // New line (LF)
    UARTConsole_ProcessCommand();
  else
    UARTConsole_CommandInsert(_char);
}

#endif
