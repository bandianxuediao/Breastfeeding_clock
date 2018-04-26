#include "includes.h"
u8 Password[2];
u8 USER_BOX_NUM ;
u8 IF_PASSWORD ;
u8 USER_CARD_ID[8];//�洢��������������Ϣbox_num,ID,C1,C2,IF_PASSWORD.
u8 CARD_ID_INF[5];//�洢����������box_num��ID[9],ID[12]
//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	EE_IIC_Init();
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ
//����ֵ  :����������
u8 AT24CXX_ReadOneByte(u32 ReadAddr)
{
	u8 temp = 0;
	u8 AddrP0 = 0;
	AddrP0 = ReadAddr >> 16;
	EE_IIC_Start();

	if(AddrP0 == 0)
	{
		EE_IIC_Send_Byte(0XA0);    //����д����
	}
	else
	{
		EE_IIC_Send_Byte(0XA0 | 0x02); //����д���� ��P0λ
	}

	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte((ReadAddr >> 8) & 0xff); //���͸ߵ�ַ
	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte(ReadAddr & 0xff); //���͵͵�ַ
	EE_IIC_Wait_Ack();
	EE_IIC_Start();
	EE_IIC_Send_Byte(0XA1);           //�������ģʽ
	EE_IIC_Wait_Ack();
	temp = EE_IIC_Read_Byte(0);
	EE_IIC_Stop();//����һ��ֹͣ����
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(u32 WriteAddr, u8 DataToWrite)
{
	u8 AddrP0 = 0;
	AddrP0 = WriteAddr >> 16;
	EE_IIC_Start();

	if(AddrP0 == 0)
	{
		EE_IIC_Send_Byte(0XA0);    //����д����
	}
	else
	{
		EE_IIC_Send_Byte(0XA0 | 0x02); //����д���� ��P0λ
	}

	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte((WriteAddr >> 8) & 0xff); //���͸ߵ�ַ
	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte(WriteAddr & 0xff); //���͵͵�ַ
	EE_IIC_Wait_Ack();
	EE_IIC_Send_Byte(DataToWrite);     //�����ֽ�
	EE_IIC_Wait_Ack();
	EE_IIC_Stop();//����һ��ֹͣ����
	delay_ms(10);
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(u32 WriteAddr, u32 DataToWrite, u8 Len)
{
	u8 t;

	for(t = 0; t < Len; t++)
	{
		AT24CXX_WriteOneByte(WriteAddr + t, (DataToWrite >> (8 * t)) & 0xff);
	}
}

//���ݲ������������BOX_NUM�����ж���Ӧ���������Լ��������Ƿ�������
u8 BOX_EMPTY(u8 random)
{
	u8 temp;
	temp = AT24CXX_ReadOneByte((random - 1) * 10 + 100);

	if((temp != 0xFF) & (temp != 0))
	{
		return 1;   //����1��ѭ��������Ѱ����һ�������
	}

	temp = AT24CXX_ReadOneByte((random - 1) * 10 + 2500);

	if((temp != 0xFF) & (temp != 0))
	{
		return 1;   //����1��ѭ��������Ѱ����һ�������
	}

	return 0 ;
}
//���EEPROM��ȫд0xFF
void CLEAR_EEPROM(void)
{
	int i;

	for(i = 0; i <= 17; i++)
	{
		AT24CXX_WriteLenByte(100 + i * 255, 0xFF, 0xFF);
	}
}
//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
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
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp = AT24CXX_ReadOneByte(16383); //����ÿ�ο�����дAT24CXX

	if(temp == 0X55)return 0;
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(16383, 0x55);
		temp = AT24CXX_ReadOneByte(16383);

		if(temp == 0x55)return 0;
	}

	return 1;
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u32 ReadAddr, u8 *pBuffer, u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u32 WriteAddr, u8 *pBuffer, u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr, *pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}


