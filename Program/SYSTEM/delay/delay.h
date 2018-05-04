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

} DELAY_DATA;

extern void SysTickInit(void);
extern void SysTickDelay(u32 DelayTime);
extern void SetLightTimer(u32 DelayTime);
extern DELAY_STATE GetLightTimerState(void);


extern void TimingDelayDecrement(void);
extern void delay_us(u32 dlynum);
extern void delay_ms(u32 DelayTime);

#endif
