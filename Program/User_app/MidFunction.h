#ifndef _MIDFUNCTION_H_
#define _MIDFUNCTION_H_

#define PIN10  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//
#define PIN11  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//
#define PIN12  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//
#define PIN13  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//
#define PIN14  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//
#define PIN15  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//


extern u8 INPUT_PASS_STATE ; //用于表示处在哪个密码输入状态
extern SYS_STATE Detect_Pin_State(void);


extern void PIN_Init(void);
extern void pad_scan(void);
extern void find_card(void);
extern u8 compare_array(u8* array1, u8* array2);
extern void  Random_Adc_Init(void);
extern u16 GET_Random(void);



extern u32 U32DataCMP(const u32* ptr, u8 length);
extern u16 U16DataCMP(const u16* ptr, u8 length);
extern u16 GetU16DataMax(const u16* ptr, u8 length);
extern u16 GetU16DataMin(const u16* ptr, u8 length);
extern u16 GetU16DataAverage(u16* ptr, u16 lenght);
//extern void U16DataFallRank(u16* ptr_s, u16* ptr_d, u16 lenght);
//extern void RemoveCharFromString(u8*ptr, u8 char_val, u16 len);
//extern u8 HexCharToValue(u8 c);
//extern void HexStrToCharStr(u8* ptr_in, u16 in_len, u8* ptr_out);

#endif
