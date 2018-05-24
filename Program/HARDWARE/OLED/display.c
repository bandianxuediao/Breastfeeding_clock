#include "includes.h"

INPUT_DATA input_data;



//==================================================================================================
//| 函数名称 | format_string_h
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 格式化显示输出的数据
//|          | 在(x0,y0,x0+length)指定的线性区域内，字符按指定的对齐方式显示
//|----------|--------------------------------------------------------------------------------------
//| 调用模块 | oled_print：字符输出函数
//|          |
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | align字符相对于边框的对齐方式:左，ALIGN_LEFT；
//|          |                               中，ALIGN_CENTER；
//|          |                               右，ALIGN_RIGHT
//|          | (x0,y0),字符所在区域开始的位置，
//|          | length字符所在区域的长度
//|          | *str：要显示的字符
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 全局变量 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-3-25
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void format_string_h(unsigned char *str, unsigned char align, unsigned char x0, unsigned char y0, unsigned char length)
{
	unsigned char temp;

	switch (align)
	{
		case ALIGN_LEFT :                   //居左
			oled_print(x0, y0, str);        //字符输出
			break;

		case ALIGN_CENTER :                 //居中
			temp = (unsigned char)strlen((const char*)str) * LWIDTH; //计算字符所占据的OLED屏的像素

			if (length > temp)
			{
				temp = (length - temp) >> 1;
			}
			else
			{
				temp = 0;
			}

			oled_print(x0 + temp, y0, str); //字符输出
			break;

		case ALIGN_RIGHT :                  //居右
			temp = (unsigned char)strlen((const char*)str) * LWIDTH; //计算字符所占据的OLED屏的像素

			if( length > temp)
			{
				temp = length - temp;
			}
			else
			{
				temp = 0;
			}

			oled_print(x0 + temp, y0, str); //字符输出
			break;

		default :
			break;
	}
}

//==================================================================================================
//| 函数名称 | show_right_button
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 显示右功能
//|----------|--------------------------------------------------------------------------------------
//| 调用模块 | format_string_h：格式化显示输出的数据
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | *msg-需要显示的字符
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 全局变量 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-3-25
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void show_right_button(unsigned char *msg)
{
	//  format_string_h(msg, ALIGN_RIGHT, 0, LINE4, 128);
	oled_print(6, LINE4, msg) ;  //字符输出函数

}

//==================================================================================================
//| 函数名称 | show_left_button
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 显示左功能
//|----------|--------------------------------------------------------------------------------------
//| 调用模块 | format_string_h：格式化显示输出的数据
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | *msg-需要显示的字符
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 全局变量 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-3-25
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void show_left_button(unsigned char *msg)
{
	//  format_string_h(msg, ALIGN_LEFT, 0, LINE4, 128);
	oled_print(0, LINE4, msg) ;  //字符输出函数

}

//==================================================================================================
//| 函数名称 | show_title
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 显示标题
//|----------|--------------------------------------------------------------------------------------
//| 调用模块 | format_string_h：格式化显示输出的数据
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | *title-需要显示的字符
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 全局变量 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-3-25
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void show_title(unsigned char *title)
{
	format_string_h(title, ALIGN_CENTER, 0, LINE0, 128);
}
//==================================================================================================
//| 函数名称 | show_status_bar
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 在显示屏底部显示状态信息
//|----------|--------------------------------------------------------------------------------------
//| 调用模块 | oled_hline: 在OLED显示屏上绘制一条亮/暗的横线
//|          | oled_rline: 在显示屏上显示一条亮/暗的竖线
//|          | format_string_h：格式化显示输出的数据
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | *str1需要显示的字符1，align1字符1相对于边框的对齐方式
//|          | *str2需要显示的字符2，align2字符2相对于边框的对齐方式
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 全局变量 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-3-25
//|----------|--------------------------------------------------------------------------------------
//|   备注   | 底部边框内显示内容
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void show_status_bar(unsigned char *str1, unsigned char align1, unsigned char *str2, unsigned char align2)
{
	//显示框
	oled_hline(24, LINE4 - 1, 102, 1);          //在OLED显示屏上绘制一条亮/暗的横线
	oled_rline(24, LINE4 - 1, LINE4 + CHEIGHT - 1, 1); //在显示屏上显示一条亮/暗的竖线
	oled_rline(102, LINE4 - 1, LINE4 + CHEIGHT - 1, 1);

	//把字符输入到显示框中
	if (*str1 != '\0')
	{
		format_string_h(str1, align1, 27, LINE4, 74);
	}

	if (*str2 != '\0')
	{
		format_string_h(str2, align2, 27, LINE4, 74);
	}
}

//==================================================================================================
//| 函数名称 | ShowWelcome
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 显示主菜单
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-08-26
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void ShowWelcome(void)
{
	clr_disp_mem();         //清除显存数据
	lcdreset();                    //初始化LCD屏
	clrgdram();
	oled_print(0, LINE0, "    哺乳记录    ") ;  //字符输出函数
	oled_print(0, LINE1, "愿李嘉钊小宝宝") ;  //字符输出函数
	oled_print(0, LINE2, "       健康成长") ;  //字符输出函数
	oled_print(2, LINE4, "   "); //字符输出
	show_right_button("菜单");//显示右功能
	show_left_button("查看"); //显示左功能
	oled_updatescr(0, 64);     //屏幕刷新


}

