/*
   Board DAC driver for the RRAM Testchip
*/

#ifndef __TC_H__
#define __TC_H__

  /* Includes: */

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define TC_NRST_LINE_PORT  PORTD
      #define TC_NRST_LINE_DDR   DDRD
      #define TC_NRST_LINE_MASK  _BV(6)

      #define TC_NTRST_LINE_PORT PORTB
      #define TC_NTRST_LINE_DDR  DDRB
      #define TC_NTRST_LINE_MASK _BV(0)

      #define TC_ROM_SIZE 131072 // 128KB
      #define TC_RAM_SIZE 524288 // 512KB

      #define TC_NRST_DURATION  250
      #define TC_NTRST_DURATION 250
  #endif

  /* Public Interface - May be used in end-application: */
    /* Macros: */

    /* Inline Functions: */
      /**
       *  Initialize the RRAM testchip
       */
      static inline void TC_Init(void)
      {
        TC_NRST_LINE_PORT  |=  TC_NRST_LINE_MASK ; // Enable the pull-up resistor
        TC_NRST_LINE_DDR   &= ~TC_NRST_LINE_MASK ; // Set it as input 
        TC_NTRST_LINE_PORT |=  TC_NTRST_LINE_MASK; // Enable the pull-up resistor
        TC_NTRST_LINE_DDR  &= ~TC_NTRST_LINE_MASK; // Set it as input 
      }

      /**
       *  Shutdown the RRAM testchip
       */
      static inline void TC_ShutDown(void)
      {
        TC_NRST_LINE_PORT  &= ~TC_NRST_LINE_MASK ; // Disable the pull-up resistor
        TC_NTRST_LINE_PORT &= ~TC_NTRST_LINE_MASK; // Disable the pull-up resistor
      }

      /**
       *  Reset the RRAM testchip
       */
      static inline void TC_Reset(void)
      {
        TC_NRST_LINE_DDR  |=  TC_NRST_LINE_MASK; // Set it as output
        TC_NRST_LINE_PORT &= ~TC_NRST_LINE_MASK; // Pull down RST
        _delay_us(TC_NRST_DURATION);
        TC_NRST_LINE_PORT |=  TC_NRST_LINE_MASK; // Pull up RST
        TC_NRST_LINE_DDR  &= ~TC_NRST_LINE_MASK; // Set it as input 
      }

      /**
       *  Reset the RRAM testchip Test Port
       */
      static inline void TC_Test_Reset(void)
      {
        TC_NTRST_LINE_DDR  |=  TC_NTRST_LINE_MASK; // Set it as output
        TC_NTRST_LINE_PORT &= ~TC_NTRST_LINE_MASK; // Pull down TRST
        _delay_us(TC_NTRST_DURATION);
        TC_NTRST_LINE_PORT |=  TC_NTRST_LINE_MASK; // Pull up TRST
        TC_NTRST_LINE_DDR  &= ~TC_NTRST_LINE_MASK; // Set it as input 
      }

#endif

