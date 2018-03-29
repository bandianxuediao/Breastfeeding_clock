#ifndef __PAD_H
#define __PAD_H
#include "includes.h"   


#define KEY_AREA1		1
#define KEY_AREA2		2


extern u8 INPUT_DATA_NUM[10] ;
extern u8 INPUT_DATA_AMOUNT;
extern const u8 PAD_1[2]  ;
extern const u8 PAD_2[2]  ;
extern const u8 PAD_3[2]  ;
extern const u8 PAD_4[2]  ;
extern const u8 PAD_5[2]  ;
extern const u8 PAD_6[2]  ;
extern const u8 PAD_7[2]  ;
extern const u8 PAD_IN[2] ;
extern const u8 PAD_OUT[2];

extern const u8 PAD_8[2]		;
extern const u8 PAD_9[2] 	;
extern const u8 PAD_0[2] 	;
extern const u8 PAD_SYS[2] ;
extern const u8 PAD_KEY[2] ;
extern const u8 PAD_SURE[2];
extern const u8 PAD_BACK[2];

extern u8 scan_key(u8 num);

#endif
















