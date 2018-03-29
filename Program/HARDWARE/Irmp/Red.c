
#include "includes.h"


IRMP_DATA irmp_data;
uint32_t SysCtlClockGet(void)
{
    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    return RCC_ClocksStatus.SYSCLK_Frequency;
}

void timer2_init (void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 7;
    TIM_TimeBaseStructure.TIM_Prescaler = ((F_CPU / F_INTERRUPTS)/8) - 1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

 
 void irmp_get_key(void)
 {	 
//    for (;;)
//    {
        if (irmp_get_data (&irmp_data))
        {					
//          printf("R: Code: %s",irmp_protocol_names[irmp_data.protocol]);          
          printf(" Address: 0x%.2X",irmp_data.address);
          printf(" Command: 0x%.2X",irmp_data.command);
          printf(" Flags: 0x%.2X\r\n",irmp_data.flags );										
        }
//    } 	
	}		
