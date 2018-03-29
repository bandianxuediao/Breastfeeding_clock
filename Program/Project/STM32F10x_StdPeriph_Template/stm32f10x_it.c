#include "stm32f10x_it.h"
#include "ds18b20.h"
#include "keyboard.h"
#include "adc.h"
#include "stdio.h"
#include "lcd_12864.h"
////////////////////////////////////////////////////////////////////
char BUFFER_1[4]; //三轴加速值
char BUFFER_2[4];
char BUFFER_3[4];
extern uint16_t adc[3];           //adc转换的值3轴
///////////////////////////////////////////////////////////////////
char s[4];        //进行温度传感器转换后的浮点值

extern unsigned char get_keyboard_value;  //矩阵键盘扫描的值 在定时器2中扫描
extern float value;                 //温度传感器的扫面


//////////////////////////////////////////////////////////////
void NMI_Handler(void)
{
}

//////////////////////////////////////////////////////////////
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

//////////////////////////////////////////////////////////////
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}
//////////////////////////////////////////////////////////////
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

//////////////////////////////////////////////////////////////
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

//////////////////////////////////////////////////////////////
void SVC_Handler(void)
{
}

//////////////////////////////////////////////////////////////
void DebugMon_Handler(void)
{
}

//////////////////////////////////////////////////////////////
void PendSV_Handler(void)
{
}

//////////////////////////////////////////////////////////////
void SysTick_Handler(void)
{

}
unsigned char count, miao; //定义两个计数值
//////////////////////////////////////////////////////////////
//两个定时器的中断处理程序
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
		count++;

		if(count == 10)
		{
			count = 0;
			miao++;
		}

		if(miao > 9)
		{
			miao = 0;
		}

		DisplayOneChar(7, 0, '0' + miao);

		sprintf(BUFFER_1, "X 轴(mv)= %d ",  (adc[0] * 3300 / 4096)); //内部参考电压4096
		DisplayList(1, 1, BUFFER_1);
		sprintf(BUFFER_2, "Y 轴(mv)= %d ",  (adc[1] * 3300 / 4096)); //内部参考电压4096
		DisplayList(1, 2, BUFFER_2);
		sprintf(BUFFER_3, "Z 轴(mv)= %d ",  (adc[2] * 3300 / 4096)); //内部参考电压4096
		DisplayList(1, 3, BUFFER_3);

		value = readtemperature();
		sprintf(s, "温度=%04.2f度", value);
		DisplayList(1, 0, s);

	}

}
extern unsigned char wait_flag;
void TIM3_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
		get_keyboard_value = Key_Scan();
	}

}
//////////////////////////////////////////////////////////////
//四个独立按键的中断处理程序
//void EXTI0_IRQHandler(void)
//{
//  if ( EXTI_GetITStatus(EXTI_Line0) != RESET )
//  {
//      EXTI_ClearITPendingBit(EXTI_Line0);
//  }
//}
//void EXTI1_IRQHandler(void)
//{
//  if ( EXTI_GetITStatus(EXTI_Line1) != RESET )
//  {
//      EXTI_ClearITPendingBit(EXTI_Line1);
//  }
//}
//void EXTI2_IRQHandler(void)
//{
//  if ( EXTI_GetITStatus(EXTI_Line2) != RESET )
//  {
//      EXTI_ClearITPendingBit(EXTI_Line2);
//  }
//}
//void EXTI3_IRQHandler(void)
//{
//  if ( EXTI_GetITStatus(EXTI_Line3) != RESET )
//  {
//      EXTI_ClearITPendingBit(EXTI_Line3);
//  }
//}
//////////////////////////////////////////////////////////////
