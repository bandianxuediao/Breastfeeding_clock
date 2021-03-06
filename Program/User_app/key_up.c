#include "includes.h"

//==================================================================================================
//| 函数名称 | KeyUp_Program
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 上键相关流程
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
void KeyUp_Program(void)
{
	switch(Current_state)
	{
		case DISPLAY_ITEM_LACTATION://显示项目状态--默认选中哺乳
		case DISPLAY_ITEM_DRINK://显示项目状态--选中补水
		case DISPLAY_ITEM_SHIT://显示项目状态--选中大便
		case DISPLAY_ITEM_URINATE://显示项目状态--选中小便
		{
			Items_state = Calc_items(0); //1是当前状态加一，0是当前状态减一

			Display_Items(Items_state); //默认为选中Lactation

		}
		break;

		case    DISPLAY_MENU_TIME:
			Display_Menu(2);
			Current_state = DISPLAY_MENU_CLEAR;
			break;

		case    DISPLAY_MENU_CLEAR:
			Display_Menu(1);
			Current_state = DISPLAY_MENU_TIME;
			break;


		case LACTATION_LIST:

			if(((TurnPage_Calc + 1) < EepIndex.lactation) && TurnPage_Calc > 1)
			{
				TurnPage_Calc += 1;
			}

			Renovate_List(BASE_ADDR_LACTATION, 0);

			break;

		case DRINK_LIST:

			if(((TurnPage_Calc + 1) < EepIndex.drink) && TurnPage_Calc > 1)
			{
				TurnPage_Calc += 1;
			}

			Renovate_List(BASE_ADDR_DRINK, 0);

			break;

		case SHIT_LIST:

			if(((TurnPage_Calc + 1) < EepIndex.shit) && TurnPage_Calc > 1)
			{
				TurnPage_Calc += 1;
			}

			Renovate_List(BASE_ADDR_SHIT, 0);

			break;

		case URINATE_LIST:

			if(((TurnPage_Calc + 1) < EepIndex.urinate) && TurnPage_Calc > 1)
			{
				TurnPage_Calc += 1;
			}

			Renovate_List(BASE_ADDR_URINATE, 0);

			break;

		case WELCOME_WAIT:

			break;

		case SELECT_YEAR://修改当前年
			delay_ms(500);
			Current_state = SELECT_SEC;
			break;

		case SELECT_MONTH://修改月
			delay_ms(500);
			Current_state = SELECT_YEAR;
			break;

		case SELECT_DATE://修改日
			delay_ms(500);
			Current_state = SELECT_MONTH;
			break;

		case SELECT_HOUR://修改小时
			delay_ms(500);
			Current_state = SELECT_DATE;
			break;

		case SELECT_MIN://修改分钟
			delay_ms(500);
			Current_state = SELECT_HOUR;
			break;

		case SELECT_SEC://修改秒
			delay_ms(500);
			Current_state = SELECT_MIN;
			break;

		case MODIFY_YEAR://修改当前年
		case MODIFY_MONTH://修改月
		case MODIFY_DATE://修改日
		case MODIFY_HOUR://修改小时
		case MODIFY_MIN://修改分钟
		case MODIFY_SEC://修改秒
			Modify_time(1);

			break;

		default:
			break;

	}
}

