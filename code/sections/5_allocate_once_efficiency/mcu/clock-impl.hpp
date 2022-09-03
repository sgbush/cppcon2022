


#pragma once

#include <cstdint>



using ClockTree_t = struct ClockTreeStruct
{
    uint32_t pll1_p_ck;     // PLL1
    uint32_t pll1_q_ck;
    uint32_t pll1_r_ck;
    uint32_t pll2_p_ck;     // PLL2
    uint32_t pll2_q_ck;
    uint32_t pll2_r_ck;
    uint32_t pll3_p_ck;     // PLL3
    uint32_t pll3_q_ck;
    uint32_t pll3_r_ck;
    uint32_t sysclk;
    uint32_t sys_d1cpre_ck; // CPU
    uint32_t hclk;
    uint32_t aclk;          // D1 domain
    uint32_t hclk3;
    uint32_t pclk3;
    uint32_t hclk1;         // D2 domain
    uint32_t pclk1;
    uint32_t pckl1_tim;
    uint32_t hclk2;
    uint32_t pclk2;
    uint32_t pckl2_tim;
    uint32_t hclk4;         // D3 domain
    uint32_t pclk4;
};


extern ClockTree_t ClockTree;





