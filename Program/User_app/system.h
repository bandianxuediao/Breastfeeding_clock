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
	DISPLAY_ITEM_LACTATION,//��ʾ��Ŀ״̬--Ĭ��ѡ�в���
	DISPLAY_ITEM_DRINK,//��ʾ��Ŀ״̬--ѡ�в�ˮ
	DISPLAY_ITEM_SHIT,//��ʾ��Ŀ״̬--ѡ�д��
	DISPLAY_ITEM_URINATE,//��ʾ��Ŀ״̬--ѡ��С��

	LACTATION_LIST,//��ʾ����ʱ���б�״̬
	DRINK_LIST,//��ʾ��ˮ�б�״̬
	MODIFY_DRINK,//�޸Ĳ�ˮ��״̬
	MODIFY_DRINK_SURE,//�޸Ĳ�ˮ��ȷ��״̬
	SHIT_LIST,//��ʾ���ʱ���б�״̬
	URINATE_LIST,//��ʾС��ʱ���б�״̬


	BACK
} SYS_STATE;



#endif



