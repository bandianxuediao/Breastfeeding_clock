#include "includes.h"
u8 Items_state = 1;
//==================================================================================================
//| �������� | KeyLeft_Program
//|----------|--------------------------------------------------------------------------------------
//| �������� | ����������
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
void KeyLeft_Program(void)
{


	switch(Current_state)
	{
		case WELCOME_WAIT:
			Display_Items(1);   //Ĭ��Ϊѡ��Lactation
			Current_state = DISPLAY_ITEM_LACTATION; //��ǰ״̬��Ϊ��Ŀ��ʾ
			break;

		case DISPLAY_ITEM_LACTATION://��ʾ��Ŀ״̬--Ĭ��ѡ�в���

			List_Display();

			Current_state = LACTATION_LIST;
			break;

		case DISPLAY_ITEM_DRINK://��ʾ��Ŀ״̬--ѡ�в�ˮ

			List_Display();

			Current_state = DRINK_LIST;
			break;
			case DISPLAY_ITEM_SHIT://��ʾ��Ŀ״̬--ѡ�д��
							List_Display();

			Current_state = SHIT_LIST;
			break;
		case DISPLAY_ITEM_URINATE://��ʾ��Ŀ״̬--ѡ��С��
			List_Display();

			Current_state = URINATE_LIST;
			break;			
		case LACTATION_LIST:
		case DRINK_LIST:
			case SHIT_LIST:
				case URINATE_LIST:
					
				
				
				
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


