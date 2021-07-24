/*
   Board DAC driver for the RRAM Testchip
*/

#ifndef __RRAM_H__
#define __RRAM_H__

  /* Includes: */

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define RRAM_NTRST_LINE_PORT PORTD
      #define RRAM_NTRST_LINE_DDR  DDRD
      #define RRAM_NTRST_LINE_MASK _BV(6)

      #define RRAM_NRST_LINE_PORT  PORTD
      #define RRAM_NRST_LINE_DDR   DDRD
      #define RRAM_NRST_LINE_MASK  _BV(7)

      #define RRAM_ROM_SIZE 131072 // 128KB
      #define RRAM_RAM_SIZE 524288 // 512KB
  #endif

  /* Public Interface - May be used in end-application: */
    /* Macros: */

    /* Inline Functions: */
      /**
       *  Grasp the RRAM chip so that commands and data may be sent to an attached RRAM chip.
       */
      static inline void RRAM_Grasp(void)
      {
        RRAM_NRST_LINE_PORT  |=  RRAM_NRST_LINE_MASK ; // Pull high NRST
        RRAM_NRST_LINE_DDR   |=  RRAM_NRST_LINE_MASK ; // Set it as output

        RRAM_NTRST_LINE_PORT |=  RRAM_NTRST_LINE_MASK; // Pull high NTRST
        RRAM_NTRST_LINE_DDR  |=  RRAM_NTRST_LINE_MASK; // Set it as output 
      }

      /**
       *  Release the RRAM chip
       */
      static inline void RRAM_Release(void)
      {
        RRAM_NRST_LINE_PORT  &= ~RRAM_NRST_LINE_MASK ; // Disable the pull-up resistor
        RRAM_NRST_LINE_DDR   &= ~RRAM_NRST_LINE_MASK ; // Set it as input 

        RRAM_NTRST_LINE_PORT &= ~RRAM_NTRST_LINE_MASK; // Disable the pull-up resistor
        RRAM_NTRST_LINE_DDR  &= ~RRAM_NTRST_LINE_MASK; // Set it as input 
      }

      /**
       *  Reset the RRAM
       */
      static inline void RRAM_Reset(void)
      {
        RRAM_NRST_LINE_PORT &= ~RRAM_NRST_LINE_MASK;
        RRAM_NRST_LINE_PORT |=  RRAM_NRST_LINE_MASK;
      }

      /**
       *  Reset the RRAM Test Port
       */
      static inline void RRAM_Test_Reset(void)
      {
        RRAM_NTRST_LINE_PORT &= ~RRAM_NTRST_LINE_MASK;
        RRAM_NTRST_LINE_PORT |=  RRAM_NTRST_LINE_MASK;
      }

#endif

