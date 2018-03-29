
#include "includes.h"

int main(void)
{
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000); //与配置文件相对应  配置程序的起始地址，前面一部分留给了bootload
	while(1)
	{		
		MsgSched(PeekMessage());
	}
}

/************* The End ! *****************/