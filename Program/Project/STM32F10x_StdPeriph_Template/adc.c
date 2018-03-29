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
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ ÿ��ADC��������
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //ʹ��ɨ��ģʽ  scanλ����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;// contλ���� ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//EXTSEL ѡ����������ͨ����ת�����ⲿ�¼�    ���ó����������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //���ݶ��� �������λ�����   �������ó��Ҷ���
	//  ADC_InitStructure.ADC_NbrOfChannel = 1; //����ͨ�����г��� ��Щλ����������ڹ���ͨ��ת�������е�ͨ����Ŀ   1��ת�� ָ���ɶ��ٸ�ͨ����ת��
	ADC_InitStructure.ADC_NbrOfChannel = 3;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_41Cycles5);//ת��ʱ����55.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_41Cycles5);//ת��ʱ����55.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 3, ADC_SampleTime_41Cycles5);//ת��ʱ����55.5������

	ADC_DMACmd(ADC1, ENABLE);
	//  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);  //�ж�ʹ�� ת����Ϻ�����eocλ
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1); //��ʼ��У׼�Ĵ�����

	while(ADC_GetResetCalibrationStatus(ADC1));//���У׼�Ĵ����Ƿ�λ

	ADC_StartCalibration(ADC1);//��ʼУ׼   ��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����

	while(ADC_GetCalibrationStatus(ADC1));//���У׼״̬ �Ƿ����У׼

	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //��ʼ���ת��
}
//////////////////////////////////////////////////////////////
void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);//�������ֲ� ADC��ͨ��1
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//����ADC1�����ݼĴ�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adc;//��ָ��������ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//���ݴ��䷽������
	DMA_InitStructure.DMA_BufferSize = 3;//DMA�����С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//����һ�����ݺ��豸��ַ�Ƿ����
	// DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;//����һ�����ݺ�Ŀ���ڴ��ַ�Ƿ����--��Ҫ��������ɼ�������ݵ�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//ת����������ݴ�С
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//DMA���˵����ݳߴ磬ע��ADC��12λ�ģ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ת��ģʽ��ѭ������ģʽ�����ã�M2M���������ˣ����ģʽʧЧ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //ͨ�����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//M2Mģʽ��ֹ
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
