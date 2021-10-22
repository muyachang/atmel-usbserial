
#ifndef __TCCONF_H__
#define __TCCONF_H__

#define TC_CONFIG_START_ADDRESS 0x20070000  // Start at 448 KB
#define TC_CONFIG_SIZE          0x00010000  // 64 KB for each TC

    /* Data structure */
    typedef struct {
            char     date[20];    // Date saved
      const uint16_t page_number; // Location in side the dataflash
    } tc_conf_structure_t;

    /* Regulator Map */
    __attribute__((section(".eeprom"))) tc_conf_structure_t tc_conf_map[] = {
      //  Date Saved | Page Number 
      { "01/21/1991_00:00:00" ,   0*128+49*128},
      { "01/21/1991_00:00:00" ,   1*128+49*128},
      { "01/21/1991_00:00:00" ,   2*128+49*128},
      { "01/21/1991_00:00:00" ,   3*128+49*128},
      { "01/21/1991_00:00:00" ,   4*128+49*128},
      { "01/21/1991_00:00:00" ,   5*128+49*128},
      { "01/21/1991_00:00:00" ,   6*128+49*128},
      { "01/21/1991_00:00:00" ,   7*128+49*128},
      { "01/21/1991_00:00:00" ,   8*128+49*128},
      { "01/21/1991_00:00:00" ,   9*128+49*128},
    };

#endif
