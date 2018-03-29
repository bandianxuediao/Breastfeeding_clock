#include "includes.h"
#include "led.h"


//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PC�˿�ʱ��  
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOB,GPIO_Pin_8);						 //PB.5 �����

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //LED1-->PE.5 �˿�����, �������
// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_5); 						 //PE.5 ����� 
}

void LED_blink(void)
{
				GPIO_SetBits(GPIOB,GPIO_Pin_8); 						 //PC13 ����� 
			  delay_ms(100);
			  GPIO_ResetBits(GPIOB,GPIO_Pin_8); 						 //PC13 ����� 
			  delay_ms(100);
}
void LED_blink2(void)
{
				GPIO_ResetBits(GPIOB,GPIO_Pin_5); 						 //PC13 ����� 
			  delay_ms(100);
			  GPIO_SetBits(GPIOB,GPIO_Pin_5); 						 //PC13 ����� 
			  delay_ms(100);
}
