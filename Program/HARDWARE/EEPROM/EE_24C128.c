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
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    EE_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		EE_IIC_Send_Byte(0XA0);	   //����д����
		EE_IIC_Wait_Ack();
		EE_IIC_Send_Byte(ReadAddr/256);//���͸ߵ�ַ
		EE_IIC_Wait_Ack();		 
	}else EE_IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

//	IIC_Wait_Ack(); 
  EE_IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	EE_IIC_Wait_Ack();	    
	EE_IIC_Start();  	 	   
	EE_IIC_Send_Byte(0XA1);           //�������ģʽ			   
	EE_IIC_Wait_Ack();	 
    temp=EE_IIC_Read_Byte(0);		   
    EE_IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    EE_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		EE_IIC_Send_Byte(0XA0);	    //����д����
		EE_IIC_Wait_Ack();
		EE_IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		EE_IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	EE_IIC_Wait_Ack();	   
    EE_IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
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
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//���������������ҿ���(100-2100�ֽ�)
//�����������������ֽڿ���[9][12]
//����ҵ��˾ͷ������Ӻ�
//���û�ҵ��ͷ���0
/*	ע������Ҫ������Ż��� RC531_sbuf	*/
u8 FindCard_FormIndex(void)
{
	u8 i;
	u8 pBuffer[2];
	for(i=0;i<200;i++)
	{
		AT24CXX_Read(i*10+101,pBuffer,2);
		if((pBuffer[0] == RC531_sbuf[9])&&(pBuffer[1] == RC531_sbuf[12]))
		{return AT24CXX_ReadOneByte(i*10+100);}	//�ҵ���Ӧ�Ŀ��ţ��������
	}
	return 0;  	//�������Ѿ����꣬û�ҵ�����
}
//�������������������


u8 FindBox_FromIndex(u8 temp)
{
	u8 pBuffer[5];	
	AT24CXX_Read((temp-1)*10+100,pBuffer,5);
	if((pBuffer[0] !=0)&(pBuffer[0] !=0xff))
	{
		if(pBuffer[0] == temp)//������
		{
			if((pBuffer[1] == 0)|(pBuffer[1] == 0xFF))//���Ų���Ϊ��,��������
			{
				Password[0] = pBuffer[3];
				Password[1] = pBuffer[4];
				return 2;//�����ȣ������ڿ��ţ���������
			}
			return 1;//���ڿ��ţ���ˢ�������
		}
		return 0;//��Ų����
	}
	return 3;//�����Ϊ��
}



//�����������ҿ���(100-2100�ֽ�)
//�����������������ֽڿ���[9][10][11][12]
//���ƥ�俨�ųɹ��������־λΪ0x11�������룩�������벢����0x01��û�������򷵻�0x02
//ID���󷵻�3
//��Ŵ��󷵻� 4
u8 Compare_Card(u8 box_num)
{
	u8 pBuffer[8];
	AT24CXX_Read((box_num-1)*10+2500,pBuffer, 8);
	if(pBuffer[0] == box_num)
	{
		if((pBuffer[1] == RC531_sbuf[9])&&(pBuffer[2] == RC531_sbuf[10])&&(pBuffer[3] == RC531_sbuf[11])&&(pBuffer[4] == RC531_sbuf[12]))
		{
			if(pBuffer[7] == 0x11) //������
			{
				Password[0] = pBuffer[5];
				Password[1] = pBuffer[6];
				return 0x01;
			}
			if(pBuffer[7] != 0x11) //û������
			{
				Password[0] = 0;
				Password[1] = 0;
				return 0x02;
			}
		}
		return 3; // IDУ��ʧ��		
	}
	return 4; 	//���У��ʧ��	
}

//ˢ������
//��������Ϣ�����������Լ����ݴ洢��
//�õ������ݰ�����CARD_ID , USER_BOX_NUM  , IF_PASSWORD �� PASSWORD
//�������������� ��USER_BOX_NUM , IF_PASSWORD����������ʹ��ȫ�ֱ���
//���ݴ洢��Ͻ� CARD_ID , USER_BOX_NUM , IF_PASSWORD , PASSWORD ����
void SAVE_INFORMATION_CARD(void)
{
	if(INPUT_PASS_STATE == 2)
	{
		AT24CXX_Write(((USER_BOX_NUM-1)*10+100),CARD_ID_INF,5);//��������д����ź�CARD_ID
		AT24CXX_Write(((USER_BOX_NUM-1)*10+2500),USER_CARD_ID,8);//��������д����ź�CARD_ID������
	}
	if(INPUT_PASS_STATE == 5)
	{
		AT24CXX_Write(((USER_BOX_NUM-1)*10+100),CARD_ID_INF,5);//��������д����ź�CARD_ID
//		AT24CXX_Write(((USER_BOX_NUM-1)*10+2500),USER_CARD_ID,8);//��������д����ź�CARD_ID������
	}
}

//�Ѿ�ȡ�����������������д��0xFF
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

//���ݲ������������BOX_NUM�����ж���Ӧ���������Լ��������Ƿ�������
u8 BOX_EMPTY(u8 random)
{
	u8 temp;
	temp = AT24CXX_ReadOneByte((random-1)*10+100);
	if((temp != 0xFF)&(temp != 0)){ return 1;} //����1��ѭ��������Ѱ����һ�������
	temp = AT24CXX_ReadOneByte((random-1)*10+2500);
	if((temp != 0xFF)&(temp != 0)){ return 1;} //����1��ѭ��������Ѱ����һ�������
	return 0 ;
}
//���EEPROM��ȫд0xFF
void CLEAR_EEPROM(void)
{
	int i;
	for(i=0;i<=17;i++)
	{
		AT24CXX_WriteLenByte(100+i*255,0xFF,0xFF);
	}
}
//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
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
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(16383);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(16383,0x55);
	    temp=AT24CXX_ReadOneByte(16383);	  
		if(temp==0x55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}