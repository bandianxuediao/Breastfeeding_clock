#include "lcd_12864.h"

#define Null 0


/***********************
* 函数声明 *
***********************/
void ShowMenu(void);
void Menu_Change(unsigned char KeyNum);

/***********************
* 按键功能键宏定义 *
***********************/
#define UP          '3'
#define Down        '7'
#define Esc         'B'
#define Enter       'F'
#define Reset       '0'


/**********************
* 目录结构体定义 *
**********************/
struct MenuItem
{
	unsigned char MenuCount;        //当前层节点数
	unsigned char *DisplayString;   //菜单标题
	void (*Subs)();                 //节点函数
	struct MenuItem *ChildrenMenus; //子节点
	struct MenuItem *ParentMenus;   //父节点
};

/***********************
* 调用子函数区 *
***********************/
void NullSubs(void)
{
}
//----------------------以下为例子,请根据实际情况修改---------------------------

void TimeSet(void)
{

}

void DateSet(void)
{

}

void AlertSet (void)
{

}
//------------------------------------------------------------------------------






/***********************
* 结构体区 *
***********************/
//----------------------以下为例子,请根据实际情况修改---------------------------
struct MenuItem TimeMenu[4];
struct MenuItem FlashMenu[5];
struct MenuItem VoiceMenu[5];
struct MenuItem RobotMenu[5];
struct MenuItem MainMenu[5];

struct MenuItem TimeMenu[4] =
{
	//MenuCount       DisplayString           Subs               ChildrenMenus       ParentMenus
	{4,             "1.Time Set",           TimeSet,           Null,               MainMenu},
	{4,             "2.Date Set",           DateSet,           Null,               MainMenu},
	{4,             "3.AlertSet",           AlertSet,          Null,               MainMenu},
	{4,             "4.Back",               NullSubs,          MainMenu,           MainMenu},
};

struct MenuItem FlashMenu[5] =
{
	//MenuCount       DisplayString           Subs               ChildrenMenus       ParentMenus
	{5,             "1.Flash Record",       NullSubs,          Null,               MainMenu},
	{5,             "2.Play",               NullSubs,          Null,               MainMenu},
	{5,             "3.Pause",              NullSubs,          Null,               MainMenu},
	{5,             "4.Flash Delete",       NullSubs,          Null,               MainMenu},
	{5,             "5.Back",               NullSubs,          MainMenu,           MainMenu},
};

struct MenuItem VoiceMenu[5] =
{
	//MenuCount       DisplayString           Subs               ChildrenMenus       ParentMenus
	{5,             "1.Voice Record",    NullSubs,          Null,               MainMenu},
	{5,             "2.Play",               NullSubs,          Null,               MainMenu},
	{5,             "3.Pause",              NullSubs,          Null,               MainMenu},
	{5,             "4.Voice Delete",       NullSubs,          Null,               MainMenu},
	{5,             "5.Back",               NullSubs,          MainMenu,           MainMenu},
};

struct MenuItem RobotMenu[5] =
{
	//MenuCount       DisplayString           Subs               ChildrenMenus       ParentMenus
	{5,             "1.Turn Left",          NullSubs,          Null,               MainMenu},
	{5,             "2.Turn Right",         NullSubs,          Null,               MainMenu},
	{5,             "3.Go Ahead",           NullSubs,          Null,               MainMenu},
	{5,             "4.Go Back",            NullSubs,          Null,               MainMenu},
	{5,             "5.Back",               NullSubs,          MainMenu,           MainMenu},
};


struct MenuItem MainMenu[5] =
{
	//MenuCount       DisplayString           Subs               ChildrenMenus       ParentMenus
	{5,             "1.Time Set",        NullSubs,          TimeMenu,           Null},
	{5,             "2.Voice Center",       NullSubs,          VoiceMenu,          Null},
	{5,             "3.Robot Control",      NullSubs,          RobotMenu,          Null},
	{5,             "4.Flash Option",       NullSubs,          FlashMenu,          Null},
	{5,             "5.Back",               NullSubs,          MainMenu,           MainMenu},
};
//------------------------------------------------------------------------------






/***********************
* 全局变量声明区 *
***********************/
struct MenuItem (*MenuPoint) = MainMenu; //结构体指针,指向结构体后由内部函数指针指向功能函数
unsigned char DisplayStart = 0; //显示时的第一个菜单项
unsigned char UserChoose = 0;   //用户所选菜单项
unsigned char DisplayPoint = 0; //显示指针
unsigned MaxItems;              //同级最大菜单数
unsigned char ShowCount = 2;    //同屏显示菜单数


/***********************
*显示函数区 *
***********************/
void ShowMenu(void)
{
	unsigned char n;
	MaxItems = MenuPoint[0].MenuCount;//定义最大同级菜单
	DisplayPoint = DisplayStart;

	for(n = 0; DisplayPoint < MaxItems && n < ShowCount; n++)
	{
		if(DisplayPoint == UserChoose)
			DisplayList(0, n, "->");

		DisplayList(2, n, MenuPoint[DisplayPoint++].DisplayString);

	}

}

void Menu_Change(unsigned char KeyNum)

{
	if(KeyNum)
	{
		switch(KeyNum)
		{
			case UP:
				UserChoose --;

				if (UserChoose == 255)
				{
					UserChoose = 0;//上翻截至,如果要回滚赋值MaxItems-1
				}

				break;

			case Esc:
				if (MenuPoint[UserChoose].ParentMenus != Null)
				{
					MenuPoint = MenuPoint[UserChoose].ParentMenus;
					UserChoose = 0;
					DisplayStart = 0;
				}

				break;

			case Down:
				UserChoose ++;

				if (UserChoose == MaxItems)
				{
					UserChoose = MaxItems - 1; //下翻截至,如要回滚赋值为0
				}

				break;

			case Enter:
				if (MenuPoint[UserChoose].Subs != NullSubs)
				{
					(*MenuPoint[UserChoose].Subs)();
				}
				else if (MenuPoint[UserChoose].ChildrenMenus != Null)
				{
					MenuPoint = MenuPoint[UserChoose].ChildrenMenus;
					UserChoose = 0;
					DisplayStart = 0;
				}

				break;

			case Reset:
				MenuPoint = MainMenu;
				UserChoose = 0;
				DisplayStart = 0;
				break;

			default:
				break;
		}

		if (UserChoose % ShowCount == 0)       //一屏只能显示ShowCount行
			DisplayStart = UserChoose;
		else if(UserChoose == 1 || UserChoose == 3)
			DisplayStart = UserChoose - 1;      //实现滚屏的关键

		LCDClrText();              //液晶清屏,根据不同液晶函数自行修改
		//          delay_nms(5);                          //液晶为慢速器件
		ShowMenu();
	}
}