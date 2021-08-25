/*
   Board DAC driver for the RRAM Testchip
*/

#ifndef __RRAM_H__
#define __RRAM_H__

  /* Includes: */

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define RRAM_NRST_LINE_PORT  PORTB
      #define RRAM_NRST_LINE_DDR   DDRB
      #define RRAM_NRST_LINE_MASK  _BV(0)

      #define RRAM_NTRST_LINE_PORT PORTD
      #define RRAM_NTRST_LINE_DDR  DDRD
      #define RRAM_NTRST_LINE_MASK _BV(6)

      #define RRAM_ROM_SIZE 131072 // 128KB
      #define RRAM_RAM_SIZE 524288 // 512KB

      #define RRAM_NRST_DURATION  250
      #define RRAM_NTRST_DURATION 250
  #endif

  /* Public Interface - May be used in end-application: */
    /* Macros: */

    /* Inline Functions: */
      /**
       *  Initialize the RRAM chip
       */
      static inline void RRAM_Init(void)
      {
        RRAM_NRST_LINE_PORT  |=  RRAM_NRST_LINE_MASK ; // Enable the pull-up resistor
        RRAM_NRST_LINE_DDR   &= ~RRAM_NRST_LINE_MASK ; // Set it as input 
        RRAM_NTRST_LINE_PORT |=  RRAM_NTRST_LINE_MASK; // Enable the pull-up resistor
        RRAM_NTRST_LINE_DDR  &= ~RRAM_NTRST_LINE_MASK; // Set it as input 
      }

      /**
       *  Shutdown the RRAM chip
       */
      static inline void RRAM_ShutDown(void)
      {
        RRAM_NRST_LINE_PORT  &= ~RRAM_NRST_LINE_MASK ; // Disable the pull-up resistor
        RRAM_NTRST_LINE_PORT &= ~RRAM_NTRST_LINE_MASK; // Disable the pull-up resistor
      }

      /**
       *  Reset the RRAM
       */
      static inline void RRAM_Reset(void)
      {
        RRAM_NRST_LINE_DDR  |=  RRAM_NRST_LINE_MASK; // Set it as output
        RRAM_NRST_LINE_PORT &= ~RRAM_NRST_LINE_MASK; // Pull down RST
        _delay_us(RRAM_NRST_DURATION);
        RRAM_NRST_LINE_PORT |=  RRAM_NRST_LINE_MASK; // Pull up RST
        RRAM_NRST_LINE_DDR  &= ~RRAM_NRST_LINE_MASK; // Set it as input 
      }

      /**
       *  Reset the RRAM Test Port
       */
      static inline void RRAM_Test_Reset(void)
      {
        RRAM_NTRST_LINE_DDR  |=  RRAM_NTRST_LINE_MASK; // Set it as output
        RRAM_NTRST_LINE_PORT &= ~RRAM_NTRST_LINE_MASK; // Pull down TRST
        _delay_us(RRAM_NTRST_DURATION);
        RRAM_NTRST_LINE_PORT |=  RRAM_NTRST_LINE_MASK; // Pull up TRST
        RRAM_NTRST_LINE_DDR  &= ~RRAM_NTRST_LINE_MASK; // Set it as input 
      }

#endif

