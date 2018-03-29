#include "includes.h"

//==================================================================================================
//| 函数名称 | ConnectPro 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 通信连接消息响应函数
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | msg 待处理消息
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东   时间：2016-07-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
void ConnectPro(MSG msg)
{	
	u8 HAVE_CARD = 1 ,temp,card_state;
	u8 random ;
	//刷卡的时效性判断
	if((SYS_STATE)msg.param1 != GetCurrentState())
	{
		return ;
	}
	switch(GetCurrentState())
	{
		case FINDED_CARD://在开始界面刷卡
			temp = FindCard_FormIndex();//在索引区找卡
			if(temp != 0)//temp=0,就是没有找到这张卡，需要做存包操作
			{						 //temp!=0,就是返回的箱子号码
				USER_BOX_NUM = temp;
				card_state = Compare_Card(temp);
				if(card_state == 0x01)//有密码，密码为Password[0,1]
				{
					ShowSys_Message(5);
					INPUT_DATA_AMOUNT = 0;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );					
					SetCurrentState(OUTPUT_CARD_KEY);//在刷卡取包时输入密码的状态
					break;	
				}
				if(card_state == 0x02)//没有密码，直接打开箱子
				{
					ShowSys_Message(3);
					delay_ms(5000);
					USER_CARD_ID[0] = 0;	//箱号置零
					memset(RC531_sbuf,0,sizeof(RC531_sbuf));//读取到的卡号置零
					INPUT_DATA_AMOUNT = 0;	//已经输入的字符数置零
					CLEAR_BOX();					
					SetCurrentState(SHOW_WELCOME);//返回主界面等待刷卡或者按键
					break;						
				}
				if((card_state == 0x03)||(card_state == 0x04))//刷卡异常，请联系管理员
				{
					ShowSys_Message(6);
					delay_ms(5000);
					USER_CARD_ID[0] = 0;	//箱号置零
					memset(RC531_sbuf,0,sizeof(RC531_sbuf));//读取到的卡号置零
					INPUT_DATA_AMOUNT = 0;	//已经输入的字符数置零				
					SetCurrentState(SHOW_WELCOME);//返回主界面等待刷卡或者按键
					break;						
				}				
			}
			while(HAVE_CARD)
			{
				random = GET_Random(); //刷卡后立即产生一个随机数
				HAVE_CARD = BOX_EMPTY(random);//等于0 的时候退出循环
				if(HAVE_CARD == 0)
				{
					USER_BOX_NUM = random;//随机数赋值给箱号
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
			INPUT_PASS_STATE = 0 ;//存包刷卡，输入密码状态为未输入任何字符
			SetCurrentState(INPUT_CARD_KEY);//在刷卡存包时输入密码的状态
			break;	
		
		default:
			break;
	}		
}
