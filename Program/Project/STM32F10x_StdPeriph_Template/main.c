#include "stm32f10x.h"
#include "include_all.h"
#include<string.h>
#include<stdio.h>

#define WAIT 1                     //����������־�� �ڲ˵��������ܺ�����ʹ��
#define OUT 0


unsigned char get_keyboard_value; //����ɨ���ֵ 1-16
float value = 0;                  //�¶ȴ�������ֵ
extern void delay_1ms(unsigned int value);//systick
unsigned char index = 0;                  //����ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char  CGRAM_ZIKU_I2C[32] =
{
	0x03, 0x80, 0x00, 0x80, 0xF8, 0x8E, 0x23, 0x91, 0x22, 0x21, 0x22, 0x20, 0x23, 0xA0, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x20, 0x11, 0xF8, 0x0E, 0x00, 0x00, 0x00, 0x00
};//I2C
/////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct MenuStruct
{
	unsigned char KeyIndex;
	unsigned char *test;
	void (*fun)(void);
	struct MenuStruct *ChildrenMenus; //�ӽڵ�
	struct MenuStruct *ParentMenus;     //���ڵ�
} MenuStruct;

struct MenuStruct Menu_0[4];          //����˵���Ŀ�ĸ�
struct MenuStruct Menu_1[4];
struct MenuStruct Menu_2[4];
struct MenuStruct Menu_3[4];
struct MenuStruct Menu_4[4];
/////////////////////////////////////////////////////////////////////////////////////////////////////
void show_menu(void);                        //�˵���ʾ
void menu_change(unsigned char key_change);  //���������˵�
void fun_0(void);                            //���ܺ���
void fun_1(void);
void fun_2(void);
void fun_3(void);
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct MenuStruct MainMenu[4] =
{
	{0,             "1.ffcaidan1  ",            fun_0,         Menu_0,             MainMenu},
	{1,             "2.ffcaidan2  ",            fun_0,         Menu_1,             MainMenu},
	{2,             "3.ffcaidan3  ",            fun_0,         Menu_2,             MainMenu},
	{3,             "4.ffcaidan4  ",            fun_0,         Menu_3,             MainMenu}
};
///////////////////////////////////
struct MenuStruct Menu_0[4] =
{
	{0,             "1.xcaidan1  ",             fun_0,         0,              MainMenu},
	{1,             "2.xcaidan2  ",             fun_0,         0,              MainMenu},
	{2,             "3.xcaidan3  ",             fun_0,         0,              MainMenu},
	{3,             "4.xcaidan4  ",             fun_0,         MainMenu,           MainMenu}
};
///////////////////////////////////
struct MenuStruct Menu_1[4] =
{
	{0,             "1.ycaidan1  ",             fun_0,         0,              MainMenu},
	{1,             "2.ycaidan2  ",             fun_0,         0,              MainMenu},
	{2,             "3.ycaidan3  ",             fun_0,         0,              MainMenu},
	{3,             "4.ycaidan4  ",             fun_0,         MainMenu,           MainMenu}
};
///////////////////////////////////
struct MenuStruct Menu_2[4] =
{
	{0,             "1.zcaidan1  ",             fun_0,         0,              MainMenu},
	{1,             "2.zcaidan2  ",             fun_0,         0,              MainMenu},
	{2,             "3.zcaidan3  ",             fun_0,         0,              MainMenu},
	{3,             "4.zcaidan4  ",             fun_0,         MainMenu,           MainMenu}
};
///////////////////////////////////
struct MenuStruct Menu_3[4] =
{
	{0,             "1.vcaidan1  ",             fun_0,         0,              MainMenu},
	{1,             "2.vcaidan2  ",             fun_0,         0,              MainMenu},
	{2,             "3.vcaidan3  ",             fun_0,         0,              MainMenu},
	{3,             "4.vcaidan4  ",             fun_0,         MainMenu,           MainMenu}
};
///////////////////////////////////
struct MenuStruct (*MenuPoint) = MainMenu; //����ṹ��ָ��
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	RCC_Configuration();   //ʱ�����û���һ�������� û�н��
	Usart1_Init();         //�������� \ 
	Adc_Init();            //��·adc����
	//  Timer2_Init();         //��ʱ������
	Timer3_Init();         //��ʱ������

	//  debug();               //����ģʽ
	LCD_Init();            //Һ����ʼ��
	LCD_Cusor_OFF();       //���ص�
	STM_Ds18b20_Init();    //�¶ȴ�������ʼ��



	while(1)
	{
		menu_change(get_keyboard_value);//�˵�����
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void show_menu(void)
{
	unsigned char n;

	for(n = 0; n < 4; n++)
	{
		if(n == index)
		{
			DisplayList(0, n, "->");
		}
		else
		{
			DisplayList(0, n, "  ");
		}

		DisplayList(1, n, MenuPoint[n].test);
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void menu_change(unsigned char key_change)
{
	delay_1ms(720000);

	if(key_change != 0xff)
	{
		delay_1ms(720000);

		switch (key_change)
		{
			case 1:
				index++;//����

				if(index > 3)
					index = 0;

				break;

			case 2:
				index--;//����

				if(index == 0xff)
					index = 3;

				break;

			case 3:
				if (MenuPoint[index].ChildrenMenus != 0)
				{
					MenuPoint = MenuPoint[index].ChildrenMenus;
					index = 0;
				}
				else
				{
					MenuPoint[index].fun();
				}

				break;

			case 4:
				if(MenuPoint != 0)
				{
					MenuPoint = MenuPoint[index].ParentMenus;
				}
				else
				{
					MenuPoint = MainMenu;
				}

				//                    index = 0;
				break;

			default:
				break;
		}
	}

	show_menu();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_0(void) //���ܺ���
{
	unsigned char Exit_flag = WAIT;
	LCDClrText();
	delay_1ms(100000);

	//  Timer2_Init();
	while(Exit_flag)
	{
		Display_HZ_Line(2, 2, "����������");
		get_keyboard_value = Key_Scan();

		if(get_keyboard_value != 0xff)
		{
			Exit_flag = OUT;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_1(void)
{
	unsigned char Exit_flag = WAIT;

	while(Exit_flag)
	{

		get_keyboard_value = Key_Scan();

		if(get_keyboard_value != 0xff)
		{
			Exit_flag = OUT;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_2(void)
{
	unsigned char Exit_flag = WAIT;

	while(Exit_flag)
	{
		get_keyboard_value = Key_Scan();

		if(get_keyboard_value != 0xff)
		{
			Exit_flag = OUT;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_3(void)
{
	unsigned char Exit_flag = WAIT;

	while(Exit_flag)
	{
		get_keyboard_value = Key_Scan();

		if(get_keyboard_value != 0xff)
		{
			Exit_flag = OUT;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

//  GUI_Fill_GDRAM(0x00);
//  Set_CGRAM(1,CGRAM_ZIKU_I2C); //���Զ�����ֿ�д��CGRAM
//  Display_CGRAM(0,1,1);         //ָ��λ����ʾ�Զ�����ֿ�
//  GUI_Fill_GDRAM(0x00);

//
//  GUI_Fill_GDRAM(0x00);
//  GUI_Point(64,32,1);          //������
//  GUI_Point(1,8,1);            //������
//  GUI_Point(15,8,1);            //������
//  GUI_Point(18,44,1);            //������
//  GUI_Fill_GDRAM(0xff);
//  GUI_Point(64,32,0);          //������
//  GUI_Point(1,8,0);           //������


//  GUI_HLine(10,120,10,1);         //��ˮƽ�߲���
//  GUI_RLine(10,10,60,1);          //����ֱ�߲���
//  GUI_Line(1,1,117,63,1);
//  GUI_Line(1,1,12,63,1);
//  GUI_Line(62,1,45,45,1);
//  GUI_Rectangle(5,5,122,58,1);
//  GUI_Rectangle_Fill(1,1,5,5,1);
//  GUI_Circle(32,32,30,1);
//  GUI_Square(10,10,50,1);         //�������β���
//  GUI_Square_Fill(20,20,20,1);    //��������β���
/////////////////////////////////////////////////////////
#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
	printf("\n\r Wrong parameter value detected on\r\n");
	printf("       file  %s\r\n", file);
	printf("       line  %d\r\n", line);

	while (1)
	{
	}
}
#endif






