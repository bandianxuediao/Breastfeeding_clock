#include "includes.h"

//MEASURE_STR measure_str;

//OPERATE_DATA op_data;
//LOGGER_INFO logger_info;
//u8 temp_buffer[1056];//用于全局的中间缓冲区，非专用。
u8 INPUT_PASS_STATE ; //用于表示处在哪个密码输入状态
EEP_index EepIndex;
Time_Struct TimeDiffer;
Time_Struct Temp_Time;
u32 TurnPage_Calc = 0; //翻页操作计数
//==================================================================================================
//| 函数名称 | Current_index_read
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 获取当前索引值（共存了多少个）
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-18
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
u16 Current_index_read(u16 base)
{
	switch(base)
	{
		case BASE_ADDR_LACTATION:
			EepIndex.lactation = AT24CXX_ReadLenByte(INDEX_ADDR_LACTATION, 2);
			return EepIndex.lactation;

		case BASE_ADDR_DRINK:

			EepIndex.drink = AT24CXX_ReadLenByte(INDEX_ADDR_DRINK, 2);
			return EepIndex.drink;

		case BASE_ADDR_SHIT:
			EepIndex.shit = AT24CXX_ReadLenByte(INDEX_ADDR_SHIT, 2);
			return EepIndex.shit;

		case BASE_ADDR_URINATE:
			EepIndex.urinate = AT24CXX_ReadLenByte(INDEX_ADDR_URINATE, 2);

			return EepIndex.urinate;

		default:
			break;
	}
}
//==================================================================================================
//| 函数名称 | Current_index_write
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 存储索引值，并更新显示索引
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-18
//|----------|--------------------------------------------------------------------------------------
//|   备注   |   u16 WriteAddr, u32 DataToWrite, u8 Len
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
u16 Current_index_write(u16 base, u16 num)
{
	switch(base)
	{
		case BASE_ADDR_LACTATION:
			AT24CXX_WriteLenByte(INDEX_ADDR_LACTATION, num, 2);
			EepIndex.lactation = num;
			break;

		case BASE_ADDR_DRINK:

			AT24CXX_WriteLenByte(INDEX_ADDR_DRINK, num, 2);
			EepIndex.drink = num;
			break;

		case BASE_ADDR_SHIT:
			AT24CXX_WriteLenByte(INDEX_ADDR_SHIT, num, 2);
			EepIndex.shit = num;
			break;

		case BASE_ADDR_URINATE:
			AT24CXX_WriteLenByte(INDEX_ADDR_URINATE, num, 2);
			EepIndex.urinate = num;
			break;

		default:
			break;
	}
}


//==================================================================================================
//| 函数名称 | Renovate_List
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 列表刷新
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-24
//|----------|--------------------------------------------------------------------------------------
//|   备注   |direction 0,向上   1，向下  ,2  第一页
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void Renovate_List(u16 base, u8 direction)
{
	u8 read_temp[14];
	u32 timecount = 0;

	if(TurnPage_Calc >= Current_index_read(base))
	{
		TurnPage_Calc++;
		return;
	}

	switch(base)
	{
		case BASE_ADDR_LACTATION:
			if(direction == 1)
			{
				AT24CXX_Read((TurnPage_Calc * 6 + base), read_temp, 6);
				SecTo_Time(read_temp);
				sprintf((char*)read_temp, "20%02d%02d%02d %02d:%02d", Temp_Time.year - 2000, Temp_Time.month, Temp_Time.day, Temp_Time.hour, Temp_Time.min);
				new_front_state = 0; //从半汉字开始输入

				oled_print(0, LINE1, &read_temp[0]);//字符输出

				if((TurnPage_Calc == 0) || (TurnPage_Calc >= Current_index_read(base)))
				{
					return;
				}

				AT24CXX_Read((--TurnPage_Calc * 6 + base), read_temp, 6);
				SecTo_Time(read_temp);
				sprintf((char*)read_temp, "20%02d%02d%02d %02d:%02d", Temp_Time.year - 2000, Temp_Time.month, Temp_Time.day, Temp_Time.hour, Temp_Time.min);
				new_front_state = 0; //从半汉字开始输入

				oled_print(0, LINE2, &read_temp[0]);//字符输出

				if((TurnPage_Calc == 0) || (TurnPage_Calc >= Current_index_read(base)))
				{
					return;
				}

				AT24CXX_Read((--TurnPage_Calc * 6 + base), read_temp, 6);
				SecTo_Time(read_temp);
				sprintf((char*)read_temp, "20%02d%02d%02d %02d:%02d", Temp_Time.year - 2000, Temp_Time.month, Temp_Time.day, Temp_Time.hour, Temp_Time.min);
				new_front_state = 0; //从半汉字开始输入

				oled_print(0, LINE3, &read_temp[0]);//字符输出

				if((TurnPage_Calc == 0) || (TurnPage_Calc >= Current_index_read(base)))
				{
					return;
				}
			}

			else if(direction == 0)
			{
				AT24CXX_Read((TurnPage_Calc * 6 + base), read_temp, 6);
				SecTo_Time(read_temp);
				sprintf((char*)read_temp, "20%02d%02d%02d %02d:%02d", Temp_Time.year - 2000, Temp_Time.month, Temp_Time.day, Temp_Time.hour, Temp_Time.min);
				new_front_state = 0; //从半汉字开始输入

				oled_print(0, LINE1, &read_temp[0]);//字符输出

				if((TurnPage_Calc == 0) || (TurnPage_Calc >= Current_index_read(base)))
				{
					return;
				}

				AT24CXX_Read((++TurnPage_Calc * 6 + base), read_temp, 6);
				SecTo_Time(read_temp);
				sprintf((char*)read_temp, "20%02d%02d%02d %02d:%02d", Temp_Time.year - 2000, Temp_Time.month, Temp_Time.day, Temp_Time.hour, Temp_Time.min);
				new_front_state = 0; //从半汉字开始输入

				oled_print(0, LINE2, &read_temp[0]);//字符输出

				if((TurnPage_Calc == 0) || (TurnPage_Calc >= Current_index_read(base)))
				{
					return;
				}

				AT24CXX_Read((++TurnPage_Calc * 6 + base), read_temp, 6);
				SecTo_Time(read_temp);
				sprintf((char*)read_temp, "20%02d%02d%02d %02d:%02d", Temp_Time.year - 2000, Temp_Time.month, Temp_Time.day, Temp_Time.hour, Temp_Time.min);
				new_front_state = 0; //从半汉字开始输入

				oled_print(0, LINE3, &read_temp[0]);//字符输出

				if((TurnPage_Calc == 0) || (TurnPage_Calc >= Current_index_read(base)))
				{
					return;
				}
			}

			oled_updatescr(0, 64);     //屏幕刷新
			break;

		case BASE_ADDR_DRINK:

		//AT24CXX_Read((num * 6 + base), read_temp, 6);
		//      EepIndex.drink=num;
		//          break;

		//      case BASE_ADDR_SHIT:
		//AT24CXX_Read((num * 6 + base), read_temp, 6);
		//      EepIndex.shit=num;
		//          break;

		//      case BASE_ADDR_URINATE:
		//      AT24CXX_Read((num * 6 + base), read_temp, 6);
		//EepIndex.urinate=num;
		//          break;

		default:
			break;
	}


}

