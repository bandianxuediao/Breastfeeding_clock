#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//W25Q64 ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	  
//W25Xϵ��/Qϵ��оƬ�б�	   
//W25Q80  ID  0XEF13
//W25Q16  ID  0XEF14
//W25Q32  ID  0XEF15
//W25Q64  ID  0XEF16	
//W25Q128 ID  0XEF17	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17

extern u16 W25QXX_TYPE;					//����W25QXXоƬ�ͺ�		   
extern u8  W25Q_ADD_ID[];
extern u32 FLASH_SIZE;
extern int BOX_SEAT;

#define	W25QXX_CS 		PBout(12)  		//W25QXX��Ƭѡ�ź�
#define	BOX_TOTAL_NUM		300

typedef struct
{
	u8	BOX_NUM;
	u8	CARD_NUM[8];
	u8	BOX_KEY[3];
	u8	BOX_STATE;//0x01���棬0x02�ܴ棬0x11��
}BOX_INFO;




////////////////////////////////////////////////////////////////////////////
 
//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

extern void W25QXX_Init(void);
extern u16  W25QXX_ReadID(void);  	    		//��ȡFLASH ID
extern u8	 W25QXX_ReadSR(void);        		//��ȡ״̬�Ĵ��� 
extern void W25QXX_Write_SR(u8 sr);  			//д״̬�Ĵ���
extern void W25QXX_Write_Enable(void);  		//дʹ�� 
extern void W25QXX_Write_Disable(void);		//д����
extern void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
extern void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
extern void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
extern void W25QXX_Erase_Chip(void);    	  	//��Ƭ����
extern void W25QXX_Erase_Sector(u32 Dst_Addr);	//��������
extern void W25QXX_Wait_Busy(void);           	//�ȴ�����
extern void W25QXX_PowerDown(void);        	//�������ģʽ
extern void W25QXX_WAKEUP(void);				//����
extern void Write_ID_W25Q(u8 addr , u8*ID_BUFF ); //ADDRռ��1���ֽ����255
extern u8 Find_ID_W25Q(u8 *ID_BUFF);




#endif
















