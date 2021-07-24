/*
   I2C driver for the RRAM Testchip
*/

#ifndef __I2C_RRAM_H__
#define __I2C_RRAM_H__

  /* Includes: */

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define I2C_SDA_PIN   PIND
      #define I2C_SDA_POUT  PORTD
      #define I2C_SDA_DDR   DDRD
      #define I2C_SDA_MASK  _BV(1)

      #define I2C_SCL_POUT  PORTD
      #define I2C_SCL_DDR   DDRD
      #define I2C_SCL_MASK  _BV(0)
  #endif

  /* Public Interface - May be used in end-application: */

  /* Inline Functions: */

    /**
     *
     */
    static inline void I2C_StartTransmission(void)
    {
      I2C_SDA_DDR  |=  I2C_SDA_MASK; // Set it as an output
      I2C_SCL_DDR  |=  I2C_SCL_MASK; // Set it as an output

      I2C_SDA_POUT |=  I2C_SDA_MASK; // Pull up SDA
      I2C_SCL_POUT |=  I2C_SCL_MASK; // Pull up SCL
      I2C_SDA_POUT &= ~I2C_SDA_MASK; // Pull down SDA
      I2C_SCL_POUT &= ~I2C_SCL_MASK; // Pull down SCL
    }

    /**
     *
     */
    static inline void I2C_EndTransmission(void)
    {
      I2C_SDA_POUT &= ~I2C_SDA_MASK; // Pull low SDA
      I2C_SCL_POUT |=  I2C_SCL_MASK; // Pull up SCL
      I2C_SDA_POUT |=  I2C_SDA_MASK; // Pull up SDA

      I2C_SDA_DDR  &= ~I2C_SDA_MASK; // Set it as an input 
      I2C_SCL_DDR  &= ~I2C_SCL_MASK; // Set it as an input 
    }

    /**
     *
     */
    static inline bool I2C_SendByte(uint8_t _data)
    {
      /* Send the byte part */
      for(int8_t i = 7; i>=0; i--){
        /* SDA */
        if((_data >> i) & 1)
          I2C_SDA_POUT |=  I2C_SDA_MASK;
        else
          I2C_SDA_POUT &= ~I2C_SDA_MASK;

        /* Toggle SCL */
        I2C_SCL_POUT |=  I2C_SCL_MASK;
        I2C_SCL_POUT &= ~I2C_SCL_MASK;
      }

      /* Receive the acknowledge part */
      bool ack;
      I2C_SDA_POUT |=  I2C_SDA_MASK;    // Enable the pull-up resistor
      I2C_SDA_DDR  &= ~I2C_SDA_MASK;    // Set it as input
      I2C_SCL_POUT |=  I2C_SCL_MASK;    // Pull high SCL
      ack = I2C_SDA_PIN & I2C_SDA_MASK; // Sample SDA 
      I2C_SCL_POUT &= ~I2C_SCL_MASK;    // Pull low SCL
      I2C_SDA_DDR  |=  I2C_SDA_MASK;    // Set it as output

      return ack;
    }

    /**
     *
     */
    static inline uint8_t I2C_ReceiveByte(void)
    {
      uint8_t result = 0;

      /* Set SDA as input */
      I2C_SDA_POUT |=  I2C_SDA_MASK; // Enable the pull-up resistor
      I2C_SDA_DDR  &= ~I2C_SDA_MASK; // Set it as input

      /* Receive the byte part */
      for(int8_t i = 7; i>=0; i--){
        I2C_SCL_POUT |=  I2C_SCL_MASK;                     // Pull high SCL
        result |= (I2C_SDA_PIN & I2C_SDA_MASK)? _BV(i): 0; // Sample SDA 
        I2C_SCL_POUT &= ~I2C_SCL_MASK;                     // Pull low SCL 
      }

      /* Send the acknowledge part */
      I2C_SDA_POUT &= ~I2C_SDA_MASK; // Pull low SDA
      I2C_SDA_DDR  |=  I2C_SDA_MASK; // Set it as output
      I2C_SCL_POUT |=  I2C_SCL_MASK; // Pull high SCL
      I2C_SCL_POUT &= ~I2C_SCL_MASK; // Pull low SCL
      I2C_SDA_POUT |=  I2C_SDA_MASK; // Pull high SDA 

      return result;
    }

#endif
