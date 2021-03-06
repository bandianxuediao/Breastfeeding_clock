#ifndef _MIDFUNCTION_H_
#define _MIDFUNCTION_H_


#define KEY_DOWN    (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))?0:1 //

#define INFRARED    (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))?0:1 //
#define KEY_LEFT    (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13))?0:1 //
#define KEY_UP      (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14))?0:1 //
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
	vu8 min;
	vu8 hour;
	vu8 day;
	vu8 month;
	vu16 year;
} Time_Struct;
extern Time_Struct TimeDiffer;
extern Time_Struct Temp_Time;
#define INITIAL_ADDR    5   //在第五字节位置存放是否第一次使用的标志

#define INDEX_ADDR_LACTATION     10//显示项目状态--默认选中哺乳
#define INDEX_ADDR_DRINK     20//显示项目状态--选中补水
#define INDEX_ADDR_SHIT      30//显示项目状态--选中大便
#define INDEX_ADDR_URINATE       40//显示项目状态--选中小便 

#define BASE_ADDR_LACTATION     100//显示项目状态--默认选中哺乳
#define BASE_ADDR_DRINK     30100//显示项目状态--选中补水
#define BASE_ADDR_SHIT      60100//显示项目状态--选中大便
#define BASE_ADDR_URINATE       90100//显示项目状态--选中小便 

//#define Back_Light_1  GPIO_SetBits(GPIOA, GPIO_Pin_15)
//#define   Back_Light_0    GPIO_ResetBits(GPIOA, GPIO_Pin_15)
//#define Back_Light(x) x?Back_Light_1:Back_Light_0


extern SYS_STATE Current_state;
extern SYS_STATE KEY_state;
extern u32 TurnPage_Calc; //翻页操作计数
extern u32 Diff_timecount;
extern u16 Total_List;
extern u8 Draw_Line;
void Modify_time(u8 state);
void Renovate_List(u32 base, u8 direction);
extern void Storage_One_Data(u32 base);
extern void PIN_Init(void);
extern void pad_scan(void);
//extern void find_card(void);
//extern u8 compare_array(u8* array1, u8* array2);
void TimeDiffer_Calc(u32 base);
void List_Display(void);

extern u16 Current_index_read(u32 base);

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
