#include "lcd_12864.h"
#include "stm32f10x.h"
#include "string.h"
#include <STDLIB.H>

#define Busy    0x80


#define RS GPIO_Pin_8 //pc
#define RW GPIO_Pin_7
#define E  GPIO_Pin_2
#define PSB GPIO_Pin_3//���в���ת��
#define RST GPIO_Pin_4




#define DATA GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 //pa

#define RS_HIGH   GPIO_SetBits(GPIOC,RS)   //����
#define RS_LOW    GPIO_ResetBits(GPIOC,RS) //ָ��
#define E_HIGH    GPIO_SetBits(GPIOC,E)    //�ߵ�ƽʹ��
#define E_LOW     GPIO_ResetBits(GPIOC,E)  //�͵�ƽ����
#define RW_HIGH   GPIO_SetBits(GPIOC,RW)   //�ߵ�ƽ��
#define RW_LOW    GPIO_ResetBits(GPIOC,RW)
#define PSB_HIGH  GPIO_SetBits(GPIOC,PSB)   //����
#define PSB_LOW   GPIO_ResetBits(GPIOC,PSB) //����
#define RST_HIGH  GPIO_SetBits(GPIOC,RST)
#define RST_LOW   GPIO_ResetBits(GPIOC,RST) //�͵�ƽ��Ч


extern void delay_1ms(unsigned int ticks);//�˴��ĺ����õ�ds18b20�ļ���systick����

////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
void LCD_I0_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = RS | RW | E | PSB | RST;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void LCD_DataIo_Out(void)//���������
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void LCD_DataIo_In(void)//����������
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
//дָ��ʱ��
void LCD_Write_Reg(unsigned char adr, unsigned char busy)
{
	__disable_fault_irq();
	//  if(busy)
	//  LCD_Check_Busy();
	delay_1ms(1200);
	LCD_DataIo_Out();
	RS_LOW;//ָ��
	RW_LOW;//д
	E_HIGH;
	GPIO_Write(GPIOA, adr);

	delay_1ms(1000);
	E_LOW;

	__enable_fault_irq();
}
//////////////////////////////////////////////////////////////
//д����ʱ��  д���ݵ�ram   (DDRAM/CGRAM/IRAM/GDRAM)
void LCD_Write_Ram(unsigned char data)
{
	__disable_fault_irq();
	delay_1ms(1200);
	LCD_DataIo_Out();
	RS_HIGH;
	RW_LOW;
	E_HIGH;
	GPIO_Write(GPIOA, data);
	delay_1ms(1000);
	E_LOW;
	__enable_fault_irq();
}
//////////////////////////////////////////////////////////////
//������ʱ��  ��ram����    (DDRAM/CGRAM/IRAM/GDRAM)
unsigned char LCD_Read_Ram(void)
{
	unsigned char dat;
	__disable_fault_irq();
	delay_1ms(1200);
	LCD_DataIo_In();
	RS_HIGH;
	RW_HIGH;
	E_HIGH;
	delay_1ms(1000);
	dat = GPIO_ReadInputData(GPIOA);
	E_LOW;
	__enable_fault_irq();
	return dat;
}
////////////////////////////////////////////////////////////////
//���Ĵ���ʱ��  ��æ ͬʱ���Զ���λ�ü�����ac��ֵ
unsigned char LCD_Check_Busy(void)
{
	unsigned char dat;
	__disable_fault_irq();
	LCD_DataIo_In();
	RS_LOW;
	RW_HIGH;
	E_HIGH;
	delay_1ms(1000);
	dat = GPIO_ReadInputData(GPIOA);

	while(dat & Busy);  //��æ����һ��

	E_LOW;
	LCD_DataIo_Out();
	__enable_fault_irq();
	return dat;
}
////////////////////////////////////////////////////////////////�����ǵײ��������� �����ǵ���api����///////////////////////////////////////////////////////
void LCD_Init(void)
{
	LCD_I0_Config();
	RST_LOW;
	delay_1ms(10000);
	RST_HIGH;
	//  PSB_HIGH;

	LCD_Write_Reg(0x30, 1); //����ָ� 8λ����
	LCD_Write_Reg(0x0c, 1); //������ʾ�� �α��off �α�λ�÷���off
	//  LCD_Write_Reg(0x0f,1);//������ʾ�� �α�on �α�λ�÷���on
	//  LCD_Write_Reg(0x0e,1);//������ʾ�� �α�on �α�λ�÷���off
	LCD_Write_Reg(0x01, 1);
	LCD_Write_Reg(0x06, 1);
}
////////////////////////////////////////////////////////////////
void Set_DDRAM(unsigned char X, unsigned char Y)
{
	if(Y < 1)               //y��1��4֮��
		Y = 0;

	if(Y > 3)
		Y = 3;

	X &= 0x0F;              //����X���ܴ���16

	switch(Y)               //��Yѡ��ڼ���
	{
		case 0:
			X |= 0X80;
			break;//��һ��

		case 1:
			X |= 0X90;
			break;//�ڶ���

		case 2:
			X |= 0X88;
			break;//������

		case 3:
			X |= 0X98;
			break;//������
	}

	LCD_Write_Reg(X, 0);   //д������ ���ǵ�ַddram��ַ
}
////////////////////////////////////////////////////////////////
//��ʾһ���ַ�
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
	Set_DDRAM(X, Y);
	LCD_Write_Ram(DData); //��ʾ����
}


