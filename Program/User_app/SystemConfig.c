#include "includes.h"

char RC531_SWITCH = 0 ;
char KEY_BOARD = 0 ;
u16 SURE_BOXNUM ;
u32 SURE_BOXKEY ;
u32	SURE_SURE_BOXKEY ;
//unsigned char RC531_sbuf[50];


void SystemHWConfig(void)
{	
	BufferInit();                 //缓冲区数据初始化
	SysTickInit();         //设置滴答定时器中断时间为1ms
//	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration();  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	//uart_init(9600);	 	 //串口初始化为9600
	//PAD_IIC_Init();			 //IIC初始化 
	//EE_IIC_Init();			 //EEPROM的IIC初始化
	//Random_Adc_Init(); //通过ADC获得一个随机数

  //irmp_init();         // initialize irmp
  //timer2_init();       // initialize timer2

	//DeviceInit();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//使用了spi3，禁用JATG，保留SWD功能
		lcd12864_init();//12864初始化
	
	
}

u8 DeviceInit(void)
{
		LED_Init();
//		delay_init();
		lcd12864_init();//12864初始化
		//rc_init();		
		//PCD_reset();
	  delay_ms(200);    
	  //PCD_cfg_iso_type('A');
	  delay_ms(5);
//		W25QXX_Init();			//W25QXX初始化
		
	
		return 0;
}

void BufferInit(void)
{	
	
	RemoveAllMessage();
	RemoveBackupState();
}






