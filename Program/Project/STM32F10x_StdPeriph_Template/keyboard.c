#include "stm32f10x.h"
#include "keyboard.h"


#define Key      GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7//pd
#define Key_Hang GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
#define Key_Lie  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7

unsigned char key_table[] =
{
	0xe7, 0xd7, 0xb7, 0x77, /*��һ���ĸ�����*/
	0xeb, 0xdb, 0xbb, 0x7b, /*�ڶ����ĸ�����*/
	0xed, 0xdd, 0xbd, 0x7d, /*�������ĸ�����*/
	0xee, 0xde, 0xbe, 0x7e /*�������ĸ�����*/
};

////////////////////////////////////////////////////////////////
void Keyboard_IO_Config(void)//
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Key;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void Key_hang_IO_out(void)//�����ģʽ
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Key_Hang;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void Key_hang_IO_in(void)//������ģʽ
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Key_Hang;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void Key_lie_IO_out(void)//�����ģʽ
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Key_Lie;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void Key_lie_IO_in(void)//������ģʽ
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Key_Lie;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
unsigned char Read_hang(void)
{
	unsigned char hang = 0x0f;
	Keyboard_IO_Config();//���ж����
	GPIO_Write(GPIOD, 0x0f);
	Key_hang_IO_in();//�л�ģʽ ����
	hang = GPIO_ReadInputData(GPIOD);

	if(hang != 0x0f)
	{
		hang = GPIO_ReadInputData(GPIOD);
	}

	//  Key_hang_IO_out();
	return hang;
}
////////////////////////////////////////////////////////////////
unsigned char Read_lie(void)
{
	unsigned char lie = 0xf0;
	Keyboard_IO_Config();//���ж����
	GPIO_Write(GPIOD, 0xf0);
	Key_lie_IO_in();//�л�ģʽ �����
	lie = GPIO_ReadInputData(GPIOD);

	if(lie != 0xf0)
	{
		lie = GPIO_ReadInputData(GPIOD);
	}

	//  Key_lie_IO_out();
	return lie;
}
////////////////////////////////////////////////////////////////
unsigned char Key_Scan(void)
{
	unsigned char hang;
	unsigned char lie;
	unsigned char key, i, final = 0xff;
	hang = 0x0f & Read_hang();
	//  Delay(9);
	lie = 0xf0 & Read_lie();
	key = hang | lie;

	for(i = 0; i < 16; i++)
	{
		if(key == key_table[i])
		{
			final = i + 1;
		}
	}

	return final;
}