//==================================================================================================
//| 函数名称 | Storage_One_Data
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 时间差计算
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-24
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void Storage_One_Data(u16 base)
{
	u16 num = 0;
	u32 timecount = 0;
	u32 timecount_crc = 0;
	u8 write_temp[10];
	u8 read_temp[10];
	num =  Current_index_read(base);//读取当前索引
	timecount = RTC_GetCounter();//获取当前秒计数
	write_temp[0] = timecount;
	write_temp[1] = timecount >> 8;
	write_temp[2] = timecount >> 16;
	write_temp[3] = timecount >> 24;


	AT24CXX_Write((num * 6 + base), write_temp, 6);
	delay_ms(50);
	AT24CXX_Read((num * 6 + base), read_temp, 6);
	timecount_crc += read_temp[0];
	timecount_crc += read_temp[1] << 8;
	timecount_crc += read_temp[2] << 16;
	timecount_crc += read_temp[3] << 24;
	SecTo_Time(read_temp);

	if(timecount_crc == timecount)//再次读出进行校验
	{
		//存储成功，刷新列表
		num++;
		Current_index_write(base, num); //更新EEPROM中的索引信息
		TurnPage_Calc = num - 1;
		TimeDiffer_Calc(base);
		//Renovate_List(base, 1);

	}
	else
	{
		//存储失败，返回列表

	}

}



//==================================================================================================
//| 函数名称 | TimeDiffer_Calc
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 时间差计算
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-18
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void TimeDiffer_Calc(u16 base)
{
	u8 read_temp[10];
	u8 display_temp[30];
	u8 month_date;
	vs32 Current_timecount = 0;
	u32 Next_timecount = 0;
	u16 num = 0;
	num = Current_index_read(base);

	if(num == 0)
	{
		sprintf((char*)display_temp, "共0条|无数据");

	}
	else
	{
		TurnPage_Calc = num - 1;
		AT24CXX_Read((TurnPage_Calc * 6 + base), read_temp, 6);

		Next_timecount += read_temp[0];
		Next_timecount += read_temp[1] << 8;
		Next_timecount += read_temp[2] << 16;
		Next_timecount += read_temp[3] << 24;
		SecTo_Time(read_temp);
		Current_timecount = RTC_GetCounter();//获取当前秒计数

		Current_timecount -= Next_timecount;

		if(Current_timecount < 0)
		{
			sprintf((char*)display_temp, "共%d条|error", num);
		}
		else
		{
			if(Current_timecount <= (10 * 24 * 60 * 60)) //暂定10天超时
			{
				sprintf((char*)display_temp, "共%d条|%d.%d小时", num, Current_timecount / 3600, Current_timecount / 360);
				//刷新列表
				Renovate_List(BASE_ADDR_LACTATION, 1);
			}
			else
			{
				sprintf((char*)display_temp, "共%d条|超时", num);
				//刷新列表
				Renovate_List(BASE_ADDR_LACTATION, 1);
			}

		}
	}

	oled_print(0, LINE0, &display_temp[0]);//字符输出
	oled_updatescr(0, 64);     //屏幕刷新
}

