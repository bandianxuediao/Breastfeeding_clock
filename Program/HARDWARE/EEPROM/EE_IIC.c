#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//IIC���� ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//��ʼ��IIC
void EE_IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE ); //ʹ��GPIOBʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7); //PB10,PB11 ����ߵ�ƽ

	//if(AT24CXX_ReadOneByte(INITIAL_ADDR) != 0x55) //�ж��ǲ��ǵ�һ����������һ������������������
	{
		AT24CXX_WriteOneByte(INITIAL_ADDR, 0x55);
		AT24CXX_WriteLenByte(6, 1801010620, 4);

		AT24CXX_WriteLenByte(10, 0, 2);
		AT24CXX_WriteLenByte(20, 0, 2);
		AT24CXX_WriteLenByte(30, 0, 2);
		AT24CXX_WriteLenByte(40, 0, 2);
	}

}
//����IIC��ʼ�ź�
void EE_IIC_Start(void)
{
	EE_SDA_OUT();     //sda�����
	EE_IIC_SDA = 1;
	EE_IIC_SCL = 1;
	delay_us(4);
	EE_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
	delay_us(4);
	EE_IIC_SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void EE_IIC_Stop(void)
{
	EE_SDA_OUT();//sda�����
	EE_IIC_SCL = 0;
	EE_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
	delay_us(4);
	EE_IIC_SCL = 1;
	EE_IIC_SDA = 1; //����I2C���߽����ź�
	delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 EE_IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	EE_SDA_IN();      //SDA����Ϊ����
	EE_IIC_SDA = 1;
	delay_us(1);
	EE_IIC_SCL = 1;
	delay_us(1);

	while(EE_READ_SDA)
	{
		ucErrTime++;

		if(ucErrTime > 250)
		{
			EE_IIC_Stop();
			return 1;
		}
	}

	EE_IIC_SCL = 0; //ʱ�����0
	return 0;
}
//����ACKӦ��
void EE_IIC_Ack(void)
{
	EE_IIC_SCL = 0;
	EE_SDA_OUT();
	EE_IIC_SDA = 0;
	delay_us(2);
	EE_IIC_SCL = 1;
	delay_us(2);
	EE_IIC_SCL = 0;
}
//������ACKӦ��
void EE_IIC_NAck(void)
{
	EE_IIC_SCL = 0;
	EE_SDA_OUT();
	EE_IIC_SDA = 1;
	delay_us(2);
	EE_IIC_SCL = 1;
	delay_us(2);
	EE_IIC_SCL = 0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void EE_IIC_Send_Byte(u8 txd)
{
	u8 t;
	EE_SDA_OUT();
	EE_IIC_SCL = 0; //����ʱ�ӿ�ʼ���ݴ���

	for(t = 0; t < 8; t++)
	{
		EE_IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		EE_IIC_SCL = 1;
		delay_us(2);
		EE_IIC_SCL = 0;
		delay_us(2);
	}
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 EE_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	EE_SDA_IN();//SDA����Ϊ����

	for(i = 0; i < 8; i++ )
	{
		EE_IIC_SCL = 0;
		delay_us(2);
		EE_IIC_SCL = 1;
		receive <<= 1;

		if(EE_READ_SDA)receive++;

		delay_us(1);
	}

	if (!ack)
		EE_IIC_NAck();//����nACK
	else
		EE_IIC_Ack(); //����ACK

	return receive;
}



























