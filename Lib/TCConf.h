
#ifndef __TCCONF_H__
#define __TCCONF_H__

#define TC_CONFIG_START_ADDRESS 0x20070000            // Start at 448 KB
#define TC_CONFIG_SIZE          0x00010000            // 64 KB for each TC
#define TC_CONFIG_DEFAULT_DATE  "--/--/----_--:--:--" // Default date
#define TC_CONFIG_SECTOR_OFFSET 49                    // Sector offset in DF for testchip configs
#define TC_CONFIG_SECTOR_SIZE   1                     // Sector size in DF for each testchip config 

    /* Data structure */
    typedef struct {
            char    date[20];    // Date saved
      const uint8_t sector_number; // Location in side the dataflash
    } tc_conf_structure_t;

    /* Regulator Map */
    __attribute__((section(".eeprom"))) tc_conf_structure_t tc_conf_map[] = {
      // Date Saved            | Sector Number 
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 0 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 1 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 2 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 3 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 4 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 5 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 6 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 7 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 8 * TC_CONFIG_SECTOR_SIZE},
      {  TC_CONFIG_DEFAULT_DATE, TC_CONFIG_SECTOR_OFFSET + 9 * TC_CONFIG_SECTOR_SIZE},
    };

#endif
