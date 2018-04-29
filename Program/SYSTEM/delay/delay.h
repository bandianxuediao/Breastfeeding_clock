#ifndef _DELAY_H_
#define _DELAY_H_

typedef enum
{
	RUNNING,
	TIME_OUT
} DELAY_STATE;

typedef struct
{
	u32 delay0_cnt;
	u32 delay1_cnt;
	u32 delay2_cnt;
	u32 delay3_cnt;
	u32 delay4_cnt;	
} DELAY_DATA;

extern void SysTickInit(void);
extern void SysTickDelay(u32 DelayTime);
extern void SetLactationTimer(u32 DelayTime);
extern DELAY_STATE GetLactationTimerState(void);
extern void SetDrinkTimer(u32 DelayTime);
extern DELAY_STATE GetDrinkTimerState(void);
extern void SetShitTimer(u32 DelayTime);
extern DELAY_STATE GetShitTimerState(void);
extern void SetUrinateTimer(u32 DelayTime);
extern DELAY_STATE GetUrinateTimerState(void);

extern void TimingDelayDecrement(void);
extern void delay_us(u32 dlynum);
extern void delay_ms(u32 DelayTime);

#endif