//==================================================================================================
//| 函数名称 | List_Display
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 列表显示
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-18
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void List_Display(void)
{
	u8 display_temp[30];


	clr_disp_mem();         //清除显存数据

	switch(Current_state)
	{
		case DISPLAY_ITEM_LACTATION://显示项目状态--默认选中哺乳
		{
			TurnPage_Calc = Current_index_read(BASE_ADDR_LACTATION); //更新当前索引
			TimeDiffer_Calc(BASE_ADDR_LACTATION);


			show_left_button("哺乳");//显示右功能
			break;
		}

		case DISPLAY_ITEM_DRINK://显示项目状态--选中补水
		{
			Current_index_read(BASE_ADDR_DRINK);//更新当前索引
			TimeDiffer_Calc(BASE_ADDR_DRINK);
			show_left_button("补水");//显示右功能
			break;
		}

		case DISPLAY_ITEM_SHIT://显示项目状态--选中大便
		{
			Current_index_read(BASE_ADDR_SHIT);//更新当前索引
			TimeDiffer_Calc( BASE_ADDR_SHIT);
			show_left_button("大便");//显示右功能
			break;
		}

		case DISPLAY_ITEM_URINATE://显示项目状态--选中小便
		{
			Current_index_read(BASE_ADDR_URINATE);//更新当前索引
			TimeDiffer_Calc(BASE_ADDR_URINATE);
			show_left_button("小便");//显示右功能
			break;
		}

		default:
			break;
	}


	show_right_button("返回");//显示右功能
	oled_updatescr(0, 64);     //屏幕刷新
}


//==================================================================================================
//| 函数名称 | Detect_Pin_State
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | 按键检测功能函数
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------
//| 返回参数 |
//|----------|--------------------------------------------------------------------------------------
//| 函数设计 | 编写人：李亚东    时间：2018-04-18
//|----------|--------------------------------------------------------------------------------------
//|   备注   |
//|----------|--------------------------------------------------------------------------------------
//| 修改记录 | 修改人：          时间：         修改内容：
//==================================================================================================
void Detect_Pin_State(void)
{
	if(KEY_UP)
	{
		delay_ms(10);

		if(KEY_UP)
		{
			KeyUp_Program();
			return;
		}
	}

	if(KEY_DOWN)
	{
		delay_ms(10);

		if(KEY_DOWN)
		{
			KeyDown_Program();
			return;
		}
	}

	if(KEY_LEFT)
	{
		delay_ms(10);

		if(KEY_LEFT)
		{
			KeyLeft_Program();
			return;
		}
	}

	if(KEY_RIGHT)
	{
		delay_ms(10);

		if(KEY_RIGHT)
		{
			KeyRight_Program();
			return;
		}
	}
}

void PIN_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE ); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
	//PA15配置为背光控制，高有效
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_15);   //PA15 输出高电平,检测红外电平

	//PA8配置为KEY_DOWN 按键检测管脚，配置高输入，检测低电平
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE ); //使能GPIOB时钟
	//PB12配置为红外检测    配置高输入，检测低电平
	//PB13配置为KEY_LEF 按键检测管脚，配置高输入，检测低电平
	//PB14配置为KEY_UP      按键检测管脚，配置高输入，检测低电平
	//PB15配置为KEY_RIGHT   按键检测管脚，配置高输入，检测低电平
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PB 0,1,3,4用于12864的控制引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PA0-7配置为ST7920数据线
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

//u8 compare_array(u8* array1, u8* array2)
//{
//  int i;

//  for(i = 0;; i < 1)
//  {

//      if(array1[i] != array2[i])
//          return 0;

//      i++;
//  }

//  return 1;
//}




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

	for(i = 1; i < length; i++)
	{
		if(*(ptr + i) > max_value)
		{
			max_value = *(ptr + i) ;
		}
		else if(*(ptr + i) < min_value)
		{
			min_value = *(ptr + i) ;
		}
	}

	return (max_value - min_value); //返回相差值
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

	for(i = 1; i < length; i++)
	{
		if(*(ptr + i) > max_value)
		{
			max_value = *(ptr + i) ;
		}
		else if(*(ptr + i) < min_value)
		{
			min_value = *(ptr + i) ;
		}
	}

	return (max_value - min_value); //返回相差值
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
	u16 max_value = 0;
	u8 i ;

	max_value = *ptr; //最大值

	for(i = 1; i < length; i++)
	{
		if(*(ptr + i) > max_value)
		{
			max_value = *(ptr + i) ;
		}
	}

	return max_value ;  //返回最大值
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

	for(i = 1; i < length; i++)
	{
		if(*(ptr + i) < min_value)
		{
			min_value = *(ptr + i) ;
		}
	}

	return min_value ;  //返回最小值
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

	for(i = 0; i < lenght; i++)
	{
		sum += *ptr++;
	}

	if(lenght != 0)
	{
		sum /= lenght ;
	}

	return (u16)sum;
}



