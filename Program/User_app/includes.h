#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "core_cm3.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"
#include "system.h"

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "rtc.h"

#include "KeyScan.h"
#include "ST7920.h"
#include "oled.h"
#include "display.h"
#include "EE_IIC.h"
#include "EE_24C128.h"
#include "MidFunction.h"

#define ID_LENGTH = 15
#define FIRST_ADDR 0       //定义字符/汉字显示起始位置

#endif
