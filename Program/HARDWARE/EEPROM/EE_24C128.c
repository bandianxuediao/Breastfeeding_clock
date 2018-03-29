#include "includes.h" 
u8 Password[2];
u8 USER_BOX_NUM ;
u8 IF_PASSWORD ;
u8 USER_CARD_ID[8];//存储数据区的所有信息box_num,ID,C1,C2,IF_PASSWORD.
u8 CARD_ID_INF[5];//存储在索引区的box_num和ID[9],ID[12]
//初始化IIC接口
void AT24CXX_Init(void)
{
	EE_IIC_Init();
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    EE_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		EE_IIC_Send_Byte(0XA0);	   //发送写命令
		EE_IIC_Wait_Ack();
		EE_IIC_Send_Byte(ReadAddr/256);//发送高地址
		EE_IIC_Wait_Ack();		 
	}else EE_IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

//	IIC_Wait_Ack(); 
  EE_IIC_Send_Byte(ReadAddr%256);   //发送低地址
	EE_IIC_Wait_Ack();	    
	EE_IIC_Start();  	 	   
	EE_IIC_Send_Byte(0XA1);           //进入接收模式			   
	EE_IIC_Wait_Ack();	 
    temp=EE_IIC_Read_Byte(0);		   
    EE_IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    EE_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		EE_IIC_Send_Byte(0XA0);	    //发送写命令
		EE_IIC_Wait_Ack();
		EE_IIC_Send_Byte(WriteAddr>>8);//发送高地址
 	}else
	{
		EE_IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	EE_IIC_Wait_Ack();	   
    EE_IIC_Send_Byte(WriteAddr%256);   //发送低地址
	EE_IIC_Wait_Ack(); 	 										  		   
	EE_IIC_Send_Byte(DataToWrite);     //发送字节							   
	EE_IIC_Wait_Ack();  		    	   
    EE_IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在数据索引区查找卡号(100-2100字节)
//索引里面存入的是两字节卡号[9][12]
//如果找到了就返回箱子号
//如果没找到就返回0
/*	注：不需要清除卡号缓存 RC531_sbuf	*/
u8 FindCard_FormIndex(void)
{
	u8 i;
	u8 pBuffer[2];
	for(i=0;i<200;i++)
	{
		AT24CXX_Read(i*10+101,pBuffer,2);
		if((pBuffer[0] == RC531_sbuf[9])&&(pBuffer[1] == RC531_sbuf[12]))
		{return AT24CXX_ReadOneByte(i*10+100);}	//找到相应的卡号，返回箱号
	}
	return 0;  	//索引区已经读完，没找到卡号
}
//在数据索引区查找箱号


u8 FindBox_FromIndex(u8 temp)
{
	u8 pBuffer[5];	
	AT24CXX_Read((temp-1)*10+100,pBuffer,5);
	if((pBuffer[0] !=0)&(pBuffer[0] !=0xff))
	{
		if(pBuffer[0] == temp)//箱号相等
		{
			if((pBuffer[1] == 0)|(pBuffer[1] == 0xFF))//卡号部分为空,继续进行
			{
				Password[0] = pBuffer[3];
				Password[1] = pBuffer[4];
				return 2;//箱号相等，不存在卡号，返回密码
			}
			return 1;//存在卡号，是刷卡存包的
		}
		return 0;//箱号不相等
	}
	return 3;//此箱号为空
}



//在数据区查找卡号(100-2100字节)
//索引里面存入的是四字节卡号[9][10][11][12]
//如果匹配卡号成功且密码标志位为0x11（有密码）保存密码并返回0x01，没有密码则返回0x02
//ID错误返回3
//箱号错误返回 4
u8 Compare_Card(u8 box_num)
{
	u8 pBuffer[8];
	AT24CXX_Read((box_num-1)*10+2500,pBuffer, 8);
	if(pBuffer[0] == box_num)
	{
		if((pBuffer[1] == RC531_sbuf[9])&&(pBuffer[2] == RC531_sbuf[10])&&(pBuffer[3] == RC531_sbuf[11])&&(pBuffer[4] == RC531_sbuf[12]))
		{
			if(pBuffer[7] == 0x11) //有密码
			{
				Password[0] = pBuffer[5];
				Password[1] = pBuffer[6];
				return 0x01;
			}
			if(pBuffer[7] != 0x11) //没有密码
			{
				Password[0] = 0;
				Password[1] = 0;
				return 0x02;
			}
		}
		return 3; // ID校验失败		
	}
	return 4; 	//箱号校验失败	
}

//刷卡操作
//将卡的信息存入索引，以及数据存储区
//用到的数据包括：CARD_ID , USER_BOX_NUM  , IF_PASSWORD ， PASSWORD
//传过来的数据是 ：USER_BOX_NUM , IF_PASSWORD，其他参数使用全局变量
//数据存储完毕将 CARD_ID , USER_BOX_NUM , IF_PASSWORD , PASSWORD 清零
void SAVE_INFORMATION_CARD(void)
{
	if(INPUT_PASS_STATE == 2)
	{
		AT24CXX_Write(((USER_BOX_NUM-1)*10+100),CARD_ID_INF,5);//在索引区写入箱号和CARD_ID
		AT24CXX_Write(((USER_BOX_NUM-1)*10+2500),USER_CARD_ID,8);//在数据区写入箱号和CARD_ID，密码
	}
	if(INPUT_PASS_STATE == 5)
	{
		AT24CXX_Write(((USER_BOX_NUM-1)*10+100),CARD_ID_INF,5);//在索引区写入箱号和CARD_ID
//		AT24CXX_Write(((USER_BOX_NUM-1)*10+2500),USER_CARD_ID,8);//在数据区写入箱号和CARD_ID，密码
	}
}

//已经取包，将数据区清除，写入0xFF
void CLEAR_BOX(void)
{
	if(INPUT_PASS_STATE == 2)
	{
		AT24CXX_WriteLenByte(((USER_BOX_NUM-1)*10+100),0xFF,10);
		AT24CXX_WriteLenByte(((USER_BOX_NUM-1)*10+2500),0xFF,10);
		USER_BOX_NUM = 0;
	}
	if(INPUT_PASS_STATE == 5)
	{
		AT24CXX_WriteLenByte(((USER_BOX_NUM-1)*10+100),0xFF,10);
		USER_BOX_NUM = 0;		
	}		
}

//根据产生的随机数（BOX_NUM）来判断相应的索引区以及数据区是否有数据
u8 BOX_EMPTY(u8 random)
{
	u8 temp;
	temp = AT24CXX_ReadOneByte((random-1)*10+100);
	if((temp != 0xFF)&(temp != 0)){ return 1;} //返回1，循环继续，寻找下一个随机数
	temp = AT24CXX_ReadOneByte((random-1)*10+2500);
	if((temp != 0xFF)&(temp != 0)){ return 1;} //返回1，循环继续，寻找下一个随机数
	return 0 ;
}
//清空EEPROM，全写0xFF
void CLEAR_EEPROM(void)
{
	int i;
	for(i=0;i<=17;i++)
	{
		AT24CXX_WriteLenByte(100+i*255,0xFF,0xFF);
	}
}
//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(16383);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(16383,0x55);
	    temp=AT24CXX_ReadOneByte(16383);	  
		if(temp==0x55)return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}