/*
   Board Power Management driver for the RRAM Testchip
*/

#ifndef __PM_RRAM_H__
#define __PM_RRAM_H__

  /* Includes: */
  #include "LTC3676.h"
  #include "I2C.h"
  #include "SWD.h"
  #include "DAC.h"
  #include "RRAM.h"

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
    /* Feedback Ratio */
    #define PM_3V3_FB_RATIO       4
    #define PM_AVDD_WR_FB_RATIO   4
    #define PM_AVDD_WL_FB_RATIO   4
    #define PM_AVDD_RRAM_FB_RATIO 1

    /* Mapping */
    /* 
     * 3V3       : BUCK1
     * AVDD_WR   : BUCK2
     * AVDD_WL   : BUCK3
     * AVDD_RRAM : BUCK4
     * 3V3_AO    : LDO1
     * VDD       : LDO2
     * AVDD_SRAM : LDO4
     */

    /* Adjust mode */
    #define PM_ADJUST_MODE_INCREMENT 0
    #define PM_ADJUST_MODE_DECREMENT 1
    #define PM_ADJUST_MODE_PLUS      2
    #define PM_ADJUST_MODE_MINUS     3
    #define PM_ADJUST_MODE_ABSOLUTE  4

    /* Data structure */
    typedef struct {
      const char    *name;
      const uint8_t on_off_reg;
      const uint8_t on_off_mask;
      const uint8_t value_reg;
      const uint8_t value_mask;
      const uint8_t feedback_ratio;
      const bool    adjustable;
            uint8_t* DVBx_addr; // inside EEPROM
    } regulator_structure_t;

    /* Regulator Map */
    __attribute__((section(".eeprom"))) uint8_t  PM_3V3_DVBx       = 0x14;
    __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_WR_DVBx   = 0x00;
    __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_WL_DVBx   = 0x00;
    __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_RRAM_DVBx = 0x03;

    regulator_structure_t regulators_map[] = {
      // Name      | On/Off Register |        On/Off Mask | Volt Value Register | Voltage Value Mask |       Feedback Ratio | Adjustability | DVBx address
      { "3V3"      ,     PM_CMD_BUCK1, PM_BUCK_ENABLE_MASK,         PM_CMD_DVB1A, PM_BUCK_FB_REF_MASK, PM_3V3_FB_RATIO      ,          true , &PM_3V3_DVBx       },
      { "AVDD_WR"  ,     PM_CMD_BUCK2, PM_BUCK_ENABLE_MASK,         PM_CMD_DVB2A, PM_BUCK_FB_REF_MASK, PM_AVDD_WR_FB_RATIO  ,          true , &PM_AVDD_WR_DVBx   },
      { "AVDD_WL"  ,     PM_CMD_BUCK3, PM_BUCK_ENABLE_MASK,         PM_CMD_DVB3A, PM_BUCK_FB_REF_MASK, PM_AVDD_WL_FB_RATIO  ,          true , &PM_AVDD_WL_DVBx   },
      { "AVDD_RRAM",     PM_CMD_BUCK4, PM_BUCK_ENABLE_MASK,         PM_CMD_DVB4A, PM_BUCK_FB_REF_MASK, PM_AVDD_RRAM_FB_RATIO,          true , &PM_AVDD_RRAM_DVBx },
      { "VDD"      ,      PM_CMD_LDOA, PM_LDO2_ENABLE_MASK,                    0,                   0,                     0,         false ,               NULL },
      { "AVDD_SRAM",      PM_CMD_LDOB, PM_LDO4_ENABLE_MASK,                    0,                   0,                     0,         false ,               NULL },
      { NULL }
    };

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
     * Calculate the DVB value based on the target voltage (mV) and the ratio of the feedback resistors
     */
    static inline uint8_t PM_Encode_DVBx(uint16_t _target_voltage, uint8_t _feedback_ratio) 
    {
      int8_t DVBx = (int8_t)((((float)_target_voltage)/(1.0+(float)_feedback_ratio)-412.5)/12.5);
      if(DVBx < 0)
        DVBx = 0;
      else if(DVBx >= _BV(5))
        DVBx = _BV(5)-1;
      return (uint8_t) DVBx;
    }

    /**
     * Calculate the voltage (mV) based on the DVB value and the ratio of the feedback resistors
     */
    static inline uint16_t PM_Decode_DVBx(uint8_t _code, uint8_t _feedback_ratio) 
    {
      return (uint16_t) ((1.0+(float)_feedback_ratio)*((float)_code*12.5+412.5));
    }

    /**
     * Function for finding the pointer of the target
     */
    static inline regulator_structure_t* PM_Find_Target(const char* _target) { 
      regulator_structure_t *candidate = regulators_map;
      while(candidate->name) {
        if(0 == strcmp(_target, candidate->name))
          break;
        else
          candidate++;
      }
      return candidate;
    }

    /**
     * Function for adjusting the voltage
     */
    static inline void PM_Adjust(const char* _target, uint16_t _target_voltage, const char _mode) { 
      regulator_structure_t *regulator = PM_Find_Target(_target);

      /* No target found, simply ignore the function call */
      if(!regulator->name)
        return;

      /* Get the original binary code and adjust it if needed */
      uint8_t oldDVBx = PM_ReadReg(regulator->value_reg) & regulator->value_mask;
      uint8_t newDVBx;
      uint16_t oldVoltage = PM_Decode_DVBx(oldDVBx, regulator->feedback_ratio);

      if(_mode == PM_ADJUST_MODE_ABSOLUTE)
        newDVBx = PM_Encode_DVBx(             _target_voltage, regulator->feedback_ratio);
      else if(_mode == PM_ADJUST_MODE_PLUS)
        newDVBx = PM_Encode_DVBx(oldVoltage + _target_voltage, regulator->feedback_ratio);
      else if(_mode == PM_ADJUST_MODE_MINUS)
        newDVBx = PM_Encode_DVBx(oldVoltage - _target_voltage, regulator->feedback_ratio);
      else if(_mode == PM_ADJUST_MODE_INCREMENT)
        newDVBx = oldDVBx + 1 >= _BV(5)? _BV(5) - 1: oldDVBx + 1;
      else if(_mode == PM_ADJUST_MODE_DECREMENT)
        newDVBx = (int8_t)oldDVBx - 1 < 0? 0: oldDVBx - 1;
      else
        newDVBx = oldDVBx;

      PM_UpdateReg(regulator->value_reg, newDVBx, regulator->value_mask);
      
    }

    /**
     * Function for checking if the target is enabled
     */
    static inline bool PM_Is_Enabled(const char* _target) { 
      regulator_structure_t *regulator = PM_Find_Target(_target);

      /* No target found, simply ignore the function call */
      if(!regulator->name)
        return 0;

      /* Otherwise we read the status */
      return PM_ReadReg(regulator->on_off_reg) & regulator->on_off_mask? true: false;
    }

    /**
     * Function for reading the current voltage
     */
    static inline uint16_t PM_Read_Voltage(const char* _target) { 
      regulator_structure_t *regulator = PM_Find_Target(_target);

      /* No target found, simply ignore the function call */
      if(!regulator->name || !regulator->adjustable)
        return -1;

      /* Otherwise we read the voltage */
      return PM_Decode_DVBx(PM_ReadReg(regulator->value_reg) & regulator->value_mask, regulator->feedback_ratio);
    }

    /**
     * Function for enabling the voltage
     */
    static inline void PM_Enable(const char* _target) { 
      regulator_structure_t *regulator = PM_Find_Target(_target);

      /* No target found, simply ignore the function call */
      if(!regulator->name)
        return;

      /* Otherwise we enable the voltage */
      PM_UpdateReg(regulator->on_off_reg, regulator->on_off_mask, regulator->on_off_mask);
    }

    /**
     * Function for disabling the voltage
     */
    static inline void PM_Disable(const char* _target) { 
      regulator_structure_t *regulator = PM_Find_Target(_target);

      /* No target found, simply ignore the function call */
      if(!regulator->name)
        return;

      /* Otherwise we disable the voltage */
      PM_UpdateReg(regulator->on_off_reg, 0, regulator->on_off_mask);
    }
    
    /**
     * Function for reseting the regulator
     */
    static inline void PM_Reset(void) { PM_WriteReg(PM_CMD_HRST , 0); }

    /**
     * Function for clear interruptions
     */
    static inline void PM_ClearIRQ(void) { PM_WriteReg(PM_CMD_CLIRQ, 0); }

    /**
     * Function for reading the interruption status 
     */
    static inline uint8_t PM_ReadIRQ(void) { return PM_ReadReg(PM_STATUS_IRQSTAT); }

    /**
     * Function for storing the DVBx into EEPROM
     */
    static inline void PM_Save(void)
    {
      regulator_structure_t *regulator = regulators_map;
      while(regulator->name) {
        if(regulator->adjustable){
          uint8_t DVBx = PM_ReadReg(regulator->value_reg) & regulator->value_mask;
          eeprom_write_byte(regulator->DVBx_addr, DVBx);
          eeprom_busy_wait();
        }
        regulator++;
      }
    }

    /**
     * Function for loading the DVBx from EEPROM
     */
    static inline void PM_Load(void)
    {
      regulator_structure_t *regulator = regulators_map;
      while(regulator->name) {
        if(regulator->adjustable){
          uint8_t DVBx = eeprom_read_byte(regulator->DVBx_addr);
          PM_UpdateReg(regulator->value_reg, DVBx, regulator->value_mask);
        }
        regulator++;
      }
    }

    /**
     * Function for turning on all the voltages
     */
    static inline void PM_EnableAll(void)
    {
      /* Enable the low voltages first */
      PM_Enable("VDD");
      PM_Enable("AVDD_SRAM");
      PM_Enable("AVDD_RRAM");

      /* Enable the high voltages second */
      PM_Enable("3V3");
      PM_Enable("AVDD_WR");
      PM_Enable("AVDD_WL");
    }
    
    /**
     * Function for turning off all the voltages
     */
    static inline void PM_DisableAll(void)
    {
      /* Disable the high voltages first */
      PM_Disable("3V3");
      PM_Disable("AVDD_WR");
      PM_Disable("AVDD_WL");

      /* Disable the low voltages second */
      PM_Disable("VDD");
      PM_Disable("AVDD_SRAM");
      PM_Disable("AVDD_RRAM");
    }

    /**
     * Interrupt functions
     */
    ISR(PCINT0_vect){
    }

    ISR(PCINT1_vect){
      if(PM_WAKE_PIN & PM_WAKE_MASK){
        /* Reset power voltages */
        PM_ClearIRQ();
        PM_Load();
        PM_EnableAll();

        /* Enable Protocols */
        SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING | SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
        SW_Init();

        /* Enable Board Components */
        RRAM_Init();
        LEDs_Init();
        DAC_Init();
        Dataflash_Init();
      }
      else if(~(PM_WAKE_PIN & PM_WAKE_MASK)){
        /* Disable Protocols */
        SPI_ShutDown();
        SW_ShutDown();

        /* Disable Board Components */
        RRAM_ShutDown();
        LEDs_ShutDown();
        DAC_ShutDown();
        Dataflash_ShutDown();
      }
    }

    /**
     * Function for initializing the PM
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
      PM_RSTO_POUT  |=  PM_RSTO_MASK ; // Enable the pull up resistor
      PM_RSTO_DDR   &= ~PM_RSTO_MASK ; // Set it as input

      /* Enable Pin Change Interrupt Control Register */
      PCICR |= _BV(PCIE0); // For PCINT[7:0]
      PCICR |= _BV(PCIE1); // For PCINT[12:8]

      /* Choose Which Pins to Interrupt */
      PM_WAKE_INT_REG  |= PM_WAKE_INT_MASK;
      //PM_NIRQ_INT_REG  |= PM_NIRQ_INT_MASK;
      //PM_PGOOD_INT_REG |= PM_PGOOD_INT_MASK;
      //PM_RSTO_INT_REG  |= PM_RSTO_INT_MASK;
      
      PCINT1_vect();
    }
    

#endif
