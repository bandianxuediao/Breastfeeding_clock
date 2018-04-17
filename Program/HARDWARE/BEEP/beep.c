#include "beep.h"
//#include "12864.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//蜂鸣器驱动代码
//12864 驱动代码
//////////////////////////////////////////////////////////////////////////////////

//初始化PB8为输出口.并使能这个口的时钟
//蜂鸣器初始化
void BEEP_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //使能GPIOB端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              //BEEP-->PB.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);  //根据参数初始化GPIOB.8

	GPIO_ResetBits(GPIOC, GPIO_Pin_12); //输出0，关闭蜂鸣器输出


	// GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);   //使能GPIOB端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //BEEP-->PB.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //根据参数初始化GPIOB.8

	GPIO_ResetBits(GPIOE, GPIO_Pin_10); //输出0，关闭蜂鸣器输出

}
