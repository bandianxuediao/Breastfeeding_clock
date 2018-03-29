#include "lcd_12864.h"

#define Null 0


/***********************
* �������� *
***********************/
void ShowMenu(void);
void Menu_Change(unsigned char KeyNum);

/***********************
* �������ܼ��궨�� *
***********************/
#define UP          '3'
#define Down        '7'
#define Esc         'B'
#define Enter       'F'
#define Reset       '0'


/**********************
* Ŀ¼�ṹ�嶨�� *
**********************/
struct MenuItem
{
	unsigned char MenuCount;        //��ǰ��ڵ���
	unsigned char *DisplayString;   //�˵�����
	void (*Subs)();                 //�ڵ㺯��
	struct MenuItem *ChildrenMenus; //�ӽڵ�
	struct MenuItem *ParentMenus;   //���ڵ�
};

/***********************
* �����Ӻ����� *
***********************/
void NullSubs(void)
{
}
//----------------------����Ϊ����,�����ʵ������޸�---------------------------

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
* �ṹ���� *
***********************/
//----------------------����Ϊ����,�����ʵ������޸�---------------------------
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
* ȫ�ֱ��������� *
***********************/
struct MenuItem (*MenuPoint) = MainMenu; //�ṹ��ָ��,ָ��ṹ������ڲ�����ָ��ָ���ܺ���
unsigned char DisplayStart = 0; //��ʾʱ�ĵ�һ���˵���
unsigned char UserChoose = 0;   //�û���ѡ�˵���
unsigned char DisplayPoint = 0; //��ʾָ��
unsigned MaxItems;              //ͬ�����˵���
unsigned char ShowCount = 2;    //ͬ����ʾ�˵���


/***********************
*��ʾ������ *
***********************/
void ShowMenu(void)
{
	unsigned char n;
	MaxItems = MenuPoint[0].MenuCount;//�������ͬ���˵�
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
					UserChoose = 0;//�Ϸ�����,���Ҫ�ع���ֵMaxItems-1
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
					UserChoose = MaxItems - 1; //�·�����,��Ҫ�ع���ֵΪ0
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

		if (UserChoose % ShowCount == 0)       //һ��ֻ����ʾShowCount��
			DisplayStart = UserChoose;
		else if(UserChoose == 1 || UserChoose == 3)
			DisplayStart = UserChoose - 1;      //ʵ�ֹ����Ĺؼ�

		LCDClrText();              //Һ������,���ݲ�ͬҺ�����������޸�
		//          delay_nms(5);                          //Һ��Ϊ��������
		ShowMenu();
	}
}