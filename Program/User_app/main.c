
#include "includes.h"

int main(void)
{
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //�������ļ����Ӧ  ���ó������ʼ��ַ��ǰ��һ����������bootload
	while(1)
	{		
		MsgSched(PeekMessage());
	}
}

/************* The End ! *****************/