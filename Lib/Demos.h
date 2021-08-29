
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
      { "user"                 ,        0*2+1},
      //{ "apb_mux_tests"        ,        1*2+1},
      //{ "debug_tests"          ,        2*2+1},
      { "default_slaves_tests" ,        3*2+1},
      { "dhry"                 ,        4*2+1},
      { "dualtimer_demo"       ,        5*2+1},
      //{ "gpio_driver_tests"    ,        6*2+1},
      //{ "gpio_tests"           ,        7*2+1},
      { "hello"                ,        8*2+1},
      //{ "interrupt_demo"       ,        9*2+1},
      //{ "memory_tests"         ,       10*2+1},
      //{ "romtable_tests"       ,       11*2+1},
      //{ "rtx_demo"             ,       12*2+1},
      //{ "self_reset_demo"      ,       13*2+1},
      //{ "sleep_demo"           ,       14*2+1},
      //{ "timer_driver_tests"   ,       15*2+1},
      //{ "timer_tests"          ,       16*2+1},
      //{ "trace_tests"          ,       17*2+1},
      //{ "uart_driver_tests"    ,       18*2+1},
      //{ "uart_tests"           ,       19*2+1},
      //{ "watchdog_demo"        ,       20*2+1}
    };

#endif
