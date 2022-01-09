/*
   Serial Wire Debug driver for the RRAM Testchip
*/

#ifndef __SWD_RRAM_H__
#define __SWD_RRAM_H__

  /* Includes: */
  #include <util/delay.h>

  /* Private Interface - For use in library only: */
  #if !defined(__DOXYGEN__)
    /* Macros: */
      /*
       * SW pins 
       */
      #define SW_DIO_PIN   PINC
      #define SW_DIO_POUT  PORTC
      #define SW_DIO_DDR   DDRC
      #define SW_DIO_MASK  _BV(6)

      #define SW_CLK_PIN   PINC
      #define SW_CLK_POUT  PORTC
      #define SW_CLK_DDR   DDRC
      #define SW_CLK_MASK  _BV(7)

      /*
       * SW responses
       */
      #define SW_CMD_JTAG_TO_SWD 0xE79E

      /* Phase 1: 8-bit Request Fields */ 
      #define SW_REQ_START_MASK (1 << 0)
      #define SW_REQ_AP_MASK    (1 << 1)
      #define SW_REQ_DP_MASK    (0 << 1)
      #define SW_REQ_READ_MASK  (1 << 2)
      #define SW_REQ_WRITE_MASK (0 << 2)
      #define SW_REQ_STOP_MASK  (0 << 6)
      #define SW_REQ_PARK_MASK  (1 << 7)

      /* Phase 2: 3-bit Acknowledgement Fields */ 
      #define SW_DP_ACK_OK      (1 << 0)
      #define SW_DP_ACK_WAIT    (1 << 1)
      #define SW_DP_ACK_FAULT   (1 << 2)
      
      /* AP Register Addresses */
      #define SW_REG_AP_CSW       0x00
      #define SW_REG_AP_TAR       0x04
      #define SW_REG_AP_DRW       0x0c
      #define SW_REG_AP_BD0       0x10
      #define SW_REG_AP_BD1       0x14
      #define SW_REG_AP_BD2       0x18
      #define SW_REG_AP_BD3       0x1c
      #define SW_REG_AP_CFG       0xf4
      #define SW_REG_AP_BASE      0xf8
      #define SW_REG_AP_IDR       0xfc

      /* DP Register Addresses */
      #define SW_REG_DP_DPIDR     0x0
      #define SW_REG_DP_ABORT     0x0 
      #define SW_REG_DP_CTRLSTAT  0x4
      #define SW_REG_DP_DLCR      0x4
      #define SW_REG_DP_TARGETID  0x4
      #define SW_REG_DP_HALTEV    0x4
      #define SW_REG_DP_RESEND    0x8
      #define SW_REG_DP_SELECT    0x8
      #define SW_REG_DP_RDBUFF    0xc
      #define SW_REG_DP_TARGETSEL 0xc

      /* AP CSW Register Fields */
      #define SW_REG_AP_CSW_PROT_MASTER_CORE_MASK ((uint32_t)0<<29)
      #define SW_REG_AP_CSW_PROT_MASTER_DBG_MASK  ((uint32_t)1<<29)
      #define SW_REG_AP_CSW_PROT_CACH_MASK        ((uint32_t)1<<27)
      #define SW_REG_AP_CSW_PROT_BUFF_MASK        ((uint32_t)1<<26)
      #define SW_REG_AP_CSW_PROT_USER_MASK        ((uint32_t)0<<25)
      #define SW_REG_AP_CSW_PROT_PRIV_MASK        ((uint32_t)1<<25)
      #define SW_REG_AP_CSW_INCR_OFF_MASK         ((uint32_t)0<< 4)
      #define SW_REG_AP_CSW_INCR_SINGLE_MASK      ((uint32_t)1<< 4)
      #define SW_REG_AP_CSW_INCR_PACK_MASK        ((uint32_t)2<< 4)
      #define SW_REG_AP_CSW_SIZE_BYTE_MASK        ((uint32_t)0<< 0) 
      #define SW_REG_AP_CSW_SIZE_HALFWORD_MASK    ((uint32_t)1<< 0)
      #define SW_REG_AP_CSW_SIZE_WORD_MASK        ((uint32_t)2<< 0)

      /* DP CTRLSTAT Register Fields */
      #define SW_REG_DP_CTRLSTAT_CSYSPWRUPACK_MASK ((uint32_t)1<<31) //System power up ack, RO
      #define SW_REG_DP_CTRLSTAT_CSYSPWRUPREQ_MASK ((uint32_t)1<<30) //System power up req, RW
      #define SW_REG_DP_CTRLSTAT_CDBGPWRUPACK_MASK ((uint32_t)1<<29) //Debug  power up ack, RO
      #define SW_REG_DP_CTRLSTAT_CDBGPWRUPREQ_MASK ((uint32_t)1<<28) //Debug  power up req, RW
      #define SW_REG_DP_CTRLSTAT_CDBGRSTACK_MASK   ((uint32_t)1<<27) //Debug  reset    ack, RO
      #define SW_REG_DP_CTRLSTAT_CDBGRSTREQ_MASK   ((uint32_t)1<<26) //Debug  reset    req, RW

      /* ARMv6M and ARMv7M Architectural Debug Register Definitions */
      #define SW_REG_DHCSR_ADDR      0xE000EDF0
      #define SW_REG_DBGKEY          0xA05F0000
      #define SW_REG_S_LOCKUP_MASK   ((uint32_t)1<<19)
      #define SW_REG_S_SLEEP_MASK    ((uint32_t)1<<18)
      #define SW_REG_S_HALT_MASK     ((uint32_t)1<<17)
      #define SW_REG_S_REGRDY_MASK   ((uint32_t)1<<16)
      #define SW_REG_C_MASKINTS_MASK ((uint32_t)1<<3)
      #define SW_REG_C_STEP_MASK     ((uint32_t)1<<2)
      #define SW_REG_C_HALT_MASK     ((uint32_t)1<<1)
      #define SW_REG_C_DEBUGEN_MASK  ((uint32_t)1<<0)
      #define SW_REG_DCRDR_ADDR      0xE000EDF8
      #define SW_REG_DEMCR_ADDR      0xE000EDFC
      #define SW_REG_AIRCR_ADDR      0xE000ED0C
      #define SW_REG_RSTINFO_ADDR    0x4001F010

      /* ROM Address */
      #define SW_ROM_ADDR 0x00000000

      #define SW_DELAY 0
  #endif

  /* Public Interface - May be used in end-application: */

  /* Inline Functions: */

    /**
     * Calculate the parity of the given number
     */
    bool getParity(uint32_t n)
    {
      bool parity = 0;
      while (n) {
        parity = !parity; 
        n = n & (n - 1);
      }    
      return parity;
    }
 
    /**
     *
     */
    static inline void SW_Init(void)
    {
      SW_DIO_POUT |=  SW_DIO_MASK; // Enable the pull-up resistor
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as an input 

      SW_CLK_POUT &= ~SW_CLK_MASK; // Pull low CLK
      SW_CLK_DDR  |=  SW_CLK_MASK; // Set it as an output
    }

    /**
     *
     */
    static inline void SW_ShutDown(void)
    {
      SW_DIO_POUT &= ~SW_DIO_MASK; // Disable the Pull-up resistor 
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as an input 

      SW_CLK_POUT &= ~SW_CLK_MASK; // Disable the Pull-up resistor
      SW_CLK_DDR  &= ~SW_CLK_MASK; // Set it as an input 
    }

    /**
     *
     */
    static inline void SW_PulseClock(uint8_t cycles)
    {
      for(uint8_t i=0;i<cycles;i++){
        _delay_us(SW_DELAY);
        SW_CLK_POUT ^= SW_CLK_MASK;
        _delay_us(SW_DELAY);
        SW_CLK_POUT ^= SW_CLK_MASK;
        _delay_us(SW_DELAY);
      }
    }

    /**
     *
     */
    static inline void SW_LineReset(void)
    {
      SW_DIO_POUT |=  SW_DIO_MASK; // Pull high DIO
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as an output 
      SW_PulseClock(50);

      SW_DIO_POUT &= ~SW_DIO_MASK; // Pull low DIO
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as an output 
      SW_PulseClock(50);

      SW_DIO_POUT |=  SW_DIO_MASK; // Enable the pull-up resistor
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as an input 
    }

    /**
     *
     */
    static inline void SW_Send(uint32_t _data, uint8_t _bits)
    {
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as an output 

      /* Send the bits part */
      for(uint8_t i = 0; i<_bits; i++){
        /* DIO */
        if((_data >> i) & 1)
          SW_DIO_POUT |=  SW_DIO_MASK;
        else
          SW_DIO_POUT &= ~SW_DIO_MASK;

        /* Toggle CLK */
        SW_PulseClock(1);
      }

      SW_DIO_POUT |=  SW_DIO_MASK; // Enable the pull-up resistor
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as an input 
    }

    /**
     *
     */
    static inline uint32_t SW_Receive(uint8_t _bits)
    {
      uint32_t result = 0;

      /* Receive the byte part */
      for(uint8_t i = 0; i<_bits; i++){
        result |= (SW_DIO_PIN & SW_DIO_MASK)? (uint32_t)1<<i: 0; // Sample DIO 
        SW_PulseClock(1);
      }

      return result;
    }

    /**
     *
     */
    static inline uint32_t SW_SendPacket(uint8_t _APnDP, uint8_t _RnW, uint8_t _reg, uint32_t _data)
    {
      uint8_t  request;  // 8-bit request (host->target)
      uint8_t  ack;      // 3-bit acknowledge response (target->host)
      uint32_t data = 0; // 32 bit wdata/rdata (host->target / target->host)
      bool     parity;

      // Build the request
      parity = getParity(_reg>>2) ^ getParity(_RnW) ^ getParity(_APnDP);
      request = SW_REQ_START_MASK          | // bit 0
                _APnDP                     | // bit 1
                _RnW                       | // bit 2
                ((_reg>>2) << 3)           | // bit 3-4
                parity << 5                | // bit 5
                SW_REQ_STOP_MASK           | // bit 6
                SW_REQ_PARK_MASK           ; // bit 7
                
      // Send the request and wait for the acknowledgement
      ack = SW_DP_ACK_WAIT;
      do {
        SW_Send(request, 8); // Request
        SW_PulseClock(1); // TM
        if((ack = SW_Receive(3)) == SW_DP_ACK_WAIT) // Ack
          SW_PulseClock(1); // TM
      } while(ack == SW_DP_ACK_WAIT);

      _delay_us(5*SW_DELAY);

      // Read/Write
      if(_RnW == SW_REQ_WRITE_MASK){
        SW_PulseClock(1); // TM
        SW_Send(          _data , 32); // Write the data
        SW_Send(getParity(_data),  1); // Parity 
      }
      else{
        data = SW_Receive(32); // Receive the data 
        SW_PulseClock(1); // Parity
        SW_PulseClock(1); // TM
      }

      _delay_us(5*SW_DELAY);

      return data;
    }

    /**
     *
     */
    static inline void SW_JTAGToSW(void)
    {
      SW_DIO_POUT |=  SW_DIO_MASK; // Pull up DIO
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as an output 
      SW_PulseClock(50);

      SW_Send(SW_CMD_JTAG_TO_SWD, 16);

      SW_DIO_POUT |=  SW_DIO_MASK; // Pull up DIO
      SW_DIO_DDR  |=  SW_DIO_MASK; // Set it as an output 
      SW_PulseClock(50);

      SW_DIO_POUT |=  SW_DIO_MASK; // Enable the pull-up resistor
      SW_DIO_DDR  &= ~SW_DIO_MASK; // Set it as an input 
    }

    /**
     *
     */
    static inline void SW_DAPPowerUp(void)
    {
      SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_WRITE_MASK, SW_REG_DP_CTRLSTAT, 
                    SW_REG_DP_CTRLSTAT_CSYSPWRUPREQ_MASK | SW_REG_DP_CTRLSTAT_CDBGPWRUPREQ_MASK);

      uint32_t state;
      do{
        state = SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_READ_MASK, SW_REG_DP_CTRLSTAT , 0);
      } while( (state & 0xF0000000) != (SW_REG_DP_CTRLSTAT_CSYSPWRUPREQ_MASK | SW_REG_DP_CTRLSTAT_CSYSPWRUPACK_MASK |
                                        SW_REG_DP_CTRLSTAT_CDBGPWRUPREQ_MASK | SW_REG_DP_CTRLSTAT_CDBGPWRUPACK_MASK));
    }

    /**
     *
     */
    static inline void SW_DAPPowerDown(void)
    {
      SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_WRITE_MASK, SW_REG_DP_CTRLSTAT, 0);

      uint32_t state;
      do{
        state = SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_READ_MASK, SW_REG_DP_CTRLSTAT , 0);
      } while( (state & 0xF0000000) != 0);
    }

    /**
     *
     */
    static inline void SW_WriteMem(uint32_t _address, uint32_t _size, uint32_t _data)
    {
      // Ensure CSW is set up
      SW_SendPacket(SW_REQ_AP_MASK, SW_REQ_WRITE_MASK, SW_REG_AP_CSW,
                    SW_REG_AP_CSW_PROT_MASTER_DBG_MASK | SW_REG_AP_CSW_PROT_PRIV_MASK | SW_REG_AP_CSW_INCR_OFF_MASK | _size);

      // Write TAR
      SW_SendPacket(SW_REQ_AP_MASK, SW_REQ_WRITE_MASK, SW_REG_AP_TAR, _address);

      // Write DRW
      uint32_t data;
      switch(_size){
        case SW_REG_AP_CSW_SIZE_BYTE_MASK:
          data = _data & 0xFF;
          data = data | data << 8 | data << 16 | data << 24; 
          break;
        case SW_REG_AP_CSW_SIZE_HALFWORD_MASK:
          data = _data & 0xFFFF;
          data = data | data << 16;
          break;
        case SW_REG_AP_CSW_SIZE_WORD_MASK:
          data = _data;
          break;
      } 
      SW_SendPacket(SW_REQ_AP_MASK, SW_REQ_WRITE_MASK, SW_REG_AP_DRW, data);

      // Read RdBuff to flush the write
      SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_READ_MASK, SW_REG_DP_RDBUFF, 0);
    }

    /**
     *
     */
    static inline uint32_t SW_ReadMem(uint32_t _address, uint32_t _size)
    {
      // Ensure CSW is set up
      SW_SendPacket(SW_REQ_AP_MASK, SW_REQ_WRITE_MASK, SW_REG_AP_CSW,
                    SW_REG_AP_CSW_PROT_MASTER_DBG_MASK | SW_REG_AP_CSW_PROT_PRIV_MASK | SW_REG_AP_CSW_INCR_OFF_MASK | _size);

      // Write TAR
      SW_SendPacket(SW_REQ_AP_MASK, SW_REQ_WRITE_MASK, SW_REG_AP_TAR, _address);

      // Read DRW
      SW_SendPacket(SW_REQ_AP_MASK, SW_REQ_READ_MASK, SW_REG_AP_DRW, 0);
      uint32_t data = SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_READ_MASK, SW_REG_DP_RDBUFF, 0);
      switch(_size){
        case SW_REG_AP_CSW_SIZE_BYTE_MASK:
          data = data | data << 8 | data << 16 | data << 24; 
          break;
        case SW_REG_AP_CSW_SIZE_HALFWORD_MASK:
          data = data | data << 16;
          break;
        case SW_REG_AP_CSW_SIZE_WORD_MASK:
          data = data;
          break;
      }

      return data;
    }

    /**
     *
     */
    static inline void SW_HaltCore(void)
    {
      // Halt the core
      SW_WriteMem(SW_REG_DHCSR_ADDR, SW_REG_AP_CSW_SIZE_WORD_MASK, (SW_REG_DBGKEY | SW_REG_C_HALT_MASK | SW_REG_C_DEBUGEN_MASK));

      // Wait for core to be halted
      while((SW_ReadMem(SW_REG_DHCSR_ADDR,SW_REG_AP_CSW_SIZE_WORD_MASK) & SW_REG_S_HALT_MASK) == 0){}

      // Write 1 to bit VC_CORERESET in DEMCR
      //SW_WriteMem(SW_REG_DEMCR_ADDR, SW_REG_AP_CSW_SIZE_WORD_MASK, 1);
    }

    /**
     *
     */
    static inline void SW_UnhaltCore(void)
    {
      // Unhalt the core
      SW_WriteMem(SW_REG_DHCSR_ADDR, SW_REG_AP_CSW_SIZE_WORD_MASK, SW_REG_DBGKEY);

      // Wait for core to be halted
      while((SW_ReadMem(SW_REG_DHCSR_ADDR,SW_REG_AP_CSW_SIZE_WORD_MASK) & SW_REG_S_HALT_MASK) == 1){}
    }

    /**
     *
     */
    static inline void SW_ResetCore(void)
    {
      // Reset the target
      SW_WriteMem(SW_REG_AIRCR_ADDR, SW_REG_AP_CSW_SIZE_WORD_MASK, 0x05FA0004);

      // Write 1 to bit 0 (SYSRESETREQ caused the reset) to clear RSTINFO register so the watchdog test passes
      SW_WriteMem(SW_REG_RSTINFO_ADDR, SW_REG_AP_CSW_SIZE_WORD_MASK, 1);
    }

    /**
     *
     */
    static inline uint32_t SW_Connect(void)
    {
      SW_LineReset();
      SW_JTAGToSW();
      SW_LineReset();
      uint32_t id = SW_SendPacket(SW_REQ_DP_MASK, SW_REQ_READ_MASK, SW_REG_DP_DPIDR, 0);
      SW_DAPPowerUp();
      SW_HaltCore();
      return id;
    }

    /**
     *
     */
    static inline void SW_Disconnect(void)
    {
      SW_UnhaltCore();
      SW_DAPPowerDown();
      //SW_LineReset();
      //SW_JTAGToSW();
      //SW_LineReset();
    }

#endif
