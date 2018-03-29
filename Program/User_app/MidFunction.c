#include "includes.h"

//MEASURE_STR measure_str;

//OPERATE_DATA op_data;  
//LOGGER_INFO logger_info;
//u8 temp_buffer[1056];//用于全局的中间缓冲区，非专用。
u8 INPUT_PASS_STATE ; //用于表示处在哪个密码输入状态
/*
存包刷卡还没有输入密码  0
存包刷卡第一次输入密码	1
存包刷卡第二次输入密码	2
刷卡取包输入密码				3
密码存包第一次输入密码  4
密码存包第二次输入密码  5
取包输入箱号						6
取包输入密码						7

*/

void pad_scan(void)
{
	int i;
	if((!PAD_INT1|!PAD_INT2)&(KEY_BOARD ==1))  
		{
			RC531_SWITCH = 0; //禁止寻卡
			for(i=0;i<=10;i++)
			{
				if( KeyScan() ==0 )	      //键盘扫描
				break;
			}
			RC531_SWITCH = 1; //允许寻卡
		}
}

void find_card(void)
{
		static MSG msg;	
		if(RC531_SWITCH == 1)
		{
	
			Find_Card_A();
			if(RC531_sbuf[7] != 0 | RC531_sbuf[8] != 0) 
			{
				 SetCurrentState(FINDED_CARD);//系统上电，检测充电状态
				 msg.code = CONNECT;
				 msg.param1 = FINDED_CARD;//连击产生的消息状态不改变							
				 PostMessage(msg);//产生一个消息	
			}	else{ return ;}
		}
}



u8 compare_array(u8* array1 , u8* array2)
{
	int i;
	for(i=0;;i<1)
	{
		
		if(array1[i] != array2[i])
			return 0;
		i++;
	}
	return 1;
}
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Random_Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入，用以获得随机数
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(void)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, 10, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道10,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
//通过ADC获取一个随机数
u16 GET_Random(void)
{
	u8 Random=0,temp_val=0;
	u8 t;
	for(t=0;t<8;t++)
	{
		temp_val=Get_Adc()&0x0001;
		Random = (Random<<1)+temp_val;
		delay_ms(5);
	}
	if(Random>200){ Random-=56; }
	return Random;
} 	 


//==================================================================================================
//| 函数名称 | U32DataCMP 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 比较指定缓冲区中的数据(32位数据),返回最大相差值
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | ptr:需要比较的数据缓冲区首址
//|          | length:需要比较的数据缓冲区长度
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 缓冲区中数据最大相差值
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
u32 U32DataCMP(const u32* ptr, u8 length)
{
	u32 max_value, min_value ;
	u8 i ;

	max_value = *ptr; //最大值
	min_value = *ptr; //最小值
	for(i=1;i<length;i++)
	{
		if(*(ptr+i)>max_value)
		{
			max_value = *(ptr+i) ;
		}
		else if(*(ptr+i) < min_value)
		{
			min_value = *(ptr+i) ;
		}
	}
	return (max_value - min_value);	//返回相差值
}

//==================================================================================================
//| 函数名称 | U16DataCMP 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 比较指定缓冲区中的数据(16位数据),返回最大相差值
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | ptr:需要比较的数据缓冲区首址
//|          | length:需要比较的数据缓冲区长度
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 缓冲区中数据最大相差值
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
u16 U16DataCMP(const u16* ptr, u8 length)
{
	u16 max_value, min_value ;
	u8 i ;

	max_value = *ptr; //最大值
	min_value = *ptr; //最小值
	for(i=1;i<length;i++)
	{
		if(*(ptr+i)>max_value)
		{
			max_value = *(ptr+i) ;
		}
		else if(*(ptr+i) < min_value)
		{
			min_value = *(ptr+i) ;
		}
	}
	return (max_value - min_value);	//返回相差值
}

//==================================================================================================
//| 函数名称 | GetU16DataMax 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 对一组数据(16位)求最大值
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | ptr 指针，指要求平均值的数据
//|          | lenght数据个数
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 最大值
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
u16 GetU16DataMax(const u16* ptr, u8 length)
{
	u16 max_value =0;
	u8 i ;

	max_value = *ptr; //最大值
	for(i=1;i<length;i++)
	{
		if(*(ptr+i)>max_value)
		{
			max_value = *(ptr+i) ;
		}
	}
	return max_value ;	//返回最大值
}

//==================================================================================================
//| 函数名称 | GetU16DataMin 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 对一组数据(16位)求最小值
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | ptr 指针，指要求平均值的数据
//|          | lenght数据个数
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 最小值
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
u16 GetU16DataMin(const u16* ptr, u8 length)
{
	u16 min_value = 0 ;
	u8 i ;

	min_value = *ptr; //最小值
	for(i=1;i<length;i++)
	{
		if(*(ptr+i) < min_value)
		{
			min_value = *(ptr+i) ;
		}
	}
	return min_value ;	//返回最小值
}

//==================================================================================================
//| 函数名称 | GetU16DataAverage 
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 对数据(16位)求平均值
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 | ptr 指针，指要求平均值的数据
//|          | lenght数据个数
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 | 平均值
//|----------|--------------------------------------------------------------------------------------       
//| 函数设计 | 编写人：李亚东    时间：2016-08-25 
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   | 
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
u16 GetU16DataAverage(u16* ptr, u16 lenght)
{
	u16 i;
	u32 sum = 0;
	
	for(i=0; i< lenght; i++)
	{
		sum += *ptr++;
	}
	if(lenght!=0)
	{
		sum /= lenght ;
	}

	return (u16)sum;
}



