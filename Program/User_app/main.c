
#include "includes.h"
SYS_STATE Current_state;
SYS_STATE KEY_state;
int main(void)
{
	//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //与配置文件相对应  配置程序的起始地址，前面一部分留给了bootload
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	SysTickInit();         //设置滴答定时器中断时间为1ms
	//  delay_init();            //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	//EE_IIC_Init();             //EEPROM的IIC初始化


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);        //使用了spi3，禁用JATG，保留SWD功能

	PIN_Init();
	  lcd12864_init();//12864初始化
	          ShowWelcome();
	delay_ms(6000);
	Current_state = WELCOME_WAIT;
  
	while(1)
	{
		KEY_state=Detect_Pin_State();
		//  oled_updatescr(0, 64);     //屏幕刷新
if(KEY_state)
{
	//检测到按键之后应该点亮屏幕，并且重新装载屏幕背光关闭计数器
		switch(KEY_state)
		{
			case KEY_UP:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;
				}

				break;
			}


			case KEY_DOWN:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;

				}

				break;
			}


			case KEY_SET:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;

				}

				break;
			}


			case KEY_BACK:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;

				}

				break;
			}

			default:
				break;

		}
	}
	else
	{delay_ms(10);}

		//      if(max_waite==10000)
		//      {   lcdreset();                    //初始化LCD屏
		//              clrgdram();
		//              max_waite=0;
		//      }

	}
}

/************* The End ! *****************/