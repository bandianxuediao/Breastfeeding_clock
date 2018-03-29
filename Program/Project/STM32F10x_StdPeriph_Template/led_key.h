#ifndef _LED_KEY_H
#define _LED_KEY_H
#include "stm32f10x.h"
////////////////////////////////////////////////////////////////////////////////////
//宏定义灯亮灭
#define Set_Led_1()  GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define Set_Led_2()  GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define Set_Led_3()  GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define Set_Led_4()  GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define Close_Led_1()    GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define Close_Led_2()    GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define Close_Led_3()    GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define Close_Led_4()    GPIO_ResetBits(GPIOB,GPIO_Pin_11)

////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	LED1 = 0,
	LED2 = 1,
	LED3 = 2,
	LED4 = 3
} Led_TypeDef;
////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	KEY1 = 0,
	KEY2 = 1,
	KEY3 = 2,
	KEY4 = 3
} Key_TypeDef;


void STM_LED_Init(Led_TypeDef LED);
void STM_KEY_Init(Key_TypeDef KEY);
void NVIC0_Configuration(void);//四个按键的中断优先级设置
void NVIC1_Configuration(void);
void NVIC2_Configuration(void);
void NVIC3_Configuration(void);
void EXIT1_Configuration(void);//四个按键的外部中断线设置
void EXIT0_Configuration(void);
void EXIT2_Configuration(void);//四个按键的外部中断线设置
void EXIT3_Configuration(void);


#endif

