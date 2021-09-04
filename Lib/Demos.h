
#ifndef __DEMOS_H__
#define __DEMOS_H__

    /* Data structure */
    typedef struct {
      const char    *name;
      const uint16_t sector_number;
    } demos_structure_t;

    /* Regulator Map */
    demos_structure_t demos_map[] = {
      // Name                  | Sector Number
      { "user 0"                 ,        0*2+1},
      { "user 1"                 ,        1*2+1},
      { "user 2"                 ,        2*2+1},
      { "user 3"                 ,        3*2+1},
      { "user 4"                 ,        4*2+1},
      //{ "apb_mux_tests"        ,        5*2+1},
      //{ "debug_tests"          ,        6*2+1},
      //{ "default_slaves_tests" ,        7*2+1},
      //{ "dhry"                 ,        8*2+1},
      //{ "dualtimer_demo"       ,        9*2+1},
      //{ "gpio_driver_tests"    ,       10*2+1},
      //{ "gpio_tests"           ,       11*2+1},
      //{ "hello"                ,       12*2+1},
      //{ "interrupt_demo"       ,       13*2+1},
      //{ "memory_tests"         ,       14*2+1},
      //{ "romtable_tests"       ,       15*2+1},
      //{ "self_reset_demo"      ,       16*2+1},
      //{ "sleep_demo"           ,       17*2+1},
      //{ "timer_driver_tests"   ,       18*2+1},
      //{ "timer_tests"          ,       19*2+1},
      //{ "trace_tests"          ,       20*2+1},
      //{ "uart_driver_tests"    ,       21*2+1},
      //{ "uart_tests"           ,       22*2+1},
      { "watchdog_demo"        ,       23*2+1}
    };

#endif
