#include "timer.h"
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////
void Timer2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_DeInit(TIM2);
	//定时器计时时间是 300/72/36000  大概是0.15s
	TIM_TimeBaseStructure.TIM_Period = 200;                         //自动重装载寄存器周期的值(计数值)
	//累计 TIM_Period个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Prescaler = (36000 - 1);              //时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                           //清除溢出中断标志
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);                                          //开启时钟

}
//////////////////////////////////////////////////////////////////////////////
void NVIC_Tim2Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//定时器定时中段设置为 0.1s 呵呵
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;   //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//////////////////////////////////////////////////////////////////////////////
void Timer3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_DeInit(TIM3);

	TIM_TimeBaseStructure.TIM_Period = 100;                         //自动重装载寄存器周期的值(计数值)
	//累计 TIM_Period个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Prescaler = (36000 - 1);              //时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);                           //清除溢出中断标志
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE);                                          //开启时钟
}
//////////////////////////////////////////////////////////////////////////////
void NVIC_Tim3Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;   //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
////////////////////////////////////////////////////////////////////////////////
void Timer2_Init(void)
{
	Timer2_Configuration();//定时器2的设置
	NVIC_Tim2Configuration();//定时器2的中断优先级设置
}
///////////////////////////////////////////////////////////////////////////////
void Timer3_Init(void)
{
	Timer3_Configuration();//定时器2的设置
	NVIC_Tim3Configuration();//定时器2的中断优先级设置
}


