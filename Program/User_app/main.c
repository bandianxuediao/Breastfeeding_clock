
#include "includes.h"
SYS_STATE Current_state;
SYS_STATE KEY_state;
int main(void)
{
	//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //�������ļ����Ӧ  ���ó������ʼ��ַ��ǰ��һ����������bootload
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	SysTickInit();         //���õδ�ʱ���ж�ʱ��Ϊ1ms
	//  delay_init();            //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//EE_IIC_Init();             //EEPROM��IIC��ʼ��


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);        //ʹ����spi3������JATG������SWD����

	PIN_Init();
	  lcd12864_init();//12864��ʼ��
	          ShowWelcome();
	delay_ms(6000);
	Current_state = WELCOME_WAIT;
  
	while(1)
	{
		KEY_state=Detect_Pin_State();
		//  oled_updatescr(0, 64);     //��Ļˢ��
if(KEY_state)
{
	//��⵽����֮��Ӧ�õ�����Ļ����������װ����Ļ����رռ�����
		switch(KEY_state)
		{
			case KEY_UP:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;
				}

				break;
			}


			case KEY_DOWN:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;

				}

				break;
			}


			case KEY_SET:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;

				}

				break;
			}


			case KEY_BACK:
			{
				switch(Current_state)
				{
					case WELCOME_WAIT:
						break;

					default:
						break;

				}

				break;
			}

			default:
				break;

		}
	}
	else
	{delay_ms(10);}

		//      if(max_waite==10000)
		//      {   lcdreset();                    //��ʼ��LCD��
		//              clrgdram();
		//              max_waite=0;
		//      }

	}
}

/************* The End ! *****************/