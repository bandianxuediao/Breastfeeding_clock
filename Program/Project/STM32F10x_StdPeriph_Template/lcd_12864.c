#include "lcd_12864.h"
#include "stm32f10x.h"
#include "string.h"
#include <STDLIB.H>

#define Busy    0x80


#define RS GPIO_Pin_8 //pc
#define RW GPIO_Pin_7
#define E  GPIO_Pin_2
#define PSB GPIO_Pin_3//串行并行转换
#define RST GPIO_Pin_4




#define DATA GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 //pa

#define RS_HIGH   GPIO_SetBits(GPIOC,RS)   //数据
#define RS_LOW    GPIO_ResetBits(GPIOC,RS) //指令
#define E_HIGH    GPIO_SetBits(GPIOC,E)    //高电平使能
#define E_LOW     GPIO_ResetBits(GPIOC,E)  //低电平除能
#define RW_HIGH   GPIO_SetBits(GPIOC,RW)   //高电平读
#define RW_LOW    GPIO_ResetBits(GPIOC,RW)
#define PSB_HIGH  GPIO_SetBits(GPIOC,PSB)   //并行
#define PSB_LOW   GPIO_ResetBits(GPIOC,PSB) //串行
#define RST_HIGH  GPIO_SetBits(GPIOC,RST)
#define RST_LOW   GPIO_ResetBits(GPIOC,RST) //低电平有效


extern void delay_1ms(unsigned int ticks);//此处的函数用的ds18b20文件中systick函数

////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
void LCD_I0_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = RS | RW | E | PSB | RST;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void LCD_DataIo_Out(void)//数据线输出
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
void LCD_DataIo_In(void)//数据线输入
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
////////////////////////////////////////////////////////////////
//写指令时序
void LCD_Write_Reg(unsigned char adr, unsigned char busy)
{
	__disable_fault_irq();
	//  if(busy)
	//  LCD_Check_Busy();
	delay_1ms(1200);
	LCD_DataIo_Out();
	RS_LOW;//指令
	RW_LOW;//写
	E_HIGH;
	GPIO_Write(GPIOA, adr);

	delay_1ms(1000);
	E_LOW;

	__enable_fault_irq();
}
//////////////////////////////////////////////////////////////
//写数据时序  写数据到ram   (DDRAM/CGRAM/IRAM/GDRAM)
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
//读数据时序  读ram数据    (DDRAM/CGRAM/IRAM/GDRAM)
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
//读寄存器时序  读忙 同时可以读出位置计数器ac的值
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

	while(dat & Busy);  //不忙走下一步

	E_LOW;
	LCD_DataIo_Out();
	__enable_fault_irq();
	return dat;
}
////////////////////////////////////////////////////////////////上面是底层驱动函数 下面是调用api函数///////////////////////////////////////////////////////
void LCD_Init(void)
{
	LCD_I0_Config();
	RST_LOW;
	delay_1ms(10000);
	RST_HIGH;
	//  PSB_HIGH;

	LCD_Write_Reg(0x30, 1); //基本指令集 8位控制
	LCD_Write_Reg(0x0c, 1); //整体显示开 游标关off 游标位置反白off
	//  LCD_Write_Reg(0x0f,1);//整体显示开 游标on 游标位置反白on
	//  LCD_Write_Reg(0x0e,1);//整体显示开 游标on 游标位置反白off
	LCD_Write_Reg(0x01, 1);
	LCD_Write_Reg(0x06, 1);
}
////////////////////////////////////////////////////////////////
void Set_DDRAM(unsigned char X, unsigned char Y)
{
	if(Y < 1)               //y在1和4之间
		Y = 0;

	if(Y > 3)
		Y = 3;

	X &= 0x0F;              //限制X不能大于16

	switch(Y)               //用Y选择第几行
	{
		case 0:
			X |= 0X80;
			break;//第一行

		case 1:
			X |= 0X90;
			break;//第二行

		case 2:
			X |= 0X88;
			break;//第三行

		case 3:
			X |= 0X98;
			break;//第四行
	}

	LCD_Write_Reg(X, 0);   //写控制字 就是地址ddram地址
}
////////////////////////////////////////////////////////////////
//显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
	Set_DDRAM(X, Y);
	LCD_Write_Ram(DData); //显示数据
}


