
#include <array>
#include <cstddef>
#include <queue>
#include <list>
#include <memory>
#include <cstddef>

#define STM32H743xx
#include "stm32h743xx.h"

#include "clock-impl.hpp"

static USART_TypeDef* usart = nullptr;

using fifo = std::queue<char, std::list<char>>;
std::unique_ptr<fifo> txfifo = nullptr;


bool GPIOConfigure()
{
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN;
    GPIOD->MODER &= ~(GPIO_MODER_MODE8_Msk);
    GPIOD->MODER |= (2 << GPIO_MODER_MODE8_Pos);
    GPIOD->AFR[1] |= (7 << GPIO_AFRH_AFSEL8_Pos);
    GPIOD->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED8_Msk);
    GPIOD->OSPEEDR |= (2 << GPIO_OSPEEDR_OSPEED8_Pos);

    GPIOD->MODER &= ~(GPIO_MODER_MODE9_Msk);
    GPIOD->MODER |= (2 << GPIO_MODER_MODE9_Pos);
    GPIOD->AFR[1] |= (7 << GPIO_AFRH_AFSEL9_Pos);
    GPIOD->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED9_Msk);
    GPIOD->OSPEEDR |= (2 << GPIO_OSPEEDR_OSPEED9_Pos);

    return true;
}

bool SerialCommChannelConfigure(size_t baudrate, size_t )
{
	bool success = true;

    txfifo = std::make_unique<fifo>();

    uint32_t clk = 0;

    usart = USART3;
    clk = ClockTree.pclk1;
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;
    RCC->D2CCIP2R &= ~(RCC_D2CCIP2R_USART28SEL);
    RCC->D2CCIP2R |= (0x00 << RCC_D2CCIP2R_USART28SEL_Pos);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_SetPriority(USART3_IRQn, 0x0F);

	// USART
    usart->ICR |= USART_ICR_TCCF;   // clear interrupt
    usart->RQR |= USART_RQR_RXFRQ;  // flush fifo
    usart->ICR |= USART_ICR_TCCF;
	usart->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_TCIE | USART_CR1_RXNEIE;
	// TODO: switch statement to set stop bits in CR2
	usart->BRR = clk/baudrate;
	usart->CR1 |= USART_CR1_UE;

	return success;
}


extern "C" int _write(int , char *ptr, int len)
{
	int index;

	index = 0;
	while ( index < len )
	{
		txfifo->push(ptr[index]);
		index += 1;
	}
    if ( ( !txfifo->empty() ) && (usart->ISR & USART_ISR_TXE_TXFNF) )
    {
        usart->TDR = txfifo->front();
        txfifo->pop();
        usart->CR1 |= USART_CR1_TCIE;
    }

	return index;
}


size_t txcount = 0;
size_t rxcount = 0;

extern "C" void USART3_IRQHandler()
{

	if ( USART3->ISR & USART_ISR_TC )
	{
        txcount += 1;
		if ( !txfifo->empty() ) { USART3->TDR = txfifo->front(); txfifo->pop(); }
        else USART3->CR1 &= ~(USART_CR1_TCIE);      // disable the interrupt so we don't get repeated TC flags
		USART3->ICR |= USART_ICR_TCCF;
	}
	if ( USART3->ISR & USART_ISR_RXNE_RXFNE )
	{
        rxcount += 1;
        // TODO: read the received data
		// (void*)USART3->RDR;
        USART3->RQR |= USART_RQR_RXFRQ;	// flush, clear interrupt
	}
}
















