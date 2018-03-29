#ifndef _usart1_h__
#define _usart1_h__

#include "stm32f10x.h"



void Usart1_Init(void);//只需要调用者一个函数 就完成对dma的串口发送设置全部内容
void RCC_Configuration(void);//时钟设置 和 外设使能函数 在usart1_all已经调用了
void NVIC_Configuration(void);


#endif