////////////////////////////////////////////////////////////////
//显示一个字符串
void DisplayList(unsigned char X, unsigned char Y, unsigned char *DData)
{
	Set_DDRAM(X, Y);

	while (*DData != '\0') //若到达字串尾则退出
	{
		LCD_Write_Ram(*DData);
		DData++;
	}
}
/////////////////////////////////////////////////////////////////
void Display_HZ(unsigned char x, unsigned char y, unsigned char *HZ)
{
	Set_DDRAM(x, y);              //设置显示的起始地址
	LCD_Write_Ram(HZ[0]);               //写入需要显示汉字的高八位数据
	LCD_Write_Ram(HZ[1]);               //写入需要显示字符的低八位数据
}
///////////////////////////////////////////////////////////////////
void Display_HZ_Line(unsigned char x, unsigned char y, unsigned char *HZ)
{
	unsigned char i = 0;
	Set_DDRAM(x, y);                         //设置显示的起始地址

	while(HZ[i] != '\0')
	{
		LCD_Write_Ram(HZ[i++]);                   //写入需要显示汉字的高八位数据
		LCD_Write_Ram(HZ[i++]);                   //写入需要显示字符的低八位数据

		if((y + i) % 16 == 0)                 //如果满一行
		{
			x++;

			if(x == 4)                          //如果满一屏
				x = 0;

			Set_DDRAM(x, 0);           //重新设置显示的起始地址
		}
	}
}
////////////////////////////////////////////////////////////////
void LCDClrText(void)//清除文本RAM(DDRAM)
{
	LCD_Write_Reg(0x30, 1);
	LCD_Write_Reg(0x01, 1);    //清显示,將DDRAM 填滿 "20H"，并设地址指针为00H
}
///////////////////////////////////////////////////////////////////
void LCD_Cusor_OFF(void)
{
	LCD_Write_Reg(0x30, 1);    //选择基本指令集
	LCD_Write_Reg(0x0c, 1);    //开显示(无游标,不反白)
}
////////////////////////////////////////////////////////////////
void LCD_Cusor_ON(void)
{
	LCD_Write_Reg(0x30, 1);    //选择基本指令集
	LCD_Write_Reg(0x0f, 1);    //开显示(游标,反白)
}

