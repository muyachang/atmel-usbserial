/*
   Board DAC driver for the RRAM Testchip
*/

#ifndef __DAC_RRAM_H__
#define __DAC_RRAM_H__

  /* Includes: */
    #include "DAC7612.h"

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define DAC_CHIPCS_POUT    PORTB
      #define DAC_CHIPCS_DDR     DDRB
      #define DAC_CHIPCS_MASK    _BV(5)
      #define DAC_LOADDACS_POUT  PORTB
      #define DAC_LOADDACS_DDR   DDRB
      #define DAC_LOADDACS_MASK  _BV(6)
  #endif

  /* Public Interface - May be used in end-application: */
    /* Macros: */
      /** Mask for no dataflash chip selected. */
      #define DAC_NO_CHIP     DAC_CHIPCS_MASK
      #define DAC_CHIP1       (DAC_CHIPCS_MASK ^ _BV(5))
      #define DAC_PRECISION   12 // bits
      #define DAC_LEVELS      _BV(DAC_PRECISION)
      #define DAC_VCC         3300 // mV

    /* Mapping */
    /* 
     * VTGT    : DAC_A
     * ADC_CAL : DAC_B
     */

    /* Adjust mode */
    #define DAC_ADJUST_MODE_INCREMENT 0
    #define DAC_ADJUST_MODE_DECREMENT 1
    #define DAC_ADJUST_MODE_PLUS      2
    #define DAC_ADJUST_MODE_MINUS     3
    #define DAC_ADJUST_MODE_ABSOLUTE  4

    /* Data structure */
    typedef struct {
      const char     *name;
      const uint8_t  value_reg;
            uint16_t current_level; // Current binary value for the corresponding voltage
    } target_dac_structure_t;

    /* DAC Map */
    target_dac_structure_t target_dac_map[] = {
      // Name      | Value Register
      { "VTGT"     , LOAD_DAC_REG_A, 100 }, 
      { "ADC_CAL"  , LOAD_DAC_REG_B, 200 }, 
      { NULL }
    };

    /* Inline Functions: */

      /**
       * Function for finding the pointer of the target
       */
      static inline target_dac_structure_t* DAC_Find_Target(const char* _target) { 
        target_dac_structure_t *candidate = target_dac_map;
        while(candidate->name) {
          if( 0 == strcmp(_target, candidate->name))
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
      static inline void DAC_Configure_DAC(const char* _target, uint16_t _mVolt, const char _mode)
      {
        target_dac_structure_t *channel = DAC_Find_Target(_target);

        /* No channel found, simply ignore the function call */
        if(!channel->name)
          return;

        /* Get the current voltage value */
        uint16_t current_voltage = DAC_Decode_Level(channel->current_level);

        /* Get the new level */
             if(_mode == DAC_ADJUST_MODE_ABSOLUTE)
          channel->current_level = DAC_Encode_Voltage(_mVolt);
        else if(_mode == DAC_ADJUST_MODE_PLUS)
          channel->current_level = DAC_Encode_Voltage(current_voltage + _mVolt);
        else if(_mode == DAC_ADJUST_MODE_MINUS)
          channel->current_level = DAC_Encode_Voltage(current_voltage - _mVolt);
        else if(_mode == DAC_ADJUST_MODE_INCREMENT)
          channel->current_level++;
        else if(_mode == DAC_ADJUST_MODE_DECREMENT)
          channel->current_level--;
        else
          channel->current_level = channel->current_level;

        /* Compose the 14-bit command */
        uint16_t _command = ((channel->value_reg << DAC_PRECISION) + channel->current_level) & 0x3FFF; // 14 bits in total

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
      static inline uint16_t DAC_Read(const char* _target)
      {
        target_dac_structure_t *channel = DAC_Find_Target(_target);

        /* No channel found, simply ignore the function call */
        if(!channel->name)
          return 0;

        /* Return the current level */
        return DAC_Decode_Level(channel->current_level);
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
        
        target_dac_structure_t *channel = target_dac_map;
        while(channel->name) {
          DAC_Configure_DAC(channel->name, DAC_Decode_Level(channel->current_level), DAC_ADJUST_MODE_ABSOLUTE);
          channel++;
        }
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
