#include <stdint.h>

typedef struct {
  const char *name;
  uint32_t speed; /* in kHZ */
  uint32_t size; /* Memory size in byte = col * row * width */
}HAL_DDR_InfoTypeDef;

typedef struct {
  uint32_t MSTR;
  uint32_t MRCTRL0;
  uint32_t MRCTRL1;
  uint32_t DERATEEN;
  uint32_t DERATEINT;
  uint32_t PWRCTL;
  uint32_t PWRTMG;
  uint32_t HWLPCTL;
  uint32_t RFSHCTL0;
  uint32_t RFSHCTL3;
  uint32_t CRCPARCTL0;
  uint32_t ZQCTL0;
  uint32_t DFITMG0;
  uint32_t DFITMG1;
  uint32_t DFILPCFG0;
  uint32_t DFIUPD0;
  uint32_t DFIUPD1;
  uint32_t DFIUPD2;
  uint32_t DFIPHYMSTR;
  uint32_t ODTMAP;
  uint32_t DBG0;
  uint32_t DBG1;
  uint32_t DBGCMD;
  uint32_t POISONCFG;
  uint32_t PCCFG;
}HAL_DDR_RegTypeDef;

typedef struct {
  uint32_t RFSHTMG;
  uint32_t DRAMTMG0;
  uint32_t DRAMTMG1;
  uint32_t DRAMTMG2;
  uint32_t DRAMTMG3;
  uint32_t DRAMTMG4;
  uint32_t DRAMTMG5;
  uint32_t DRAMTMG6;
  uint32_t DRAMTMG7;
  uint32_t DRAMTMG8;
  uint32_t DRAMTMG14;
  uint32_t ODTCFG;
}HAL_DDR_TimingTypeDef;

typedef struct {
  uint32_t ADDRMAP1;
  uint32_t ADDRMAP2;
  uint32_t ADDRMAP3;
  uint32_t ADDRMAP4;
  uint32_t ADDRMAP5;
  uint32_t ADDRMAP6;
  uint32_t ADDRMAP9;
  uint32_t ADDRMAP10;
  uint32_t ADDRMAP11;
}HAL_DDR_MapTypeDef;

typedef struct {
  uint32_t SCHED;
  uint32_t SCHED1;
  uint32_t PERFHPR1;
  uint32_t PERFLPR1;
  uint32_t PERFWR1;
  uint32_t PCFGR_0;
  uint32_t PCFGW_0;
  uint32_t PCFGQOS0_0;
  uint32_t PCFGQOS1_0;
  uint32_t PCFGWQOS0_0;
  uint32_t PCFGWQOS1_0;
#ifdef DDR_DUAL_AXI_PORT
  uint32_t PCFGR_1;
  uint32_t PCFGW_1;
  uint32_t PCFGQOS0_1;
  uint32_t PCFGQOS1_1;
  uint32_t PCFGWQOS0_1;
  uint32_t PCFGWQOS1_1;
#endif
}HAL_DDR_PerfTypeDef;

typedef struct {
  uint32_t PGCR;
  uint32_t ACIOCR;
  uint32_t DXCCR;
  uint32_t DSGCR;
  uint32_t DCR;
  uint32_t ODTCR;
  uint32_t ZQ0CR1;
  uint32_t DX0GCR;
  uint32_t DX1GCR;
#ifdef DDR_32BIT_INTERFACE
  uint32_t DX2GCR;
  uint32_t DX3GCR;
#endif
}HAL_DDR_PhyRegTypeDef;

typedef struct {
  uint32_t PTR0;
  uint32_t PTR1;
  uint32_t PTR2;
  uint32_t DTPR0;
  uint32_t DTPR1;
  uint32_t DTPR2;
  uint32_t MR0;
  uint32_t MR1;
  uint32_t MR2;
  uint32_t MR3;
}HAL_DDR_PhyTimingTypeDef;

typedef struct  {
  HAL_DDR_InfoTypeDef      info;
  HAL_DDR_RegTypeDef       c_reg;
  HAL_DDR_TimingTypeDef    c_timing;
  HAL_DDR_MapTypeDef       c_map;
  HAL_DDR_PerfTypeDef      c_perf;
  HAL_DDR_PhyRegTypeDef    p_reg;
  HAL_DDR_PhyTimingTypeDef p_timing;
}HAL_DDR_ConfigTypeDef;

