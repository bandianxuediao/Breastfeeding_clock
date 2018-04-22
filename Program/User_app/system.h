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

	LACTATION_LIST,//显示哺乳时间列表状态
	DRINK_LIST,//显示补水列表状态
	MODIFY_DRINK,//修改补水量状态
	MODIFY_DRINK_SURE,//修改补水量确认状态
	SHIT_LIST,//显示大便时间列表状态
	URINATE_LIST,//显示小编时间列表状态


	BACK
} SYS_STATE;



#endif



