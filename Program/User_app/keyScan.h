#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_

/*��������*/
#define KEY0_CODE       	0x10	//��Ӧԭ��ͼ���B5
#define KEY1_CODE       	0x01	//��Ӧԭ��ͼ���B13
#define KEY2_CODE       	0x02	//��Ӧԭ��ͼ���B8
#define KEY3_CODE       	0x03	//��Ӧԭ��ͼ���B12
#define KEY4_CODE       	0x04	//��Ӧԭ��ͼ���B11
#define KEY5_CODE       	0x05	//��Ӧԭ��ͼ���7
#define KEY6_CODE       	0x06	//��Ӧԭ��ͼ���B3
#define KEY7_CODE       	0x07	//��Ӧԭ��ͼ���B10
#define KEY8_CODE       	0x08	//��Ӧԭ��ͼ���B6
#define KEY9_CODE       	0x09  //��Ӧԭ��ͼ���B2
#define KEY_IN_CODE       0x0A  //��Ӧԭ��ͼ���B9
#define KEY_OUT_CODE      0x0B  //��Ӧԭ��ͼ���B4
#define KEY_SYS_CODE      0x0C	//��Ӧԭ��ͼ���B1
#define KEY_KEY_CODE     	0x0D	//��Ӧԭ��ͼ���B14
#define KEY_BACK_CODE     0x0E	//��Ӧԭ��ͼ���B14
#define KEY_SURE_CODE     0x0F	//��Ӧԭ��ͼ���B14




/*����״̬*/
#define KEY_DOWN    0
#define KEY_UP      1

extern u8 KeyScan(void);

#endif
