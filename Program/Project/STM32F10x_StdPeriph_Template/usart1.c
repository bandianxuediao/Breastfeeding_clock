#include "usart1.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	USART_SendData(USART1, (uint8_t) ch);

	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{
	}

	return ch;
}
///////////////////////////////////////////////////////////////////////////////////////
RCC_ClocksTypeDef RCC_ClockFreq;
ErrorStatus HSEStartUpStatus;
///////////////////////////////////////////////////////////////////////////////////////
void RCC_Configuration(void)
{
	RCC_DeInit();//

	RCC_HSEConfig(RCC_HSE_ON);

	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		FLASH_SetLatency(FLASH_Latency_2);

		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		RCC_PCLK2Config(RCC_HCLK_Div1);

		RCC_PCLK1Config(RCC_HCLK_Div2);

		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);//很大的问题 为什么不能用RCC_PLLSource_HSE_Div1

		RCC_PLLCmd(ENABLE);

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
							RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE | RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE); //时钟使能
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}
///////////////////////////////////////////////////////////////////////////////////////
void Usart1_Init()//USART1 管脚设置
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_Init(USART1, &USART_InitStructure);

	//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	USART_Cmd(USART1, ENABLE);
}
///////////////////////////////////////////////////////////////////////////////////////
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
///////////////////////////////////////////////////////////////////////////////////////







