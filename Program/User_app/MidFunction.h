#ifndef _MIDFUNCTION_H_
#define _MIDFUNCTION_H_

extern u8 INPUT_PASS_STATE ; //用于表示处在哪个密码输入状态




extern void pad_scan(void);
extern void find_card(void);
extern u8 compare_array(u8* array1 , u8* array2);
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
