
/** \file
 *  \brief Board specific Power Management commands header for the LTC3676 .
 *
 *  Board specific Power Management commands header for the LTC3676.
 */

#ifndef __PM_CMDS_H__
#define __PM_CMDS_H__

  /* Power Management Address and Operation Mode*/
  #define PM_WR_MODE         0x78
  #define PM_RD_MODE         0x79

  /* Command Registers */
  #define PM_CMD_BUCK1       0x01
  #define PM_CMD_BUCK2       0x02
  #define PM_CMD_BUCK3       0x03
  #define PM_CMD_BUCK4       0x04
  #define PM_CMD_LDOA        0x05
  #define PM_CMD_LDOB        0x06
  #define PM_CMD_SQD1        0x07
  #define PM_CMD_SQD2        0x08
  #define PM_CMD_CNTRL       0x09
  #define PM_CMD_DVB1A       0x0A
  #define PM_CMD_DVB1B       0x0B
  #define PM_CMD_DVB2A       0x0C
  #define PM_CMD_DVB2B       0x0D
  #define PM_CMD_DVB3A       0x0E
  #define PM_CMD_DVB3B       0x0F
  #define PM_CMD_DVB4A       0x10
  #define PM_CMD_DVB4B       0x11
  #define PM_CMD_MSKIRQ      0x12
  #define PM_CMD_MSKPG       0x13
  #define PM_CMD_USER        0x14
  #define PM_CMD_HRST        0x1E
  #define PM_CMD_CLIRQ       0x1F

  /* Bit purpose for BUCKx ~ LDOx */
  #define PM_BUCK_ENABLE_MASK _BV(7)
  #define PM_LDO2_ENABLE_MASK _BV(2)
  #define PM_LDO4_ENABLE_MASK _BV(2)

  /* Bit purpose for DVBxA, DVBxB */
  #define PM_BUCK_FB_REF_MASK (0x1F << 0)

  /* Status Registers */
  #define PM_STATUS_IRQSTAT  0x15
  #define PM_STATUS_PGSTATL  0x16
  #define PM_STATUS_PGSTATRT 0x17

#endif
