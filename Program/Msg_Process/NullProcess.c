#include "includes.h"

void NullPro(MSG msg)
{
//	u16 v_temp,i_temp;
//	u16 i,k; 	
//	MSG temp_msg;
//	u8 re_num ;
	static u16 max_waite;
//	uint8_t i;
//	uint8_t status;
	
	switch(GetCurrentState())
	{
		case GPIO_INIT://оƬ�ϵ������ִ�и���Ϣ
			SystemHWConfig();
			ShowWelcome();
			delay_ms(2000);
//			BufferInit();
//			RC531_SWITCH = 1;
//			KEY_BOARD =1;
			SetCurrentState(SHOW_WELCOME);//��ʼ�����
			break;
		case SHOW_WELCOME:
			ShowWelcome();
			delay_ms(200);
//			result = INT3;
			SetCurrentState(WAIT_CARD_KEY);//�ȴ�ˢ��״̬���ص��ȴ�����״̬
			break;
			
		case 	WAIT_CARD:
			RC531_SWITCH = 1; //��CARD���ش򿪣����Լ�⿨
			KEY_BOARD =0;			//�ð������عرգ������Լ�ⰴ��
			find_card();
			break;
		case OUT_INPUT_BOXNUM://����Ϊ"ȡ"�������״̬	
		case OUT_INPUT_PASSW://��ȡ����������			
		case INPUT_BOXNUM:
		case INPUT_BOXKEY:
		case WAIT_KEY:
		case WAIT_SURE_KEY:
		case INPUT_CARD_KEY:
		case INPUT_CARD_KEY_AGAIN://��ˢ�����ʱ�ٴ����������״̬
		case PASSW_INPUT_KEY:
		case PASSW_INPUT_KEY_AGAIN:
//		case INPUT_CARD_KEY_SURE://��ˢ�����ʱȷ�����������
		case OUTPUT_CARD_KEY://��ˢ�����ʱ���������״̬
		case OUTPUT_CARD_KEY_AGAIN://��ˢ�����ʱ�ٴ����������״̬
//		case OUTPUT_CARD_KEY_SURE://��ˢ�����ʱȷ�����������	
			RC531_SWITCH = 0; //���Լ������룬�����Լ�⿨
			KEY_BOARD =1;			//�ð������ش򿪣����Լ�ⰴ��
			pad_scan();
			break;
			
		case	WAIT_CARD_KEY:
			RC531_SWITCH = 1; //�����Լ������룬���Լ�⿨
			KEY_BOARD =1;			//�ð������ش򿪣����Լ�ⰴ��			
			find_card();
			pad_scan();
			break;	


//		case FINDED_CARD:  //�����˸��ʱû��ʵ��
//			if(GetSysTickTimer1State() == TIME_OUT)
//			{
//				SetSysTickTimer1(500);
//				FlashCursor();//�����˸
//			}
//			break;

		default:		
			break;
	}


	oled_updatescr(0, 64);	   //��Ļˢ��	
		max_waite++;
//		if(max_waite==10000)
//		{   lcdreset();                    //��ʼ��LCD��
//				clrgdram();
//				max_waite=0;
//		}
}
