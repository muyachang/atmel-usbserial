/*
   Board DAC driver for the RRAM Testchip
*/

#ifndef __DAC_RRAM_H__
#define __DAC_RRAM_H__

  /* Includes: */
    #include "DAC7612.h"

    /* Pin assignment: */
    #define DAC_CHIPCS_POUT    PORTB
    #define DAC_CHIPCS_DDR     DDRB
    #define DAC_CHIPCS_MASK    _BV(5)

    #define DAC_LOADDACS_POUT  PORTB
    #define DAC_LOADDACS_DDR   DDRB
    #define DAC_LOADDACS_MASK  _BV(6)

    /* Mask and DAC information */
    #define DAC_NO_CHIP     DAC_CHIPCS_MASK
    #define DAC_CHIP1       (DAC_CHIPCS_MASK ^ _BV(5))
    #define DAC_PRECISION   12 // bits
    #define DAC_LEVELS      _BV(DAC_PRECISION)
    #define DAC_VCC         3300 // mV

    /* Adjust mode */
    #define DAC_ADJUST_MODE_LOAD      0
    #define DAC_ADJUST_MODE_INCREMENT 1
    #define DAC_ADJUST_MODE_DECREMENT 2
    #define DAC_ADJUST_MODE_PLUS      3
    #define DAC_ADJUST_MODE_MINUS     4
    #define DAC_ADJUST_MODE_ABSOLUTE  5

    /* Mapping */
    /* 
     * VTGT_BL: DAC_A
     * ADC_CAL: DAC_B 
     */
    #define DAC_VTGT_BL     0x41
    #define DAC_ADC_CAL     0x42

    /* Data structure */
    typedef struct {
      const uint8_t   name;
      const uint8_t   value_reg;
            uint16_t  level; // Binary value for the corresponding voltage
            uint16_t* level_addr; // EEPROM address of the binary value for the corresponding voltage (inside EEPROM)
    } dac_structure_t;

    /* DAC Map */
    __attribute__((section(".eeprom"))) uint16_t DAC_VTGT_BL_Level = 0;
    __attribute__((section(".eeprom"))) uint16_t DAC_ADC_CAL_Level = 0;

    dac_structure_t dacs_map[] = {
      // Name      | Value Register | Level | Level Address
      { DAC_VTGT_BL, LOAD_DAC_REG_A ,     0 , &DAC_VTGT_BL_Level}, 
      { DAC_ADC_CAL, LOAD_DAC_REG_B ,     0 , &DAC_ADC_CAL_Level}, 
      { (int) NULL }
    };

    /* Inline Functions: */

      /**
       * Function for finding the pointer of the target
       */
      static inline dac_structure_t* DAC_Find_Target(const uint8_t _target) { 
        dac_structure_t *candidate = dacs_map;
        while(candidate->name) {
          if(_target == candidate->name)
            break;
          else
            candidate++;
        }
        return candidate;
      }

      /**
       * Calculate the binary value based on the target voltage (mV)
       */
      static inline uint16_t DAC_Encode_Voltage(uint16_t _target_voltage) 
      {
        uint16_t level =_target_voltage > DAC_VCC? DAC_LEVELS-1: (long)_target_voltage*(long)DAC_LEVELS/(long)DAC_VCC;
        return level;
      }

      /**
       * Calculate the voltage (mV) based on the binary level
       */
      static inline uint16_t DAC_Decode_Level(uint16_t _level) 
      {
        uint16_t current_voltage = (long)_level*(long)DAC_VCC/(long)DAC_LEVELS;
        return current_voltage;
      }

      /** 
       *  For the selected DAC chip, set the _target DAC to the _mVolt  
       */
      static inline void DAC_Configure_DAC(const uint8_t _target, uint16_t _mVolt, const uint8_t _mode)
      {
        dac_structure_t *channel = DAC_Find_Target(_target);

        /* No channel found, simply ignore the function call */
        if(!channel->name)
          return;

        /* Get the current voltage value */
        uint16_t current_voltage = DAC_Decode_Level(channel->level);

        /* Get the new level */
             if(_mode == DAC_ADJUST_MODE_ABSOLUTE)
          channel->level = DAC_Encode_Voltage(_mVolt);
        else if(_mode == DAC_ADJUST_MODE_PLUS)
          channel->level = DAC_Encode_Voltage(current_voltage + _mVolt);
        else if(_mode == DAC_ADJUST_MODE_MINUS)
          channel->level = DAC_Encode_Voltage(current_voltage - _mVolt);
        else if(_mode == DAC_ADJUST_MODE_INCREMENT)
          channel->level = (channel->level) + 1;
        else if(_mode == DAC_ADJUST_MODE_DECREMENT)
          channel->level = (channel->level) - 1;
        else if(_mode == DAC_ADJUST_MODE_LOAD)
          channel->level = (channel->level);
        else
          channel->level = (channel->level);

        /* Compose the 14-bit command */
        uint16_t _command = ((channel->value_reg << DAC_PRECISION) + (channel->level)) & 0x3FFF; // 14 bits in total

        /* Send the command */
        DAC_CHIPCS_DDR |=  DAC_CHIPCS_MASK  ; // Set it as an output
        DAC_CHIPCS_POUT = (DAC_CHIPCS_POUT & ~DAC_CHIPCS_MASK) | DAC_CHIP1;
        SPI_SendByte((_command >> 8) & 0xFF);
        SPI_SendByte((_command     ) & 0xFF);
        DAC_CHIPCS_POUT = (DAC_CHIPCS_POUT & ~DAC_CHIPCS_MASK) | DAC_NO_CHIP;
        DAC_CHIPCS_DDR &= ~DAC_CHIPCS_MASK  ; // Set it as an input 

        /* Toggle LOADDAC to update the DAC output */
        DAC_LOADDACS_DDR  |=  DAC_LOADDACS_MASK; // Set it as an output
        DAC_LOADDACS_POUT ^=  DAC_LOADDACS_MASK;
        DAC_LOADDACS_POUT ^=  DAC_LOADDACS_MASK;
        DAC_LOADDACS_DDR  &= ~DAC_LOADDACS_MASK; // Set it as an input 
      }

      /** 
       *  For the selected DAC chip, read the _target channel voltage 
       */
      static inline uint16_t DAC_Read_Voltage(const uint8_t _target)
      {
        dac_structure_t *channel = DAC_Find_Target(_target);

        /* No channel found, simply ignore the function call */
        if(!channel->name)
          return 0;

        /* Return the current level */
        return DAC_Decode_Level(channel->level);
      }

      /**
       * Function for storing the levels into EEPROM
       */
      static inline void DAC_Save(void)
      {
        dac_structure_t *channel = dacs_map;
        while(channel->name) {
          eeprom_write_word(channel->level_addr, channel->level);
          eeprom_busy_wait();
          channel++;
        }
      }

      /**
       * Function for loading the levels from EEPROM
       */
      static inline void DAC_Load(void)
      {
        dac_structure_t *channel = dacs_map;
        while(channel->name) {
          channel->level = eeprom_read_word(channel->level_addr);
          DAC_Configure_DAC(channel->name, 0, DAC_ADJUST_MODE_LOAD);
          channel++;
        }
      }

      /**
       *  Initialize the DAC with some low voltages
       */
      static inline void DAC_Init(void)
      {
        DAC_CHIPCS_POUT   |=  DAC_CHIPCS_MASK  ; // Enable the pull high resistor
        DAC_CHIPCS_DDR    &= ~DAC_CHIPCS_MASK  ; // Set it as an input 
        DAC_LOADDACS_POUT |=  DAC_LOADDACS_MASK; // Enable the pull high resistor
        DAC_LOADDACS_DDR  &= ~DAC_LOADDACS_MASK; // Set it as an input 
        
        DAC_Load();
      }

      /**
       *  Shutdown the DAC
       */
      static inline void DAC_ShutDown(void)
      {
        DAC_CHIPCS_POUT   &= ~DAC_CHIPCS_MASK  ; // Disable the pull high resistor
        DAC_LOADDACS_POUT &= ~DAC_LOADDACS_MASK; // Disable the pull high resistor
      }

#endif
