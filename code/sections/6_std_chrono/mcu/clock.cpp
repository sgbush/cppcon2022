


#include <cstddef>

#define STM32H743xx
#include "stm32h7xx.h"

#include "clock-impl.hpp"



uint32_t CoreClockSpeed = 0;
ClockTree_t ClockTree;

void MillisecondPeriod() __attribute__ ((weak));


bool SystemClockConfigure()
{
    bool success = true;

    SCB->VTOR = FLASH_BANK1_BASE;       /* Vector Table Relocation in Internal FLASH */

    SCB->CPACR |= ((0x03 << 10*2)|(0x03 << 11*2));  // enable floating point coprocessors

    SCB_EnableICache();     // enable cache
    SCB_EnableDCache();

    //  Reset the RCC clock configuration to the default reset state 
    RCC->CR |= RCC_CR_HSION;		//  Set HSION bit 
    RCC->CFGR = 0x00000000;		// Reset CFGR register
    RCC->CR &= (uint32_t)0xEAF6ED7F;		// Reset HSEON, CSSON , CSION,RC48ON, CSIKERON PLL1ON, PLL2ON and PLL3ON bits 
    RCC->D1CFGR = 0x00000000;		//  Reset D1CFGR register 
    RCC->D2CFGR = 0x00000000;		//  Reset D2CFGR register
    RCC->D3CFGR = 0x00000000;		//  Reset D3CFGR register
    RCC->PLLCKSELR = 0x00000000;		//  Reset PLLCKSELR register 
    RCC->PLLCFGR = 0x00000000;		//  Reset PLLCFGR register
    RCC->PLL1DIVR = 0x00000000;		//  Reset PLL1DIVR register 
    RCC->PLL1FRACR = 0x00000000;		//  Reset PLL1FRACR register 
    RCC->PLL2DIVR = 0x00000000;		//  Reset PLL2DIVR register 
    RCC->PLL2FRACR = 0x00000000;		//  Reset PLL2FRACR register
    RCC->PLL3DIVR = 0x00000000;		//  Reset PLL3DIVR register 
    RCC->PLL3FRACR = 0x00000000;		//  Reset PLL3FRACR register
    RCC->CR &= (uint32_t)0xFFFBFFFF;		//  Reset HSEBYP bit 
    RCC->CIER = 0x00000000;		//  Disable all interrupts 
    *((__IO uint32_t*)0x51008108) = 0x00000001;		// Change  the switch matrix read issuing capability to 1 for the AXI SRAM target (Target 7) 

    NVIC_SetPriorityGrouping(7 - 4);    // priority grouping 4, to maximize interrupt priorities

    RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;   // activate syscfg peripheral to allow configuration

    PWR->CR3 |= PWR_CR3_SCUEN;      // Supply configuration update enable 

    PWR->D3CR &= ~(PWR_D3CR_VOS);
    PWR->D3CR |= ( 0x03 << PWR_D3CR_VOS_Pos);        // Configure the main internal regulator output voltage 
    while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) continue;

    RCC->CR &= ~(RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON);   // ensure PLL is off

    uint32_t hsidiv = 1;
    uint32_t hsidivshift = 0;
    while ( hsidiv > 1 ) { hsidiv /= 2; hsidivshift += 1; }
    RCC->CR |= RCC_CR_HSION | hsidivshift;    //    /!\ selects HSI with /8 divider --- change to HSE/BYPASS for Nucleo

    const uint32_t HSIFrequency = 64'000'000/hsidiv;
    uint32_t m, n, p, q, r;
    uint32_t ref1_ck;

    RCC->PLLCKSELR |= RCC_PLLCKSELR_PLLSRC_HSI;

    RCC->PLLCFGR =    ( 0x02 << RCC_PLLCFGR_PLL1RGE_Pos ) | (0x01 << RCC_PLLCFGR_PLL1VCOSEL_Pos)
                    | ( 0x02 << RCC_PLLCFGR_PLL2RGE_Pos ) | (0x01 << RCC_PLLCFGR_PLL2VCOSEL_Pos)
                    | ( 0x02 << RCC_PLLCFGR_PLL3RGE_Pos ) | (0x01 << RCC_PLLCFGR_PLL3VCOSEL_Pos)
                    | RCC_PLLCFGR_DIVP1EN | RCC_PLLCFGR_DIVQ3EN;

    // ---------------- PLL 1 ----------------
    m = 16; n = 200; p = 2; q = 48; r = 2;
    ref1_ck = HSIFrequency/m;
    RCC->PLLCKSELR |= ( m << RCC_PLLCKSELR_DIVM1_Pos );
    RCC->PLL1DIVR = ( (n-1) << RCC_PLL1DIVR_N1_Pos ) 
                    | ( (p-1) << RCC_PLL1DIVR_P1_Pos ) 
                    | ( (q-1) << RCC_PLL1DIVR_Q1_Pos )
                    | ( (r-1) << RCC_PLL1DIVR_R1_Pos);

    RCC->CR |= RCC_CR_PLL1ON;   // activate PLL
    while ( !(RCC->CR & RCC_CR_PLL1RDY) ) continue;


    ClockTree.pll1_p_ck = ref1_ck*n/p;
    ClockTree.pll1_q_ck = ref1_ck*n/q;
    ClockTree.pll1_r_ck = ref1_ck*n/r;
    ClockTree.sysclk = ClockTree.pll1_p_ck;
    const size_t d1cpre = 1;
    const size_t hpre = 2;
    const size_t d1ppre = 2;
    RCC->D1CFGR = RCC_D1CFGR_HPRE_DIV2 | RCC_D1CFGR_D1PPRE_DIV2 | RCC_D1CFGR_D1CPRE_DIV1;   // clock tree dividers
    ClockTree.sys_d1cpre_ck = ClockTree.sysclk/d1cpre;
    CoreClockSpeed = ClockTree.sys_d1cpre_ck;
    ClockTree.hclk = ClockTree.sysclk/hpre;
    ClockTree.pclk3 = ClockTree.hclk/d1ppre;
    ClockTree.hclk3 = ClockTree.hclk;
    RCC->D2CFGR = RCC_D2CFGR_D2PPRE1_DIV2 | RCC_D2CFGR_D2PPRE2_DIV2;
    const size_t d2ppre1 = 2;
    const size_t d2ppre2 = 2;
    ClockTree.hclk1 = ClockTree.hclk;
    ClockTree.hclk2 = ClockTree.hclk;
    ClockTree.pclk1 = ClockTree.hclk/d2ppre1;
    ClockTree.pclk2 = ClockTree.hclk/d2ppre2;
    ClockTree.pckl1_tim = 2*ClockTree.pclk1;
    ClockTree.pckl2_tim = 2*ClockTree.pclk2;
    RCC->D3CFGR = RCC_D3CFGR_D3PPRE_DIV2;
    const size_t d3ppre = 2;
    ClockTree.hclk4 = ClockTree.hclk;
    ClockTree.pclk4 = ClockTree.hclk/d3ppre;

    RCC->CFGR |= RCC_CFGR_SW_PLL1;    // switch to PLL
    while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1) continue;

    // ---------------- PLL 2 ----------------
    n = 50;
    RCC->PLLCKSELR |= ( 0x20 << RCC_PLLCKSELR_DIVM2_Pos );
    RCC->PLL2DIVR = ( (n-1) << RCC_PLL2DIVR_N2_Pos ) 
                    | ( (p-1) << RCC_PLL2DIVR_P2_Pos ) 
                    | ( (q-1) << RCC_PLL2DIVR_Q2_Pos )
                    | ( (r-1) << RCC_PLL2DIVR_R2_Pos);

    // RCC->CR |= RCC_CR_PLL2ON;   // activate PLL
    // while ( !(RCC->CR & RCC_CR_PLL2RDY) ) continue;

    // ---------------- PLL 3 ----------------
    RCC->PLLCKSELR |= ( 0x04 << RCC_PLLCKSELR_DIVM3_Pos );
    RCC->PLL3DIVR = ( (n-1) << RCC_PLL3DIVR_N3_Pos ) 
                    | ( (p-1) << RCC_PLL3DIVR_P3_Pos ) 
                    | ( (q-1) << RCC_PLL3DIVR_Q3_Pos )
                    | ( (r-1) << RCC_PLL3DIVR_R3_Pos);

    // RCC->CR |= RCC_CR_PLL3ON;   // activate PLL
    // while ( !(RCC->CR & RCC_CR_PLL3RDY) ) continue;


    // TODO: LSE/LSI/RTC

    return success;
}













