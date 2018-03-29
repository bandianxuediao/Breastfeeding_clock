#include "includes.h"

//==================================================================================================
//| 函数名称 | KeyRightPro 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 右功能键消息响应函数
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | msg 待处理消息
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 无
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
void KeySurePro(MSG msg)
{
	u8 pas1,pas2,temp_state;
	u8 TEMP_BOXNUM ;
	//按键消息的时效性判断
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
				case 1: //存包刷卡第一次输入密码	1
					SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					SetCurrentState(INPUT_CARD_KEY_AGAIN);	//设置成再次输入密码状态
					break;
				case 2: //存包刷卡第二次输入密码	2
					SURE_SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					if(SURE_SURE_BOXKEY == SURE_BOXKEY)
					{
						ShowSys_Message(3);
						USER_CARD_ID[5] =  SURE_SURE_BOXKEY / 100;
						USER_CARD_ID[6] =  SURE_SURE_BOXKEY % 100;
						USER_CARD_ID[7] = 0x11;//设置密码标志位
						delay_ms(2000);
						SAVE_INFORMATION_CARD();
						delay_ms(1000);
						SURE_SURE_BOXKEY = 0;
						SURE_BOXKEY = SURE_SURE_BOXKEY;
						memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
						memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));												
						SetCurrentState(SHOW_WELCOME);	//返回主界面
					break;
					}	
					if(SURE_SURE_BOXKEY != SURE_BOXKEY)
					{
						ShowSys_Message(4);
						delay_ms(2000);
						ShowSys_Message(2);			
						memset(RC531_sbuf,0,sizeof(RC531_sbuf));
						INPUT_DATA_AMOUNT = 0;
						INPUT_PASS_STATE = 0 ;//存包刷卡，输入密码状态为未输入任何字符						
						SetCurrentState(INPUT_CARD_KEY);//在刷卡存包时输入密码的状态
					break;
					}
				case 3://刷卡取包输入密码				3
					pas1 = (int)(INPUT_DATA_NUM[0]-48)*10+(int)(INPUT_DATA_NUM[1]-48);
					pas2 = (int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0;
					memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
					memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));																
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );					

					if((Password[0] == pas1)&(Password[1] == pas2))//如果密码正确
					{
						ShowSys_Message(3);
						delay_ms(2000);
						CLEAR_BOX();
						SetCurrentState(SHOW_WELCOME);	//返回主界面
						break;				
					}
					else
					{
						ShowSys_Message(4);
						delay_ms(2000);
						ShowSys_Message(5);
//						SetCurrentState(SHOW_WELCOME);//返回主界面
						break;	
					}
					break;
				case 4://密码存包第一次输入密码  4
					SURE_BOXKEY=(int)(INPUT_DATA_NUM[0]-48)*1000+(int)(INPUT_DATA_NUM[1]-48)*100+(int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					SetCurrentState(PASSW_INPUT_KEY_AGAIN);	//设置成再次输入密码状态
					break;
				case 5://密码存包第二次输入密码  5
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
						SetCurrentState(SHOW_WELCOME);	//返回主界面
					break;
					}	
					if(SURE_SURE_BOXKEY != SURE_BOXKEY)
					{
						ShowSys_Message(4);
						delay_ms(2000);
//						ShowSys_Message(7);			
						memset(RC531_sbuf,0,sizeof(RC531_sbuf));
						INPUT_DATA_AMOUNT = 0;
						INPUT_PASS_STATE = 0 ;//密码存包，输入密码状态为未输入任何字符						
						SetCurrentState(SHOW_WELCOME);//返回主界面
					break;
					}
					//箱号为3位
				case 6://取包输入箱号	6
					TEMP_BOXNUM=(int)(INPUT_DATA_NUM[0]-48)*100+(int)(INPUT_DATA_NUM[1]-48)*10+(int)(INPUT_DATA_NUM[2]-48);
					INPUT_DATA_AMOUNT = 0 ;
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );
					if((TEMP_BOXNUM>0)&(TEMP_BOXNUM<200))
					{
						temp_state = FindBox_FromIndex(TEMP_BOXNUM);
						if(temp_state == 0)//箱号与存储的不同，请联系管理员
						{
							ShowSys_Message(9);
							delay_ms(3000);
							SetCurrentState(SHOW_WELCOME);	//返回主界面
							break;
						}
						if(temp_state == 1)//存在卡号，是刷卡存包的箱子
						{
							ShowSys_Message(10);  //需要刷卡开箱，请刷卡
							delay_ms(3000); 
							SetCurrentState(SHOW_WELCOME);	//返回主界面
							break;
						}
						if(temp_state == 2)//箱号正确，不存在密码，密码已存储到全局变量Password[0、1]
						{
							USER_BOX_NUM = TEMP_BOXNUM;
							ShowSys_Message(11);  //箱号正确，需要输入密码							
							SetCurrentState(OUT_INPUT_PASSW);	//取，输入密码状态
							break;
						}
						if(temp_state == 3)//此箱为空
						{
							ShowSys_Message(12);  //此箱为空	
							delay_ms(3000); 							
							SetCurrentState(SHOW_WELCOME);	//返回主界面
							break;
						}						
					break;
					}	
					if(TEMP_BOXNUM > 200)
					{
						ShowSys_Message(13);//箱号不存在
						delay_ms(3000);
						SetCurrentState(SHOW_WELCOME);//返回主界面
					break;
					}
				case 7://密码取包输入密码				7
					pas1 = (int)(INPUT_DATA_NUM[0]-48)*10+(int)(INPUT_DATA_NUM[1]-48);
					pas2 = (int)(INPUT_DATA_NUM[2]-48)*10+(int)(INPUT_DATA_NUM[3]-48);
					INPUT_DATA_AMOUNT = 0;
					memset(CARD_ID_INF,0,sizeof(CARD_ID_INF));
					memset(USER_CARD_ID,0,sizeof(USER_CARD_ID));																
					memset( INPUT_DATA_NUM, '\0', sizeof(INPUT_DATA_NUM) );									
					if((Password[0] == pas1)&(Password[1] == pas2))//如果密码正确
					{
						ShowSys_Message(3);
						delay_ms(2000);
						CLEAR_BOX();
						SetCurrentState(SHOW_WELCOME);	//返回主界面
						break;				
					}
					else
					{
						ShowSys_Message(4);
						delay_ms(2000);
						ShowSys_Message(11);
//						SetCurrentState(SHOW_WELCOME);//返回主界面
						break;	
					}
					break;


					
				default:					
					break;				
			}
			break;
		//箱号小于3位
		case OUT_INPUT_BOXNUM://取包输入箱号	6
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
				if(temp_state == 0)//箱号与存储的不同，请联系管理员
				{
					ShowSys_Message(9);
					delay_ms(3000);
					SetCurrentState(SHOW_WELCOME);	//返回主界面
					break;
				}
				if(temp_state == 1)//存在卡号，是刷卡存包的箱子
				{
					ShowSys_Message(10);  //需要刷卡开箱，请刷卡
					delay_ms(3000); 
					SetCurrentState(SHOW_WELCOME);	//返回主界面
					break;
				}
				if(temp_state == 2)//箱号正确，不存在密码，密码已存储到全局变量Password[0、1]
				{
					USER_BOX_NUM = TEMP_BOXNUM;
					ShowSys_Message(11);  //箱号正确，需要输入密码							
					SetCurrentState(OUT_INPUT_PASSW);	//取，输入密码状态
					break;
				}
				if(temp_state == 3)//此箱为空
				{
					ShowSys_Message(12);  //此箱为空	
					delay_ms(3000); 							
					SetCurrentState(SHOW_WELCOME);	//返回主界面
					break;
				}						
			break;
			}	
			if(TEMP_BOXNUM > 200)
			{
				ShowSys_Message(13);//箱号不存在
				delay_ms(3000);
				SetCurrentState(SHOW_WELCOME);//返回主界面
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
/*减去四十八，是因为输入读取的是字符，对应的十六进制需要减去48才是十进制的数字*/
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
