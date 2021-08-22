/*
   Board LEDs driver for the RRAM Testchip
*/

#ifndef __LEDS_RRAM_H__
#define __LEDS_RRAM_H__

  /* Includes: */
  #include <util/delay.h>

  /* Enable C linkage for C++ Compilers: */
  #if defined(__cplusplus)
    extern "C" {
  #endif
  
  /* Preprocessor Checks: */
  #if !defined(INCLUDE_FROM_LEDS_H)
    #error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
  #endif
  
  #define LEDS_PORT        PORTD
  #define LEDS_DDR         DDRD
  #define LEDMASK_RX       _BV(4)
  #define LEDMASK_TX       _BV(5)
  #define LEDS_ALL_LEDS    (LEDMASK_TX | LEDMASK_RX)
  #define LEDS_NO_LEDS     ~LEDS_ALL_LEDS
  #define LEDS_PULSE_MS    3
  
  /* Pulse generation counters to keep track of the number of milliseconds remaining for each pulse type */
  uint8_t TxLEDPulse; /**< Milliseconds remaining for data Tx LED pulse */
  uint8_t RxLEDPulse; /**< Milliseconds remaining for data Rx LED pulse */

  /* Inline Functions: */
  #if !defined(__DOXYGEN__)
  static inline void LEDs_ShutDown(void)
  {
    LEDS_PORT |=  LEDS_ALL_LEDS; // Turn off all LEDs after shutdown
    LEDS_DDR  &= ~LEDS_ALL_LEDS; // Set it as input
  }
  
  static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
  {
    LEDS_PORT &= ~LEDMask;
  }
  
  static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
  {
    LEDS_PORT |=  LEDMask;
  }
  
  static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
  {
    LEDS_PORT ^=  LEDMask;
  }
  
  static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
  {
    LEDS_PORT = ((LEDS_PORT | LEDS_ALL_LEDS) & ~LEDMask);
  }
  
  static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
  {
    LEDS_PORT = ((LEDS_PORT | ActiveMask) & ~LEDMask);
  }

  static inline void LEDs_Blink(const uint8_t duration, const uint8_t times)
  {
    for(uint8_t i=0;i<times;i++){
      LEDs_TurnOnLEDs(LEDMASK_RX);
      _delay_ms(duration);
      LEDs_TurnOffLEDs(LEDMASK_RX);
      _delay_ms(duration);
      LEDs_TurnOnLEDs(LEDMASK_TX);
      _delay_ms(duration);
      LEDs_TurnOffLEDs(LEDMASK_TX);
      _delay_ms(duration);
    }
  }
  
  static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
  static inline uint8_t LEDs_GetLEDs(void)
  {
    return (LEDS_PORT & LEDS_ALL_LEDS);
  }

  static inline void LEDs_Init(void)
  {
    LEDS_PORT |=  LEDS_ALL_LEDS; // Turn off all LEDs by default
    LEDS_DDR  |=  LEDS_ALL_LEDS; // Set it as output

    LEDs_Blink(25,10);
  }
  #endif
  
  /* Disable C linkage for C++ Compilers: */
  #if defined(__cplusplus)
  }
  #endif
    
#endif