////////////////////////////////////////////////////////////////
//��ʾһ���ַ���
void DisplayList(unsigned char X, unsigned char Y, unsigned char *DData)
{
	Set_DDRAM(X, Y);

	while (*DData != '\0') //�������ִ�β���˳�
	{
		LCD_Write_Ram(*DData);
		DData++;
	}
}
/////////////////////////////////////////////////////////////////
void Display_HZ(unsigned char x, unsigned char y, unsigned char *HZ)
{
	Set_DDRAM(x, y);              //������ʾ����ʼ��ַ
	LCD_Write_Ram(HZ[0]);               //д����Ҫ��ʾ���ֵĸ߰�λ����
	LCD_Write_Ram(HZ[1]);               //д����Ҫ��ʾ�ַ��ĵͰ�λ����
}
///////////////////////////////////////////////////////////////////
void Display_HZ_Line(unsigned char x, unsigned char y, unsigned char *HZ)
{
	unsigned char i = 0;
	Set_DDRAM(x, y);                         //������ʾ����ʼ��ַ

	while(HZ[i] != '\0')
	{
		LCD_Write_Ram(HZ[i++]);                   //д����Ҫ��ʾ���ֵĸ߰�λ����
		LCD_Write_Ram(HZ[i++]);                   //д����Ҫ��ʾ�ַ��ĵͰ�λ����

		if((y + i) % 16 == 0)                 //�����һ��
		{
			x++;

			if(x == 4)                          //�����һ��
				x = 0;

			Set_DDRAM(x, 0);           //����������ʾ����ʼ��ַ
		}
	}
}
////////////////////////////////////////////////////////////////
void LCDClrText(void)//����ı�RAM(DDRAM)
{
	LCD_Write_Reg(0x30, 1);
	LCD_Write_Reg(0x01, 1);    //����ʾ,��DDRAM ��M "20H"�������ַָ��Ϊ00H
}
///////////////////////////////////////////////////////////////////
void LCD_Cusor_OFF(void)
{
	LCD_Write_Reg(0x30, 1);    //ѡ�����ָ�
	LCD_Write_Reg(0x0c, 1);    //����ʾ(���α�,������)
}
////////////////////////////////////////////////////////////////
void LCD_Cusor_ON(void)
{
	LCD_Write_Reg(0x30, 1);    //ѡ�����ָ�
	LCD_Write_Reg(0x0f, 1);    //����ʾ(�α�,����)
}

