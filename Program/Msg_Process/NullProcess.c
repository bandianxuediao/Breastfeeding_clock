#include "includes.h"

void NullPro(MSG msg)
{
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
