#ifndef _MIDFUNCTION_H_
#define _MIDFUNCTION_H_


#define KEY_DOWN    (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))?0:1 //

#define INFRARED    (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))?0:1 //
#define KEY_LEFT    (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13))?0:1 //
#define KEY_UP          (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14))?0:1 //
#define KEY_RIGHT   (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))?0:1 //

#define Back_Light(x) x?(GPIO_SetBits(GPIOA, GPIO_Pin_15)):(GPIO_ResetBits(GPIOA, GPIO_Pin_15))
typedef struct
{
	u16 lactation;
	u16 drink;
	u16 shit;
	u16 urinate;

} EEP_index;
extern EEP_index EepIndex;
typedef struct
{
	vs16 min;
	vs8 hour;
	vs8 day;
	vs8 month;
	vs8 year;
} Time_Differ;
extern Time_Differ TimeDiffer;

#define INITIAL_ADDR    5   //在第五字节位置存放是否第一次使用的标志
#define BASE_ADDR_LACTATION     100//显示项目状态--默认选中哺乳
#define BASE_ADDR_DRINK     300//显示项目状态--选中补水
#define BASE_ADDR_SHIT      500//显示项目状态--选中大便
#define BASE_ADDR_URINATE       700//显示项目状态--选中小便 



//#define Back_Light_1  GPIO_SetBits(GPIOA, GPIO_Pin_15)
//#define   Back_Light_0    GPIO_ResetBits(GPIOA, GPIO_Pin_15)

//#define Back_Light(x) x?Back_Light_1:Back_Light_0

extern SYS_STATE Current_state;
extern SYS_STATE KEY_state;
extern void PIN_Init(void);
extern void pad_scan(void);
//extern void find_card(void);
//extern u8 compare_array(u8* array1, u8* array2);
void TimeDiffer_Calc(u16 num, u16 base);
void List_Display(void);

extern u16 Current_index_read(u16 base);

extern void  Random_Adc_Init(void);
extern u16 GET_Random(void);
extern void Detect_Pin_State(void);


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
