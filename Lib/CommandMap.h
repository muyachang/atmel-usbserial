
#ifndef _COMMANDMAP_H_
#define _COMMANDMAP_H_

/* argv[0] */
#define CM_PM     0x41
#define CM_DAC    0x42
#define CM_DF     0x43
#define CM_EEPROM 0x44
#define CM_LED    0x45
#define CM_TC     0x46
#define CM_DEMO   0x47
#define CM_RRAM   0x48
#define CM_VECTOR 0x49

/* argv[1] */
#define CM_PM_LIST    0x41
#define CM_PM_CLEAR   0x42
#define CM_PM_STATUS  0x43
#define CM_PM_SAVE    0x44
#define CM_PM_LOAD    0x45
#define CM_PM_ALLON   0x46
#define CM_PM_ALLOFF  0x47
#define CM_PM_RESET   0x48
#define CM_PM_ENABLE  0x49
#define CM_PM_DISABLE 0x4A
#define CM_PM_INCR    0x4B
#define CM_PM_DECR    0x4C
#define CM_PM_PLUS    0x4D
#define CM_PM_MINUS   0x4E
#define CM_PM_SET     0x4F
#define CM_PM_GET     0x50

#define CM_DAC_LIST    0x41
#define CM_DAC_INCR    0x42
#define CM_DAC_DECR    0x43
#define CM_DAC_PLUS    0x44
#define CM_DAC_MINUS   0x45
#define CM_DAC_SET     0x46
#define CM_DAC_GET     0x47

#define CM_DF_STATUS     0x41
#define CM_DF_ID         0x42
#define CM_DF_RESET      0x43
#define CM_DF_READ       0x44
#define CM_DF_WRITE      0x45
#define CM_DF_ERASE      0x46
#define CM_DF_PROTECT    0x47
#define CM_DF_BLANKCHECK 0x48

#define CM_DF_PROTECT_ENABLE  0x41
#define CM_DF_PROTECT_DISABLE 0x42
#define CM_DF_PROTECT_STATUS  0x43
#define CM_DF_PROTECT_ALL     0x44
#define CM_DF_PROTECT_NONE    0x46
#define CM_DF_PROTECT_ADD     0x47
#define CM_DF_PROTECT_REMOVE  0x48

#define CM_EEPROM_READ  0x41
#define CM_EEPROM_WRITE 0x42

#define CM_LED_ENABLE  0x41
#define CM_LED_DISABLE 0x42
#define CM_LED_TOGGLE  0x43

#define CM_TC_CONNECT  0x41
#define CM_TC_RESET    0x42
#define CM_TC_READ     0x43
#define CM_TC_WRITE    0x44

#define CM_DEMO_LIST    0x41
#define CM_DEMO_LOAD    0x42
#define CM_DEMO_RUN     0x43
#define CM_DEMO_ANALYZE 0x44

#endif
