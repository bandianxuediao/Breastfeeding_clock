#include "includes.h"

//==================================================================================================
//| �������� | KeyRight_Program
//|----------|--------------------------------------------------------------------------------------
//| �������� | �Ҽ��������
//|----------|--------------------------------------------------------------------------------------
//| ������� | ��
//|----------|--------------------------------------------------------------------------------------
//| ���ز��� | ��
//|----------|--------------------------------------------------------------------------------------
//| ������� | ��д�ˣ����Ƕ�    ʱ�䣺2018-04-21
//|----------|--------------------------------------------------------------------------------------
//|   ��ע   |
//|----------|--------------------------------------------------------------------------------------
//| �޸ļ�¼ | �޸��ˣ�          ʱ�䣺         �޸����ݣ�
//==================================================================================================
void KeyRight_Program(void)
{
	switch(Current_state)
	{

		case DISPLAY_ITEM_LACTATION://��ʾ��Ŀ״̬--Ĭ��ѡ�в���
		case DISPLAY_ITEM_DRINK://��ʾ��Ŀ״̬--ѡ�в�ˮ
		case DISPLAY_ITEM_SHIT://��ʾ��Ŀ״̬--ѡ�д��
		case DISPLAY_ITEM_URINATE://��ʾ��Ŀ״̬--ѡ��С��
		case DISPLAY_MENU_TIME:
			ShowWelcome();
			Current_state = WELCOME_WAIT;
			break;

		case MODIFY_YEAR://�޸ĵ�ǰ��
		case MODIFY_MONTH://�޸���
		case MODIFY_DATE://�޸���
		case MODIFY_HOUR://�޸�Сʱ
		case MODIFY_MIN://�޸ķ���
		case MODIFY_SEC://�޸���



		case        SELECT_YEAR://ѡ����
		case    SELECT_MONTH://ѡ����
		case    SELECT_DATE://ѡ����
		case    SELECT_HOUR://ѡ��Сʱ
		case    SELECT_MIN://ѡ�з���
		case    SELECT_SEC://ѡ����
		case DISPLAY_CURRENT_TIME:
		case WELCOME_WAIT:
			Display_Menu(1);
			Current_state = DISPLAY_MENU_TIME;
			break;
			break;

		case LACTATION_LIST:
			Display_Items(1);   //Ĭ��Ϊѡ��Lactation
			Current_state = DISPLAY_ITEM_LACTATION; //��ǰ״̬��Ϊ��Ŀ��ʾ
			break;

		case DRINK_LIST:
			Display_Items(3);   //Ĭ��Ϊѡ��Lactation
			Current_state = DISPLAY_ITEM_DRINK; //��ǰ״̬��Ϊ��Ŀ��ʾ
			break;

		case SHIT_LIST:
			Display_Items(2);   //Ĭ��Ϊѡ��Lactation
			Current_state = DISPLAY_ITEM_SHIT; //��ǰ״̬��Ϊ��Ŀ��ʾ
			break;

		case URINATE_LIST:
			Display_Items(4);   //Ĭ��Ϊѡ��Lactation
			Current_state = DISPLAY_ITEM_URINATE; //��ǰ״̬��Ϊ��Ŀ��ʾ
			break;



		default:
			break;

	}
}

