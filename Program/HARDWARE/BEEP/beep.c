#include "beep.h"
//#include "12864.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//��������������
//12864 ��������
//////////////////////////////////////////////////////////////////////////////////

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��
//��������ʼ��
void BEEP_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //ʹ��GPIOB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              //BEEP-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);  //���ݲ�����ʼ��GPIOB.8

	GPIO_ResetBits(GPIOC, GPIO_Pin_12); //���0���رշ��������


	// GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);   //ʹ��GPIOB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //BEEP-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //���ݲ�����ʼ��GPIOB.8

	GPIO_ResetBits(GPIOE, GPIO_Pin_10); //���0���رշ��������

}
