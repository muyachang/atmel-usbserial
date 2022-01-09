
#ifndef __DEMOS_H__
#define __DEMOS_H__

#define DEMO_SECTOR_OFFSET 1 // Sector offset in DF for the demos
#define DEMO_SECTOR_SIZE   2 // Sector size in DF for each demo

    /* Data structure */
    typedef struct {
      const char    name[24];      // Demo name
      const uint8_t sector_number; // Location in side the dataflash
            uint8_t size;          // Demo Size (KB)
    } demos_structure_t;

    /* Regulator Map */
    __attribute__((section(".eeprom"))) demos_structure_t demos_map[] = {
      // Name                  | Sector Number                              | Demo Size
      { "icsrl_uart_server"    , DEMO_SECTOR_OFFSET +  0 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "user 1"               , DEMO_SECTOR_OFFSET +  1 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "user 2"               , DEMO_SECTOR_OFFSET +  2 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "user 3"               , DEMO_SECTOR_OFFSET +  3 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "user 4"               , DEMO_SECTOR_OFFSET +  4 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "apb_mux_tests"        , DEMO_SECTOR_OFFSET +  5 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "debug_tests"          , DEMO_SECTOR_OFFSET +  6 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "default_slaves_tests" , DEMO_SECTOR_OFFSET +  7 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "dhry"                 , DEMO_SECTOR_OFFSET +  8 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "dualtimer_demo"       , DEMO_SECTOR_OFFSET +  9 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "gpio_driver_tests"    , DEMO_SECTOR_OFFSET + 10 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "gpio_tests"           , DEMO_SECTOR_OFFSET + 11 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "hello"                , DEMO_SECTOR_OFFSET + 12 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "interrupt_demo"       , DEMO_SECTOR_OFFSET + 13 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "memory_tests"         , DEMO_SECTOR_OFFSET + 14 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "romtable_tests"       , DEMO_SECTOR_OFFSET + 15 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "self_reset_demo"      , DEMO_SECTOR_OFFSET + 16 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "sleep_demo"           , DEMO_SECTOR_OFFSET + 17 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "timer_driver_tests"   , DEMO_SECTOR_OFFSET + 18 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "timer_tests"          , DEMO_SECTOR_OFFSET + 19 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "trace_tests"          , DEMO_SECTOR_OFFSET + 20 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "uart_driver_tests"    , DEMO_SECTOR_OFFSET + 21 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "uart_tests"           , DEMO_SECTOR_OFFSET + 22 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64},
      { "watchdog_demo"        , DEMO_SECTOR_OFFSET + 23 * DEMO_SECTOR_SIZE , DEMO_SECTOR_SIZE * 64}
    };

#endif
