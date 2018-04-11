
#include "includes.h"

int main(void)
{

//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //与配置文件相对应  配置程序的起始地址，前面一部分留给了bootload
	SysTickInit();         //设置滴答定时器中断时间为1ms
//	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration();  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	//EE_IIC_Init();			 //EEPROM的IIC初始化
	//Random_Adc_Init(); //通过ADC获得一个随机数

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//使用了spi3，禁用JATG，保留SWD功能
	


	
		lcd12864_init();//12864初始化

			ShowWelcome();
			delay_ms(200);	
	while(1)
	{		
	oled_updatescr(0, 64);	   //屏幕刷新	
delay_ms(6000);
PBout(9)=0;
delay_ms(6000);
PBout(9)=1;
//		if(max_waite==10000)
//		{   lcdreset();                    //初始化LCD屏
//				clrgdram();
//				max_waite=0;
//		}
	}
}

/************* The End ! *****************/