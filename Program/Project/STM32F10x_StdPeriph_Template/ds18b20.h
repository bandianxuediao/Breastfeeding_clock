#ifndef _DS18B20_H_
#define _DS18B20_H_


#define skipRom 0xcc
#define convert 0x44
#define readTemp 0xbe

void Init_ds18b20(void);
void STM_Ds18b20_Init(void); //≥ı ºªØdq
float readtemperature(void);
#endif




