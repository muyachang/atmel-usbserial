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

    /* Inline Functions: */
      /** 
       *  For the selected DAC chip, set the _target DAC to the _mVolt  
       */
      static inline void DAC_Configure_DAC(uint8_t _chip_mask, uint8_t _target, uint16_t _mVolt) ATTR_ALWAYS_INLINE;
      static inline void DAC_Configure_DAC(uint8_t _chip_mask, uint8_t _target, uint16_t _mVolt)
      {
        /* Convert from mV to the binary code */
        uint16_t value = _mVolt > DAC_VCC? DAC_LEVELS-1: (uint32_t)_mVolt*DAC_LEVELS/3300.0;

        /* Compose the 14-bit command */
        uint16_t _command = ((_target << DAC_PRECISION) + value) & 0x3FFF; // 14 bits in total

        /* Send the command */
        DAC_CHIPCS_POUT = (DAC_CHIPCS_POUT & ~DAC_CHIPCS_MASK) | _chip_mask;
        SPI_SendByte((_command >> 8) & 0xFF);
        SPI_SendByte((_command     ) & 0xFF);
        DAC_CHIPCS_POUT = (DAC_CHIPCS_POUT & ~DAC_CHIPCS_MASK) | DAC_NO_CHIP;

        /* Toggle LOADDAC to update the DAC output */
        DAC_LOADDACS_POUT ^= DAC_LOADDACS_MASK;
        DAC_LOADDACS_POUT ^= DAC_LOADDACS_MASK;
      }

      /**
       *  Grasp the DAC driver so that commands and data may be sent to an attached DAC IC.
       */
      static inline void DAC_Grasp(void)
      {
        DAC_CHIPCS_POUT   |=  DAC_CHIPCS_MASK  ; // Set the output value to 1 (Deselect the DAC by default)
        DAC_CHIPCS_DDR    |=  DAC_CHIPCS_MASK  ; // Set it as an output

        DAC_LOADDACS_POUT |=  DAC_LOADDACS_MASK; // Set the output value to 1 (Don't load the DAC by default)
        DAC_LOADDACS_DDR  |=  DAC_LOADDACS_MASK; // Set it as an output
      }

      /**
       *
       */
      static inline void DAC_Release(void)
      {
        DAC_CHIPCS_POUT   &= ~DAC_CHIPCS_MASK  ; // Disable the pull high resistor
        DAC_CHIPCS_DDR    &= ~DAC_CHIPCS_MASK  ; // Set it as an input 

        DAC_LOADDACS_POUT &= ~DAC_LOADDACS_MASK; // Disable the pull high resistor
        DAC_LOADDACS_DDR  &= ~DAC_LOADDACS_MASK; // Set it as an input 
      }

#endif