//==================================================================================================
//| 函数名称 | Display_Items
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 在主界面按下“查看”后，显示条目列表
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-08-26
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void Display_Items(u8 state)
{
	clr_disp_mem();         //清除显存数据
	oled_print(0, LINE0, "项目") ;  //字符输出函数
	oled_print(0, LINE1, "  哺乳 		补水") ;  //字符输出函数
	oled_print(0, LINE2, "  大便 		小便") ;  //字符输出函数

	switch(state)
	{
		case 1:
		{
			oled_print(0, LINE1, "√") ;  //字符输出函数
			Current_state = DISPLAY_ITEM_LACTATION; //当前状态置为项目显示
			break;
		}

		case 2:
		{
			oled_print(0, LINE2, "√") ;  //大便

			Current_state = DISPLAY_ITEM_SHIT; //当前状态置为项目显示
			break;
		}

		case 3:
		{

			oled_print(4, LINE1, "√") ;  //补水
			Current_state = DISPLAY_ITEM_DRINK; //当前状态置为项目显示
			break;
		}

		case 4:
		{

			oled_print(4, LINE2, "√") ;  //小便
			Current_state = DISPLAY_ITEM_URINATE; //当前状态置为项目显示
			break;
		}

		default:
			break;
	}

	show_right_button("返回");//显示右功能
	show_left_button("查看"); //显示左功能
	oled_updatescr(0, 64);     //屏幕刷新
}


//==================================================================================================
//| 函数名称 | Display_Menu
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 在主界面按下“菜单”后，显示条目列表
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2016-08-26
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void Display_Menu(u8 state)
{
	clr_disp_mem();         //清除显存数据
	oled_print(0, LINE0, "      菜单      ") ;  //字符输出函数
	oled_print(0, LINE1, "  时间 		") ;  //字符输出函数
	oled_print(0, LINE2, "  ") ;  //字符输出函数

	switch(state)
	{
		case 1:
		{
			oled_print(0, LINE1, "√") ;  //字符输出函数
			Current_state = DISPLAY_MENU_TIME; //当前状态置为项目显示
			break;
		}


		default:
			break;
	}

	show_right_button("返回");//显示右功能
	show_left_button("查看"); //显示左功能
	oled_updatescr(0, 64);     //屏幕刷新
}
//显示日期和时间的函数

void Show_Time(void)
{
	u8 tim_temp[30];

	switch(Current_state)
	{
		case WELCOME_WAIT:

		case    LACTATION_LIST://显示哺乳时间列表状态
		case    DRINK_LIST://显示补水列表状态
		case    MODIFY_DRINK://修改补水量状态
		case    MODIFY_DRINK_SURE://修改补水量确认状态
		case    SHIT_LIST://显示大便时间列表状态
		case    URINATE_LIST://显示小编时间列表状态
		case DISPLAY_MENU_TIME:
		case DISPLAY_CURRENT_TIME:
			//      case MODIFY_YEAR://修改当前年
			//      case MODIFY_MONTH://修改月
			//      case MODIFY_DATE://修改日
			//      case MODIFY_HOUR://修改小时
			//      case MODIFY_MIN://修改分钟
			//      case MODIFY_SEC://修改秒
		{
			//      ShowWelcome();
			//          sprintf((char*)tim_temp,"%d-%02d-%02d",calendar.w_year,calendar.w_month,calendar.w_date);
			//          new_front_state=0;//从整汉字处开始输入
			//          oled_print(1, LINE3, &tim_temp[0]);//字符输出
			sprintf((char*)tim_temp, "%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
			new_front_state = 0; //从半汉字开始输入
			oled_print(2, LINE4, &tim_temp[0]);//字符输出
			oled_updatescr(0, 64);     //屏幕刷新
			break;
		}

		case DISPLAY_ITEM_LACTATION://显示项目状态--默认选中哺乳
		case DISPLAY_ITEM_DRINK://显示项目状态--选中补水
		case DISPLAY_ITEM_SHIT://显示项目状态--选中大便
		case DISPLAY_ITEM_URINATE://显示项目状态--选中小便
		{
			oled_hline(2, 8, 111, 0);//在OLED显示屏上绘制一条亮/暗的横线
			oled_print(3, LINE4, "↑↓");//在显示屏底部显示状态信息
			oled_updatescr(0, 64);     //屏幕刷新



		}

		default:
			//          clr_disp_mem();         //清除显存数据
			break;
	}
}

void display_current_time(void)
{
	u8 tim_temp[30];
	clr_disp_mem();         //清除显存数据

	memcpy(&temp_time, &calendar, sizeof(calendar));
	oled_print(0, LINE0, "按上下键选择");//字符输出
	sprintf((char*)tim_temp, "%d-%02d-%02d", temp_time.w_year, temp_time.w_month, temp_time.w_date);
	new_front_state = 0; //从整汉字处开始输入
	oled_print(1, LINE1, &tim_temp[0]);//字符输出
	sprintf((char*)tim_temp, "%02d:%02d:%02d", temp_time.hour, temp_time.min, temp_time.sec);
	new_front_state = 0; //从半汉字开始输入
	oled_print(2, LINE2, &tim_temp[0]);//字符输出

	show_right_button("返回");//显示右功能
	show_left_button("选择"); //显示左功能
	oled_updatescr(0, 64);     //屏幕刷新

}
void display_modify_time(void)
{
	u8 tim_temp[30];
	clr_disp_mem();         //清除显存数据
	oled_print(0, LINE0, "按上下键修改");//字符输出
	sprintf((char*)tim_temp, "%d-%02d-%02d", temp_time.w_year, temp_time.w_month, temp_time.w_date);
	new_front_state = 0; //从整汉字处开始输入
	oled_print(1, LINE1, &tim_temp[0]);//字符输出
	sprintf((char*)tim_temp, "%02d:%02d:%02d", temp_time.hour, temp_time.min, temp_time.sec);
	new_front_state = 0; //从半汉字开始输入
	oled_print(2, LINE2, &tim_temp[0]);//字符输出

	show_right_button("返回");//显示右功能
	show_left_button("保存"); //显示左功能
	oled_updatescr(0, 64);     //屏幕刷新

}


