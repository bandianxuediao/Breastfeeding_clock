#include "includes.h"

//==================================================================================================
//| �������� | ConnectPro 
//|----------|--------------------------------------------------------------------------------------
//| �������� | ͨ��������Ϣ��Ӧ����
//|----------|--------------------------------------------------------------------------------------
//| ������� | msg ��������Ϣ
//|----------|--------------------------------------------------------------------------------------       
//| ���ز��� | ��
//|----------|--------------------------------------------------------------------------------------       
//| ������� | ��д�ˣ����Ƕ�   ʱ�䣺2016-07-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   ��ע   | 
//|----------|-------------------------------------------------------------------------------------- 
//| �޸ļ�¼ | �޸��ˣ�          ʱ�䣺         �޸����ݣ� 
//==================================================================================================
void ConnectPro(MSG msg)
{	
	u8 HAVE_CARD = 1 ,temp,card_state;
	u8 random ;
	//ˢ����ʱЧ���ж�
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch(GetCurrentState())
	{
		case FINDED_CARD://�ڿ�ʼ����ˢ��
			temp = FindCard_FormIndex();//���������ҿ�
			if(temp != 0)//temp=0,����û���ҵ����ſ�����Ҫ���������
			{						 //temp!=0,���Ƿ��ص����Ӻ���
				USER_BOX_NUM = temp;
				card_state = Compare_Card(temp);
				if(card_state == 0x01)//�����룬����ΪPassword[0,1]
				{
					ShowSys_Message(5);
					INPUT_DATA_AMOUNT = 0;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );					
					SetCurrentState(OUTPUT_CARD_KEY);//��ˢ��ȡ��ʱ���������״̬
					break;	
				}
				if(card_state == 0x02)//û�����룬ֱ�Ӵ�����
				{
					ShowSys_Message(3);
					delay_ms(5000);
					USER_CARD_ID[0] = 0;	//�������
					memset(RC531_sbuf,0,sizeof(RC531_sbuf));//��ȡ���Ŀ�������
					INPUT_DATA_AMOUNT = 0;	//�Ѿ�������ַ�������
					CLEAR_BOX();					
					SetCurrentState(SHOW_WELCOME);//����������ȴ�ˢ�����߰���
					break;						
				}
				if((card_state == 0x03)||(card_state == 0x04))//ˢ���쳣������ϵ����Ա
				{
					ShowSys_Message(6);
					delay_ms(5000);
					USER_CARD_ID[0] = 0;	//�������
					memset(RC531_sbuf,0,sizeof(RC531_sbuf));//��ȡ���Ŀ�������
					INPUT_DATA_AMOUNT = 0;	//�Ѿ�������ַ�������				
					SetCurrentState(SHOW_WELCOME);//����������ȴ�ˢ�����߰���
					break;						
				}				
			}
			while(HAVE_CARD)
			{
				random = GET_Random(); //ˢ������������һ�������
				HAVE_CARD = BOX_EMPTY(random);//����0 ��ʱ���˳�ѭ��
				if(HAVE_CARD == 0)
				{
					USER_BOX_NUM = random;//�������ֵ�����
				}
			}
			CARD_ID_INF[0] = USER_BOX_NUM;
			CARD_ID_INF[1] = RC531_sbuf[9];
			CARD_ID_INF[2] = RC531_sbuf[12];

			USER_CARD_ID[0] = USER_BOX_NUM; 
			USER_CARD_ID[1] = RC531_sbuf[9];
			USER_CARD_ID[2] = RC531_sbuf[10];
			USER_CARD_ID[3] = RC531_sbuf[11];
			USER_CARD_ID[4] = RC531_sbuf[12];
			
			ShowSys_Message(2);			
			memset(RC531_sbuf,0,sizeof(RC531_sbuf));
			INPUT_DATA_AMOUNT = 0;
			INPUT_PASS_STATE = 0 ;//���ˢ������������״̬Ϊδ�����κ��ַ�
			SetCurrentState(INPUT_CARD_KEY);//��ˢ�����ʱ���������״̬
			break;	
		
		default:
			break;
	}		
}
