
#include "includes.h"

int main(void)
{
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //�������ļ����Ӧ  ���ó������ʼ��ַ��ǰ��һ����������bootload
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	SysTickInit();         //���õδ�ʱ���ж�ʱ��Ϊ1ms
//	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//EE_IIC_Init();			 //EEPROM��IIC��ʼ��


	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//ʹ����spi3������JATG������SWD����
 
	PIN_Init();
	lcd12864_init();//12864��ʼ��
 EXTIX_Init();  
			ShowWelcome();
			delay_ms(6000);
	
	while(1)
	{		
	oled_updatescr(0, 64);	   //��Ļˢ��	
//	if(KEY1==0)	 //����KEY1
//	{				 
//PBout(9)=1;
//	}
	if(KEY1==1)	 //����KEY1
	{				 
		PBout(9)=0;
	}

//		if(max_waite==10000)
//		{   lcdreset();                    //��ʼ��LCD��
//				clrgdram();
//				max_waite=0;
//		}
	
	}
}

/************* The End ! *****************/