#include "includes.h"

//==================================================================================================
//| 函数名称 | Key8Pro 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 按键8消息响应函数
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
void Key8Pro(MSG msg)
{	
	//按键消息的时效性判断
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch((SYS_STATE)msg.param1)
	{
		case WAIT_CARD://在主菜单下按‘1’键，进入注册流程
//			ShowPad(8);
//			delay_ms(200);
//			RC531_SWITCH = 1;
//			SetCurrentState(SHOW_WELCOME);//系统上电，检测充电状态
			break;
		case OUT_INPUT_BOXNUM://设置为"取"输入箱号状态
			memcpy((char*)&INPUT_DATA_NUM[INPUT_DATA_AMOUNT], "8", 1);
			INPUT_DATA_AMOUNT++;
			ShowInput(2);
			if(INPUT_DATA_AMOUNT == 3)
			{
			SetCurrentState(WAIT_SURE_KEY);//四位密码输入完成，等待按下确认按键
			break;				
			}
		
			break;			
		case OUT_INPUT_PASSW://“取”输入密码					
		case INPUT_CARD_KEY:
		case INPUT_CARD_KEY_AGAIN:			
		case INPUT_BOXNUM:	
		case	INPUT_BOXKEY:
		case OUTPUT_CARD_KEY:
		case PASSW_INPUT_KEY:
		case PASSW_INPUT_KEY_AGAIN:			
			memcpy((char*)&INPUT_DATA_NUM[INPUT_DATA_AMOUNT], "8", 1);
			INPUT_DATA_AMOUNT++;
			ShowInput(2);
			if(INPUT_DATA_AMOUNT == 4)
			{
			SetCurrentState(WAIT_SURE_KEY);//四位密码输入完成，等待按下确认按键
			break;				
			}
			break;
		
		default:
			break;
	}		
}