HAL_DDR_ConfigTypeDef static_ddr_config = {
  .info = {
    .name = "DDR3-1066/888 bin G 1x4Gb 533MHz v1.45",
    .speed = 533000,
    .size = 0x20000000
  },

  .c_reg = {
    .MSTR = 0x00041401,
    .MRCTRL0 = 0x00000010,
    .MRCTRL1 = 0x00000000,
    .DERATEEN = 0x00000000,
    .DERATEINT = 0x00800000,
    .PWRCTL = 0x00000000,
    .PWRTMG = 0x00400010,
    .HWLPCTL = 0x00000000,
    .RFSHCTL0 = 0x00210000,
    .RFSHCTL3 = 0x00000000,
    .CRCPARCTL0 = 0x00000000,
    .ZQCTL0 = 0xC2000040,
    .DFITMG0 = 0x02060105,
    .DFITMG1 = 0x00000202,
    .DFILPCFG0 = 0x07000000,
    .DFIUPD0 = 0xC0400003,
    .DFIUPD1 = 0x00000000,
    .DFIUPD2 = 0x00000000,
    .DFIPHYMSTR = 0x00000000,
    .ODTMAP = 0x00000001,
    .DBG0 = 0x00000000,
    .DBG1 = 0x00000000,
    .DBGCMD = 0x00000000,
    .POISONCFG = 0x00000000,
    .PCCFG = 0x00000010
  },

  .c_timing = {
    .RFSHTMG = 0x0081008B,
    .DRAMTMG0 = 0x121B2414,
    .DRAMTMG1 = 0x000A041C,
    .DRAMTMG2 = 0x0608090F,
    .DRAMTMG3 = 0x0050400C,
    .DRAMTMG4 = 0x08040608,
    .DRAMTMG5 = 0x06060403,
    .DRAMTMG6 = 0x02020002,
    .DRAMTMG7 = 0x00000202,
    .DRAMTMG8 = 0x00001005,
    .DRAMTMG14 = 0x000000A0,
    .ODTCFG = 0x06000600
  },


  .c_map = {
    .ADDRMAP1 = 0x00070707,
    .ADDRMAP2 = 0x00000000,
    .ADDRMAP3 = 0x1F000000,
    .ADDRMAP4 = 0x00001F1F,
    .ADDRMAP5 = 0x06060606,
    .ADDRMAP6 = 0x0F060606,
    .ADDRMAP9 = 0x00000000,
    .ADDRMAP10 = 0x00000000,
    .ADDRMAP11 = 0x00000000
  },

  .c_perf = {
    .SCHED = 0x00000C01,
    .SCHED1 = 0x00000000,
    .PERFHPR1 = 0x01000001,
    .PERFLPR1 = 0x08000200,
    .PERFWR1 = 0x08000400,
    .PCFGR_0 = 0x00010000,
    .PCFGW_0 = 0x00000000,
    .PCFGQOS0_0 = 0x02100C03,
    .PCFGQOS1_0 = 0x00800100,
    .PCFGWQOS0_0 = 0x01100C03,
    .PCFGWQOS1_0 = 0x01000200,
#ifdef DDR_DUAL_AXI_PORT
    .PCFGR_1 = 0x00010000,
    .PCFGW_1 = 0x00000000,
    .PCFGQOS0_1 = 0x02100C03,
    .PCFGQOS1_1 = 0x00800040,
    .PCFGWQOS0_1 = 0x01100C03,
    .PCFGWQOS1_1 = 0x01000200
#endif
  },

  .p_reg = {
    .PGCR = 0x01442E02,
    .ACIOCR = 0x10400812,
    .DXCCR = 0x00000C40,
    .DSGCR = 0xF200011F,
    .DCR = 0x0000000B,
    .ODTCR = 0x00010000,
    .ZQ0CR1 = 0x00000038,
    .DX0GCR = 0x0000CE81,
    .DX1GCR = 0x0000CE81,
#ifdef DDR_32BIT_INTERFACE
    .DX2GCR = 0x0000CE80,
    .DX3GCR = 0x0000CE80
#endif
  },

  .p_timing = {
    .PTR0 = 0x0022AA5B,
    .PTR1 = 0x04841104,
    .PTR2 = 0x042DA068,
    .DTPR0 = 0x38D488D0,
    .DTPR1 = 0x098B00D8,
    .DTPR2 = 0x10023600,
    .MR0 = 0x00000840,
    .MR1 = 0x00000000,
    .MR2 = 0x00000208,
    .MR3 = 0x00000000
  }
};