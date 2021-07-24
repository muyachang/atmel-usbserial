
/** \file
 *  \brief Board specific Dataflash commands header for the AT45DB321E.
 *
 *  Board specific Dataflash commands header for the AT45DB321E.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the dataflash driver
 *        dispatch header located in LUFA/Drivers/Board/Dataflash.h.
 */

/** \ingroup Group_Dataflash_RRAM_TESTCHIP
 *  @defgroup Group_Dataflash_RRAM_TESTCHIP_AT45DB321E AT45DB321E
 *
 *  Board specific Dataflash commands header for the AT45DB321E.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the dataflash driver
 *        dispatch header located in LUFA/Drivers/Board/Dataflash.h.
 *
 *  @{
 */

#ifndef __CORTEX_M3_CMDS_H__
#define __CORTEX_M3_CMDS_H__

  /* Includes: */
  #include <util/delay.h>

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define SW_DIO_PIN   PINC
      #define SW_DIO_POUT  PORTC
      #define SW_DIO_DDR   DDRC
      #define SW_DIO_MASK  _BV(6)

      #define SW_CLK_PIN   PINC
      #define SW_CLK_POUT  PORTC
      #define SW_CLK_DDR   DDRC
      #define SW_CLK_MASK  _BV(7)

      #define SW_PACKET_INTERVAL 20 // us
      #define SW_DATA_HOLD_TIME  5 // us
  #endif

  /* Public Interface - May be used in end-application: */

  /* Inline Functions: */

    /**
     *
     */
    static inline void SW_Init(void)
    {
      SW_DIO_POUT |=  SW_DIO_MASK; // Pull up DIO
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as an output

      SW_CLK_POUT |=  SW_CLK_MASK; // Pull up CLK
      SW_CLK_DDR  |=  SW_CLK_MASK; // Set it as an output
    }

    /**
     *
     */
    static inline void SW_ShutDown(void)
    {
      SW_DIO_POUT |=  SW_DIO_MASK; // Enable the Pull-up resistor 
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as an input 

      SW_CLK_POUT |=  SW_CLK_MASK; // Enable the Pull-up resistor
      SW_CLK_DDR  &= ~SW_CLK_MASK; // Set it as an input 
    }

    /**
     *
     */
    static inline void SW_StartTransmission(void)
    {
      SW_DIO_POUT &= ~SW_DIO_MASK; // Pull down DIO
      SW_CLK_POUT &= ~SW_CLK_MASK; // Pull down CLK
    }

    /**
     *
     */
    static inline void SW_EndTransmission(void)
    {
      SW_DIO_POUT &= ~SW_DIO_MASK; // Pull low DIO
      SW_CLK_POUT |=  SW_CLK_MASK; // Pull up CLK
      SW_DIO_POUT |=  SW_DIO_MASK; // Pull up DIO
    }

    /**
     *
     */
    static inline bool SW_SendByte(uint8_t _data)
    {
      /* Send the byte part */
      for(int8_t i = 7; i>=0; i--){
        /* DIO */
        if((_data >> i) & 1)
          SW_DIO_POUT |=  SW_DIO_MASK;
        else
          SW_DIO_POUT &= ~SW_DIO_MASK;

        /* Toggle CLK */
        SW_CLK_POUT |=  SW_CLK_MASK;
        _delay_us(SW_DATA_HOLD_TIME);
        SW_CLK_POUT &= ~SW_CLK_MASK;
      }

      /* Receive the acknowledge part */
      bool ack;
      SW_DIO_POUT |=  SW_DIO_MASK;    // Enable the pull-up resistor
      SW_DIO_DDR  &= ~SW_DIO_MASK;    // Set it as input
      SW_CLK_POUT |=  SW_CLK_MASK;    // Pull high CLK
      _delay_us(SW_DATA_HOLD_TIME);    // Hold for some time
      ack = SW_DIO_PIN & SW_DIO_MASK; // Sample DIO 
      SW_CLK_POUT &= ~SW_CLK_MASK;    // Pull low CLK
      SW_DIO_DDR  |=  SW_DIO_MASK;    // Set it as output

      /* Some delay between packets */
      _delay_us(SW_PACKET_INTERVAL);

      return ack;
    }

    /**
     *
     */
    static inline uint8_t SW_ReceiveByte(void)
    {
      uint8_t result = 0;

      /* Set DIO as input */
      SW_DIO_POUT |=  SW_DIO_MASK; // Enable the pull-up resistor
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as input

      /* Receive the byte part */
      for(int8_t i = 7; i>=0; i--){
        SW_CLK_POUT |=  SW_CLK_MASK;                     // Pull high CLK
        _delay_us(SW_DATA_HOLD_TIME);                     // Hold for some time
        result |= (SW_DIO_PIN & SW_DIO_MASK)? _BV(i): 0; // Sample DIO 
        SW_CLK_POUT &= ~SW_CLK_MASK;                     // Pull low CLK 
      }

      /* Send the acknowledge part */
      SW_DIO_POUT &= ~SW_DIO_MASK; // Pull low DIO
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as output
      SW_CLK_POUT |=  SW_CLK_MASK; // Pull high CLK
      _delay_us(SW_DATA_HOLD_TIME); // Hold for some time
      SW_CLK_POUT &= ~SW_CLK_MASK; // Pull low CLK
      SW_DIO_POUT |=  SW_DIO_MASK; // Pull high DIO 

      /* Some delay between packets */
      _delay_us(SW_PACKET_INTERVAL);

      return result;
    }

#endif