////////////////////////////////////////////////////////////////
//********************************************************
//����CGRAM�ֿ�
//ST7920 CGRAM���û��Զ���ͼ�꣩�ռ�ֲ�
//�ռ�1��ַ��40H��4FH��16����ַ��һ����ַ��Ӧ�����ֽ�����;��Ӧ������:0000H
//�ռ�2��ַ��50H��5FH��16����ַ��һ����ַ��Ӧ�����ֽ�����;��Ӧ������:0002H
//�ռ�3��ַ��60H��6FH��16����ַ��һ����ַ��Ӧ�����ֽ�����;��Ӧ������:0004H
//�ռ�4��ַ��70H��7FH��16����ַ��һ����ַ��Ӧ�����ֽ�����;��Ӧ������:0006H
//����˵��:numΪ�ռ���,CGRAM_ZIKUΪ��ַָ��
//********************************************************
void Set_CGRAM(unsigned char num, unsigned char *CGRAM_ZIKU)
{
	//    LCD_Write_Reg(0x36,1);         //�л�������ָ�,��ͼ��ʾ��
	//    LCD_Write_Reg(y % 32 + 0x80,1);//�趨GDRAM(��ͼRAM)��ֱλ�õ�ַ,���°�����GDRAM�Ĵ�ֱ��ַ��Ϊ0~31
	//
	//    //�趨GDRAM(��ͼRAM)ˮƽλ�õ�ַ
	//    //0x80 + (y / 32) * 8 ����ȷ�����°���,�ϰ���Ϊ0x80��ʼ,�°���Ϊ0x88��ʼ
	//    //���°�����GDRAM�Ĵ�ֱ��ַ��Ϊ0~31
	//    //WriteCom(x / 16 + 0x80 + (y / 32) * 8);
	//    x = x / 16 + 0x80 + (y / 32) * 8;
	//    LCD_Write_Reg(x,1);
	//    LCD_Write_Reg(0x30,1);         //�л�������ָ�
	unsigned char i, add;
	LCD_Write_Reg(0x34, 1);    //�ٴ�����Ϊ8λ���пڣ���չָ�
	LCD_Write_Reg(0x02, 1);    //SR=0,��������CGRAM��ַ
	LCD_Write_Reg(0x30, 1);    //�ָ�����Ϊ8λ���пڣ�����ָ�
	add = (num << 4) | 0x40; //����CGRAM���׵�ַ

	for(i = 0; i < 16; i++)
	{
		LCD_Write_Reg(add + i, 1); //����CGRAM���׵�ַ
		LCD_Write_Ram(CGRAM_ZIKU[i * 2]); //д���8λ����
		LCD_Write_Ram(CGRAM_ZIKU[i * 2 + 1]); //д���8λ����
	}
}
///////////////////////////////////////////////////////////////////////
//********************************************************
//ָ��λ����ʾCGRAM�����ֺ���
//����˵����xΪ�кţ�yΪ�кţ�numΪ���
//********************************************************
void Display_CGRAM(unsigned char x, unsigned char y, unsigned char num)
{
	Set_DDRAM(x, y);   //������ʾ����ʼ��ַ
	LCD_Write_Ram(0x00);     //д����Ҫ��ʾ���ֵĸ߰�λ����
	LCD_Write_Ram(num * 2);  //д����Ҫ��ʾ�ַ��ĵͰ�λ����
}
////////////////////////////////////////////////////////////////
//********************************************************
//���GDRAM���ݣ�
//������datΪ��������
//********************************************************
void GUI_Fill_GDRAM(unsigned char dat)
{
	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char bGDRAMAddrX = 0x80;  //GDRAMˮƽ��ַ
	unsigned char bGDRAMAddrY = 0x80;  //GDRAM��ֱ��ַ

	LCD_Write_Reg(0x36, 1);      //�򿪻�ͼģʽ

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				LCD_Write_Reg(0x34, 1);   //����Ϊ8λMPU�ӿڣ�����ָ�,��ͼģʽ��
				LCD_Write_Reg(bGDRAMAddrY + j, 1); //��ֱ��ַY
				LCD_Write_Reg(bGDRAMAddrX + k, 1); //ˮƽ��ַX
				LCD_Write_Ram(dat);
				LCD_Write_Ram(dat);
			}
		}

		bGDRAMAddrX = 0x88;
	}

	LCD_Write_Reg(0x30, 1);      //�ָ�����ָ����رջ�ͼģʽ
}
////////////////////////////////////////////////////////////////////////////
//********************************************************
//��㺯��
//������color=1���õ����1��color=0���õ�����ɫ0��
//********************************************************
void GUI_Point(unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char x_Dyte, x_byte;   //�����е�ַ���ֽ�λ�������ֽ��е���1λ
	unsigned char y_Dyte, y_byte;   //����Ϊ����������(ȡֵΪ0��1)���е�ַ(ȡֵΪ0~31)
	unsigned char GDRAM_hbit, GDRAM_lbit;

	LCD_Write_Reg(0x34, 1);       //��չָ������
	/***X,Y���껥��������ͨ��X,Y����***/
	x_Dyte = x / 16;    //������16���ֽ��е���һ��
	x_byte = x & 0x0f;    //�����ڸ��ֽ��е���һλ
	y_Dyte = y / 32;    //0Ϊ�ϰ�����1Ϊ�°���
	y_byte = y & 0x1f;    //������0~31���е���һ��

	LCD_Write_Reg(0x80 + y_byte, 1);   //�趨�е�ַ(y����),���Ǵ�ֱ��ַ
	LCD_Write_Reg(0x80 + x_Dyte + 8 * y_Dyte, 1); //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������������ˮƽ��ַ


	GDRAM_hbit = LCD_Read_Ram();         //Ԥ��ȡ����

	delay_1ms(100);
	GDRAM_hbit = LCD_Read_Ram();    //��ȡ��ǰ��ʾ��8λ����
	delay_1ms(100);
	GDRAM_lbit = LCD_Read_Ram();    //��ȡ��ǰ��ʾ��8λ����
	delay_1ms(100);

	LCD_Write_Reg(0x80 + y_byte, 1);   //�趨�е�ַ(y����)
	LCD_Write_Reg(0x80 + x_Dyte + 8 * y_Dyte, 1); //�趨�е�ַ(x����)����ͨ��8*y_Dyteѡ��������
	delay_1ms(100);

	if(x_byte < 8)        //�ж����ڸ�8λ�������ڵ�8λ
	{
		if(color == 1)
			LCD_Write_Ram(GDRAM_hbit | (0x01 << (7 - x_byte))); //��λGDRAM����8λ��������Ӧ�ĵ�
		else
			LCD_Write_Ram(GDRAM_hbit & (~(0x01 << (7 - x_byte)))); //���GDRAM����8λ��������Ӧ�ĵ�

		LCD_Write_Ram(GDRAM_lbit);       //��ʾGDRAM����8λ����
	}
	else
	{
		LCD_Write_Ram(GDRAM_hbit);

		if(color == 1)
			LCD_Write_Ram(GDRAM_lbit | (0x01 << (15 - x_byte))); //��λGDRAM����8λ��������Ӧ�ĵ�
		else
			LCD_Write_Ram(GDRAM_lbit & (~(0x01 << (15 - x_byte)))); //���GDRAM����8λ��������Ӧ�ĵ�
	}

	LCD_Write_Reg(0x36, 1);         //�ָ�������ָ�
}
/////////////////////////////////////////////////////////////////////////////////
//**************************************************************
//��ˮƽ�ߺ���
//������color=1�����1��color=0�����0��
//  x0,x1Ϊ��ʼ���յ��ˮƽ����ֵ��yΪ��ֱ����ֵ
//**************************************************************
void GUI_HLine(unsigned char x0, unsigned char x1, unsigned char y, unsigned char color)
{
	unsigned char  bak;

	if(x0 > x1)      // ��x0��x1��С�������У��Ա㻭ͼ
	{
		bak = x1;
		x1 = x0;
		x0 = bak;
	}

	do
	{
		GUI_Point(x0, y, color);  // �����������ʾ�������ֱ��
		x0++;
	}
	while(x1 >= x0);
}
//********************************************************
//����ֱ�ߺ���
//������color=1������ɫ1��color=0�����0��
//  xΪ��ʼ���յ��ˮƽ����ֵ��y0,y1Ϊ��ֱ����ֵ
//********************************************************
void GUI_RLine(unsigned char x, unsigned char y0, unsigned char y1, unsigned char color)
{
	unsigned char  bak;

	if(y0 > y1)      // ��y0��y1��С�������У��Ա㻭ͼ
	{
		bak = y1;
		y1 = y0;
		y0 = bak;
	}

	do
	{
		GUI_Point(x, y0, color);  // ���ϵ��������ʾ�������ֱ��
		y0++;
	}
	while(y1 >= y0);
}
///////////////////////////////////////////////////////////////
void GUI_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c)
{
	unsigned char i;
	float x_length, y_length;
	float abs_x_length, abs_y_length;
	float temp = 0;

	x_length = (float)x2 - x1;
	y_length = (float)y2 - y1;

	abs_x_length = abs(x_length);
	abs_y_length = abs(y_length);

	if(abs_x_length > abs_y_length)
	{
		for(i = 0; i < abs_x_length; i++)
		{
			temp = (float)y_length / abs_x_length * i;

			if(x_length < 0)
				GUI_Point(x1 - i, y1 + temp, c);
			else
				GUI_Point(x1 + i, y1 + temp, c);
		}
	}
	else
	{
		for(i = 0; i < abs_y_length; i++)
		{
			temp = (float)x_length / abs_y_length * i;

			if(x_length < 0)
				GUI_Point(x1 + temp, y1 - i, c);
			else
				GUI_Point(x1 + temp, y1 + i, c);
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//***************************************************************************
//�����κ���
//������ x0���������Ͻǵ�x����ֵ
//       y0���������Ͻǵ�y����ֵ
//       x1���������½ǵ�x����ֵ
//       y1���������½ǵ�y����ֵ
//       color=1������ɫ1��color=0�����0��
//****************************************************************************
void GUI_Rectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color)
{
	GUI_HLine(x0, x1, y0, color);
	GUI_RLine(x0, y0, y1, color);
	GUI_RLine(x1, y0, y1, color);
	GUI_HLine(x0, x1, y1, color);
}
///////////////////////////////////////////////////////////////////////////////
//***************************************************************************
//�����κ���
//������ x0���������Ͻǵ�x����ֵ
//       y0���������Ͻǵ�y����ֵ
//       x1���������½ǵ�x����ֵ
//       y1���������½ǵ�y����ֵ
//       color=1�����1��color=0�����0��
//****************************************************************************
void GUI_Rectangle_Fill(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color)
{
	unsigned char  i;

	//���ҳ��������Ͻ������½ǵ������㣬������(x0,y0)��(x1,y1)
	if(x0 > x1)     // ��x0>x1����x0��x1����
	{
		i = x0;
		x0 = x1;
		x1 = i;
	}

	if(y0 > y1)    // ��y0>y1����y0��y1����
	{
		i = y0;
		y0 = y1;
		y1 = i;
	}

	//�ж��Ƿ�ֻ��ֱ��
	if(y0 == y1)
	{
		GUI_HLine(x0, x1, y0, color);
		return;
	}

	if(x0 == x1)
	{
		GUI_RLine(x0, y0, y1, color);
		return;
	}

	while(y0 <= y1)
	{
		GUI_HLine(x0, x1, y0, color); // ��ǰ��ˮƽ��
		y0++;       // ��һ��
	}
}
//***************************************************************************
//�������κ���
//������x0:���������Ͻǵ�x����ֵ
//      y0:���������Ͻǵ�y����ֵ
//      with:�����εı߳�
//      color=1�����1��color=0�����0��
//˵���������μ��ǳ�����ȵ��������
//****************************************************************************
void GUI_Square(unsigned char x0, unsigned char y0, unsigned char with, unsigned char  color)
{
	if(with == 0) return;

	if((x0 + with) > 127) return;

	if((y0 + with) > 63) return;

	GUI_Rectangle(x0, y0, x0 + with, y0 + with, color);
}
//***************************************************************************
//�������β����
//������x0:���������Ͻǵ�x����ֵ
//      y0:���������Ͻǵ�y����ֵ
//      with:�����εı߳�
//      color=1������ɫ(1)��color=0������ɫ(0)
//****************************************************************************
void GUI_Square_Fill(unsigned char x0, unsigned char y0, unsigned char with, unsigned char color)
{
	if(with == 0) return;

	if( (x0 + with) > 127 ) return;

	if( (y0 + with) > 163) return;

	GUI_Rectangle_Fill(x0, y0, x0 + with, y0 + with, color);
}
//********************************************************
//��Բ����
//������color=1�����1��color=0�����0��
//      x0��y0ΪԲ�����꣬rΪԲ�İ뾶��
//********************************************************
void GUI_Circle(unsigned char x0, unsigned char y0, unsigned char r, unsigned char color)
{
	signed char a, b;
	signed char di;

	if(r > 31 || r == 0) return; //�������ˣ���Һ����ʾ�����Բ�뾶Ϊ31

	a = 0;
	b = r;
	di = 3 - 2 * r; //�ж��¸���λ�õı�־

	while(a <= b)
	{
		GUI_Point(x0 - b, y0 - a, color); //3
		GUI_Point(x0 + b, y0 - a, color); //0
		GUI_Point(x0 - a, y0 + b, color); //1
		GUI_Point(x0 - b, y0 - a, color); //7
		GUI_Point(x0 - a, y0 - b, color); //2
		GUI_Point(x0 + b, y0 + a, color); //4
		GUI_Point(x0 + a, y0 - b, color); //5
		GUI_Point(x0 + a, y0 + b, color); //6
		GUI_Point(x0 - b, y0 + a, color);
		a++;

		/***ʹ��Bresenham�㷨��Բ**/
		if(di < 0)
			di += 4 * a + 6;
		else
		{
			di += 10 + 4 * (a - b);
			b--;
		}

		GUI_Point(x0 + a, y0 + b, color);
	}
}
