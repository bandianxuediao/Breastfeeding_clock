#include "includes.h"

char RC531_SWITCH = 0 ;
char KEY_BOARD = 0 ;
u16 SURE_BOXNUM ;
u32 SURE_BOXKEY ;
u32	SURE_SURE_BOXKEY ;
//unsigned char RC531_sbuf[50];


void SystemHWConfig(void)
{	
	BufferInit();                 //���������ݳ�ʼ��
	SysTickInit();         //���õδ�ʱ���ж�ʱ��Ϊ1ms
//	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration();  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//uart_init(9600);	 	 //���ڳ�ʼ��Ϊ9600
	//PAD_IIC_Init();			 //IIC��ʼ�� 
	//EE_IIC_Init();			 //EEPROM��IIC��ʼ��
	//Random_Adc_Init(); //ͨ��ADC���һ�������

  //irmp_init();         // initialize irmp
  //timer2_init();       // initialize timer2

	//DeviceInit();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//ʹ����spi3������JATG������SWD����
		lcd12864_init();//12864��ʼ��
	
	
}

u8 DeviceInit(void)
{
		LED_Init();
//		delay_init();
		lcd12864_init();//12864��ʼ��
		//rc_init();		
		//PCD_reset();
	  delay_ms(200);    
	  //PCD_cfg_iso_type('A');
	  delay_ms(5);
//		W25QXX_Init();			//W25QXX��ʼ��
		
	
		return 0;
}

void BufferInit(void)
{	
	
	RemoveAllMessage();
	RemoveBackupState();
}






