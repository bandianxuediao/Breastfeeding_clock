#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_

/*按键代码*/
#define KEY0_CODE       	0x10	//对应原理图里的B5
#define KEY1_CODE       	0x01	//对应原理图里的B13
#define KEY2_CODE       	0x02	//对应原理图里的B8
#define KEY3_CODE       	0x03	//对应原理图里的B12
#define KEY4_CODE       	0x04	//对应原理图里的B11
#define KEY5_CODE       	0x05	//对应原理图里的7
#define KEY6_CODE       	0x06	//对应原理图里的B3
#define KEY7_CODE       	0x07	//对应原理图里的B10
#define KEY8_CODE       	0x08	//对应原理图里的B6
#define KEY9_CODE       	0x09  //对应原理图里的B2
#define KEY_IN_CODE       0x0A  //对应原理图里的B9
#define KEY_OUT_CODE      0x0B  //对应原理图里的B4
#define KEY_SYS_CODE      0x0C	//对应原理图里的B1
#define KEY_KEY_CODE     	0x0D	//对应原理图里的B14
#define KEY_BACK_CODE     0x0E	//对应原理图里的B14
#define KEY_SURE_CODE     0x0F	//对应原理图里的B14




/*按键状态*/
#define KEY_DOWN    0
#define KEY_UP      1

extern u8 KeyScan(void);

#endif
