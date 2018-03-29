#ifndef __12864_H
#define __12864_H
#define     uchar                  unsigned char      
#define     uint                   unsigned int
uchar adc_data[4]={0,0,0,0};

#define Fcy 7370000                  //7.37MHz外部晶振带4倍频，指令周期为7.37MIPs
#define u8   unsigned char 
#define u16  unsigned int 

/*******************12864液晶端口定义****************************
****************************************************************/
#define     LCD_RCC  RCC_APB2Periph_GPIOC	   
#define     LCD_PORT   GPIOC				  //C0-C7 
#define     LCD_DATA  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7        // LATB       //8 bit数据线
#define     LCD_EN   PEout(4)  //GPIO_Pin_4     //PE4     LATGbits.LATG3     //片选信号
#define     LCD_RW   PEout(3)  //GPIO_Pin_3      //PE3   LATGbits.LATG2     //读写控制
#define     LCD_RS   PEout(2)  //GPIO_Pin_2     //PE2   LATCbits.LATC15    //数据/命令选择
#define     LCD_CS1  PAout(0)  // GPIO_Pin_0   //PA0   LATFbits.LATF6     //左半屏
#define     LCD_CS2  PAout(1)   //GPIO_Pin_1    //PA1   LATFbits.LATF2     //右半屏
//#define     LCD_RST                PORTB.5     //LCD复位

/********************12864液晶初始化指令定义*********************
****************************************************************/
#define CLEAR_SCREEN 0x01  //清屏指令：清屏且AC值为00H
#define AC_INIT   0x02  //将AC设置为00H。且游标移到原点位置
#define CURSE_ADD  0x06  //设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE  0x30  //工作模式：8位基本指令集
#define DISPLAY_ON  0x0c  //显示开,显示游标，且游标位置反白
#define DISPLAY_OFF  0x08  //显示关
#define CURSE_DIR  0x14  //游标向右移动:AC=AC+1
#define SET_CG_AC  0x40  //设置AC，范围为：00H~3FH
#define SET_DD_AC  0x80
#define Disp_On  0x3f       //显示开
#define Disp_Off 0x3e       //显示关
#define Col_Add  0x40
#define Page_Add 0xb8
#define Start_Line 0xc0

/**********************************字模表***********************************/
/*****************************放电显示（3.7V）******************************/
uchar fang[]={
/*--  文字:  放  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x08,0xF8,0x49,0x4E,0xC8,0x88,0x40,0x38,0xCF,0x0A,0x08,0x88,0x78,0x08,0x00,
0x40,0x30,0x0F,0x40,0x80,0x7F,0x00,0x40,0x20,0x10,0x0B,0x0E,0x31,0x60,0x20,0x00}; 

uchar dian[]={
/*--  文字:  电  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xF8,0x48,0x48,0x48,0x48,0xFF,0x48,0x48,0x48,0x48,0xF8,0x00,0x00,0x00,
0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0x3F,0x44,0x44,0x44,0x44,0x4F,0x40,0x70,0x00};

uchar xian[]={
/*--  文字:  显  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x3E,0x2A,0xEA,0x2A,0x2A,0x2A,0xEA,0x2A,0x3E,0x00,0x00,0x00,0x00,
0x20,0x21,0x22,0x2C,0x20,0x3F,0x20,0x20,0x20,0x3F,0x28,0x24,0x23,0x20,0x20,0x00};

uchar shi[]={
/*--  文字:  示  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x20,0x20,0x22,0x22,0x22,0x22,0xE2,0x22,0x22,0x22,0x22,0x22,0x20,0x20,0x00,
0x10,0x08,0x04,0x03,0x00,0x40,0x80,0x7F,0x00,0x00,0x01,0x02,0x0C,0x18,0x00,0x00};

//uchar ya[]={
/*--  文字:  压  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
//0x00,0x00,0xFE,0x02,0x42,0x42,0x42,0x42,0xFA,0x42,0x42,0x42,0x62,0x42,0x02,0x00,
//0x20,0x18,0x27,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x21,0x2E,0x24,0x20,0x20,0x00};

uchar maohao[]={
/*--  文字:  :  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00}; 

uchar shu_0[]={
/*--  文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00};

uchar shu_1[]={
/*--  文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};

uchar shu_2[]={
/*--  文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00};

uchar shu_3[]={
/*--  文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00};

uchar shu_4[]={
/*--  文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00};

uchar shu_5[]={
/*--  文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00};

uchar shu_6[]={
/*--  文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00};

uchar shu_7[]={
/*--  文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00};

uchar shu_8[]={
/*--  文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00};

uchar shu_9[]={
/*--  文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00};

uchar dian_[]={
/*--  文字:  .  --*/
/*--  仿宋_GB231212;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00};

uchar xs_v[]={
/*--  文字:  v  --*/
/*--  仿宋_GB231212;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x40,0xC0,0x40,0x00,0xC0,0x40,0x00,0x00,0x00,0x03,0x1C,0x1C,0x03,0x00,0x00};
 


/********************************************************
**********************端口初始化*************************/
void port_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LCD_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = LCD_DATA ;	 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_PORT, &GPIO_InitStructure); 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4 ;	 //E2,E3,E4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0  |GPIO_Pin_1;	 //	 A0,A1
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);     
}

