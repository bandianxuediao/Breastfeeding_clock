#include "includes.h"

//==================================================================================================
//| �������� | KeyDown_Program
//|----------|--------------------------------------------------------------------------------------
//| �������� | �¼��������
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
void KeyDown_Program(void)
{
	switch(Current_state)
	{

		case DISPLAY_ITEM_LACTATION://��ʾ��Ŀ״̬--Ĭ��ѡ�в���
		case DISPLAY_ITEM_DRINK://��ʾ��Ŀ״̬--ѡ�в�ˮ
		case DISPLAY_ITEM_SHIT://��ʾ��Ŀ״̬--ѡ�д��
		case DISPLAY_ITEM_URINATE://��ʾ��Ŀ״̬--ѡ��С��
		{
			Items_state = Calc_items(1); //1�ǵ�ǰ״̬��һ��0�ǵ�ǰ״̬��һ

			Display_Items(Items_state); //Ĭ��Ϊѡ��Lactation

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
			if((TurnPage_Calc - 2) > 0)
			{
				TurnPage_Calc--;
				Renovate_List(BASE_ADDR_LACTATION, 1);
			}

			break;

		case DRINK_LIST:
			if((TurnPage_Calc - 2) > 0)
			{
				TurnPage_Calc--;
				Renovate_List(BASE_ADDR_DRINK, 1);
			}

			break;

		case SHIT_LIST:
			if((TurnPage_Calc - 2) > 0)
			{
				TurnPage_Calc--;
				Renovate_List(BASE_ADDR_SHIT, 1);
			}

			break;

		case URINATE_LIST:
			if((TurnPage_Calc - 2) > 0)
			{
				TurnPage_Calc--;
				Renovate_List(BASE_ADDR_URINATE, 1);
			}

			break;

		case WELCOME_WAIT:

			break;

		case SELECT_YEAR://�޸ĵ�ǰ��
			delay_ms(500);
			Current_state = SELECT_MONTH;
			break;

		case SELECT_MONTH://�޸���
			delay_ms(500);
			Current_state = SELECT_DATE;
			break;

		case SELECT_DATE://�޸���
			delay_ms(500);
			Current_state = SELECT_HOUR;
			break;

		case SELECT_HOUR://�޸�Сʱ
			delay_ms(500);
			Current_state = SELECT_MIN;
			break;

		case SELECT_MIN://�޸ķ���
			delay_ms(500);
			Current_state = SELECT_SEC;
			break;

		case SELECT_SEC://�޸���
			delay_ms(500);
			Current_state = SELECT_YEAR;
			break;


		case MODIFY_YEAR://�޸ĵ�ǰ��
		case MODIFY_MONTH://�޸���
		case MODIFY_DATE://�޸���
		case MODIFY_HOUR://�޸�Сʱ
		case MODIFY_MIN://�޸ķ���
		case MODIFY_SEC://�޸���
			Modify_time(0);

			break;

		default:
			break;

	}
}

