
#include "includes.h"

int main(void)
{

//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //�������ļ����Ӧ  ���ó������ʼ��ַ��ǰ��һ����������bootload
	SysTickInit();         //���õδ�ʱ���ж�ʱ��Ϊ1ms
//	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration();  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	//EE_IIC_Init();			 //EEPROM��IIC��ʼ��
	//Random_Adc_Init(); //ͨ��ADC���һ�������

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//ʹ����spi3������JATG������SWD����
	


	
		lcd12864_init();//12864��ʼ��

			ShowWelcome();
			delay_ms(200);	
	while(1)
	{		
	oled_updatescr(0, 64);	   //��Ļˢ��	
delay_ms(6000);
PBout(9)=0;
delay_ms(6000);
PBout(9)=1;
//		if(max_waite==10000)
//		{   lcdreset();                    //��ʼ��LCD��
//				clrgdram();
//				max_waite=0;
//		}
	}
}

/************* The End ! *****************/