void Lcd_Delay_us(u16 x)
{
	while(x--);
}
 
/*****************************************************************************
函数功能:写命令到LCD程序
入口参数:cmdcode
出口参数:
*****************************************************************************/
void write_com(uchar cmdcode)
{	
	
    LCD_RS=0;
    LCD_RW=0;
	LCD_PORT->ODR = ((LCD_PORT->ODR&0xff00)|cmdcode);  
    delay_ms(2);
    LCD_EN=1;
    delay_ms(2);
    LCD_EN=0;
} 

/*****************************************************************************
函数功能:写数据到LCD程序
入口参数:Dispdata
出口参数:
*****************************************************************************/
void write_data(uchar Dispdata)
{		
	LCD_RS=1;
	LCD_RW=0;
	LCD_PORT->ODR = ((LCD_PORT->ODR&0xff00)|Dispdata);

	delay_ms(2);
	LCD_EN=1;
	delay_ms(2);
	LCD_EN=0;
}


/*****************************************************************************
函数功能:LCD初始化程序
入口参数:
出口参数:
*****************************************************************************/
void lcd12864_init()
{
	delay_ms(50);
	LCD_CS1=1;
	LCD_CS2=1;
	delay_ms(50);
	write_com(Disp_Off);        //显示关
	write_com(Page_Add+0);      //设置页地址
	write_com(Start_Line+0);    //读显示数据
	write_com(Col_Add+0);
	write_com(Disp_On);
}

/*****************************************************************************
函数功能:清除LCD内存程序
入口参数:pag,col,hzk
出口参数:
*****************************************************************************/
void Clr_Scr()
{
	uchar j,k;
	LCD_CS1=1;LCD_CS2=1;
 	write_com(Page_Add+0);
 	write_com(Col_Add+0);
 	for(k=0;k<8;k++)
 		{
		write_com(Page_Add+k);
  		for(j=0;j<64;j++)write_data(0x00);
		}
	LCD_CS1=0;LCD_CS2=0;
}



/*****************************************************************************
函数功能:指定位置显示数字16*16程序
入口参数:pag,col,hzk
出口参数:             
*****************************************************************************/
void hz_disp16(uchar pag,uchar col, uchar  *hzk)
{
    uchar j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+pag+j);
		write_com(Col_Add+col);
		for(i=0;i<16;i++) 
		write_data(hzk[16*j+i]);
	}
}

