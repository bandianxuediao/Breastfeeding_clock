#include"ds18b20.h"
#include "stm32f10x.h"


#define DS_PORT   GPIOC                                 //ѡ������GPIOA
#define DS_DQIO   GPIO_Pin_6                                //ѡ��ܽ�Pa1
#define ResetDQ() GPIO_ResetBits(DS_PORT,DS_DQIO)       //����DQ
#define SetDQ()   GPIO_SetBits(DS_PORT,DS_DQIO)           //����DQ
#define GetDQ()   GPIO_ReadInputDataBit(DS_PORT,DS_DQIO)  //��ȡDQ�ĵ�ƽ
/////////////////////////////////////////////////////////////////////////////////
void STM_Ds18b20_Init(void) //��ʼ��led
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //����©����·
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
	NVIC_SetPriority (SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1); //���ȼ�15
}
/////////////////////////////////////////////////////////////////////////////////
void delay_1us(unsigned int value)
{
	SysTick->LOAD = value * 9; //ʱ�����
	SysTick->CTRL |= 0x01; //��ʼ����

	while(!(SysTick->CTRL & (1 << 16))); //�ȴ�ʱ�䵽��

	SysTick->CTRL = 0x00000000; //�رռ�����
	SysTick->VAL = 0x00000000; //��ռ�����
}
void delay_1ms(unsigned int value)
{
	SysTick->LOAD = value - 1; //ʱ�����
	SysTick->CTRL |= 0x01; //��ʼ����

	while(!(SysTick->CTRL & (1 << 16))); //�ȴ�ʱ�䵽��

	SysTick->CTRL = 0x00000000; //�رռ�����
	SysTick->VAL = 0x00000000; //��ռ�����
}
/////////////////////////////////////////////////////////////////////////////////
void Init_ds18b20(void)    //��ʼ��DS18B20
{
	//  STM_Ds18b20_Init();
	__disable_irq();
	SetDQ();
	delay_1us(30);   //���ָߵ�ƽһ��ʱ��ʱ��
	ResetDQ();       //���߽������͵�ƽ
	delay_1us(600);  //��ʱ400us-960us��������ʱ600us
	SetDQ();         //�����ͷŵ͵�ƽ
	delay_1us(30);   //��ʱ15us-60us��������ʱ30us

	while(GetDQ());  //��Ϊ�ߵ�ƽ������ȴ�һֱѭ��

	delay_1us(500);  //��ʣ��ʱ��������
	SetDQ();         //���߽���ƽ����
	__enable_irq();
}
/////////////////////////////////////////////////////////////////////////////////
void DS18B20WriteByte(unsigned char Dat)
{
	unsigned char i;
	__disable_irq() ;

	for(i = 8; i > 0; i--)
	{
		ResetDQ();         //��15us�������������ߣ���15-60us�ڲ���
		delay_1us(5);

		if(Dat & 0x01)    //�����ݵ����λ
			SetDQ();
		else
			ResetDQ();

		delay_1us(65);     //��ʣ��ʱ��������
		SetDQ();
		delay_1us(2);     //д����λ֮��������1us
		Dat >>= 1;        //����һλ��
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
		ResetDQ(); //�Ӷ�ʱ��ʼ�������ź��߱�����15us�ڣ��Ҳ�������������15us���
		delay_1us(5);
		SetDQ(); //�ͷ����ߣ�Ȼ����ܽ��в��������������塣ֻ�е͵�ƽ
		delay_1us(5);

		if(GetDQ())
			Dat |= 0x80;
		else
			Dat &= 0x7f;

		delay_1us(65);  //����ʣ��ʱ��
		SetDQ();  //��������
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
	Init_ds18b20();             //��ʼ��
	DS18B20WriteByte(skipRom);
	DS18B20WriteByte(convert); //��ʼת���¶�
	delay_1ms(72000);              //��ʱ���ȴ��¶�ת�����

	Init_ds18b20();
	DS18B20WriteByte(skipRom);
	DS18B20WriteByte(readTemp); //��ȡ�ݴ���

	a = DS18B20ReadByte();      //��ȡ��8λ
	b = DS18B20ReadByte();      //��ȡ��8λ

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
