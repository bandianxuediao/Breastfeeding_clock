#include "includes.h"

void NullPro(MSG msg)
{
	static u16 max_waite;
//	uint8_t i;
//	uint8_t status;
	
	switch(GetCurrentState())
	{
		case GPIO_INIT://芯片上电后首先执行该消息
			SystemHWConfig();
			ShowWelcome();
			delay_ms(2000);
//			BufferInit();
//			RC531_SWITCH = 1;
//			KEY_BOARD =1;
			SetCurrentState(SHOW_WELCOME);//初始化完毕
			break;
		case SHOW_WELCOME:
			ShowWelcome();
			delay_ms(200);
//			result = INT3;
			SetCurrentState(WAIT_CARD_KEY);//等待刷卡状态，重叠等待按键状态
			break;
			
	


//		case FINDED_CARD:  //光标闪烁暂时没有实现
//			if(GetSysTickTimer1State() == TIME_OUT)
//			{
//				SetSysTickTimer1(500);
//				FlashCursor();//光标闪烁
//			}
//			break;

		default:		
			break;
	}


	oled_updatescr(0, 64);	   //屏幕刷新	
		max_waite++;
//		if(max_waite==10000)
//		{   lcdreset();                    //初始化LCD屏
//				clrgdram();
//				max_waite=0;
//		}
}
