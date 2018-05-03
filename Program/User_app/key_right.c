#include "includes.h"

//==================================================================================================
//| 函数名称 | KeyRight_Program
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 右键相关流程
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-21
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void KeyRight_Program(void)
{
	switch(Current_state)
	{

		case DISPLAY_ITEM_LACTATION://显示项目状态--默认选中哺乳
		case DISPLAY_ITEM_DRINK://显示项目状态--选中补水
		case DISPLAY_ITEM_SHIT://显示项目状态--选中大便
		case DISPLAY_ITEM_URINATE://显示项目状态--选中小便
		case DISPLAY_MENU_TIME:
			ShowWelcome();
			Current_state = WELCOME_WAIT;
			break;

		case WELCOME_WAIT:
			Display_Menu(1);
			Current_state = DISPLAY_MENU_TIME;
			break;




		case LACTATION_LIST:
			Display_Items(1);   //默认为选中Lactation
			Current_state = DISPLAY_ITEM_LACTATION; //当前状态置为项目显示
			break;

		case DRINK_LIST:
			Display_Items(3);   //默认为选中Lactation
			Current_state = DISPLAY_ITEM_DRINK; //当前状态置为项目显示
			break;

		case SHIT_LIST:
			Display_Items(2);   //默认为选中Lactation
			Current_state = DISPLAY_ITEM_SHIT; //当前状态置为项目显示
			break;

		case URINATE_LIST:
			Display_Items(4);   //默认为选中Lactation
			Current_state = DISPLAY_ITEM_URINATE; //当前状态置为项目显示
			break;



		default:
			break;

	}
}

