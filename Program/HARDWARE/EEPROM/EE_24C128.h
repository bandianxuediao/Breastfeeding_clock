#ifndef __EE_24CXX_H
#define __EE_24CXX_H

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//24CXX驱动 代码(适合24C01~24C16,24C32~256未经过测试!有待验证!)
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#define AT24C01     127
#define AT24C02     255
#define AT24C04     511
#define AT24C08     1023
#define AT24C16     2047
#define AT24C32     4095
#define AT24C64     8191
#define AT24C128    16383
#define AT24C256    32767
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C128

extern  u8 Password[2] ;
extern  u8 USER_BOX_NUM ;
extern  u8 IF_PASSWORD ;
extern  u8 CARD_ID_INF[5];
extern  u8 USER_CARD_ID[8];//存储数据区的所有信息box_num,ID,C1,C2,IF_PASSWORD.
extern  void CLEAR_EEPROM(void);//清空存储区域数据
extern  void CLEAR_BOX(void);//清空该箱子的存储区、索引区


extern  u8 FindCard_FormIndex(void);
extern u8 FindBox_FromIndex(u8 temp);
extern  u8 Compare_Card(u8 box_num);
extern  void SAVE_INFORMATION_CARD(void);
extern  u8 BOX_EMPTY(u8 random);


u8 AT24CXX_ReadOneByte(u32 ReadAddr);                           //指定地址读取一个字节
void AT24CXX_WriteOneByte(u32 WriteAddr, u8 DataToWrite);       //指定地址写入一个字节
void AT24CXX_WriteLenByte(u32 WriteAddr, u32 DataToWrite, u8 Len); //指定地址开始写入指定长度的数据
u32 AT24CXX_ReadLenByte(u32 ReadAddr, u8 Len);                  //指定地址开始读取指定长度数据
void AT24CXX_Write(u32 WriteAddr, u8 *pBuffer, u16 NumToWrite); //从指定地址开始写入指定长度的数据
void AT24CXX_Read(u32 ReadAddr, u8 *pBuffer, u16 NumToRead);    //从指定地址开始读出指定长度的数据

u8 AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC
#endif
















