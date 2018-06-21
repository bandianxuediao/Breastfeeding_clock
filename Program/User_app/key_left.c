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
	u8 display_temp[16];

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
			if((Diff_timecount >= 3600) || ((EepIndex.lactation | Diff_timecount) == 0)) //������ʱ������1Сʱ
			{
				Storage_One_Data(BASE_ADDR_LACTATION);
			}

			break;

		case DRINK_LIST:
			if((Diff_timecount >= 3600) || ((EepIndex.drink | Diff_timecount) == 0)) //��ˮ���ʱ������1Сʱ
			{
				Storage_One_Data(BASE_ADDR_DRINK);
			}

			break;

		case SHIT_LIST:
			if((Diff_timecount >= 3600) || ((EepIndex.shit | Diff_timecount) == 0)) //�����ʱ������1Сʱ
			{
				Storage_One_Data(BASE_ADDR_SHIT);
			}

			break;

		case URINATE_LIST:
			if((Diff_timecount >= 1800) || ((EepIndex.urinate | Diff_timecount) == 0)) //С����ʱ������0.5Сʱ
			{
				Storage_One_Data(BASE_ADDR_URINATE);
			}

			break;

		case DISPLAY_MENU_CLEAR:
			clr_disp_mem();         //����Դ�����
			oled_updatescr(0, 64);     //��Ļˢ��
			sprintf((char*)display_temp, "�������������");
			oled_print(0, LINE1, &display_temp[0]);//�ַ����
			sprintf((char*)display_temp, "��ȷ��ִ�в���");
			oled_print(0, LINE2, &display_temp[0]);//�ַ����
			sprintf((char*)display_temp, "ȷ��        ����");
			oled_print(0, LINE4, &display_temp[0]);//�ַ����

			oled_updatescr(0, 64);     //��Ļˢ��
			Current_state = DISPLAY_MENU_CLEAR_WAIT;
			break;

		case DISPLAY_MENU_CLEAR_WAIT:
			AT24CXX_WriteLenByte(10, 0, 2);
			AT24CXX_WriteLenByte(20, 0, 2);
			AT24CXX_WriteLenByte(30, 0, 2);
			AT24CXX_WriteLenByte(40, 0, 2);
			sprintf((char*)display_temp, "   �������");
			oled_print(0, LINE1, &display_temp[0]);//�ַ����
			sprintf((char*)display_temp, "��������������");
			oled_print(0, LINE2, &display_temp[0]);//�ַ����
			oled_updatescr(0, 64);     //��Ļˢ��
			delay_ms(2000);
			ShowWelcome();
			Current_state = WELCOME_WAIT;

			break;


		case MODIFY_YEAR://�޸ĵ�ǰ��
		case MODIFY_MONTH://�޸���
		case MODIFY_DATE://�޸���
		case MODIFY_HOUR://�޸�Сʱ
		case MODIFY_MIN://�޸ķ���
		case MODIFY_SEC://�޸���
			RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_EnterConfigMode();/// ��������
			RTC_SetPrescaler(32767); //����RTCԤ��Ƶ��ֵ
			RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_Set(temp_time.w_year, temp_time.w_month, temp_time.w_date, temp_time.hour, temp_time.min, temp_time.sec); //����ʱ��
			RTC_ExitConfigMode(); //�˳�����ģʽ
			BKP_WriteBackupRegister(BKP_DR1, 0X5050);   //��ָ���ĺ󱸼Ĵ�����д���û���������
			delay_ms(1100);//�ȴ�1�����ϣ�rtc����ʱ��

		case DISPLAY_MENU_TIME:
			display_current_time();
			Draw_Line = 1;
			Current_state = SELECT_YEAR; //Ĭ��ѡ����
			break;

		case SELECT_YEAR:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_YEAR; //�޸���
			break;

		case SELECT_MONTH:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_MONTH; //�޸���
			break;

		case SELECT_DATE:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_DATE; //�޸���
			break;

		case SELECT_HOUR:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_HOUR; //�޸���
			break;

		case SELECT_MIN:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_MIN; //�޸���
			break;

		case SELECT_SEC:
			Draw_Line = 1;
			display_modify_time();
			Current_state = MODIFY_SEC; //�޸���
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


