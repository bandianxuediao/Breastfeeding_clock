#include "includes.h"

void NullPro(MSG msg)
{
//	u16 v_temp,i_temp;
//	u16 i,k; 	
//	MSG temp_msg;
//	u8 re_num ;
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
			
		case 	WAIT_CARD:
			RC531_SWITCH = 1; //置CARD开关打开，可以检测卡
			KEY_BOARD =0;			//置按键开关关闭，不可以检测按键
			find_card();
			break;
		case OUT_INPUT_BOXNUM://设置为"取"输入箱号状态	
		case OUT_INPUT_PASSW://“取”输入密码			
		case INPUT_BOXNUM:
		case INPUT_BOXKEY:
		case WAIT_KEY:
		case WAIT_SURE_KEY:
		case INPUT_CARD_KEY:
		case INPUT_CARD_KEY_AGAIN://在刷卡存包时再次输入密码的状态
		case PASSW_INPUT_KEY:
		case PASSW_INPUT_KEY_AGAIN:
//		case INPUT_CARD_KEY_SURE://在刷卡存包时确认输入的密码
		case OUTPUT_CARD_KEY://在刷卡存包时输入密码的状态
		case OUTPUT_CARD_KEY_AGAIN://在刷卡存包时再次输入密码的状态
//		case OUTPUT_CARD_KEY_SURE://在刷卡存包时确认输入的密码	
			RC531_SWITCH = 0; //可以键盘输入，不可以检测卡
			KEY_BOARD =1;			//置按键开关打开，可以检测按键
			pad_scan();
			break;
			
		case	WAIT_CARD_KEY:
			RC531_SWITCH = 1; //不可以键盘输入，可以检测卡
			KEY_BOARD =1;			//置按键开关打开，可以检测按键			
			find_card();
			pad_scan();
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
