#include "includes.h"

//==================================================================================================
//| �������� | Key8Pro 
//|----------|--------------------------------------------------------------------------------------
//| �������� | ����8��Ϣ��Ӧ����
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
void Key8Pro(MSG msg)
{	
	//������Ϣ��ʱЧ���ж�
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch((SYS_STATE)msg.param1)
	{
		case WAIT_CARD://�����˵��°���1����������ע������
//			ShowPad(8);
//			delay_ms(200);
//			RC531_SWITCH = 1;
//			SetCurrentState(SHOW_WELCOME);//ϵͳ�ϵ磬�����״̬
			break;
		case OUT_INPUT_BOXNUM://����Ϊ"ȡ"�������״̬
			memcpy((char*)&INPUT_DATA_NUM[INPUT_DATA_AMOUNT], "8", 1);
			INPUT_DATA_AMOUNT++;
			ShowInput(2);
			if(INPUT_DATA_AMOUNT == 3)
			{
			SetCurrentState(WAIT_SURE_KEY);//��λ����������ɣ��ȴ�����ȷ�ϰ���
			break;				
			}
		
			break;			
		case OUT_INPUT_PASSW://��ȡ����������					
		case INPUT_CARD_KEY:
		case INPUT_CARD_KEY_AGAIN:			
		case INPUT_BOXNUM:	
		case	INPUT_BOXKEY:
		case OUTPUT_CARD_KEY:
		case PASSW_INPUT_KEY:
		case PASSW_INPUT_KEY_AGAIN:			
			memcpy((char*)&INPUT_DATA_NUM[INPUT_DATA_AMOUNT], "8", 1);
			INPUT_DATA_AMOUNT++;
			ShowInput(2);
			if(INPUT_DATA_AMOUNT == 4)
			{
			SetCurrentState(WAIT_SURE_KEY);//��λ����������ɣ��ȴ�����ȷ�ϰ���
			break;				
			}
			break;
		
		default:
			break;
	}		
}
