#ifndef _SYSTEM_H_
#define _SYSTEM_H_



typedef enum
{
	WELCOME_WAIT,
	PRESS_KEY_UP,
	PRESS_KEY_DOWN,
	PRESS_KEY_LEFT,
	PRESS_KEY_RIGHT,
	DISPLAY_ITEM,
	DISPLAY_ITEM_LACTATION,//显示项目状态--默认选中哺乳
	DISPLAY_ITEM_DRINK,//显示项目状态--选中补水
	DISPLAY_ITEM_SHIT,//显示项目状态--选中大便
	DISPLAY_ITEM_URINATE,//显示项目状态--选中小便

	DISPLAY_MENU_TIME,//显示菜单--选中时间
	DISPLAY_MENU_CLEAR,//显示菜单--选中清空
	DISPLAY_MENU_CLEAR_WAIT,//等待确认清空
	DISPLAY_MENU_CLEAR_DONE,//清空完成
	DISPLAY_CURRENT_TIME,//显示当前时间
	SELECT_YEAR,//选中年
	SELECT_MONTH,//选中月
	SELECT_DATE,//选中日
	SELECT_HOUR,//选中小时
	SELECT_MIN,//选中分钟
	SELECT_SEC,//选中秒

	MODIFY_YEAR,//修改当前年
	MODIFY_MONTH,//修改月
	MODIFY_DATE,//修改日
	MODIFY_HOUR,//修改小时
	MODIFY_MIN,//修改分钟
	MODIFY_SEC,//修改秒

	LACTATION_LIST,//显示哺乳时间列表状态
	DRINK_LIST,//显示补水列表状态
	MODIFY_DRINK,//修改补水量状态
	MODIFY_DRINK_SURE,//修改补水量确认状态
	SHIT_LIST,//显示大便时间列表状态
	URINATE_LIST,//显示小编时间列表状态


	BACK
} SYS_STATE;



#endif