////////////////////////////////////////////////////////////////
//********************************************************
//设置CGRAM字库
//ST7920 CGRAM（用户自定义图标）空间分布
//空间1地址：40H～4FH共16个地址，一个地址对应两个字节数据;对应调用码:0000H
//空间2地址：50H～5FH共16个地址，一个地址对应两个字节数据;对应调用码:0002H
//空间3地址：60H～6FH共16个地址，一个地址对应两个字节数据;对应调用码:0004H
//空间4地址：70H～7FH共16个地址，一个地址对应两个字节数据;对应调用码:0006H
//参数说明:num为空间编号,CGRAM_ZIKU为地址指针
//********************************************************
void Set_CGRAM(unsigned char num, unsigned char *CGRAM_ZIKU)
{
	//    LCD_Write_Reg(0x36,1);         //切换到扩充指令集,绘图显示开
	//    LCD_Write_Reg(y % 32 + 0x80,1);//设定GDRAM(绘图RAM)垂直位置地址,上下半屏中GDRAM的垂直地址都为0~31
	//
	//    //设定GDRAM(绘图RAM)水平位置地址
	//    //0x80 + (y / 32) * 8 用于确定上下半屏,上半屏为0x80开始,下半屏为0x88开始
	//    //上下半屏中GDRAM的垂直地址都为0~31
	//    //WriteCom(x / 16 + 0x80 + (y / 32) * 8);
	//    x = x / 16 + 0x80 + (y / 32) * 8;
	//    LCD_Write_Reg(x,1);
	//    LCD_Write_Reg(0x30,1);         //切换到基本指令集
	unsigned char i, add;
	LCD_Write_Reg(0x34, 1);    //再次设置为8位并行口，扩展指令集
	LCD_Write_Reg(0x02, 1);    //SR=0,允许设置CGRAM地址
	LCD_Write_Reg(0x30, 1);    //恢复设置为8位并行口，基本指令集
	add = (num << 4) | 0x40; //计算CGRAM的首地址

	for(i = 0; i < 16; i++)
	{
		LCD_Write_Reg(add + i, 1); //设置CGRAM的首地址
		LCD_Write_Ram(CGRAM_ZIKU[i * 2]); //写入高8位数据
		LCD_Write_Ram(CGRAM_ZIKU[i * 2 + 1]); //写入低8位数据
	}
}
///////////////////////////////////////////////////////////////////////
//********************************************************
//指定位置显示CGRAM自造字函数
//参数说明：x为行号，y为列号，num为编号
//********************************************************
void Display_CGRAM(unsigned char x, unsigned char y, unsigned char num)
{
	Set_DDRAM(x, y);   //设置显示的起始地址
	LCD_Write_Ram(0x00);     //写入需要显示汉字的高八位数据
	LCD_Write_Ram(num * 2);  //写入需要显示字符的低八位数据
}
////////////////////////////////////////////////////////////////
//********************************************************
//填充GDRAM数据：
//参数：dat为填充的数据
//********************************************************
void GUI_Fill_GDRAM(unsigned char dat)
{
	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char bGDRAMAddrX = 0x80;  //GDRAM水平地址
	unsigned char bGDRAMAddrY = 0x80;  //GDRAM垂直地址

	LCD_Write_Reg(0x36, 1);      //打开绘图模式

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				LCD_Write_Reg(0x34, 1);   //设置为8位MPU接口，扩充指令集,绘图模式关
				LCD_Write_Reg(bGDRAMAddrY + j, 1); //垂直地址Y
				LCD_Write_Reg(bGDRAMAddrX + k, 1); //水平地址X
				LCD_Write_Ram(dat);
				LCD_Write_Ram(dat);
			}
		}

		bGDRAMAddrX = 0x88;
	}

	LCD_Write_Reg(0x30, 1);      //恢复基本指令集，关闭绘图模式
}
////////////////////////////////////////////////////////////////////////////
//********************************************************
//打点函数
//参数：color=1，该点填充1；color=0，该点填充白色0；
//********************************************************
void GUI_Point(unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char x_Dyte, x_byte;   //定义列地址的字节位，及在字节中的哪1位
	unsigned char y_Dyte, y_byte;   //定义为上下两个屏(取值为0，1)，行地址(取值为0~31)
	unsigned char GDRAM_hbit, GDRAM_lbit;

	LCD_Write_Reg(0x34, 1);       //扩展指令命令
	/***X,Y坐标互换，即普通的X,Y坐标***/
	x_Dyte = x / 16;    //计算在16个字节中的哪一个
	x_byte = x & 0x0f;    //计算在该字节中的哪一位
	y_Dyte = y / 32;    //0为上半屏，1为下半屏
	y_byte = y & 0x1f;    //计算在0~31当中的哪一行

	LCD_Write_Reg(0x80 + y_byte, 1);   //设定行地址(y坐标),即是垂直地址
	LCD_Write_Reg(0x80 + x_Dyte + 8 * y_Dyte, 1); //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏，即是水平地址


	GDRAM_hbit = LCD_Read_Ram();         //预读取数据

	delay_1ms(100);
	GDRAM_hbit = LCD_Read_Ram();    //读取当前显示高8位数据
	delay_1ms(100);
	GDRAM_lbit = LCD_Read_Ram();    //读取当前显示低8位数据
	delay_1ms(100);

	LCD_Write_Reg(0x80 + y_byte, 1);   //设定行地址(y坐标)
	LCD_Write_Reg(0x80 + x_Dyte + 8 * y_Dyte, 1); //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
	delay_1ms(100);

	if(x_byte < 8)        //判断其在高8位，还是在低8位
	{
		if(color == 1)
			LCD_Write_Ram(GDRAM_hbit | (0x01 << (7 - x_byte))); //置位GDRAM区高8位数据中相应的点
		else
			LCD_Write_Ram(GDRAM_hbit & (~(0x01 << (7 - x_byte)))); //清除GDRAM区高8位数据中相应的点

		LCD_Write_Ram(GDRAM_lbit);       //显示GDRAM区低8位数据
	}
	else
	{
		LCD_Write_Ram(GDRAM_hbit);

		if(color == 1)
			LCD_Write_Ram(GDRAM_lbit | (0x01 << (15 - x_byte))); //置位GDRAM区高8位数据中相应的点
		else
			LCD_Write_Ram(GDRAM_lbit & (~(0x01 << (15 - x_byte)))); //清除GDRAM区高8位数据中相应的点
	}

	LCD_Write_Reg(0x36, 1);         //恢复到基本指令集
}
/////////////////////////////////////////////////////////////////////////////////
//**************************************************************
//画水平线函数
//参数：color=1，填充1；color=0，填充0；
//  x0,x1为起始和终点的水平坐标值，y为垂直坐标值
//**************************************************************
void GUI_HLine(unsigned char x0, unsigned char x1, unsigned char y, unsigned char color)
{
	unsigned char  bak;

	if(x0 > x1)      // 对x0、x1大小进行排列，以便画图
	{
		bak = x1;
		x1 = x0;
		x0 = bak;
	}

	do
	{
		GUI_Point(x0, y, color);  // 从左到右逐点显示，描出垂直线
		x0++;
	}
	while(x1 >= x0);
}
//********************************************************
//画竖直线函数
//参数：color=1，填充黑色1；color=0，填充0；
//  x为起始和终点的水平坐标值，y0,y1为垂直坐标值
//********************************************************
void GUI_RLine(unsigned char x, unsigned char y0, unsigned char y1, unsigned char color)
{
	unsigned char  bak;

	if(y0 > y1)      // 对y0、y1大小进行排列，以便画图
	{
		bak = y1;
		y1 = y0;
		y0 = bak;
	}

	do
	{
		GUI_Point(x, y0, color);  // 从上到下逐点显示，描出垂直线
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
//画矩形函数
//参数： x0：矩形左上角的x坐标值
//       y0：矩形左上角的y坐标值
//       x1：矩形右下角的x坐标值
//       y1：矩形右下角的y坐标值
//       color=1，填充黑色1；color=0，填充0；
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
//填充矩形函数
//参数： x0：矩形左上角的x坐标值
//       y0：矩形左上角的y坐标值
//       x1：矩形右下角的x坐标值
//       y1：矩形右下角的y坐标值
//       color=1，填充1；color=0，填充0；
//****************************************************************************
void GUI_Rectangle_Fill(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color)
{
	unsigned char  i;

	//先找出矩形左上角与右下角的两个点，保存在(x0,y0)，(x1,y1)
	if(x0 > x1)     // 若x0>x1，则x0与x1交换
	{
		i = x0;
		x0 = x1;
		x1 = i;
	}

	if(y0 > y1)    // 若y0>y1，则y0与y1交换
	{
		i = y0;
		y0 = y1;
		y1 = i;
	}

	//判断是否只是直线
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
		GUI_HLine(x0, x1, y0, color); // 当前画水平线
		y0++;       // 下一行
	}
}
//***************************************************************************
//画正方形函数
//参数：x0:正方形左上角的x坐标值
//      y0:正方形左上角的y坐标值
//      with:正方形的边长
//      color=1，填充1；color=0，填充0；
//说明：正方形即是长宽相等的特殊矩形
//****************************************************************************
void GUI_Square(unsigned char x0, unsigned char y0, unsigned char with, unsigned char  color)
{
	if(with == 0) return;

	if((x0 + with) > 127) return;

	if((y0 + with) > 63) return;

	GUI_Rectangle(x0, y0, x0 + with, y0 + with, color);
}
//***************************************************************************
//画正方形并填充
//参数：x0:正方形左上角的x坐标值
//      y0:正方形左上角的y坐标值
//      with:正方形的边长
//      color=1，填充黑色(1)；color=0，填充白色(0)
//****************************************************************************
void GUI_Square_Fill(unsigned char x0, unsigned char y0, unsigned char with, unsigned char color)
{
	if(with == 0) return;

	if( (x0 + with) > 127 ) return;

	if( (y0 + with) > 163) return;

	GUI_Rectangle_Fill(x0, y0, x0 + with, y0 + with, color);
}
//********************************************************
//画圆函数
//参数：color=1，填充1；color=0，填充0；
//      x0，y0为圆心坐标，r为圆的半径；
//********************************************************
void GUI_Circle(unsigned char x0, unsigned char y0, unsigned char r, unsigned char color)
{
	signed char a, b;
	signed char di;

	if(r > 31 || r == 0) return; //参数过滤，次液晶显示的最大圆半径为31

	a = 0;
	b = r;
	di = 3 - 2 * r; //判断下个点位置的标志

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

		/***使用Bresenham算法画圆**/
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
