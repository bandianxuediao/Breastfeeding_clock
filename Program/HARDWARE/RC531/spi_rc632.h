#ifndef __SPI_RC632_H
#define __SPI_RC632_H

#include "sys.h"

#define        RC531_IRQ   (GPIO_Pin_1)                          //PA1

 
 				  	    													  
void SPIx_Init(void);			 //��ʼ��SPI��
void SPIx_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8   SPIx_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

