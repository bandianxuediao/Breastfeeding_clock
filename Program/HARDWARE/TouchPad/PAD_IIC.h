#ifndef __PAD_IIC_H
#define __PAD_IIC_H
#include "includes.h"

//IO方向设置
 
#define PAD_SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define PAD_SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
#define PAD_INT1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//读取按键TOUCH1
#define PAD_INT2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)//读取按键TOUCH2

//IO操作函数	 
#define PAD_IIC_SCL    PBout(6) //SCL
#define PAD_IIC_SDA    PBout(7) //SDA	 
#define PAD_READ_SDA   PBin(7)  //输入SDA 

//IIC所有操作函数
void PAD_IIC_Init(void);                //初始化IIC的IO口				 
void PAD_IIC_Start(void);				//发送IIC开始信号
void PAD_IIC_Stop(void);	  			//发送IIC停止信号
void PAD_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 PAD_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 PAD_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void PAD_IIC_Ack(void);					//IIC发送ACK信号
void PAD_IIC_NAck(void);				//IIC不发送ACK信号
void PAD_IIC_Key_Send_Byte(u8 txd);

#endif
















