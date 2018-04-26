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
u8 AT24CXX_ReadOneByte(u32 ReadAddr)
{
	u8 temp = 0;
	u8 AddrP0 = 0;
	AddrP0 = ReadAddr >> 16;
	EE_IIC_Start();

	if(AddrP0 == 0)
	{
		EE_IIC_Send_Byte(0XA0);    //发送写命令
	}
	else
	{
		EE_IIC_Send_Byte(0XA0 | 0x02); //发送写命令 和P0位
	}

	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte((ReadAddr >> 8) & 0xff); //发送高地址
	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte(ReadAddr & 0xff); //发送低地址
	EE_IIC_Wait_Ack();
	EE_IIC_Start();
	EE_IIC_Send_Byte(0XA1);           //进入接收模式
	EE_IIC_Wait_Ack();
	temp = EE_IIC_Read_Byte(0);
	EE_IIC_Stop();//产生一个停止条件
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u32 WriteAddr, u8 DataToWrite)
{
	u8 AddrP0 = 0;
	AddrP0 = WriteAddr >> 16;
	EE_IIC_Start();

	if(AddrP0 == 0)
	{
		EE_IIC_Send_Byte(0XA0);    //发送写命令
	}
	else
	{
		EE_IIC_Send_Byte(0XA0 | 0x02); //发送写命令 和P0位
	}

	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte((WriteAddr >> 8) & 0xff); //发送高地址
	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte(WriteAddr & 0xff); //发送低地址
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
void AT24CXX_WriteLenByte(u32 WriteAddr, u32 DataToWrite, u8 Len)
{
	u8 t;

	for(t = 0; t < Len; t++)
	{
		AT24CXX_WriteOneByte(WriteAddr + t, (DataToWrite >> (8 * t)) & 0xff);
	}
}

//根据产生的随机数（BOX_NUM）来判断相应的索引区以及数据区是否有数据
u8 BOX_EMPTY(u8 random)
{
	u8 temp;
	temp = AT24CXX_ReadOneByte((random - 1) * 10 + 100);

	if((temp != 0xFF) & (temp != 0))
	{
		return 1;   //返回1，循环继续，寻找下一个随机数
	}

	temp = AT24CXX_ReadOneByte((random - 1) * 10 + 2500);

	if((temp != 0xFF) & (temp != 0))
	{
		return 1;   //返回1，循环继续，寻找下一个随机数
	}

	return 0 ;
}
//清空EEPROM，全写0xFF
void CLEAR_EEPROM(void)
{
	int i;

	for(i = 0; i <= 17; i++)
	{
		AT24CXX_WriteLenByte(100 + i * 255, 0xFF, 0xFF);
	}
}
//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 AT24CXX_ReadLenByte(u32 ReadAddr, u8 Len)
{
	u8 t;
	u32 temp = 0;

	for(t = 0; t < Len; t++)
	{
		temp <<= 8;
		temp += AT24CXX_ReadOneByte(ReadAddr + Len - t - 1);
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
	temp = AT24CXX_ReadOneByte(16383); //避免每次开机都写AT24CXX

	if(temp == 0X55)return 0;
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(16383, 0x55);
		temp = AT24CXX_ReadOneByte(16383);

		if(temp == 0x55)return 0;
	}

	return 1;
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(u32 ReadAddr, u8 *pBuffer, u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u32 WriteAddr, u8 *pBuffer, u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr, *pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}


