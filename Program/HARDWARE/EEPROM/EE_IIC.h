#ifndef __EE_IIC_H
#define __EE_IIC_H

//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//IO��������

#define EE_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=(u32)8<<12;}
#define EE_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=(u32)3<<12;}

//IO��������
#define EE_IIC_SCL    PBout(10) //SCL
#define EE_IIC_SDA    PBout(11) //SDA    
#define EE_READ_SDA   PBin(11)  //����SDA 

//IIC���в�������
void EE_IIC_Init(void);                //��ʼ��IIC��IO��
void EE_IIC_Start(void);                //����IIC��ʼ�ź�
void EE_IIC_Stop(void);             //����IICֹͣ�ź�
void EE_IIC_Send_Byte(u8 txd);          //IIC����һ���ֽ�
u8 EE_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 EE_IIC_Wait_Ack(void);               //IIC�ȴ�ACK�ź�
void EE_IIC_Ack(void);                  //IIC����ACK�ź�
void EE_IIC_NAck(void);             //IIC������ACK�ź�

void EE_IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 EE_IIC_Read_One_Byte(u8 daddr, u8 addr);
#endif
















