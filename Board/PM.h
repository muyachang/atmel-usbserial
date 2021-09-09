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
  #include "TC.h"

  /* Pin assignment */
  #define PM_WAKE_PIN             PIND
  #define PM_WAKE_POUT            PORTD
  #define PM_WAKE_DDR             DDRD
  #define PM_WAKE_MASK            _BV(0)
  #define PM_WAKE_INT_REG         EIMSK 
  #define PM_WAKE_INT_MASK        _BV(INT0)
  #define PM_WAKE_INT_TYPE_REG    EICRA
  #define PM_WAKE_INT_TYPE_LOC    0 
  #define PM_WAKE_INT_TYPE_MASK   (_BV(ISC00)|_BV(ISC01))

  #define PM_NIRQ_PIN             PIND
  #define PM_NIRQ_POUT            PORTD
  #define PM_NIRQ_DDR             DDRD
  #define PM_NIRQ_MASK            _BV(1)
  #define PM_NIRQ_INT_REG         EIMSK
  #define PM_NIRQ_INT_MASK        _BV(INT1)
  #define PM_NIRQ_INT_TYPE_REG    EICRA
  #define PM_NIRQ_INT_TYPE_LOC    2 
  #define PM_NIRQ_INT_TYPE_MASK   _BV(ISC10)|_BV(ISC11)

  #define PM_AVDD_WR_FB_SEL_PIN   PIND
  #define PM_AVDD_WR_FB_SEL_POUT  PORTD
  #define PM_AVDD_WR_FB_SEL_DDR   DDRD
  #define PM_AVDD_WR_FB_SEL_MASK  _BV(4)

  #define PM_AVDD_WL_FB_SEL_PIN   PIND
  #define PM_AVDD_WL_FB_SEL_POUT  PORTD
  #define PM_AVDD_WL_FB_SEL_DDR   DDRD
  #define PM_AVDD_WL_FB_SEL_MASK  _BV(5)

  /* Feedback Ratio */
  #define PM_3V3_FB_RATIO          4.00
  #define PM_AVDD_WR_FB_RATIO_LOW  1.61
  #define PM_AVDD_WR_FB_RATIO_HIGH 4.00
  #define PM_AVDD_WL_FB_RATIO_LOW  1.00
  #define PM_AVDD_WL_FB_RATIO_HIGH 2.85
  #define PM_AVDD_RRAM_FB_RATIO    1.00

  /* Adjust mode */
  #define PM_ADJUST_MODE_INCREMENT 0
  #define PM_ADJUST_MODE_DECREMENT 1
  #define PM_ADJUST_MODE_PLUS      2
  #define PM_ADJUST_MODE_MINUS     3
  #define PM_ADJUST_MODE_ABSOLUTE  4

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
  #define PM_3V3       0x41
  #define PM_AVDD_WR   0x42
  #define PM_AVDD_WL   0x43
  #define PM_AVDD_RRAM 0x44
  #define PM_VDD       0x45
  #define PM_AVDD_SRAM 0x46

  /* Data structure */
  typedef struct {
    const uint8_t  name;          // String name of the voltage
    const uint8_t  on_off_reg;     // On/Off register of the voltage
    const uint8_t  on_off_mask;    // On/Off register mask of the voltage
    const uint8_t  value_reg;      // Value register of the voltage
    const uint8_t  value_mask;     // Value register mask of the voltage
          float    feedback_ratio; // Feedback ratio of the voltage
    const bool     adjustable;     // Whether this voltage is digitally controllable
          uint8_t* DVBx_addr;      // Previous DVBx saved (inside EEPROM)
          uint8_t* status_addr;    // Previous status saved (inside EEPROM)
  } regulator_structure_t;

  /* EEPROM data */
  __attribute__((section(".eeprom"))) float    PM_AVDD_WR_FB_RATIO = PM_AVDD_WR_FB_RATIO_LOW;
  __attribute__((section(".eeprom"))) float    PM_AVDD_WL_FB_RATIO = PM_AVDD_WL_FB_RATIO_LOW;

  __attribute__((section(".eeprom"))) uint8_t  PM_3V3_DVBx         = 20;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_WR_DVBx     = 0;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_WL_DVBx     = 0;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_RRAM_DVBx   = 11;

  __attribute__((section(".eeprom"))) uint8_t  PM_3V3_STATUS       = PM_BUCK_ENABLE_MASK;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_WR_STATUS   = 0;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_WL_STATUS   = 0;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_RRAM_STATUS = 0;
  __attribute__((section(".eeprom"))) uint8_t  PM_VDD_STATUS       = 0;
  __attribute__((section(".eeprom"))) uint8_t  PM_AVDD_SRAM_STATUS = 0;

  /* Regulator Map */
  regulator_structure_t regulators_map[] = {
    // Name       | On/Off Register |        On/Off Mask | Value Register | Voltage Value Mask |         Feedback Ratio | Adjustability | DVBx address       | Status
    { PM_3V3      ,     PM_CMD_BUCK1, PM_BUCK_ENABLE_MASK,    PM_CMD_DVB1A, PM_BUCK_FB_REF_MASK, PM_3V3_FB_RATIO        ,          true , &PM_3V3_DVBx       , &PM_3V3_STATUS       },
    { PM_AVDD_WR  ,     PM_CMD_BUCK2, PM_BUCK_ENABLE_MASK,    PM_CMD_DVB2A, PM_BUCK_FB_REF_MASK, PM_AVDD_WR_FB_RATIO_LOW,          true , &PM_AVDD_WR_DVBx   , &PM_AVDD_WR_STATUS   },
    { PM_AVDD_WL  ,     PM_CMD_BUCK3, PM_BUCK_ENABLE_MASK,    PM_CMD_DVB3A, PM_BUCK_FB_REF_MASK, PM_AVDD_WR_FB_RATIO_LOW,          true , &PM_AVDD_WL_DVBx   , &PM_AVDD_WL_STATUS   },
    { PM_AVDD_RRAM,     PM_CMD_BUCK4, PM_BUCK_ENABLE_MASK,    PM_CMD_DVB4A, PM_BUCK_FB_REF_MASK, PM_AVDD_RRAM_FB_RATIO  ,          true , &PM_AVDD_RRAM_DVBx , &PM_AVDD_RRAM_STATUS },
    { PM_VDD      ,      PM_CMD_LDOA, PM_LDO2_ENABLE_MASK,               0,                   0,                       0,         false ,               NULL , &PM_VDD_STATUS       },
    { PM_AVDD_SRAM,      PM_CMD_LDOB, PM_LDO4_ENABLE_MASK,               0,                   0,                       0,         false ,               NULL , &PM_AVDD_SRAM_STATUS },
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
  static inline uint8_t PM_Encode_DVBx(regulator_structure_t* _regulator, uint16_t _target_voltage) 
  {
    // Calculate the new DVBx based on the current feedback_ratio
    int8_t DVBx = (int8_t)((((float)_target_voltage)/(1.0+_regulator->feedback_ratio)-412.5)/12.5);

    // If the target voltage is too low
    if(DVBx < 0){
      // AVDD_WR supports dual feedback
           if((_regulator->name == PM_AVDD_WR) && (_regulator->feedback_ratio == PM_AVDD_WR_FB_RATIO_HIGH)){
        _regulator->feedback_ratio = PM_AVDD_WR_FB_RATIO_LOW;
        eeprom_write_float(&PM_AVDD_WR_FB_RATIO, _regulator->feedback_ratio);
        eeprom_busy_wait();
        PM_AVDD_WR_FB_SEL_POUT &= ~PM_AVDD_WR_FB_SEL_MASK; // Select Low FB
        DVBx = PM_Encode_DVBx(_regulator, _target_voltage); // Recompute
      }
      // AVDD_WL supports dual feedback
      else if((_regulator->name == PM_AVDD_WL) && (_regulator->feedback_ratio == PM_AVDD_WL_FB_RATIO_HIGH)){
        _regulator->feedback_ratio = PM_AVDD_WL_FB_RATIO_LOW;
        eeprom_write_float(&PM_AVDD_WL_FB_RATIO, _regulator->feedback_ratio);
        eeprom_busy_wait();
        PM_AVDD_WL_FB_SEL_POUT &= ~PM_AVDD_WL_FB_SEL_MASK; // Select Low FB
        DVBx = PM_Encode_DVBx(_regulator, _target_voltage); // Recompute
      }
      else
        DVBx = 0;
    }
    // If the target voltage is too high
    else if(DVBx >= _BV(5)){
      // AVDD_WR supports dual feedback
           if((_regulator->name == PM_AVDD_WR) && (_regulator->feedback_ratio == PM_AVDD_WR_FB_RATIO_LOW)){
        _regulator->feedback_ratio = PM_AVDD_WR_FB_RATIO_HIGH;
        eeprom_write_float(&PM_AVDD_WR_FB_RATIO, _regulator->feedback_ratio);
        eeprom_busy_wait();
        PM_AVDD_WR_FB_SEL_POUT |=  PM_AVDD_WR_FB_SEL_MASK; // Select High FB
        DVBx = PM_Encode_DVBx(_regulator, _target_voltage); // Recompute
      }
      // AVDD_WL supports dual feedback
      else if((_regulator->name == PM_AVDD_WL) && (_regulator->feedback_ratio == PM_AVDD_WL_FB_RATIO_LOW)){
        _regulator->feedback_ratio = PM_AVDD_WL_FB_RATIO_HIGH;
        eeprom_write_float(&PM_AVDD_WL_FB_RATIO, _regulator->feedback_ratio);
        eeprom_busy_wait();
        PM_AVDD_WL_FB_SEL_POUT |=  PM_AVDD_WL_FB_SEL_MASK; // Select High FB
        DVBx = PM_Encode_DVBx(_regulator, _target_voltage); // Recompute
      }
      else
        DVBx = _BV(5)-1;
    }
    return (uint8_t) DVBx;
  }

  /**
   * Calculate the voltage (mV) based on the DVB value and the ratio of the feedback resistors
   */
  static inline uint16_t PM_Decode_DVBx(regulator_structure_t* _regulator, uint8_t _code) 
  {
    return (uint16_t) ((1.0+_regulator->feedback_ratio)*((float)_code*12.5+412.5));
  }

  /**
   * Function for finding the pointer of the target
   */
  static inline regulator_structure_t* PM_Find_Target(const uint8_t _target) { 
    regulator_structure_t *candidate = regulators_map;
    while(candidate->name) {
      if(_target == candidate->name)
        break;
      else
        candidate++;
    }
    return candidate;
  }

  /**
   * Function for adjusting the voltage
   */
  static inline void PM_Adjust(const uint8_t _target, uint16_t _target_voltage, const uint8_t _mode) { 
    regulator_structure_t *regulator = PM_Find_Target(_target);

    /* No target found, simply ignore the function call */
    if(!regulator->name)
      return;

    /* Get the original binary code and adjust it if needed */
    uint8_t oldDVBx = PM_ReadReg(regulator->value_reg) & regulator->value_mask;
    uint8_t newDVBx;
    uint16_t oldVoltage = PM_Decode_DVBx(regulator, oldDVBx);

    if(_mode == PM_ADJUST_MODE_ABSOLUTE)
      newDVBx = PM_Encode_DVBx(regulator,              _target_voltage);
    else if(_mode == PM_ADJUST_MODE_PLUS)
      newDVBx = PM_Encode_DVBx(regulator, oldVoltage + _target_voltage);
    else if(_mode == PM_ADJUST_MODE_MINUS)
      newDVBx = PM_Encode_DVBx(regulator, oldVoltage - _target_voltage);
    else if(_mode == PM_ADJUST_MODE_INCREMENT){
      if(oldDVBx + 1 >= _BV(5)){
        // AVDD_WR supports dual feedback
             if((regulator->name == PM_AVDD_WR) && (regulator->feedback_ratio == PM_AVDD_WR_FB_RATIO_LOW)){
          regulator->feedback_ratio = PM_AVDD_WR_FB_RATIO_HIGH;
          eeprom_write_float(&PM_AVDD_WR_FB_RATIO, regulator->feedback_ratio);
          eeprom_busy_wait();
          PM_AVDD_WR_FB_SEL_POUT |=  PM_AVDD_WR_FB_SEL_MASK; // Select High FB
          newDVBx = 1; // Not 0 here, just to make sure it's larger then the maximum of PM_AVDD_WR_FB_RATIO_LOW
        }
        // AVDD_WL supports dual feedback
        else if((regulator->name == PM_AVDD_WL) && (regulator->feedback_ratio == PM_AVDD_WL_FB_RATIO_LOW)){
          regulator->feedback_ratio = PM_AVDD_WL_FB_RATIO_HIGH;
          eeprom_write_float(&PM_AVDD_WL_FB_RATIO, regulator->feedback_ratio);
          eeprom_busy_wait();
          PM_AVDD_WL_FB_SEL_POUT |=  PM_AVDD_WL_FB_SEL_MASK; // Select High FB
          newDVBx = 1; // Not 0 here, just to make sure it's larger then the maximum of PM_AVDD_WL_FB_RATIO_LOW
        }
        else
          newDVBx = _BV(5) - 1;
      }
      else
        newDVBx = oldDVBx + 1;
    }
    else if(_mode == PM_ADJUST_MODE_DECREMENT){
      if((int8_t)oldDVBx - 1 < 0){
        // AVDD_WR supports dual feedback
             if((regulator->name == PM_AVDD_WR) && (regulator->feedback_ratio == PM_AVDD_WR_FB_RATIO_HIGH)){
          regulator->feedback_ratio = PM_AVDD_WR_FB_RATIO_LOW;
          eeprom_write_float(&PM_AVDD_WR_FB_RATIO, regulator->feedback_ratio);
          eeprom_busy_wait();
          PM_AVDD_WR_FB_SEL_POUT &= ~PM_AVDD_WR_FB_SEL_MASK; // Select Low FB
          newDVBx = _BV(5) - 2; // Not _BV(5) - 1 here, just to make sure it's smaller then the manimum of PM_AVDD_WL_FB_RATIO_HIGH
        }
        // AVDD_WL supports dual feedback
        else if((regulator->name == PM_AVDD_WL) && (regulator->feedback_ratio == PM_AVDD_WL_FB_RATIO_HIGH)){
          regulator->feedback_ratio = PM_AVDD_WL_FB_RATIO_LOW;
          eeprom_write_float(&PM_AVDD_WL_FB_RATIO, regulator->feedback_ratio);
          eeprom_busy_wait();
          PM_AVDD_WL_FB_SEL_POUT &= ~PM_AVDD_WL_FB_SEL_MASK; // Select Low FB
          newDVBx = _BV(5) - 2; // Not _BV(5) - 1 here, just to make sure it's smaller then the manimum of PM_AVDD_WL_FB_RATIO_HIGH
        }
        else
          newDVBx = 0;
      }
      else
        newDVBx = oldDVBx - 1;
    }
    else
      newDVBx = oldDVBx;

    PM_UpdateReg(regulator->value_reg, newDVBx, regulator->value_mask);
    
  }

  /**
   * Function for checking if the target is enabled
   */
  static inline bool PM_Is_Enabled(const uint8_t _target) { 
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
  static inline uint16_t PM_Read_Voltage(const uint8_t _target) { 
    regulator_structure_t *regulator = PM_Find_Target(_target);

    /* No target found, simply ignore the function call */
    if(!regulator->name || !regulator->adjustable)
      return -1;

    /* Otherwise we read the voltage */
    return PM_Decode_DVBx(regulator, PM_ReadReg(regulator->value_reg) & regulator->value_mask);
  }

  /**
   * Function for enabling the voltage
   */
  static inline void PM_Enable(const uint8_t _target) { 
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
  static inline void PM_Disable(const uint8_t _target) { 
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
      // Save the DVBx if it's adjustable
      if(regulator->adjustable){
        uint8_t DVBx = PM_ReadReg(regulator->value_reg) & regulator->value_mask;
        eeprom_write_byte(regulator->DVBx_addr, DVBx);
        eeprom_busy_wait();
      }

      // Save the state
      uint8_t status = PM_ReadReg(regulator->on_off_reg) & regulator->on_off_mask;
      eeprom_write_byte(regulator->status_addr, status);
      eeprom_busy_wait();

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
      // Load the feedback ratio for AVDD_WR and AVDD_WL
      if(regulator->name == PM_AVDD_WR){
        regulator->feedback_ratio = eeprom_read_float(&PM_AVDD_WR_FB_RATIO);
        if(regulator->feedback_ratio == PM_AVDD_WR_FB_RATIO_LOW)
          PM_AVDD_WR_FB_SEL_POUT &= ~PM_AVDD_WR_FB_SEL_MASK; // Select Low FB
        else
          PM_AVDD_WR_FB_SEL_POUT |=  PM_AVDD_WR_FB_SEL_MASK; // Select High FB
      }
      else if(regulator->name == PM_AVDD_WL){
        regulator->feedback_ratio = eeprom_read_float(&PM_AVDD_WL_FB_RATIO);
        if(regulator->feedback_ratio == PM_AVDD_WL_FB_RATIO_LOW)
          PM_AVDD_WL_FB_SEL_POUT &= ~PM_AVDD_WL_FB_SEL_MASK; // Select Low FB
        else
          PM_AVDD_WL_FB_SEL_POUT |=  PM_AVDD_WL_FB_SEL_MASK; // Select High FB
      }

      // Restore the DVBs if it's adjustable
      if(regulator->adjustable){
        uint8_t DVBx = eeprom_read_byte(regulator->DVBx_addr);
        PM_UpdateReg(regulator->value_reg, DVBx, regulator->value_mask);
      }

      // Restore the state
      uint8_t status = eeprom_read_byte(regulator->status_addr);
      PM_UpdateReg(regulator->on_off_reg, status, regulator->on_off_mask);

      regulator++;
    }
  }

  /**
   * Function for turning on all the voltages
   */
  static inline void PM_EnableAll(void)
  {
    /* Enable the low voltages first */
    PM_Enable(PM_VDD);
    PM_Enable(PM_AVDD_SRAM);
    PM_Enable(PM_AVDD_RRAM);

    /* Enable the high voltages second */
    PM_Enable(PM_3V3);
    PM_Enable(PM_AVDD_WL);
    PM_Enable(PM_AVDD_WR);
  }
  
  /**
   * Function for turning off all the voltages
   */
  static inline void PM_DisableAll(void)
  {
    /* Disable the high voltages first */
    PM_Disable(PM_3V3);
    PM_Disable(PM_AVDD_WR);
    PM_Disable(PM_AVDD_WL);

    /* Disable the low voltages second */
    PM_Disable(PM_VDD);
    PM_Disable(PM_AVDD_SRAM);
    PM_Disable(PM_AVDD_RRAM);
  }

  /**
   * Interrupt functions for WAKE pin
   */
  ISR(INT0_vect){
    if(PM_WAKE_PIN & PM_WAKE_MASK){
      /* Reset power voltages */
      PM_ClearIRQ();
      PM_Load();
      //PM_EnableAll();

      /* Give some time for the voltage to settle */
      _delay_ms(500);

      /* Enable Protocols */
      SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING | SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
      SW_Init();

      /* Enable Board Components */
      TC_Init();
      LEDs_Init();
      DAC_Init();
      Dataflash_Init();
    }
    else
    {
      /* Feedback Selects */
      PM_AVDD_WR_FB_SEL_DDR &= ~PM_AVDD_WR_FB_SEL_MASK; // Set it as input
      PM_AVDD_WL_FB_SEL_DDR &= ~PM_AVDD_WL_FB_SEL_MASK; // Set it as input

      /* Disable Protocols */
      SPI_ShutDown();
      SW_ShutDown();

      /* Disable Board Components */
      TC_ShutDown();
      LEDs_ShutDown();
      DAC_ShutDown();
      Dataflash_ShutDown();
    }
  }

  /**
   * Interrupt functions for NIRQ pin
   */
  ISR(INT1_vect){
    /* Read IRQ */
    //uint8_t status = PM_ReadIRQ();
    
    /* Do things accordingly */
  }

  /**
   * Function for initializing the PM
   */
  static inline void PM_Init(void)
  {
    /* Set FB for both WR and WL low so the voltages are low */
    PM_AVDD_WR_FB_SEL_POUT &= ~PM_AVDD_WR_FB_SEL_MASK; // Select Low FB
    PM_AVDD_WR_FB_SEL_DDR  |=  PM_AVDD_WR_FB_SEL_MASK; // Set it as output
    PM_AVDD_WL_FB_SEL_POUT &= ~PM_AVDD_WL_FB_SEL_MASK; // Select Low FB
    PM_AVDD_WL_FB_SEL_DDR  |=  PM_AVDD_WL_FB_SEL_MASK; // Set it as output

    /* Set interrupt pins as input and enables the pull-up resistor */
    PM_WAKE_POUT  |=  PM_WAKE_MASK ; // Enable the pull up resistor
    PM_WAKE_DDR   &= ~PM_WAKE_MASK ; // Set it as input
    PM_NIRQ_POUT  |=  PM_NIRQ_MASK ; // Enable the pull up resistor
    PM_NIRQ_DDR   &= ~PM_NIRQ_MASK ; // Set it as input

    /* Configure Interrupt Sense */
    PM_WAKE_INT_TYPE_REG = (PM_WAKE_INT_TYPE_REG & (~PM_WAKE_INT_TYPE_MASK)) | (1 << PM_WAKE_INT_TYPE_LOC); // Any edge detection
    PM_NIRQ_INT_TYPE_REG = (PM_NIRQ_INT_TYPE_REG & (~PM_NIRQ_INT_TYPE_MASK)) | (0 << PM_NIRQ_INT_TYPE_LOC); // Low level detection

    /* Enable External Interrupt Mask Register */
    PM_WAKE_INT_REG |= PM_WAKE_INT_MASK;
    PM_NIRQ_INT_REG |= PM_NIRQ_INT_MASK;
    
    /* Run interrupt in case it was already powered up */
    if(PM_WAKE_PIN & PM_WAKE_MASK)
      INT0_vect();
  }
    

#endif
