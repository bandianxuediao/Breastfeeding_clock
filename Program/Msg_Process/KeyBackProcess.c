#include "includes.h"

//==================================================================================================
//| �������� | KeyLeftPro 
//|----------|--------------------------------------------------------------------------------------
//| �������� | ���ܼ���Ϣ��Ӧ����
//|----------|--------------------------------------------------------------------------------------
//| ������� | msg ��������Ϣ
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//|----------|--------------------------------------------------------------------------------------       
//| ������� | ��д�ˣ����Ƕ�    ʱ�䣺2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   ��ע   | 
//|----------|-------------------------------------------------------------------------------------- 
//| �޸ļ�¼ | �޸��ˣ�          ʱ�䣺         �޸����ݣ� 
//==================================================================================================
void KeyBackPro(MSG msg)
{
	SYS_STATE state;
	
	
	//������Ϣ��ʱЧ���ж�
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch((SYS_STATE)msg.param1)
	{
		case WAIT_CARD://
			break;
		case 	INPUT_BOXNUM:
			INPUT_DATA_AMOUNT = 0 ;
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );		
			SetCurrentState(SHOW_WELCOME);//ϵͳ�ϵ磬�����״̬
			RC531_SWITCH = 0;		
			break;
		case	INPUT_BOXKEY:
			INPUT_DATA_AMOUNT = 0 ;
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );		
			SetCurrentState(INPUT_BOXNUM);//ϵͳ�ϵ磬�����״̬
			RC531_SWITCH = 1;		
			break;
		case  INPUT_CARD_KEY:
		case  INPUT_CARD_KEY_AGAIN:
		case  OUTPUT_CARD_KEY:
		case PASSW_INPUT_KEY:
		case PASSW_INPUT_KEY_AGAIN:

		case OUT_INPUT_BOXNUM://����Ϊ"ȡ"�������״̬
		case OUT_INPUT_PASSW://��ȡ����������	//ȡ����������				
//		case INPUT_CARD_KEY:
//		case INPUT_CARD_KEY_AGAIN:			
//		case 	INPUT_BOXNUM:	
//		case	INPUT_BOXKEY:
//		case OUTPUT_CARD_KEY:
//		case PASSW_INPUT_KEY:
//		case PASSW_INPUT_KEY_AGAIN:			

		
			memset(RC531_sbuf,0,sizeof(RC531_sbuf));
			INPUT_DATA_AMOUNT = 0;
			INPUT_PASS_STATE = 0 ;//���ˢ������������״̬Ϊδ�����κ��ַ�
			memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
			memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));
			memset(Password,0,sizeof(Password));			
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );		
			SetCurrentState(SHOW_WELCOME);//��ˢ�����ʱ���������״̬
			break;	
			
		
		
		default:
			break;
	}		
}
