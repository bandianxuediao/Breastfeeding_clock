#ifndef _SYSTEM_CONFIG_H_
#define _SYSTEM_CONFIG_H_



/*≤‚ ‘”√µƒLED*/
#define LED1_PORT              GPIOE
#define LED1_PORT_RCC          RCC_AHB1Periph_GPIOE
#define LED1_PIN               GPIO_Pin_1

#define LED2_PORT              GPIOE
#define LED2_PORT_RCC          RCC_AHB1Periph_GPIOE
#define LED2_PIN               GPIO_Pin_0

#define LED1_TURN_ON()         GPIO_WriteBit(LED1_PORT, LED1_PIN, Bit_RESET)
#define LED1_TURN_OFF()        GPIO_WriteBit(LED1_PORT, LED1_PIN, Bit_SET)
#define LED2_TURN_ON()         GPIO_WriteBit(LED2_PORT, LED2_PIN, Bit_RESET)
#define LED2_TURN_OFF()        GPIO_WriteBit(LED2_PORT, LED2_PIN, Bit_SET)


extern char RC531_SWITCH ;
extern char KEY_BOARD ;
extern u16 SURE_BOXNUM ;
extern u32 SURE_BOXKEY ;
extern u32 SURE_SURE_BOXKEY ;


extern void BufferInit(void);
extern void SystemHWConfig(void);
extern u8 DeviceInit(void);

#endif
