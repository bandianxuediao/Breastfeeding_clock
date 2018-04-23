#include "includes.h"
u8 Items_state = 1;
//==================================================================================================
//| 函数名称 | KeyLeft_Program
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 左键相关流程
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
void KeyLeft_Program(void)
{


	switch(Current_state)
	{
		case WELCOME_WAIT:
			Display_Items(1);   //默认为选中Lactation
			Current_state = DISPLAY_ITEM_LACTATION; //当前状态置为项目显示
			break;

		case DISPLAY_ITEM_LACTATION://显示项目状态--默认选中哺乳

			List_Display();

			Current_state = LACTATION_LIST;
			break;

		case DISPLAY_ITEM_DRINK://显示项目状态--选中补水

			List_Display();

			Current_state = DRINK_LIST;
			break;
			case DISPLAY_ITEM_SHIT://显示项目状态--选中大便
							List_Display();

			Current_state = SHIT_LIST;
			break;
		case DISPLAY_ITEM_URINATE://显示项目状态--选中小便
			List_Display();

			Current_state = URINATE_LIST;
			break;			
		case LACTATION_LIST:
		case DRINK_LIST:
			case SHIT_LIST:
				case URINATE_LIST:
					
				
				
				
				break;
		
		default:
			break;
	}
}

u8 Calc_items(u8 temp)
{
	if(temp)
	{
		Items_state++;
	}
	else
	{
		Items_state--;
	}

	if(Items_state == 0)
	{
		Items_state = 4;
	}

	if(Items_state == 5)
	{
		Items_state = 1;
	}

	return Items_state;
}


