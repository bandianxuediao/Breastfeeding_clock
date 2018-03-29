#ifndef _INCLUDES_H_
#define _INCLUDES_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "core_cm3.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_adc.h"

#include "system.h"
#include "Message.h"
#include "MsgSched.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "NullProcess.h"
#include "Red.h"
#include "irmp.h"
#include "irmpconfig.h"
#include "irmpprotocols.h"
#include "SystemConfig.h"
#include "KeyScan.h"
#include "ST7920.h"
#include "oled.h"
#include "display.h"
#include "spi_rc632.h"
//#include "iso14443b.h" 
#include "rc632.h"
#include "iso14443a.h"
#include "spi2.h"
#include "w25qxx.h"
#include "PAD_IIC.h"
#include "pad.h"
#include "EE_IIC.h"
#include "EE_24C128.h"
#include "MidFunction.h"
//#include "adc.h"
#include "Key0Process.h"
#include "Key1Process.h"
#include "Key2Process.h"
#include "Key3Process.h"
#include "Key4Process.h"
#include "Key5Process.h"
#include "Key6Process.h"
#include "Key7Process.h"
#include "Key8Process.h"
#include "Key9Process.h"
#include "KeyBackProcess.h"
#include "KeySureProcess.h"
#include "KeyInProcess.h"
#include "KeyOutProcess.h"
#include "KeySysProcess.h"
#include "KeyKeyProcess.h"
#include "ConnectProcess.h"
//#include "stm32f4xx_conf.h"
//#include "irmpsystem.h"
//#include "core_cm3.h"
//#include "system_stm32f10x.h"


#define ID_LENGTH = 15
#define FIRST_ADDR 0       //定义字符/汉字显示起始位置
//#define W25Q_SIZE sizeof(RC531_sbuf)
#define W25Q_SIZE 8
 


#endif
