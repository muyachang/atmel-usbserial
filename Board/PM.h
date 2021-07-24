/*
   Board Power Management driver for the RRAM Testchip
*/

#ifndef __PM_RRAM_H__
#define __PM_RRAM_H__

  /* Includes: */
  #include "LTC3676.h"
  #include "../Lib/I2C.h"

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      #define PM_WAKE_PIN       PINC
      #define PM_WAKE_POUT      PORTC
      #define PM_WAKE_DDR       DDRC
      #define PM_WAKE_MASK      _BV(2)
      #define PM_WAKE_INT_REG   PCMSK1
      #define PM_WAKE_INT_MASK  _BV(PCINT11)

      #define PM_NIRQ_PIN       PINC
      #define PM_NIRQ_POUT      PORTC
      #define PM_NIRQ_DDR       DDRC
      #define PM_NIRQ_MASK      _BV(4)
      #define PM_NIRQ_INT_REG   PCMSK1
      #define PM_NIRQ_INT_MASK  _BV(PCINT10)

      #define PM_PGOOD_PIN      PINC
      #define PM_PGOOD_POUT     PORTC
      #define PM_PGOOD_DDR      DDRC
      #define PM_PGOOD_MASK     _BV(5)
      #define PM_PGOOD_INT_REG  PCMSK1
      #define PM_PGOOD_INT_MASK _BV(PCINT9)

      #define PM_RSTO_PIN      PINB
      #define PM_RSTO_POUT     PORTB
      #define PM_RSTO_DDR      DDRB
      #define PM_RSTO_MASK     _BV(7)
      #define PM_RSTO_INT_REG  PCMSK1
      #define PM_RSTO_INT_MASK _BV(PCINT7)
  #endif

  /* Public Interface - May be used in end-application: */
    /* Mapping */
    #define PM_3V3_FB_RATIO       4
    #define PM_AVDD_WR_FB_RATIO   4
    #define PM_AVDD_WL_FB_RATIO   4
    #define PM_AVDD_RRAM_FB_RATIO 1

    /* 
     * 3V3       : BUCK1
     * AVDD_WR   : BUCK2
     * AVDD_WL   : BUCK3
     * AVDD_RRAM : BUCK4
     * 3V3_AO    : LDO1
     * VDD       : LDO2
     * AVDD_SRAM : LDO4
     */

  /* Inline Functions: */

    /**
     * Write to a register
     */
    static inline void PM_WriteReg(uint8_t _subaddress, uint8_t _data)
    {
      I2C_StartTransmission();
      I2C_SendByte(PM_WR_MODE);
      I2C_SendByte(_subaddress);
      I2C_SendByte(_data);
      I2C_EndTransmission();
    }

    /**
     * Read from a register
     */
    static inline uint8_t PM_ReadReg(uint8_t _subaddress)
    {
      uint8_t result;
      I2C_StartTransmission();
      I2C_SendByte(PM_WR_MODE);
      I2C_SendByte(_subaddress);
      I2C_StartTransmission();
      I2C_SendByte(PM_RD_MODE);
      result = I2C_ReceiveByte();
      I2C_EndTransmission();
      return result;
    }

    /**
     * Update a register (Basically a read + a write)
     */
    static inline void PM_UpdateReg(uint8_t _subaddress, uint8_t _data, uint8_t _mask)
    {
      PM_WriteReg(_subaddress, (PM_ReadReg(_subaddress) & ~_mask) | _data);
    }

    /**
     * Calculate the DVB value based on the target voltage and the ratio of the feedback resistors
     */
    static inline uint8_t PM_Calculate_DVBx(double _target_voltage, double _feedback_ratio) 
    {
      return (uint8_t) (((_target_voltage*1000)/(1+_feedback_ratio)-412.5)/12.5);
    }

    /**
     * Functions for adjusting the voltage
     */
    static inline void PM_Adjust_3V3      (double _target_voltage) { PM_UpdateReg(PM_CMD_DVB1A, PM_Calculate_DVBx(_target_voltage, PM_3V3_FB_RATIO      ), PM_BUCK_FB_REF_MASK); }
    static inline void PM_Adjust_AVDD_WR  (double _target_voltage) { PM_UpdateReg(PM_CMD_DVB2A, PM_Calculate_DVBx(_target_voltage, PM_AVDD_WR_FB_RATIO  ), PM_BUCK_FB_REF_MASK); }
    static inline void PM_Adjust_AVDD_WL  (double _target_voltage) { PM_UpdateReg(PM_CMD_DVB3A, PM_Calculate_DVBx(_target_voltage, PM_AVDD_WL_FB_RATIO  ), PM_BUCK_FB_REF_MASK); }
    static inline void PM_Adjust_AVDD_RRAM(double _target_voltage) { PM_UpdateReg(PM_CMD_DVB4A, PM_Calculate_DVBx(_target_voltage, PM_AVDD_RRAM_FB_RATIO), PM_BUCK_FB_REF_MASK); }

    /**
     * Functions for enabling the voltage
     */
    static inline void PM_Enable_3V3      (void) { PM_UpdateReg(PM_CMD_BUCK1, PM_BUCK_ENABLE_MASK, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Enable_AVDD_WR  (void) { PM_UpdateReg(PM_CMD_BUCK2, PM_BUCK_ENABLE_MASK, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Enable_AVDD_WL  (void) { PM_UpdateReg(PM_CMD_BUCK3, PM_BUCK_ENABLE_MASK, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Enable_AVDD_RRAM(void) { PM_UpdateReg(PM_CMD_BUCK4, PM_BUCK_ENABLE_MASK, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Enable_VDD      (void) { PM_UpdateReg(PM_CMD_LDOA , PM_LDO2_ENABLE_MASK, PM_LDO2_ENABLE_MASK); }
    static inline void PM_Enable_AVDD_SRAM(void) { PM_UpdateReg(PM_CMD_LDOB , PM_LDO4_ENABLE_MASK, PM_LDO4_ENABLE_MASK); }

    /**
     * Functions for disabling the voltage
     */
    static inline void PM_Disable_3V3      (void) { PM_UpdateReg(PM_CMD_BUCK1, 0, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Disable_AVDD_WR  (void) { PM_UpdateReg(PM_CMD_BUCK2, 0, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Disable_AVDD_WL  (void) { PM_UpdateReg(PM_CMD_BUCK3, 0, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Disable_AVDD_RRAM(void) { PM_UpdateReg(PM_CMD_BUCK4, 0, PM_BUCK_ENABLE_MASK); }
    static inline void PM_Disable_VDD      (void) { PM_UpdateReg(PM_CMD_LDOA , 0, PM_LDO2_ENABLE_MASK); }
    static inline void PM_Disable_AVDD_SRAM(void) { PM_UpdateReg(PM_CMD_LDOB , 0, PM_LDO4_ENABLE_MASK); }

    /**
     * Special functions
     */
    static inline void PM_Reset(void)    { PM_WriteReg(PM_CMD_HRST , 0); }

    /**
     * Interrupt functions 
     */
    static inline void PM_ClearIRQ(void) { PM_WriteReg(PM_CMD_CLIRQ, 0); }
    static inline void PM_ReadStatus(void) { PM_ReadReg(PM_STATUS_IRQSTAT); }

    /**
     *
     */
    static inline void PM_PowerUp(void)
    {

      /* Adjust the voltages */
      PM_Adjust_3V3(3.3);
      PM_Adjust_AVDD_WL(3.6);
      PM_Adjust_AVDD_WR(3.9);
      PM_Adjust_AVDD_RRAM(1.1);

      /* Enable the low voltages first */
      PM_Enable_VDD();
      PM_Enable_AVDD_SRAM();
      PM_Enable_AVDD_RRAM();

      /* Enable the high voltages second */
      PM_Enable_3V3();
      PM_Enable_AVDD_WR();
      PM_Enable_AVDD_WL(); // ????
    }
    
    /**
     *
     */
    static inline void PM_PowerDown(void)
    {
      /* Disable the high voltages first */
      PM_Disable_3V3();
      PM_Disable_AVDD_WR();
      PM_Disable_AVDD_WL();

      /* Disable the low voltages second */
      PM_Disable_VDD();
      PM_Disable_AVDD_SRAM();
      PM_Disable_AVDD_RRAM();
    }
    
    /**
     *
     */
    static inline void PM_Init(void)
    {
      /* Set interrupt pins as input and enables the pull-up resistor*/
      PM_WAKE_POUT  |=  PM_WAKE_MASK ; // Enable the pull up resistor
      PM_WAKE_DDR   &= ~PM_WAKE_MASK ; // Set it as input
      PM_NIRQ_POUT  |=  PM_NIRQ_MASK ; // Enable the pull up resistor
      PM_NIRQ_DDR   &= ~PM_NIRQ_MASK ; // Set it as input
      PM_PGOOD_POUT |=  PM_PGOOD_MASK; // Enable the pull up resistor
      PM_PGOOD_DDR  &= ~PM_PGOOD_MASK; // Set it as input
      PM_RSTO_POUT  |=  PM_RSTO_MASK; // Enable the pull up resistor
      PM_RSTO_DDR   &= ~PM_RSTO_MASK; // Set it as input

      /* Enable Pin Change Interrupt Control Register */
      PCICR |= _BV(PCIE0); // For PCINT[7:0]
      PCICR |= _BV(PCIE1); // For PCINT[12:8]

      /* Choose Which Pins to Interrupt */
      PM_WAKE_INT_REG  |= PM_WAKE_INT_MASK;
      //PM_NIRQ_INT_REG  |= PM_NIRQ_INT_MASK;
      //PM_PGOOD_INT_REG |= PM_PGOOD_INT_MASK;
      //PM_RSTO_INT_REG  |= PM_RSTO_INT_MASK;
    }
    
    /**
     *
     */
    ISR(PCINT0_vect){
    }

    ISR(PCINT1_vect){
      if(PM_WAKE_PIN & PM_WAKE_MASK)
        PM_PowerUp();
      else if(!(PM_WAKE_PIN & PM_WAKE_MASK))
        PM_PowerDown();
    }

#endif
