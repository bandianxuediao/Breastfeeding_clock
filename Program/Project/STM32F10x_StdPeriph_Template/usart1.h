#ifndef _usart1_h__
#define _usart1_h__

#include "stm32f10x.h"



void Usart1_Init(void);//ֻ��Ҫ������һ������ ����ɶ�dma�Ĵ��ڷ�������ȫ������
void RCC_Configuration(void);//ʱ������ �� ����ʹ�ܺ��� ��usart1_all�Ѿ�������
void NVIC_Configuration(void);


#endif

