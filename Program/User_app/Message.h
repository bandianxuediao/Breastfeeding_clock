#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include "stm32f10x.h"

#define MSG_QUEUE_SIZE   32 // �¼���ջ��С������С�ڵ���255�ұ�����2�������η�

typedef enum
{
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_IN,
	KEY_OUT,
	KEY_SYS,
	KEY_KEY,
	KEY_BACK,
	KEY_SURE,
	CONNECT,
	NULL_CODE
}MSG_CODE;
#define MSG_SIZE  17   //��Ϣ����

typedef struct
{
	MSG_CODE code;	//��Ϣ����
	u32 param1; //��Ϣ�ĸ��Ӳ���1
	u32 param2; //��Ϣ�ĸ��Ӳ���2
}MSG;

typedef struct
{
	MSG msg[MSG_QUEUE_SIZE];//ϵͳ��Ϣ����
	u8 start ;
	u8 end  ;
}MSG_QUEUE;

extern u8 PostMessage(MSG msg);
extern MSG PeekMessage(void);
extern void RemoveAllMessage(void);

#endif