/*****************************************************************************
函数功能:指定位置显示数字8*16程序
入口参数:pag,col,hzk
出口参数:
*****************************************************************************/
void hz_disp8(uchar pag,uchar col, uchar  *hzk)
{    
    uchar j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+pag+j);
		write_com(Col_Add+col);
		for(i=0;i<8;i++) 
		write_data(hzk[8*j+i]);
	}
}
/********************************************************
**********************固定显示函数**********************/
void gudingxianshi(void)
{
    LCD_CS1=1;LCD_CS2=0;			//左显示
	delay_ms(2);
	hz_disp16(0,32,fang);
    hz_disp16(0,48,dian);
    hz_disp8(2,0,shu_1);
    hz_disp8(2,7,maohao); //hz_disp8(2,14,shu_5); 
    hz_disp8(4,0,shu_3);
    hz_disp8(4,7,maohao); 
    hz_disp8(6,0,shu_5);
    hz_disp8(6,7,maohao);
		delay_ms(2);
    LCD_CS1=0;LCD_CS2=1;			//右显示
	hz_disp16(0,0,xian); 
	hz_disp16(0,16,shi);                                                     
	hz_disp8(2,0,shu_2);
	hz_disp8(2,7,maohao);
	hz_disp8(4,0,shu_4);
	hz_disp8(4,7,maohao); 
	hz_disp8(6,0,shu_6);
	hz_disp8(6,7,maohao);
    delay_ms(2);

}

void sanweixs_1(void)
{
 LCD_CS1=1;LCD_CS2=0;			//左显示
 hz_disp8(2,28,dian_);
 hz_disp8(2,45,xs_v);
 switch(adc_data[0])
	    {
	    	case 0: 	hz_disp8(2,14,shu_0);break; 
	    	case 1:     hz_disp8(2,14,shu_1);break;
	    	case 2:     hz_disp8(2,14,shu_2);break; 
	    	case 3:     hz_disp8(2,14,shu_3);break; 
	    	case 4:     hz_disp8(2,14,shu_4);break;
	    	case 5:     hz_disp8(2,14,shu_5);break;
	    	case 6:     hz_disp8(2,14,shu_6);break;
	    	case 7:     hz_disp8(2,14,shu_7);break;
	    	case 8:     hz_disp8(2,14,shu_8);break;
	    	case 9:     hz_disp8(2,14,shu_9);break;  	
	 	}
	 	switch(adc_data[1])
	    {
	    	case 0: 	hz_disp8(2,21,shu_0);break; 
	    	case 1:     hz_disp8(2,21,shu_1);break;
	    	case 2:     hz_disp8(2,21,shu_2);break; 
	    	case 3:     hz_disp8(2,21,shu_3);break; 
	    	case 4:     hz_disp8(2,21,shu_4);break;
	    	case 5:     hz_disp8(2,21,shu_5);break;
	    	case 6:     hz_disp8(2,21,shu_6);break;
	    	case 7:     hz_disp8(2,21,shu_7);break;
	    	case 8:     hz_disp8(2,21,shu_8);break;
	    	case 9:     hz_disp8(2,21,shu_9);break;  	
	 	}
        switch(adc_data[2])
	    {
	    	case 0: 	hz_disp8(2,35,shu_0);break; 
	    	case 1:     hz_disp8(2,35,shu_1);break;
	    	case 2:     hz_disp8(2,35,shu_2);break; 
	    	case 3:     hz_disp8(2,35,shu_3);break; 
	    	case 4:     hz_disp8(2,35,shu_4);break;
	    	case 5:     hz_disp8(2,35,shu_5);break;
	    	case 6:     hz_disp8(2,35,shu_6);break;
	    	case 7:     hz_disp8(2,35,shu_7);break;
	    	case 8:     hz_disp8(2,35,shu_8);break;
	    	case 9:     hz_disp8(2,35,shu_9);break;
        }      
}
  
