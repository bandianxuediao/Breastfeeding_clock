#include "includes.h"

//==================================================================================================
//| �������� | KeyRightPro 
//|----------|--------------------------------------------------------------------------------------
//| �������� | �ҹ��ܼ���Ϣ��Ӧ����
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
void KeySurePro(MSG msg)
{
	u8 pas1,pas2,temp_state;
	u8 TEMP_BOXNUM ;
	//������Ϣ��ʱЧ���ж�
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch((SYS_STATE)msg.param1)
	{
		TEMP_BOXNUM = 0  ;
		case WAIT_SURE_KEY:
			switch(INPUT_PASS_STATE)
			{
				case 1: //���ˢ����һ����������	1
					SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					SetCurrentState(INPUT_CARD_KEY_AGAIN);	//���ó��ٴ���������״̬
					break;
				case 2: //���ˢ���ڶ�����������	2
					SURE_SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					if(SURE_SURE_BOXKEY == SURE_BOXKEY)
					{
						ShowSys_Message(3);
						USER_CARD_ID[5] =  SURE_SURE_BOXKEY / 100;
						USER_CARD_ID[6] =  SURE_SURE_BOXKEY % 100;
						USER_CARD_ID[7] = 0x11;//���������־λ
						delay_ms(2000);
						SAVE_INFORMATION_CARD();
						delay_ms(1000);
						SURE_SURE_BOXKEY = 0;
						SURE_BOXKEY = SURE_SURE_BOXKEY;
						memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
						memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));												
						SetCurrentState(SHOW_WELCOME);	//����������
					break;
					}	
					if(SURE_SURE_BOXKEY != SURE_BOXKEY)
					{
						ShowSys_Message(4);
						delay_ms(2000);
						ShowSys_Message(2);			
						memset(RC531_sbuf,0,sizeof(RC531_sbuf));
						INPUT_DATA_AMOUNT = 0;
						INPUT_PASS_STATE = 0 ;//���ˢ������������״̬Ϊδ�����κ��ַ�						
						SetCurrentState(INPUT_CARD_KEY);//��ˢ�����ʱ���������״̬
					break;
					}
				case 3://ˢ��ȡ����������				3
					pas1 = (int)(INPUT_DATA_NUM[0]-48)*10+(int)(INPUT_DATA_NUM[1]-48);
					pas2 = (int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0;
					memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
					memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));																
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );					

					if((Password[0] == pas1)&(Password[1] == pas2))//���������ȷ
					{
						ShowSys_Message(3);
						delay_ms(2000);
						CLEAR_BOX();
						SetCurrentState(SHOW_WELCOME);	//����������
						break;				
					}
					else
					{
						ShowSys_Message(4);
						delay_ms(2000);
						ShowSys_Message(5);
//						SetCurrentState(SHOW_WELCOME);//����������
						break;	
					}
					break;
				case 4://��������һ����������  4
					SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					SetCurrentState(PASSW_INPUT_KEY_AGAIN);	//���ó��ٴ���������״̬
					break;
				case 5://�������ڶ�����������  5
					SURE_SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					if(SURE_SURE_BOXKEY == SURE_BOXKEY)
					{
						ShowSys_Message(3);
						CARD_ID_INF[3] = SURE_SURE_BOXKEY / 100;
						CARD_ID_INF[4] = SURE_SURE_BOXKEY % 100;
						delay_ms(2000);
						SAVE_INFORMATION_CARD();
						delay_ms(1000);
						SURE_SURE_BOXKEY = 0;
						SURE_BOXKEY = SURE_SURE_BOXKEY;
						memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
						SetCurrentState(SHOW_WELCOME);	//����������
					break;
					}	
					if(SURE_SURE_BOXKEY != SURE_BOXKEY)
					{
						ShowSys_Message(4);
						delay_ms(2000);
//						ShowSys_Message(7);			
						memset(RC531_sbuf,0,sizeof(RC531_sbuf));
						INPUT_DATA_AMOUNT = 0;
						INPUT_PASS_STATE = 0 ;//����������������״̬Ϊδ�����κ��ַ�						
						SetCurrentState(SHOW_WELCOME);//����������
					break;
					}
					//���Ϊ3λ
				case 6://ȡ���������	6
					TEMP_BOXNUM=(int)(INPUT_DATA_NUM[0]-48)*100+(int)(INPUT_DATA_NUM[1]-48)*10+(int)(INPUT_DATA_NUM[2]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					if((TEMP_BOXNUM>0)&(TEMP_BOXNUM<200))
					{
						temp_state = FindBox_FromIndex(TEMP_BOXNUM);
						if(temp_state == 0)//�����洢�Ĳ�ͬ������ϵ����Ա
						{
							ShowSys_Message(9);
							delay_ms(3000);
							SetCurrentState(SHOW_WELCOME);	//����������
							break;
						}
						if(temp_state == 1)//���ڿ��ţ���ˢ�����������
						{
							ShowSys_Message(10);  //��Ҫˢ�����䣬��ˢ��
							delay_ms(3000); 
							SetCurrentState(SHOW_WELCOME);	//����������
							break;
						}
						if(temp_state == 2)//�����ȷ�����������룬�����Ѵ洢��ȫ�ֱ���Password[0��1]
						{
							USER_BOX_NUM = TEMP_BOXNUM;
							ShowSys_Message(11);  //�����ȷ����Ҫ��������							
							SetCurrentState(OUT_INPUT_PASSW);	//ȡ����������״̬
							break;
						}
						if(temp_state == 3)//����Ϊ��
						{
							ShowSys_Message(12);  //����Ϊ��	
							delay_ms(3000); 							
							SetCurrentState(SHOW_WELCOME);	//����������
							break;
						}						
					break;
					}	
					if(TEMP_BOXNUM > 200)
					{
						ShowSys_Message(13);//��Ų�����
						delay_ms(3000);
						SetCurrentState(SHOW_WELCOME);//����������
					break;
					}
				case 7://����ȡ����������				7
					pas1 = (int)(INPUT_DATA_NUM[0]-48)*10+(int)(INPUT_DATA_NUM[1]-48);
					pas2 = (int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0;
					memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
					memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));																
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );									
					if((Password[0] == pas1)&(Password[1] == pas2))//���������ȷ
					{
						ShowSys_Message(3);
						delay_ms(2000);
						CLEAR_BOX();
						SetCurrentState(SHOW_WELCOME);	//����������
						break;				
					}
					else
					{
						ShowSys_Message(4);
						delay_ms(2000);
						ShowSys_Message(11);
//						SetCurrentState(SHOW_WELCOME);//����������
						break;	
					}
					break;


					
				default:					
					break;				
			}
			break;
		//���С��3λ
		case OUT_INPUT_BOXNUM://ȡ���������	6
			if(INPUT_DATA_AMOUNT == 1)
			{
				TEMP_BOXNUM=(int)(INPUT_DATA_NUM[0]-48);
			}	
			if(INPUT_DATA_AMOUNT == 2)
			{
				TEMP_BOXNUM=(int)(INPUT_DATA_NUM[0]-48)*10+(int)(INPUT_DATA_NUM[1]-48);
			}	
			if(INPUT_DATA_AMOUNT == 3)
			{
				TEMP_BOXNUM=(int)(INPUT_DATA_NUM[0]-48)*100+(int)(INPUT_DATA_NUM[1]-48)*10+(int)(INPUT_DATA_NUM[2]-48);
			}						
			INPUT_DATA_AMOUNT = 0 ;
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
			if((TEMP_BOXNUM>0)&(TEMP_BOXNUM<200))
			{
				temp_state = FindBox_FromIndex(TEMP_BOXNUM);
				if(temp_state == 0)//�����洢�Ĳ�ͬ������ϵ����Ա
				{
					ShowSys_Message(9);
					delay_ms(3000);
					SetCurrentState(SHOW_WELCOME);	//����������
					break;
				}
				if(temp_state == 1)//���ڿ��ţ���ˢ�����������
				{
					ShowSys_Message(10);  //��Ҫˢ�����䣬��ˢ��
					delay_ms(3000); 
					SetCurrentState(SHOW_WELCOME);	//����������
					break;
				}
				if(temp_state == 2)//�����ȷ�����������룬�����Ѵ洢��ȫ�ֱ���Password[0��1]
				{
					USER_BOX_NUM = TEMP_BOXNUM;
					ShowSys_Message(11);  //�����ȷ����Ҫ��������							
					SetCurrentState(OUT_INPUT_PASSW);	//ȡ����������״̬
					break;
				}
				if(temp_state == 3)//����Ϊ��
				{
					ShowSys_Message(12);  //����Ϊ��	
					delay_ms(3000); 							
					SetCurrentState(SHOW_WELCOME);	//����������
					break;
				}						
			break;
			}	
			if(TEMP_BOXNUM > 200)
			{
				ShowSys_Message(13);//��Ų�����
				delay_ms(3000);
				SetCurrentState(SHOW_WELCOME);//����������
			break;
			}
		break;
		
		
		case	INPUT_BOXKEY:
			
		
			break;
		case	SET_KEY_BOXNUM:
			
		
			SetCurrentState(SET_KEY_OLD_BOXKEY);	
			break;
		case	SET_KEY_OLD_BOXKEY:
			
		
			SetCurrentState(SET_KEY_NEW_BOXKEY);	
			break;
		case	SET_KEY_NEW_BOXKEY:
			
		
			SetCurrentState(SET_KEY_SURE_BOXKEY);	
			break;
		case INPUT_BOXNUM:	
/*��ȥ��ʮ�ˣ�����Ϊ�����ȡ�����ַ�����Ӧ��ʮ��������Ҫ��ȥ48����ʮ���Ƶ�����*/
			SURE_BOXNUM=(int)(INPUT_DATA_NUM[0]-48)*100+(int)(INPUT_DATA_NUM[1]-48)*10+(int)(INPUT_DATA_NUM[2]-48);
			INPUT_DATA_AMOUNT = 0 ;
			memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
			ShowInput(3);
			SetCurrentState(INPUT_BOXKEY);	
			break;


		
		default:
			break;
	}		
}
