#ifndef __SPI_RC632_H
#define __SPI_RC632_H

#include "sys.h"

#define        RC531_IRQ   (GPIO_Pin_1)                          //PA1

 
 				  	    													  
void SPIx_Init(void);			 //初始化SPI口
void SPIx_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8   SPIx_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