void sanweixs_2(void)
{
 LCD_CS1=0;LCD_CS2=1;			//右显示
 hz_disp8(2,28,dian_);
 hz_disp8(2,45,xs_v);
 switch(adc_data[0])
	    {
	    	case 0: 	hz_disp8(2,14,shu_0);break; 
	    	case 1:     hz_disp8(2,14,shu_1);break;
	    	case 2:     hz_disp8(2,14,shu_2);break; 
	    	case 3:     hz_disp8(2,14,shu_3);break; 
	    	case 4:     hz_disp8(2,14,shu_4);break;
	    	case 5:     hz_disp8(2,14,shu_5);break;
	    	case 6:     hz_disp8(2,14,shu_6);break;
	    	case 7:     hz_disp8(2,14,shu_7);break;
	    	case 8:     hz_disp8(2,14,shu_8);break;
	    	case 9:     hz_disp8(2,14,shu_9);break;  	
	 	}
	 	switch(adc_data[1])
	    {
	    	case 0: 	hz_disp8(2,21,shu_0);break; 
	    	case 1:     hz_disp8(2,21,shu_1);break;
	    	case 2:     hz_disp8(2,21,shu_2);break; 
	    	case 3:     hz_disp8(2,21,shu_3);break; 
	    	case 4:     hz_disp8(2,21,shu_4);break;
	    	case 5:     hz_disp8(2,21,shu_5);break;
	    	case 6:     hz_disp8(2,21,shu_6);break;
	    	case 7:     hz_disp8(2,21,shu_7);break;
	    	case 8:     hz_disp8(2,21,shu_8);break;
	    	case 9:     hz_disp8(2,21,shu_9);break;  	
	 	}
        switch(adc_data[2])
	    {
	    	case 0: 	hz_disp8(2,35,shu_0);break; 
	    	case 1:     hz_disp8(2,35,shu_1);break;
	    	case 2:     hz_disp8(2,35,shu_2);break; 
	    	case 3:     hz_disp8(2,35,shu_3);break; 
	    	case 4:     hz_disp8(2,35,shu_4);break;
	    	case 5:     hz_disp8(2,35,shu_5);break;
	    	case 6:     hz_disp8(2,35,shu_6);break;
	    	case 7:     hz_disp8(2,35,shu_7);break;
	    	case 8:     hz_disp8(2,35,shu_8);break;
	    	case 9:     hz_disp8(2,35,shu_9);break;
        }      
}

void sanweixs_3(void)
{
 LCD_CS1=1;LCD_CS2=0;			//左显示
 hz_disp8(4,28,dian_);
 hz_disp8(4,45,xs_v);
 switch(adc_data[0])
	    {
	    	case 0: 	hz_disp8(4,14,shu_0);break; 
	    	case 1:     hz_disp8(4,14,shu_1);break;
	    	case 2:     hz_disp8(4,14,shu_2);break; 
	    	case 3:     hz_disp8(4,14,shu_3);break; 
	    	case 4:     hz_disp8(4,14,shu_4);break;
	    	case 5:     hz_disp8(4,14,shu_5);break;
	    	case 6:     hz_disp8(4,14,shu_6);break;
	    	case 7:     hz_disp8(4,14,shu_7);break;
	    	case 8:     hz_disp8(4,14,shu_8);break;
	    	case 9:     hz_disp8(4,14,shu_9);break;  	
	 	}
	 	switch(adc_data[1])
	    {
	    	case 0: 	hz_disp8(4,21,shu_0);break; 
	    	case 1:     hz_disp8(4,21,shu_1);break;
	    	case 2:     hz_disp8(4,21,shu_2);break; 
	    	case 3:     hz_disp8(4,21,shu_3);break; 
	    	case 4:     hz_disp8(4,21,shu_4);break;
	    	case 5:     hz_disp8(4,21,shu_5);break;
	    	case 6:     hz_disp8(4,21,shu_6);break;
	    	case 7:     hz_disp8(4,21,shu_7);break;
	    	case 8:     hz_disp8(4,21,shu_8);break;
	    	case 9:     hz_disp8(4,21,shu_9);break;  	
	 	}
        switch(adc_data[2])
	    {
	    	case 0: 	hz_disp8(4,35,shu_0);break; 
	    	case 1:     hz_disp8(4,35,shu_1);break;
	    	case 2:     hz_disp8(4,35,shu_2);break; 
	    	case 3:     hz_disp8(4,35,shu_3);break; 
	    	case 4:     hz_disp8(4,35,shu_4);break;
	    	case 5:     hz_disp8(4,35,shu_5);break;
	    	case 6:     hz_disp8(4,35,shu_6);break;
	    	case 7:     hz_disp8(4,35,shu_7);break;
	    	case 8:     hz_disp8(4,35,shu_8);break;
	    	case 9:     hz_disp8(4,35,shu_9);break;
        }      
}


