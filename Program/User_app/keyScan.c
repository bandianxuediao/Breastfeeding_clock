#include "includes.h"

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

	static u8 double_falg= 0;//双键为抬起触发，需单独处理

	scan_time++;
	if(scan_time == 3)//滴答定时器每1ms调用1次，每10ms扫描一次键盘
	{

		scan_time = 0;
//		current_key_code = MatrixKeyScan(); //矩阵扫描
// 
//			if((current_key_code != 0x11) && (late_key_code == current_key_code))//有键按下且与上次检测到的相同
//			{
//				if(1 == KeyCodeToKeyMsg(current_key_code, &msg))//把按键代码转换为按键消息
//				{//有效按键
//					dly_num++;
//					msg.param1 = (u32)GetCurrentState();//连击产生的消息状态不改变							
//					PostMessage(msg);//产生一个按键消息	
//					KEY_BOARD = 1;					
//					return 0 ;
//				}
//			}
			late_key_code = current_key_code;
			dly_num = 0;
			return 1 ;

	}
}

