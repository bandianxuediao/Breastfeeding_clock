#include"ds18b20.h"
#include "stm32f10x.h"


#define DS_PORT   GPIOC                                 //选择外设GPIOA
#define DS_DQIO   GPIO_Pin_6                                //选择管脚Pa1
#define ResetDQ() GPIO_ResetBits(DS_PORT,DS_DQIO)       //拉低DQ
#define SetDQ()   GPIO_SetBits(DS_PORT,DS_DQIO)           //拉高DQ
#define GetDQ()   GPIO_ReadInputDataBit(DS_PORT,DS_DQIO)  //读取DQ的电平
/////////////////////////////////////////////////////////////////////////////////
void STM_Ds18b20_Init(void) //初始化led
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //设置漏极开路
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
	NVIC_SetPriority (SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1); //优先级15
}
/////////////////////////////////////////////////////////////////////////////////
void delay_1us(unsigned int value)
{
	SysTick->LOAD = value * 9; //时间加载
	SysTick->CTRL |= 0x01; //开始倒数

	while(!(SysTick->CTRL & (1 << 16))); //等待时间到达

	SysTick->CTRL = 0x00000000; //关闭计数器
	SysTick->VAL = 0x00000000; //清空计数器
}
void delay_1ms(unsigned int value)
{
	SysTick->LOAD = value - 1; //时间加载
	SysTick->CTRL |= 0x01; //开始倒数

	while(!(SysTick->CTRL & (1 << 16))); //等待时间到达

	SysTick->CTRL = 0x00000000; //关闭计数器
	SysTick->VAL = 0x00000000; //清空计数器
}
/////////////////////////////////////////////////////////////////////////////////
void Init_ds18b20(void)    //初始化DS18B20
{
	//  STM_Ds18b20_Init();
	__disable_irq();
	SetDQ();
	delay_1us(30);   //保持高电平一段时间时间
	ResetDQ();       //总线将其拉低电平
	delay_1us(600);  //延时400us-960us，这里延时600us
	SetDQ();         //总线释放低电平
	delay_1us(30);   //延时15us-60us，这里延时30us

	while(GetDQ());  //若为高电平则出错，等待一直循环

	delay_1us(500);  //将剩余时间消耗完
	SetDQ();         //总线将电平拉高
	__enable_irq();
}
/////////////////////////////////////////////////////////////////////////////////
void DS18B20WriteByte(unsigned char Dat)
{
	unsigned char i;
	__disable_irq() ;

	for(i = 8; i > 0; i--)
	{
		ResetDQ();         //在15us内送数到数据线，在15-60us内采样
		delay_1us(5);

		if(Dat & 0x01)    //读数据的最低位
			SetDQ();
		else
			ResetDQ();

		delay_1us(65);     //将剩余时间消耗完
		SetDQ();
		delay_1us(2);     //写两个位之间间隔大于1us
		Dat >>= 1;        //右移一位，
	}

	__enable_irq();
}
/////////////////////////////////////////////////////////////////////////////////
unsigned char DS18B20ReadByte(void)
{
	unsigned char i = 0, Dat = 0x00;
	__disable_irq() ;
	SetDQ();
	delay_1us(5);

	for(i = 0; i < 8; i++)
	{
		Dat >>= 1;
		ResetDQ(); //从读时序开始到采样信号线必须在15us内，且采样尽量安排在15us最后
		delay_1us(5);
		SetDQ(); //释放总线，然后才能进行采样，否则无意义。只有低电平
		delay_1us(5);

		if(GetDQ())
			Dat |= 0x80;
		else
			Dat &= 0x7f;

		delay_1us(65);  //消耗剩余时间
		SetDQ();  //拉高总线
	}

	__enable_irq();
	return Dat;
}
/////////////////////////////////////////////////////////////////////////////////
float readtemperature(void)
{
	unsigned char a, b;
	short tmp;
	float tt;
	Init_ds18b20();             //初始化
	DS18B20WriteByte(skipRom);
	DS18B20WriteByte(convert); //开始转换温度
	delay_1ms(72000);              //延时，等待温度转换完成

	Init_ds18b20();
	DS18B20WriteByte(skipRom);
	DS18B20WriteByte(readTemp); //读取暂存器

	a = DS18B20ReadByte();      //读取低8位
	b = DS18B20ReadByte();      //读取高8位

	//  b<<=4;
	//  b+=(a&=0xf0)>>4;
	tmp = b;
	tmp <<= 8;
	tmp = tmp | a;

	tt = tmp * 0.0625;
	//  tmp = tt*10+0.5;
	return tt;
}
/////////////////////////////////////////////////////////////////////////////////
