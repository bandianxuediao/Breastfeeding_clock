#include "includes.h" 
u8 INPUT_DATA_NUM[10] ;
u8 INPUT_DATA_AMOUNT = 0;
 
const u8 PAD_1[2]   = {0xfd,0xff};
const u8 PAD_2[2]   = {0xfb,0xff};
const u8 PAD_3[2]   = {0xf7,0xff};
const u8 PAD_4[2]   = {0xff,0xdf};
const u8 PAD_5[2]   = {0xff,0xbf};
const u8 PAD_6[2]   = {0xff,0x7f};
const u8 PAD_7[2]   = {0xff,0xef};
const u8 PAD_IN[2]  = {0xef,0xff};
const u8 PAD_OUT[2] = {0xfe,0xff};

const u8 PAD_8[2]		 = {0xfb,0xff};
const u8 PAD_9[2] 	 = {0xf7,0xff};
const u8 PAD_0[2] 	 = {0xff,0x7f};
const u8 PAD_SYS[2]  = {0xef,0xff};
const u8 PAD_KEY[2]  = {0xfd,0xff};
const u8 PAD_SURE[2] = {0xfe,0xff};
const u8 PAD_BACK[2] = {0xff,0xbf};

u8 scan_key(u8 num)
{
//	u8 aa;
	u8 temp1[2];
	PAD_IIC_Start(); 
	PAD_IIC_Key_Send_Byte(0x81);	   //地址：悬空0x81-129		低0x85-133		高0x89-137
  PAD_IIC_Ack();//发送nACK	
	temp1[0]=PAD_IIC_Read_Byte(0);
	temp1[1]=PAD_IIC_Read_Byte(0);
  PAD_IIC_NAck();//发送nACK
  PAD_IIC_Stop();//产生一个停止条件	
	if(num == KEY_AREA1)
	{
		if((PAD_1[0] == temp1[0])&&(PAD_1[1] == temp1[1])){return KEY_1;}
		if((PAD_2[0] == temp1[0])&&(PAD_2[1] == temp1[1])){return KEY_2;}
		if((PAD_3[0] == temp1[0])&&(PAD_3[1] == temp1[1])){return KEY_3;}
		if((PAD_4[0] == temp1[0])&&(PAD_4[1] == temp1[1])){return KEY_4;}
		if((PAD_5[0] == temp1[0])&&(PAD_5[1] == temp1[1])){return KEY_5;}
		if((PAD_6[0] == temp1[0])&&(PAD_6[1] == temp1[1])){return KEY_6;}
		if((PAD_7[0] == temp1[0])&&(PAD_7[1] == temp1[1])){return KEY_7;}
		if((PAD_IN[0] == temp1[0])&&(PAD_IN[1] == temp1[1])){return KEY_IN;}
		if((PAD_OUT[0] == temp1[0])&&(PAD_OUT[1] == temp1[1])){return KEY_OUT;}		
	}
	if(num == KEY_AREA2)
	{
		if((PAD_8[0] ==temp1[0])&&(PAD_8[1] == temp1[1])){return KEY_8;}
		if((PAD_9[0] ==temp1[0])&&(PAD_9[1] == temp1[1])){return KEY_9;}
		if((PAD_0[0] ==temp1[0])&&(PAD_0[1] == temp1[1])){return 0x10;}
		if((PAD_SYS[0] ==temp1[0])&&(PAD_SYS[1] == temp1[1])){return KEY_SYS;}
		if((PAD_KEY[0] ==temp1[0])&&(PAD_KEY[1] == temp1[1])){return KEY_KEY;}
		if((PAD_SURE[0] ==temp1[0])&&(PAD_SURE[1] == temp1[1])){return KEY_SURE;}
		if((PAD_BACK[0] ==temp1[0])&&(PAD_BACK[1] == temp1[1])){return KEY_BACK;}
	}
	return 0x11;
//	printf("%x %x\r\n",temp1[0],temp1[1]);	
}







