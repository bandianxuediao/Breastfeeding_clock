#include "includes.h"

//==================================================================================================
//| 函数名称 | MatrixKeyScan 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 4X3键盘矩阵扫描
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | 无
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 按键代码
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-29 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
static u16 MatrixKeyScan(void)
{
//	int temp;
//	
//		if(!PAD_INT1)
//		{
//			temp = scan_key(KEY_AREA1);	//扫描按键		
//		}
//		if(!PAD_INT2)
//		{
//			temp = scan_key(KEY_AREA2);	//扫描按键		
//		}
//		return temp;
}


//==================================================================================================
//| 函数名称 | KeyCodeToKeyMsg 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 根据扫描到的按键代码转换为对应的系统按键消息
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | keycode 按键代码  msg 转换后的消息指针
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 0  未找到对应的按键消息
//|          | 1  转换成功
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
static u8 KeyCodeToKeyMsg(u16 keycode, MSG* msg)
{
	/*对输入的指针进行必需的判断*/
	if(msg == NULL)
	{
		return 0;
	}
//	msg->param1 = (u32)GetCurrentState();
	switch(keycode)//按键代码转换为对应的系统按键消息
	{
		case KEY0_CODE:
			msg->code = KEY_0;
			break;
		case KEY1_CODE:
			msg->code = KEY_1;
			break;
		case KEY2_CODE:
			msg->code = KEY_2;
			break;
		case KEY3_CODE:
			msg->code = KEY_3;
			break;
		case KEY4_CODE:
			msg->code = KEY_4;
			break;
		case KEY5_CODE:
			msg->code = KEY_5;
			break;
		case KEY6_CODE:
			msg->code = KEY_6;
			break;
		case KEY7_CODE:
			msg->code = KEY_7;
			break;
		case KEY8_CODE:
			msg->code = KEY_8;
			break;		
		case KEY9_CODE:
			msg->code = KEY_9;
			break;	
		case KEY_IN_CODE:
			msg->code = KEY_IN;
			break;	
		case KEY_OUT_CODE:
			msg->code = KEY_OUT;
			break;
		case KEY_SYS_CODE:
			msg->code = KEY_SYS;
			break;		
		case KEY_KEY_CODE:
			msg->code = KEY_KEY;
			break;	
		case KEY_BACK_CODE:
			msg->code = KEY_BACK;
			break;	
		case KEY_SURE_CODE:
			msg->code = KEY_SURE;
			break;	

//		default:
//			return 0;
//			break;			
	}
	return 1;
}


//==================================================================================================
//| 函数名称 | KeyScan 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 按键扫描函数，根据扫描结果将产生按键消息
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | 无
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 函数由滴答定时器每隔1ms调用1次，单键为按下触发，1和3双键为抬起触发
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
u8 KeyScan(void)
{
	static u16 late_key_code = 0 ; //保存上一次的代码代码
	static u8 dly_num = 0;	
	static u8 scan_time = 0;
	u16 current_key_code = 0;
	static MSG msg;
	static u8 double_falg= 0;//双键为抬起触发，需单独处理

	scan_time++;
	if(scan_time == 3)//滴答定时器每1ms调用1次，每10ms扫描一次键盘
	{
		KEY_BOARD = 0;
		scan_time = 0;
		current_key_code = MatrixKeyScan(); //矩阵扫描
 
			if((current_key_code != 0x11) && (late_key_code == current_key_code))//有键按下且与上次检测到的相同
			{
				if(1 == KeyCodeToKeyMsg(current_key_code, &msg))//把按键代码转换为按键消息
				{//有效按键
					dly_num++;
					msg.param1 = (u32)GetCurrentState();//连击产生的消息状态不改变							
					PostMessage(msg);//产生一个按键消息	
					KEY_BOARD = 1;					
					return 0 ;
				}
			}
			late_key_code = current_key_code;
			dly_num = 0;
			KEY_BOARD = 1;
			return 1 ;

	}
}

