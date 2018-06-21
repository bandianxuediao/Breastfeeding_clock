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
	u8 display_temp[16];

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
			if((Diff_timecount >= 3600) || ((EepIndex.lactation | Diff_timecount) == 0)) //哺乳间隔时间最少1小时
			{
				Storage_One_Data(BASE_ADDR_LACTATION);
			}

			break;

		case DRINK_LIST:
			if((Diff_timecount >= 3600) || ((EepIndex.drink | Diff_timecount) == 0)) //补水间隔时间最少1小时
			{
				Storage_One_Data(BASE_ADDR_DRINK);
			}

			break;

		case SHIT_LIST:
			if((Diff_timecount >= 3600) || ((EepIndex.shit | Diff_timecount) == 0)) //大便间隔时间最少1小时
			{
				Storage_One_Data(BASE_ADDR_SHIT);
			}

			break;

		case URINATE_LIST:
			if((Diff_timecount >= 1800) || ((EepIndex.urinate | Diff_timecount) == 0)) //小便间隔时间最少0.5小时
			{
				Storage_One_Data(BASE_ADDR_URINATE);
			}

			break;

		case DISPLAY_MENU_CLEAR:
			clr_disp_mem();         //清除显存数据
			oled_updatescr(0, 64);     //屏幕刷新
			sprintf((char*)display_temp, "将清空所有数据");
			oled_print(0, LINE1, &display_temp[0]);//字符输出
			sprintf((char*)display_temp, "请确认执行操作");
			oled_print(0, LINE2, &display_temp[0]);//字符输出
			sprintf((char*)display_temp, "确认        返回");
			oled_print(0, LINE4, &display_temp[0]);//字符输出

			oled_updatescr(0, 64);     //屏幕刷新
			Current_state = DISPLAY_MENU_CLEAR_WAIT;
			break;

		case DISPLAY_MENU_CLEAR_WAIT:
			AT24CXX_WriteLenByte(10, 0, 2);
			AT24CXX_WriteLenByte(20, 0, 2);
			AT24CXX_WriteLenByte(30, 0, 2);
			AT24CXX_WriteLenByte(40, 0, 2);
			sprintf((char*)display_temp, "   操作完成");
			oled_print(0, LINE1, &display_temp[0]);//字符输出
			sprintf((char*)display_temp, "即将返回主界面");
			oled_print(0, LINE2, &display_temp[0]);//字符输出
			oled_updatescr(0, 64);     //屏幕刷新
			delay_ms(2000);
			ShowWelcome();
			Current_state = WELCOME_WAIT;

			break;


		case MODIFY_YEAR://修改当前年
		case MODIFY_MONTH://修改月
		case MODIFY_DATE://修改日
		case MODIFY_HOUR://修改小时
		case MODIFY_MIN://修改分钟
		case MODIFY_SEC://修改秒
			RTC_WaitForLastTask();  //等待最近一次对RTC寄存器的写操作完成
			RTC_EnterConfigMode();/// 允许配置
			RTC_SetPrescaler(32767); //设置RTC预分频的值
			RTC_WaitForLastTask();  //等待最近一次对RTC寄存器的写操作完成
			RTC_Set(temp_time.w_year, temp_time.w_month, temp_time.w_date, temp_time.hour, temp_time.min, temp_time.sec); //设置时间
			RTC_ExitConfigMode(); //退出配置模式
			BKP_WriteBackupRegister(BKP_DR1, 0X5050);   //向指定的后备寄存器中写入用户程序数据
			delay_ms(1100);//等待1秒以上，rtc更新时间

		case DISPLAY_MENU_TIME:
			display_current_time();
			Draw_Line = 1;
			Current_state = SELECT_YEAR; //默认选中年
			break;

		case SELECT_YEAR:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_YEAR; //修改年
			break;

		case SELECT_MONTH:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_MONTH; //修改年
			break;

		case SELECT_DATE:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_DATE; //修改年
			break;

		case SELECT_HOUR:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_HOUR; //修改年
			break;

		case SELECT_MIN:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_MIN; //修改年
			break;

		case SELECT_SEC:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_SEC; //修改年
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


