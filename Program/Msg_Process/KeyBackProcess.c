#include "includes.h"

//==================================================================================================
//| 函数名称 | KeyLeftPro 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 左功能键消息响应函数
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | msg 待处理消息
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
void KeyBackPro(MSG msg)
{
	SYS_STATE state;
	
	
	//按键消息的时效性判断
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch((SYS_STATE)msg.param1)
	{
		case WAIT_CARD://
			break;
		case 	INPUT_BOXNUM:
			INPUT_DATA_AMOUNT = 0 ;
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );		
			SetCurrentState(SHOW_WELCOME);//系统上电，检测充电状态
			RC531_SWITCH = 0;		
			break;
		case	INPUT_BOXKEY:
			INPUT_DATA_AMOUNT = 0 ;
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );		
			SetCurrentState(INPUT_BOXNUM);//系统上电，检测充电状态
			RC531_SWITCH = 1;		
			break;
		case  INPUT_CARD_KEY:
		case  INPUT_CARD_KEY_AGAIN:
		case  OUTPUT_CARD_KEY:
		case PASSW_INPUT_KEY:
		case PASSW_INPUT_KEY_AGAIN:

		case OUT_INPUT_BOXNUM://设置为"取"输入箱号状态
		case OUT_INPUT_PASSW://“取”输入密码	//取，输入密码				
//		case INPUT_CARD_KEY:
//		case INPUT_CARD_KEY_AGAIN:			
//		case 	INPUT_BOXNUM:	
//		case	INPUT_BOXKEY:
//		case OUTPUT_CARD_KEY:
//		case PASSW_INPUT_KEY:
//		case PASSW_INPUT_KEY_AGAIN:			

		
			memset(RC531_sbuf,0,sizeof(RC531_sbuf));
			INPUT_DATA_AMOUNT = 0;
			INPUT_PASS_STATE = 0 ;//存包刷卡，输入密码状态为未输入任何字符
			memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
			memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));
			memset(Password,0,sizeof(Password));			
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );		
			SetCurrentState(SHOW_WELCOME);//在刷卡存包时输入密码的状态
			break;	
			
		
		
		default:
			break;
	}		
}
