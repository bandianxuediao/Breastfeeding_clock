#include "timer.h"
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////
void Timer2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_DeInit(TIM2);
	//��ʱ����ʱʱ���� 300/72/36000  �����0.15s
	TIM_TimeBaseStructure.TIM_Period = 200;                         //�Զ���װ�ؼĴ������ڵ�ֵ(����ֵ)
	//�ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Prescaler = (36000 - 1);              //ʱ��Ԥ��Ƶ��   ���磺ʱ��Ƶ��=72MHZ/(ʱ��Ԥ��Ƶ+1)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                           //�������жϱ�־
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);                                          //����ʱ��

}
//////////////////////////////////////////////////////////////////////////////
void NVIC_Tim2Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//��ʱ����ʱ�ж�����Ϊ 0.1s �Ǻ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;   //ͨ��
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

	TIM_TimeBaseStructure.TIM_Period = 100;                         //�Զ���װ�ؼĴ������ڵ�ֵ(����ֵ)
	//�ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Prescaler = (36000 - 1);              //ʱ��Ԥ��Ƶ��   ���磺ʱ��Ƶ��=72MHZ/(ʱ��Ԥ��Ƶ+1)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);                           //�������жϱ�־
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE);                                          //����ʱ��
}
//////////////////////////////////////////////////////////////////////////////
void NVIC_Tim3Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;   //ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
////////////////////////////////////////////////////////////////////////////////
void Timer2_Init(void)
{
	Timer2_Configuration();//��ʱ��2������
	NVIC_Tim2Configuration();//��ʱ��2���ж����ȼ�����
}
///////////////////////////////////////////////////////////////////////////////
void Timer3_Init(void)
{
	Timer3_Configuration();//��ʱ��2������
	NVIC_Tim3Configuration();//��ʱ��2���ж����ȼ�����
}