void sanweixs_4(void)
{
 LCD_CS1=0;LCD_CS2=1;			//右显示
 hz_disp8(4,28,dian_);
 hz_disp8(4,45,xs_v);
 switch(adc_data[0])
	    {
	    	case 0: 	hz_disp8(4,14,shu_0);break; 
	    	case 1:     hz_disp8(4,14,shu_1);break;
	    	case 2:     hz_disp8(4,14,shu_2);break; 
	    	case 3:     hz_disp8(4,14,shu_3);break; 
	    	case 4:     hz_disp8(4,14,shu_4);break;
	    	case 5:     hz_disp8(4,14,shu_5);break;
	    	case 6:     hz_disp8(4,14,shu_6);break;
	    	case 7:     hz_disp8(4,14,shu_7);break;
	    	case 8:     hz_disp8(4,14,shu_8);break;
	    	case 9:     hz_disp8(4,14,shu_9);break;  	
	 	}
	 	switch(adc_data[1])
	    {
	    	case 0: 	hz_disp8(4,21,shu_0);break; 
	    	case 1:     hz_disp8(4,21,shu_1);break;
	    	case 2:     hz_disp8(4,21,shu_2);break; 
	    	case 3:     hz_disp8(4,21,shu_3);break; 
	    	case 4:     hz_disp8(4,21,shu_4);break;
	    	case 5:     hz_disp8(4,21,shu_5);break;
	    	case 6:     hz_disp8(4,21,shu_6);break;
	    	case 7:     hz_disp8(4,21,shu_7);break;
	    	case 8:     hz_disp8(4,21,shu_8);break;
	    	case 9:     hz_disp8(4,21,shu_9);break;  	
	 	}
        switch(adc_data[2])
	    {
	    	case 0: 	hz_disp8(4,35,shu_0);break; 
	    	case 1:     hz_disp8(4,35,shu_1);break;
	    	case 2:     hz_disp8(4,35,shu_2);break; 
	    	case 3:     hz_disp8(4,35,shu_3);break; 
	    	case 4:     hz_disp8(4,35,shu_4);break;
	    	case 5:     hz_disp8(4,35,shu_5);break;
	    	case 6:     hz_disp8(4,35,shu_6);break;
	    	case 7:     hz_disp8(4,35,shu_7);break;
	    	case 8:     hz_disp8(4,35,shu_8);break;
	    	case 9:     hz_disp8(4,35,shu_9);break;
        }      
}


