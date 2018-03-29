#ifndef _LCD12864_H
#define _LCD12864_H

void delay(unsigned char i);

void LCD_I0_Config(void);                                //��ʼ��io�˿�
void LCD_DataIo_Out(void);                               //���ݶ˿��������
void LCD_DataIo_In(void);                                //���ݶ˿����ö���
void LCD_Write_Reg(unsigned char adr, unsigned char busy); //д����
void LCD_Write_Ram(unsigned char data);                  //д����
unsigned char LCD_Read_Ram(void);                        //�����ݵ�ǰ��ַ����
unsigned char LCD_Check_Busy(void);                  //��״̬ ��û����


void LCD_Init(void);                                                        //Һ����ʼ������
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData); //��ʾһ���ַ�
void DisplayList(unsigned char X, unsigned char Y, unsigned char *DData);   //��ʾһ���ַ���
void LCDClrText(void);     //����ģʽ���ram
void LCD_Cusor_OFF(void);                                                   //���ص�
void LCD_Cusor_ON(void);                                                    //��꿪
void Set_DDRAM(unsigned char x, unsigned char y);                           //����ddram��ַ ��ʾ����RAM��DDRAM)
void Set_CGRAM(unsigned char num, unsigned char *CGRAM_ZIKU);                                                                           //CGROM�������ֿ⣩��HCGROM��ASCII���ֿ⣩//
//��CGRAM���Զ������Σ�����ʾ����RAM��DDRAM)���ַ���ʾRAM��������DDRAM������
void Display_HZ(unsigned char x, unsigned char y, unsigned char *HZ);
void Display_HZ_Line(unsigned char x, unsigned char y, unsigned char *HZ);
void Display_CGRAM(unsigned char x, unsigned char y, unsigned char num);    //��ʾ�����ֿ�
void GUI_Fill_GDRAM(unsigned char dat);                                     //��� �ο�����
void GUI_Point(unsigned char x, unsigned char y, unsigned char color);      //���ο�����
void GUI_HLine(unsigned char x0, unsigned char x1, unsigned char y, unsigned char color) ;//ˮƽ��
void GUI_RLine(unsigned char x, unsigned char y0, unsigned char y1, unsigned char color);//��ֱ��
void GUI_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bit);
void GUI_Rectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color);
void GUI_Rectangle_Fill(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color);
void GUI_Square(unsigned char x0, unsigned char y0, unsigned char with, unsigned char  color);
void GUI_Square_Fill(unsigned char x0, unsigned char y0, unsigned char with, unsigned char color);
void GUI_Circle(unsigned char x0, unsigned char y0, unsigned char r, unsigned char color);
#endif
