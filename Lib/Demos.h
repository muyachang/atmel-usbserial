
#ifndef __DEMOS_H__
#define __DEMOS_H__

    /* Data structure */
    typedef struct {
      const char    name[24];      // Demo name
      const uint8_t sector_number; // Location in side the dataflash
      const uint8_t size;          // Demo Size (KB)
    } demos_structure_t;

    /* Regulator Map */
    __attribute__((section(".eeprom"))) demos_structure_t demos_map[] = {
      // Name                  | Sector Number | Demo Size
      { "user 0"               ,        0*2+1  ,       128},
      { "user 1"               ,        1*2+1  ,       128},
      { "user 2"               ,        2*2+1  ,       128},
      { "user 3"               ,        3*2+1  ,       128},
      { "user 4"               ,        4*2+1  ,       128},
      { "apb_mux_tests"        ,        5*2+1  ,       128},
      { "debug_tests"          ,        6*2+1  ,       128},
      { "default_slaves_tests" ,        7*2+1  ,       128},
      { "dhry"                 ,        8*2+1  ,       128},
      { "dualtimer_demo"       ,        9*2+1  ,       128},
      { "gpio_driver_tests"    ,       10*2+1  ,       128},
      { "gpio_tests"           ,       11*2+1  ,       128},
      { "hello"                ,       12*2+1  ,       128},
      { "interrupt_demo"       ,       13*2+1  ,       128},
      { "memory_tests"         ,       14*2+1  ,       128},
      { "romtable_tests"       ,       15*2+1  ,       128},
      { "self_reset_demo"      ,       16*2+1  ,       128},
      { "sleep_demo"           ,       17*2+1  ,       128},
      { "timer_driver_tests"   ,       18*2+1  ,       128},
      { "timer_tests"          ,       19*2+1  ,       128},
      { "trace_tests"          ,       20*2+1  ,       128},
      { "uart_driver_tests"    ,       21*2+1  ,       128},
      { "uart_tests"           ,       22*2+1  ,       128},
      { "watchdog_demo"        ,       23*2+1  ,       128}
    };

#endif
