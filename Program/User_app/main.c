
#include "includes.h"
SYS_STATE Current_state;
SYS_STATE KEY_state;
int main(void)
{
	u8 temp = 0;
	u8 read_temp1[6];
	//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //与配置文件相对应  配置程序的起始地址，前面一部分留给了bootload
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	SysTickInit();         //设置滴答定时器中断时间为1ms

	EE_IIC_Init();             //EEPROM的IIC初始化

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);        //使用了spi3，禁用JATG，保留SWD功能

	PIN_Init();

	lcd12864_init();//12864初始化
	RTC_Init();
	ShowWelcome();
	delay_ms(600);
	Back_Light(1);//开机背光电源输出5V
	SetLightTimer(60000);//设置背光亮起时间1分钟
	Current_state = WELCOME_WAIT;



	//  Back_Light(0);
	//RTC_Set(2018, 4, 24, 23, 26, 30); //设置时间
	//          AT24CXX_WriteLenByte(10, 0,2);
	//          AT24CXX_WriteLenByte(20, 0,2);
	//          AT24CXX_WriteLenByte(30,0, 2);
	//          AT24CXX_WriteLenByte(40,0, 2);



	oled_updatescr(0, 64);//屏幕刷新

	//  //测试一下，一直刷新屏幕，清空缓存是否还会出现乱码现象
	//  while(1)
	//  {
	//

	//          oled_updatescr(0, 64);     //屏幕刷新
	//      delay_ms(10);

	//  }



	while(1)
	{
		Detect_Pin_State();

		if(GetLightTimerState() == TIME_OUT)
		{
			Back_Light(0);//背光电源关闭输出5V
		}

		White_Line();

		//      if(max_waite==10000)
		//      {   lcdreset();                    //初始化LCD屏
		//              clrgdram();
		//              max_waite=0;
		//      }

		oled_updatescr(0, 64);       //屏幕刷新
	}
}

/************* The End ! *****************/