void sanweixs_5(void)
{
 LCD_CS1=1;LCD_CS2=0;			//左显示
 hz_disp8(6,28,dian_);
 hz_disp8(6,45,xs_v);
 switch(adc_data[0])
	    {
	    	case 0: 	hz_disp8(6,14,shu_0);break; 
	    	case 1:     hz_disp8(6,14,shu_1);break;
	    	case 2:     hz_disp8(6,14,shu_2);break; 
	    	case 3:     hz_disp8(6,14,shu_3);break; 
	    	case 4:     hz_disp8(6,14,shu_4);break;
	    	case 5:     hz_disp8(6,14,shu_5);break;
	    	case 6:     hz_disp8(6,14,shu_6);break;
	    	case 7:     hz_disp8(6,14,shu_7);break;
	    	case 8:     hz_disp8(6,14,shu_8);break;
	    	case 9:     hz_disp8(6,14,shu_9);break;  	
	 	}
	 	switch(adc_data[1])
	    {
	    	case 0: 	hz_disp8(6,21,shu_0);break; 
	    	case 1:     hz_disp8(6,21,shu_1);break;
	    	case 2:     hz_disp8(6,21,shu_2);break; 
	    	case 3:     hz_disp8(6,21,shu_3);break; 
	    	case 4:     hz_disp8(6,21,shu_4);break;
	    	case 5:     hz_disp8(6,21,shu_5);break;
	    	case 6:     hz_disp8(6,21,shu_6);break;
	    	case 7:     hz_disp8(6,21,shu_7);break;
	    	case 8:     hz_disp8(6,21,shu_8);break;
	    	case 9:     hz_disp8(6,21,shu_9);break;  	
	 	}
        switch(adc_data[2])
	    {
	    	case 0: 	hz_disp8(6,35,shu_0);break; 
	    	case 1:     hz_disp8(6,35,shu_1);break;
	    	case 2:     hz_disp8(6,35,shu_2);break; 
	    	case 3:     hz_disp8(6,35,shu_3);break; 
	    	case 4:     hz_disp8(6,35,shu_4);break;
	    	case 5:     hz_disp8(6,35,shu_5);break;
	    	case 6:     hz_disp8(6,35,shu_6);break;
	    	case 7:     hz_disp8(6,35,shu_7);break;
	    	case 8:     hz_disp8(6,35,shu_8);break;
	    	case 9:     hz_disp8(6,35,shu_9);break;
        }      
}


void sanweixs_6(void)
{
 LCD_CS1=0;LCD_CS2=1;			//右显示
 hz_disp8(6,28,dian_);
 hz_disp8(6,45,xs_v);
 switch(adc_data[0])
	    {
	    	case 0: 	hz_disp8(6,14,shu_0);break; 
	    	case 1:     hz_disp8(6,14,shu_1);break;
	    	case 2:     hz_disp8(6,14,shu_2);break; 
	    	case 3:     hz_disp8(6,14,shu_3);break; 
	    	case 4:     hz_disp8(6,14,shu_4);break;
	    	case 5:     hz_disp8(6,14,shu_5);break;
	    	case 6:     hz_disp8(6,14,shu_6);break;
	    	case 7:     hz_disp8(6,14,shu_7);break;
	    	case 8:     hz_disp8(6,14,shu_8);break;
	    	case 9:     hz_disp8(6,14,shu_9);break;  	
	 	}
	 	switch(adc_data[1])
	    {
	    	case 0: 	hz_disp8(6,21,shu_0);break; 
	    	case 1:     hz_disp8(6,21,shu_1);break;
	    	case 2:     hz_disp8(6,21,shu_2);break; 
	    	case 3:     hz_disp8(6,21,shu_3);break; 
	    	case 4:     hz_disp8(6,21,shu_4);break;
	    	case 5:     hz_disp8(6,21,shu_5);break;
	    	case 6:     hz_disp8(6,21,shu_6);break;
	    	case 7:     hz_disp8(6,21,shu_7);break;
	    	case 8:     hz_disp8(6,21,shu_8);break;
	    	case 9:     hz_disp8(6,21,shu_9);break;  	
	 	}
        switch(adc_data[2])
	    {
	    	case 0: 	hz_disp8(6,35,shu_0);break; 
	    	case 1:     hz_disp8(6,35,shu_1);break;
	    	case 2:     hz_disp8(6,35,shu_2);break; 
	    	case 3:     hz_disp8(6,35,shu_3);break; 
	    	case 4:     hz_disp8(6,35,shu_4);break;
	    	case 5:     hz_disp8(6,35,shu_5);break;
	    	case 6:     hz_disp8(6,35,shu_6);break;
	    	case 7:     hz_disp8(6,35,shu_7);break;
	    	case 8:     hz_disp8(6,35,shu_8);break;
	    	case 9:     hz_disp8(6,35,shu_9);break;
        }      
}

 #endif	


