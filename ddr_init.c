/*----------------------------------------------------------------------
                        Macro Definitions
----------------------------------------------------------------------*/
#define STPMIC_SLV_ADDR 0x66

/*----------------------------------------------------------------------
                      Structure Definitions
----------------------------------------------------------------------*/
typedef struct
{
  bool wakeup_from_standby;
  bool self_refresh;
  uint32_t zdata;
  bool clear_bkp;
} DDR_InitTypeDef;

/*----------------------------------------------------------------------
                           I2C API's
----------------------------------------------------------------------*/
uint8_t BSP_I2C_ReadReg(uint8_t slave_addr, uint8_t mem_addr)
{
  uint8_t value = 0;
  /* Lock and unlock is not implemented*/
  lock(var);
  value = I2C_ReadReg(slave_addr, mem_addr);
  unlock(var);
}

uint8_t BSP_I2C_WriteReg(uint8_t slave_addr, uint8_t mem_addr, uint8_t value)
{
  uint8_t value = 0;
  /* Lock and unlock is not implemented*/
  lock(var);
  value = I2C_WriteReg(slave_addr, mem_addr, value);
  unlock(var);
}

/*----------------------------------------------------------------------
                           PMIC API's
----------------------------------------------------------------------*/
/* Note DDR rails are not configured by the below API */
void SystemPower_Config(void)
{
  /* Configures the I2C peripheral in which PMIC was connected*/
  BSP_PMIC_Init();

  /* Since we initialized I2C peripheral now we should be able to access the PMIC registers.
     For sanity purpose read "VERSION_STATUS_REG --> addr --> 0x06" --> register which holds PMIC version.
  */
  BSP_I2C_ReadReg(STPMIC_SLV_ADDR, 0x06);

  /* Enable power control functionality */

  /* Enable PMIC Vin detection and disable Vout detection */

  /* Set VDD_CORE --> BUCK1 to 1200mV and enable the regulator */

  /* Set 3V3 --> BUCK3 to 3300mV and enable the regulator */

  /* Set VDDA --> LDO1 to 2900mV and enable the regulator */

  /* Set 2V2 --> LDO2 to 2800mV and enable the regulator */

  /* Set VDD_USB --> LDO4 to 3300mV and enable the regulator */

  /* Set VDD_SD --> LDO5 to 2900mV and enable the regulator */

  /* Set 1V8 --> LDO6 to 1800mV and enable the regulator */

}

void HAL_DDR_powerinit()
{
  /* LDO3 configurations in LDO3 main control register --> LDO3_MAIN_CR
          - Configure it in normal mode (Each LDO has 2 modes Normal mode, bypass mode)
          - Set output voltage to Vout2 / 2 (means LDO3 output will be equal to BUCK2 output divided by 2)
  */

  /* Set BUCK2 Output voltage to 1.35V or 1350mV */

  /* Enable BUCK2 Regulator */
  delay(1); // 1ms delay
  /* Enable VREFDDR Regulator */
  delay(1); // 1ms delay
  /* Enable LDO3 Regulator */
  delay(1); // 1ms delay
}

/*----------------------------------------------------------------------
                           HAL API's
----------------------------------------------------------------------*/
bool HAL_Init(void)
{
  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HAL_RCC_GetSystemCoreClockFreq();
  /* Configure systick timer with 1ms tick (it will generate interrupt after 1ms) with some interrupt priority*/
  HAL_InitTick(TICK_INT_PRIORITY);
}

