#ifndef _LCD12864_H
#define _LCD12864_H

void delay(unsigned char i);

void LCD_I0_Config(void);                                //初始化io端口
void LCD_DataIo_Out(void);                               //数据端口设置输出
void LCD_DataIo_In(void);                                //数据端口设置读入
void LCD_Write_Reg(unsigned char adr, unsigned char busy); //写命令
void LCD_Write_Ram(unsigned char data);                  //写数据
unsigned char LCD_Read_Ram(void);                        //读数据当前地址数据
unsigned char LCD_Check_Busy(void);                  //读状态 还没测试


void LCD_Init(void);                                                        //液晶初始化函数
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData); //显示一个字符
void DisplayList(unsigned char X, unsigned char Y, unsigned char *DData);   //显示一个字符串
void LCDClrText(void);     //文字模式清楚ram
void LCD_Cusor_OFF(void);                                                   //光标关掉
void LCD_Cusor_ON(void);                                                    //光标开
void Set_DDRAM(unsigned char x, unsigned char y);                           //设置ddram地址 显示数据RAM（DDRAM)
void Set_CGRAM(unsigned char num, unsigned char *CGRAM_ZIKU);                                                                           //CGROM（中文字库）、HCGROM（ASCII码字库）//
//及CGRAM（自定义字形）、显示数据RAM（DDRAM)、字符显示RAM缓冲区（DDRAM）。）
void Display_HZ(unsigned char x, unsigned char y, unsigned char *HZ);
void Display_HZ_Line(unsigned char x, unsigned char y, unsigned char *HZ);
void Display_CGRAM(unsigned char x, unsigned char y, unsigned char num);    //显示自造字库
void GUI_Fill_GDRAM(unsigned char dat);                                     //打点 参考网络
void GUI_Point(unsigned char x, unsigned char y, unsigned char color);      //打点参考网络
void GUI_HLine(unsigned char x0, unsigned char x1, unsigned char y, unsigned char color) ;//水平线
void GUI_RLine(unsigned char x, unsigned char y0, unsigned char y1, unsigned char color);//竖直线
void GUI_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bit);
void GUI_Rectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color);
void GUI_Rectangle_Fill(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color);
void GUI_Square(unsigned char x0, unsigned char y0, unsigned char with, unsigned char  color);
void GUI_Square_Fill(unsigned char x0, unsigned char y0, unsigned char with, unsigned char color);
void GUI_Circle(unsigned char x0, unsigned char y0, unsigned char r, unsigned char color);
#endif
