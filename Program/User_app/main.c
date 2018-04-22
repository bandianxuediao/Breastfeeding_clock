
#include "includes.h"
SYS_STATE Current_state;
SYS_STATE KEY_state;
int main(void)
{

	//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //�������ļ����Ӧ  ���ó������ʼ��ַ��ǰ��һ����������bootload
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	SysTickInit();         //���õδ�ʱ���ж�ʱ��Ϊ1ms
	//  delay_init();            //��ʱ������ʼ��

	EE_IIC_Init();             //EEPROM��IIC��ʼ��


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);        //ʹ����spi3������JATG������SWD����

	PIN_Init();

	lcd12864_init();//12864��ʼ��
	RTC_Init();
	ShowWelcome();
	delay_ms(600);
	Current_state = WELCOME_WAIT;
	//  Back_Light(0);

	oled_updatescr(0, 64);//��Ļˢ��

	while(1)
	{
		Detect_Pin_State();

		//      if(max_waite==10000)
		//      {   lcdreset();                    //��ʼ��LCD��
		//              clrgdram();
		//              max_waite=0;
		//      }

		//oled_updatescr(0, 64);       //��Ļˢ��
	}
}

/************* The End ! *****************/