bool HAL_DDR_Init(DDR_InitTypeDef *iddr)
{
  /* Disable AXI dynamic clock gating feature using DDR interface control register --> RCC_DDRITFCR */
  RCC_DDRITFCR->AXIDCGEN = 0;

  /* Configure and enable DDR rails */
  HAL_DDR_powerinit();

  if (!iddr->self_refresh)
  {
    // Below task can be accomplished using Power control register 3
    /* Disable DDR retention */
    /* Disable DDR self refresh */
  }

  // ********** DDR init sequence **********
  // ---------- 1.1 Assert Reset Signals ----------
  /*  Assert Reset to the DDR controller APB interface (Register configuration interface)
      Assert Reset to the DDR controller AXI interface (CPU <--> MC interface)
      Assert Reset to the DDR core controller

      Assert Reset to the DDRPHY controller APB interface (Register configuration interface)
      Assert Reset to the DDRPHY controller
      Assert Reset to the DDRPHY controller Contrl block
  */
  
  // ---------- 1.2 Enable Clock ----------
  /*  DDR controller port1 peripheral clock enable
      DDR controller port2 peripheral clock enable
      DDRPHY controller peripheral clock enable
      DDR controller APB clock enable
      DDRPHY controller APB clock enable
      Configure DDR clock to 532.896Mhz
  */

  // ---------- 1.3 Deassert Reset signals (Since clocks are active) ----------
  /*  Deassert Reset to the DDRPHY controller
      Deassert Reset to the DDRPHY controller Contrl block
      Deassert Reset to the DDR controller APB interface (Register configuration interface)
  */

  // ---------- 1.4 Delay 128 cycles ----------

  // ---------- 1.5 Initialize Synopsys Universal Memory Controller registers ----------
  /*  Disable DFI_INIT_COMPLETE_EN bit from DDRCTLR_DFIMISC register. To make sure DDR init should not happen before DDRPHY is initialized
      Configure DDR memory controller registers using static configuration
      if Static configuration says disable DLL then Disable DLL using DDRCTRL->MSTR (Mostly don't try to disable DLL)
      Configure DDR memory controller timing registers using static configuration
      Configure DDR memory controller mapping registers using static configuration
      Skip DRAM initialization by configuring DDRCTLR SDRAM Initialization register 0 (DRAM init is accomplished by PHY)
      Configure DDR memory controller perf registers using static configuration
  */

  // ---------- 2 Dessert DDR controller reset ----------
  /*  Deassert Reset to the DDR Core controller
      Deassert Reset to the DDR controller AXI interface (CPU <--> MC interface)
      Deassert Reset to the DDRPHY controller APB interface (Register configuration interface)
  */

  // ---------- 3 DDR Phy Initialization ----------
  /*  Configure DDR PHY controller registers using static configuration
      Configure DDR PHY Timing registers using static configuration
      if Static configuration says disable DLL then Disable DLL using DDRPHYC->MR1 (Mostly don't try to disable DLL)
  */

  // ---------- 4 Wait till PHY init gets completed ----------
  /*  Monitor the PHY init by continuously polling PUBL register (PUBL - PHY utility Block) --> PGSR.IDONE ((PHY Global Status Register --> Initialization Done)
  */

  // ---------- 5 PHY Calibration and init ----------
  /*  Configure PHY initialization register (PIR)
            - Trigger soft DLL reset
            - Wait until PHY DLL's to get locked
            - Perform PHY impedence Calibration (ZQ Calibration)
            - Soft reset for the ITM (Interface Timing Modules) for the Data and Data strobes
            - Configure to assert the signal when PHY init is completed
            - Do DDR system initialization which includes (PHY initialization, PHY training, DDR reset and DRAM initialization)
      Monitor the PHY init by continuously polling PUBL register (PUBL - PHY utility Block) --> PGSR.IDONE ((PHY Global Status Register --> Initialization Done)
  */

  // ---------- 6 Set DFIMISC.dfi_init_complete_en to 1 ----------
  /*  Clear DDRCTRL_SWCTL.SW_DONE=0 (Enables Quasi register programming)
      Set DDRCTRL_DFIMISC.DFI_INIT_COMPLETE_EN (Its like I am telling PHY init is complete, lets trigger DRAM init)
      Disable DDRCTRL_SWCTL.SW_DONE=1 (Enables Quasi register programming)
  */

  // ---------- 7 Wait till memory controller moves to normal operation mode ----------
  /*  Wait till DDRCTRL_STAT.OPERATING_MODE[2:0] gets changed from Init mode to Normal mode
      DQS training done --> needs to understand how DQS training got completed
  */

  // ---------- 8 Disable auto refresh and power down ----------
  /*  Disable AXI host interface and make sure there is no RD/WR pending transactions in the pipeline as well using DBG1 register and CAM debug register
      Disable Auto refresh by setting DDRCTRL->RFSHCTL3.DIS_AUTO_REFRESH
      Memory controller going to power down state without keeping DDR in self refresh mode --> Configured using DDRCTLR Low power control register
      Set DFIMISC.dfiinit_complete_en = 0
      Enable AXI host interface using DBG1 register
  */

  // ---------- 9 Program PUBL PGCR to enable refresh during training and rank to train not done => keep the programed value in PGCR  ----------

  // ---------- 10 Configure the PIR (PHY initialization register to specify which all trainings needs to be ran) ----------
  /*  Do read DQS gate training algorithm
  */

  // ---------- 11 Monitor the PHY init by continuously polling PUBL register ----------
  /*  PUBL - PHY utility Block --> PGSR.IDONE (PHY Global Status Register --> Initialization Done)
  */

  // ---------- 12 ----------
  /*  Revert the changes which we made in step8
      Enable both AXI ports by configuring DDRCTRL->PCTRL_0 and DDRCTRL->PCTRL_1
      Enable AXI Dynamic Clock gating by configuring RCC->DDRITFCR (DDR interface control register)
  */

}

int main(void)
{
  /* HAL_init updates core clock and initializes systick timer interrupt for each 1ms*/
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /*  Configure USART for logging messages  */
  UART_Config();

  /* Configure the system power - Initialize PMIC and set the rail voltage and enable all the rails except DDR rails*/
  SystemPower_Config();

  /* Insert 1 second delay */
  delay(1000);

  DDR_InitTypeDef iddr = {.wakeup_from_standby=false, .self_refresh=false, .zdata=false, .clear_bkp=false};
  HAL_DDR_Init(&iddr);

  /* Make sure DDR initialization is proper by accessing DDR region */
  uint32_t *ddr_base_addr = (uint32_t *) 0xC0000000;
  bool test_ddr = true;
  for (int pattern=0; pattern<1000; pattern++)
  {
    *(ddr_base_addr + pattern) = pattern;
  }

  for (int pattern=0; pattern<1000; pattern++)
  {
    if (*(ddr_base_addr + pattern) != pattern)
    {
      test_ddr = false;
    }
  }

  if (test_ddr == true)
  {
    printf("DDR init was successful!!!\n")
  }
  else
  {
    printf("DDR init was failed!!!\n")
  }

  /* Initialize the GPIO pin at output mode in which LED was connected */
  /* Blink Led for each 1second continuously */
  while(1)
  {
    led(on);
    delay(1000);
    led(off);
    delay(1000);
  }
}

