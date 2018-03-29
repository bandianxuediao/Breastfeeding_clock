#include "stm32f10x.h"
#include "adc.h"

#define ADC1_DR_Address ((uint32_t)0x4001244c)
uint16_t adc[3];
//////////////////////////////////////////////////////////////
void ADCGPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
//////////////////////////////////////////////////////////////
void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式 每个ADC独立工作
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //使用扫描模式  scan位设置
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;// cont位设置 连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//EXTSEL 选择启动规则通道组转换的外部事件    设置成有软件控制
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //数据对齐 由软件置位和清楚   这里设置成右对齐
	//  ADC_InitStructure.ADC_NbrOfChannel = 1; //规则通道序列长度 这些位由软件定义在规则通道转换序列中的通道数目   1个转换 指定由多少个通道被转换
	ADC_InitStructure.ADC_NbrOfChannel = 3;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_41Cycles5);//转换时间是55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_41Cycles5);//转换时间是55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 3, ADC_SampleTime_41Cycles5);//转换时间是55.5个周期

	ADC_DMACmd(ADC1, ENABLE);
	//  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);  //中断使能 转换完毕后设置eoc位
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1); //初始化校准寄存器。

	while(ADC_GetResetCalibrationStatus(ADC1));//检测校准寄存器是否复位

	ADC_StartCalibration(ADC1);//开始校准   该位由软件设置以开始校准，并在校准结束时由硬件清除

	while(ADC_GetCalibrationStatus(ADC1));//检测校准状态 是否完成校准

	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //开始软件转换
}
//////////////////////////////////////////////////////////////
void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);//看数据手册 ADC是通道1
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//设置ADC1的数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adc;//是指储存器地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//数据传输方向设置
	DMA_InitStructure.DMA_BufferSize = 3;//DMA缓存大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//接收一次数据后，设备地址是否后移
	// DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;//接收一次数据后，目标内存地址是否后移--重要概念，用来采集多个数据的
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//转换结果的数据大小
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//DMA搬运的数据尺寸，注意ADC是12位的，
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//转换模式，循环缓存模式，常用，M2M果果开启了，这个模式失效
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //通道优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//M2M模式禁止
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, ENABLE);
}
//////////////////////////////////////////////////////////////
void Adc_Init(void)
{
	ADCGPIO_Configuration();
	ADC_Configuration();
	DMA_Configuration();
}
////////////////////////////////////////////////////////////
