#include "includes.h"
 unsigned char iso14443a_cardtype[2];
 unsigned char iso14443a_cardsnr[4];
 unsigned char uart_indx, recv_flag;
 unsigned char RC531_sbuf[50];
 unsigned char RC531_rbuf[50];

 typedef enum{
   Card_Null,
   Card_AutoType,
   Card_ScanTag,
   Card_ScanCard,
   Card_InitOver,
   Card_ReadOver,
   Card_Recharge,
   Card_Buckle,
   Card_ReadData,
   Card_WriteData,
}Card_Oper;
 Card_Oper CARD_OPER = Card_AutoType,CARD_FLAG = Card_Null;



////读取IRQ的状态！！！！
//unsigned char Read_RC531_IRQ(void){
//        return GPIO_ReadInputDataBit(GPIOA,RC531_IRQ);
//}




void Find_Card_A(void)
{
		unsigned char  sta;
		unsigned char  buf[70];
	
		    // 自动寻卡，有新命令则停止寻卡操作
        // 协议为ISO14443A，执行一次读卡类型和读卡号操作			
				if(CARD_OPER != Card_Null && recv_flag == 0)
				{                       
						CARD_FLAG = CARD_OPER;
						sta = MI_OK;
						PCD_AntennaOFF();
						delay_ms(3);
						PCD_cfg_iso_type('A');
						delay_ms(3);
						sta = PCD_request(0x52, iso14443a_cardtype);
								
                        
						if (MI_OK == sta) 
						{
								sta = PCD_anticoll(iso14443a_cardsnr);

								if(sta == MI_OK)
								{
										printf(" 1.CardType ");	
										if(CARD_OPER == Card_AutoType) //协议为ISO14443A
										{
												CARD_OPER = Card_AutoType;
												memcpy(&buf[0], iso14443a_cardtype, 2);
												memcpy(&buf[2], iso14443a_cardsnr, 4);
												PDA_package(0x00, PDA_COMT_AUTO, 'a', 0x00, 6, buf, RC531_sbuf);
												RC531_SWITCH = 1;    //当前卡信息处理完之前不再寻卡
												PCD_AntennaOFF();
//												printf("\r\nSN = %02X %02X %02X %02X %02X %02X %02X %02X\r\n",RC531_sbuf[7],RC531_sbuf[8],RC531_sbuf[9],RC531_sbuf[10],RC531_sbuf[11],RC531_sbuf[12],RC531_sbuf[13],RC531_sbuf[14]);
												delay_ms(2);
										}																												 
								}
						}
					}
}

unsigned short crc16_tab[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
	0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
	0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
	0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
	0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
	0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
	0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
	0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
	0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
	0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
	0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
	0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
	0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
	0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};


unsigned short crc16_table(unsigned char *pcrc, unsigned short cnt)
{
	unsigned short crc16 = 0;
	unsigned char crc_reg;
	for ( ; cnt>0; cnt--) 
	{
		crc_reg = (unsigned char) (crc16>>8);
		crc16 <<= 8;
		crc16 ^= crc16_tab[crc_reg ^ *pcrc];
		pcrc++;
	}
	
	return crc16;
}


void PDA_package(unsigned char num, unsigned char com_type,
		 unsigned char com, unsigned char ack,
		 unsigned char len, unsigned char *dat, unsigned char *buf)
{
	unsigned int crc;

	buf[PACK_HEAD] = PDA_HEAD;
	buf[PACK_LENG] = len + 7;
	buf[PACK_NUMB]  = num;
	buf[PACK_COMT] = com_type;
	buf[PACK_COMM] = com;
	buf[PACK_ACKN]  = ack;
	buf[PACK_DALE] = len;
	
	if (len != 0)
		memcpy(&buf[7], dat, len);
	
	crc = crc16_table(buf, buf[PACK_LENG]);
	buf[buf[PACK_LENG]]   = crc>>8 & 0xFF;
	buf[buf[PACK_LENG]+1] = crc & 0xFF;
}












struct trans_buff{unsigned char mf_comm;
                              unsigned int  mf_leng;
                              unsigned char mf_data[64];
                             };

signed char PCD_comm_trans(struct trans_buff *pi)
{
	char recebyte = 0;
	signed   char sta;
	unsigned char irq_en = 0x00;
	unsigned char wait_for = 0x00;
	unsigned char last_bits;
	unsigned char n;
	unsigned int  i;
	
	switch (pi->mf_comm) 
        {
	case PCD_IDLE:
		irq_en   = 0x00;
		wait_for = 0x00;
		break;
	case PCD_WRITEE2:
		irq_en   = 0x11;
		wait_for = 0x10;
	case PCD_READE2:
		irq_en   = 0x07;
		wait_for = 0x04;
		recebyte = 1;
		break;
	case PCD_LOAD_CFG:
	case PCD_LOAD_KEYE2:
	case PCD_AUTH_ENT1:
		irq_en   = 0x05;
		wait_for = 0x04;
		break;
	case PCD_CALC_CRC:
		irq_en   = 0x11;
		wait_for = 0x10;
		break;
	case PCD_AUTH_ENT2:
		irq_en   = 0x04;
		wait_for = 0x04;
		break;
	case PCD_RECEIVE:
		irq_en   = 0x06;
		wait_for = 0x04;
		recebyte = 1;
		break;
	case PCD_LOAD_KEY:
		irq_en   = 0x05;
		wait_for = 0x04;
		break;
	case PCD_TRANSMIT:
		irq_en   = 0x05;
		wait_for = 0x04;
		break;
	case PCD_TRANSCEIVE:
		irq_en   = 0x3D;
		wait_for = 0x04;
		recebyte = 1;
		break;
	default:
		pi->mf_comm = MI_UNKNOWN_COMM;
		break;
	}
	
	if (pi->mf_comm != MI_UNKNOWN_COMM) 
        {
		rc_write_raw(REG_PAGE, 0x00);
		rc_write_raw(REG_IRQ_EN, 0x7F);
		rc_write_raw(REG_IRQ_REQ, 0x7F);
		rc_write_raw(REG_COMM, PCD_IDLE);
		set_bit_mask(REG_CTRL, 0x01);
		rc_write_raw(REG_IRQ_EN, irq_en|0x80);
		for (i=0; i<(pi->mf_leng); i++)
			rc_write_raw(REG_FIFO_DATA, pi->mf_data[i]);
		rc_write_raw(REG_COMM, pi->mf_comm);
		
		//i = 0xF500;
                i = 0x0688;
		do 
                {
                        //uart_putc(0x99);
			n = rc_read_raw(REG_IRQ_REQ);
			i--;
		} while ((i!=0) && !(n & irq_en & 0x20) && !(n & wait_for));
		
		sta = MI_COMM_ERR;
		if ((i!=0) && !(n & irq_en & 0x20)) 
                {
			if (!(rc_read_raw(REG_ERR_FLAG) & 0x17))
                        {
				sta = MI_OK;
				if (recebyte)
                                {
					n = rc_read_raw(REG_FIFO_LENG);
					last_bits = rc_read_raw(REG_SECONDARY_STA) & 0x07;
					if (last_bits)
						pi->mf_leng = (n-1)*8 + last_bits;
					else
						pi->mf_leng = n*8;
						
					if (n == 0) n = 1;
					
					for (i=0; i<n; i++)
						pi->mf_data[i] = rc_read_raw(REG_FIFO_DATA);
				}
			} 
                        else if (rc_read_raw(REG_ERR_FLAG) & 0x01)
                        {
				sta = MI_COLL_ERR;
				if (recebyte) 
                                {
					n = rc_read_raw(REG_FIFO_LENG);
					last_bits = rc_read_raw(REG_SECONDARY_STA) & 0x07;
					if (last_bits)
						pi->mf_leng = (n-1)*8 + last_bits;
					else
						pi->mf_leng = n*8;
						
					if (n == 0) n = 1;
					
					for (i=0; i<n; i++)
						pi->mf_data[i] = rc_read_raw(REG_FIFO_DATA);
				}
				pi->mf_data[0] = rc_read_raw(0x0B);
			}
		} 
                else if (n & irq_en & 0x20) 
                {
			sta = MI_NOTAG_ERR;
		} 
                else if (!(rc_read_raw(REG_ERR_FLAG) & 0x17)) 
                {
			sta = MI_ACCESS_TIMEOUT;
		}
                else 
                {
			sta = MI_COMM_ERR;
		}		
		rc_write_raw(REG_IRQ_EN, 0x7F);
		rc_write_raw(REG_IRQ_REQ, 0x7F);
		set_bit_mask(REG_CTRL, 0x04);
		rc_write_raw(REG_COMM, PCD_IDLE);
	}
	return sta;
}

//==================================================================================================
//| 函数名称 | rc_init
//|----------|--------------------------------------------------------------------------------------
//| 函数功能 | RC531端口初始化
//|----------|--------------------------------------------------------------------------------------
//| 调用模块 | 
//|----------|--------------------------------------------------------------------------------------
//| 输入参数 |
//|----------|--------------------------------------------------------------------------------------       
//| 返回参数 |  
//|----------|--------------------------------------------------------------------------------------       
//| 全局变量 |
//|----------|-------------------------------------------------------------------------------------- 
//| 函数设计 | 编写人：李亚东    时间：2016-4-25  
//|----------|-------------------------------------------------------------------------------------- 
//|   备注   |      
//|----------|-------------------------------------------------------------------------------------- 
//| 修改记录 | 修改人：          时间：         修改内容： 
//==================================================================================================
void rc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //PA4作为CS引脚，PA8作为RST引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //
 	GPIO_SetBits(GPIOA,GPIO_Pin_2);	
	
	SPIx_Init();	//配置SPI1端口PA5-CK  PA6-MISO  PA7-MOSI
}


unsigned char rc_read_raw(unsigned char addr)
{
	unsigned char result = 0;
	
	RCPIN_CS_LOW;
	addr = ((addr<<1) & 0x7E) | 0x80;
	
  SPIx_ReadWriteByte(addr);
	
	result = SPIx_ReadWriteByte(0x00);
	
	RCPIN_CS_HIGH;

	return result;
}


void rc_write_raw(unsigned char addr, unsigned char val)
{
	RCPIN_CS_LOW;
	
	addr = ((addr<<1) & 0x7E);
	
	SPIx_ReadWriteByte(addr);
	SPIx_ReadWriteByte(val);
	
	RCPIN_CS_HIGH;
}




void set_bit_mask(unsigned char reg, unsigned char mask)
{
	char tmp = 0x00;
	tmp = rc_read_raw(reg);
	rc_write_raw(reg, tmp | mask);
}


void clr_bit_mask(unsigned char reg, unsigned char mask)
{
	char tmp = 0x00;
	tmp = rc_read_raw(reg);
	rc_write_raw(reg, tmp & ~mask);
}


signed char PCD_reset(void)
{
	signed char sta = MI_OK;
	char n = 0xFF;
	unsigned int i = 3000;
	
	RCPIN_CS_LOW;
	RCPIN_RST_LOW;
	delay_ms(50);
	
	RCPIN_RST_HIGH;
	delay_ms(5);
	
	RCPIN_RST_LOW;
	RCPIN_CS_LOW;
	delay_ms(5);
	
	while (i!=0 && n) {
		n = rc_read_raw(REG_COMM);
		i--;
	}
	
	if (i != 0) {
		rc_write_raw(REG_PAGE, 0x80);
		n = 0x80;
		while ((i!=0) && (n&0x80)) {
			n = rc_read_raw(REG_COMM);
			i--;
		}
		
		if (i==0 || (n&0xFF))
			sta = (signed char)MI_RESET_ERR;
	} else {
		sta = (signed char)MI_RESET_ERR;
	}
	
	if (sta == MI_OK)
		rc_write_raw(REG_PAGE, 0x00);
	return sta;
}


signed char PCD_AntennaON(void)
{
	unsigned char i;
	i = rc_read_raw(REG_TX_CTRL);
	if (i & 0x03) 
	{
		return MI_OK;
	} 
	else 
	{
		set_bit_mask(REG_TX_CTRL, 0x03);
		return MI_OK;
	}
}


signed char PCD_AntennaOFF(void)
{
	clr_bit_mask(REG_TX_CTRL, 0x03);
	return MI_OK;
}


void mode_14443A(void)
{
	clr_bit_mask(REG_CTRL, 0x08);
	
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x00);
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x40);
	delay_us(2);
	clr_bit_mask(REG_CLOCK_Q_CTRL, 0x40);
	
	rc_write_raw(REG_TX_CTRL, 0x5B);
	rc_write_raw(REG_CW_CONDUCTANCE, 0x0F);
	rc_write_raw(REG_MOD_CONDUCTANCE, 0x3F);
	rc_write_raw(REG_CODER_CTRL, 0x19);  //MIFARE 106 kBd; ISO/IEC 14443 A  MIFARE, ISO/IEC 14443 A, (Miller coded)
	//rc_write_raw(REG_CODER_CTRL, 0x11);  
        
        rc_write_raw(REG_MOD_WIDTH, 0x13);
	rc_write_raw(REG_MOD_WIDTH_SOF, 0x00);
	rc_write_raw(REG_TYPEB_FRAMING, 0x00);
	
	rc_write_raw(REG_RX_CTRL1, 0x73);
	rc_write_raw(REG_DECODER_CTRL, 0x08);
	rc_write_raw(REG_BIT_PHASE, 0xAD);
	rc_write_raw(REG_RX_THRESHOLD, 0xAA);
	rc_write_raw(REG_BPSK_DEM_CTRL, 0x00);
	rc_write_raw(REG_RX_CTRL2, 0x41);
	
	rc_write_raw(REG_RX_WAIT, 0x06);
	rc_write_raw(REG_CH_REDUNDANCY, 0x0F);
	rc_write_raw(REG_CRC_PRESET_LSB, 0x63);
	rc_write_raw(REG_CRC_PRESET_MSB, 0x63);
	rc_write_raw(REG_TIME_SOLT_PERIOD, 0x00);
	rc_write_raw(REG_MFOUT_SELECT, 0x00);
	rc_write_raw(REG_PRESET_27, 0x00);
	
	rc_write_raw(REG_FIFO_LEVEL, 0x3F);
	rc_write_raw(REG_TIMER_CLOCK, 0x07);
	rc_write_raw(REG_TIMER_RELOAD, 0x0A);
	rc_write_raw(REG_TIMER_CTRL, 0x06);
	rc_write_raw(REG_IRQ_PIN_CFG, 0x02);
	rc_write_raw(REG_PRESET_2E, 0x00);
	rc_write_raw(REG_PRESET_2F, 0x00);
	
	PCD_set_TMO(106);
	delay_ms(1);
	PCD_AntennaON();
}


void mode_14443B(void)
{
	clr_bit_mask(REG_CTRL, 0x08);
	
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x00);
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x40);
	delay_us(2);
	clr_bit_mask(REG_CLOCK_Q_CTRL, 0x40);
	
	rc_write_raw(REG_TX_CTRL, 0x4B);
	rc_write_raw(REG_CW_CONDUCTANCE, 0x17);
	rc_write_raw(REG_MOD_CONDUCTANCE, 0x06);
	rc_write_raw(REG_CODER_CTRL, 0x20);
	rc_write_raw(REG_MOD_WIDTH, 0x13);
	rc_write_raw(REG_MOD_WIDTH_SOF, 0x3F);
	rc_write_raw(REG_TYPEB_FRAMING, 0x3B);
	
	rc_write_raw(REG_RX_CTRL1, 0x73);
	rc_write_raw(REG_DECODER_CTRL, 0x19);
	rc_write_raw(REG_BIT_PHASE, 0xAD);
	rc_write_raw(REG_RX_THRESHOLD, 0x88);
	rc_write_raw(REG_BPSK_DEM_CTRL, 0x7E);
	rc_write_raw(REG_RX_CTRL2, 0x01);
	
	rc_write_raw(REG_RX_WAIT, 0x06);
	rc_write_raw(REG_CH_REDUNDANCY, 0x2C);
	rc_write_raw(REG_CRC_PRESET_LSB, 0xFF);
	rc_write_raw(REG_CRC_PRESET_MSB, 0xFF);
	rc_write_raw(REG_TIME_SOLT_PERIOD, 0x00);
	rc_write_raw(REG_MFOUT_SELECT, 0x00);
	rc_write_raw(REG_PRESET_27, 0x00);
	
	rc_write_raw(REG_FIFO_LEVEL, 0x3F);
	rc_write_raw(REG_TIMER_CLOCK, 0x07);
	rc_write_raw(REG_TIMER_RELOAD, 0x0A);
	rc_write_raw(REG_TIMER_CTRL, 0x06);
	rc_write_raw(REG_IRQ_PIN_CFG, 0x02);
	rc_write_raw(REG_PRESET_2E, 0x00);
	rc_write_raw(REG_PRESET_2F, 0x00);
	
	PCD_set_TMO(106);
	delay_ms(1);
	PCD_AntennaON();
}


void mode_r(void)
{
	clr_bit_mask(REG_CTRL, 0x08);
	
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x00);
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x40);
	delay_us(2);
	clr_bit_mask(REG_CLOCK_Q_CTRL, 0x40);
	
	rc_write_raw(REG_TX_CTRL, 0x4B);
	rc_write_raw(REG_CW_CONDUCTANCE, 0x06);
	rc_write_raw(REG_MOD_CONDUCTANCE, 0x03);
	rc_write_raw(REG_CODER_CTRL, 0x20);
	rc_write_raw(REG_MOD_WIDTH, 0x13);
	rc_write_raw(REG_MOD_WIDTH_SOF, 0x00);
	rc_write_raw(REG_TYPEB_FRAMING, 0x3B);
	
	rc_write_raw(REG_RX_CTRL1, 0x73);
	rc_write_raw(REG_DECODER_CTRL, 0x19);
	rc_write_raw(REG_BIT_PHASE, 0xAD);
	rc_write_raw(REG_RX_THRESHOLD, 0x88);
	rc_write_raw(REG_BPSK_DEM_CTRL, 0x3E);
	rc_write_raw(REG_RX_CTRL2, 0x01);
	
	rc_write_raw(REG_RX_WAIT, 0x06);
	rc_write_raw(REG_CH_REDUNDANCY, 0x2C);
	rc_write_raw(REG_CRC_PRESET_LSB, 0xFF);
	rc_write_raw(REG_CRC_PRESET_MSB, 0xFF);
	rc_write_raw(REG_TIME_SOLT_PERIOD, 0x00);
	rc_write_raw(REG_MFOUT_SELECT, 0x00);
	rc_write_raw(REG_PRESET_27, 0x00);
	
	rc_write_raw(REG_FIFO_LEVEL, 0x1A);
	rc_write_raw(REG_TIMER_CLOCK, 0x07);
	rc_write_raw(REG_TIMER_RELOAD, 0x0A);
	rc_write_raw(REG_TIMER_CTRL, 0x06);
	rc_write_raw(REG_IRQ_PIN_CFG, 0x02);
	rc_write_raw(REG_PRESET_2E, 0x00);
	rc_write_raw(REG_PRESET_2F, 0x00);
	
	PCD_set_TMO(106);
	delay_ms(1);
	PCD_AntennaON();
}


void mode_s(void)
{
	clr_bit_mask(REG_CTRL, 0x08);
	
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x00);
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x40);
	delay_us(2);
	clr_bit_mask(REG_CLOCK_Q_CTRL, 0x40);
	
	rc_write_raw(REG_TX_CTRL, 0x4B);
	rc_write_raw(REG_CW_CONDUCTANCE, 0x06);
	rc_write_raw(REG_MOD_CONDUCTANCE, 0x03);
	rc_write_raw(REG_CODER_CTRL, 0x20);
	rc_write_raw(REG_MOD_WIDTH, 0x13);
	rc_write_raw(REG_MOD_WIDTH_SOF, 0x00);
	rc_write_raw(REG_TYPEB_FRAMING, 0x18);
	
	rc_write_raw(REG_RX_CTRL1, 0x73);
	rc_write_raw(REG_DECODER_CTRL, 0x19);
	rc_write_raw(REG_BIT_PHASE, 0xAD);
	rc_write_raw(REG_RX_THRESHOLD, 0x88);
	rc_write_raw(REG_BPSK_DEM_CTRL, 0x3E);
	rc_write_raw(REG_RX_CTRL2, 0x01);
	
	rc_write_raw(REG_RX_WAIT, 0x06);
	rc_write_raw(REG_CH_REDUNDANCY, 0x2C);
	rc_write_raw(REG_CRC_PRESET_LSB, 0xFF);
	rc_write_raw(REG_CRC_PRESET_MSB, 0xFF);
	rc_write_raw(REG_TIME_SOLT_PERIOD, 0x00);
	rc_write_raw(REG_MFOUT_SELECT, 0x00);
	rc_write_raw(REG_PRESET_27, 0x00);
	
	rc_write_raw(REG_FIFO_LEVEL, 0x3F);
	rc_write_raw(REG_TIMER_CLOCK, 0x07);
	rc_write_raw(REG_TIMER_RELOAD, 0x0A);
	rc_write_raw(REG_TIMER_CTRL, 0x06);
	rc_write_raw(REG_IRQ_PIN_CFG, 0x02);
	rc_write_raw(REG_PRESET_2E, 0x00);
	rc_write_raw(REG_PRESET_2F, 0x00);
	
	PCD_set_TMO(106);
	delay_ms(1);
	PCD_AntennaON();
}


void mode_15693(void)
{
	clr_bit_mask(REG_CTRL, 0x08);
	
	rc_write_raw(REG_TX_CTRL, 0x48);
	rc_write_raw(REG_CW_CONDUCTANCE, 0x3F);
	rc_write_raw(REG_MOD_CONDUCTANCE, 0x05);
	rc_write_raw(REG_CODER_CTRL, 0x2F);
	rc_write_raw(REG_MOD_WIDTH, 0x3F);
	rc_write_raw(REG_MOD_WIDTH_SOF, 0x3F);
	rc_write_raw(REG_TYPEB_FRAMING, 0x00);
	
	rc_write_raw(REG_RX_CTRL1, 0x8B);
	rc_write_raw(REG_DECODER_CTRL, 0x34);
	rc_write_raw(REG_BIT_PHASE, 0xCD);
	rc_write_raw(REG_RX_THRESHOLD, 0x88);
	rc_write_raw(REG_BPSK_DEM_CTRL, 0x00);
	rc_write_raw(REG_RX_CTRL2, 0x01);
	rc_write_raw(REG_CLOCK_Q_CTRL, 0x00);
	
	rc_write_raw(REG_RX_WAIT, 0x08);
	rc_write_raw(REG_CH_REDUNDANCY, 0x2C);
	rc_write_raw(REG_CRC_PRESET_LSB, 0xFF);
	rc_write_raw(REG_CRC_PRESET_MSB, 0xFF);
	rc_write_raw(REG_TIME_SOLT_PERIOD, 0x00);
	rc_write_raw(REG_MFOUT_SELECT, 0x00);
	rc_write_raw(REG_PRESET_27, 0x00);
	
	rc_write_raw(REG_FIFO_LEVEL, 0x38);
	rc_write_raw(REG_TIMER_CLOCK, 0x0B);
	rc_write_raw(REG_TIMER_RELOAD, 0x00);
	rc_write_raw(REG_TIMER_CTRL, 0x02);
	rc_write_raw(REG_PRESET_2E, 0x00);
	rc_write_raw(REG_PRESET_2F, 0x00);
	
	delay_ms(1);
	PCD_AntennaON();
}

signed char PCD_cfg_iso_type(unsigned char type)
{
	if (type == 'A') {
		mode_14443A();
	} else if (type == 'B') {
		mode_14443B();
	} else if (type == 'r') {
		mode_r();
	} else if (type == 's') {
		mode_s();
	} else if (type == '1') {
		mode_15693();
	} else {
		return -1;
	}
	
	return MI_OK;
}


void PCD_set_TMO(unsigned char tmo_leng)
{
	switch (tmo_leng) {
	case 0:
		rc_write_raw(REG_TIMER_CLOCK, 0x07);
		rc_write_raw(REG_TIMER_RELOAD, 0x21);
		break;
	case 1:
		rc_write_raw(REG_TIMER_CLOCK, 0x07);
		rc_write_raw(REG_TIMER_RELOAD, 0x41);
		break;
	case 2:
		rc_write_raw(REG_TIMER_CLOCK, 0x07);
		rc_write_raw(REG_TIMER_RELOAD, 0x81);
		break;
	case 3:
		rc_write_raw(REG_TIMER_CLOCK, 0x09);
		rc_write_raw(REG_TIMER_RELOAD, 0x41);
		break;
	case 4:
		rc_write_raw(REG_TIMER_CLOCK, 0x09);
		rc_write_raw(REG_TIMER_RELOAD, 0x81);
		break;
	case 5:
		rc_write_raw(REG_TIMER_CLOCK, 0x0B);
		rc_write_raw(REG_TIMER_RELOAD, 0x41);
		break;
	case 6:
		rc_write_raw(REG_TIMER_CLOCK, 0x0B);
		rc_write_raw(REG_TIMER_RELOAD, 0x81);
		break;
	case 7:
		rc_write_raw(REG_TIMER_CLOCK, 0x0D);
		rc_write_raw(REG_TIMER_RELOAD, 0x41);
		break;
	case 8:
		rc_write_raw(REG_TIMER_CLOCK, 0x0D);
		rc_write_raw(REG_TIMER_RELOAD, 0x81);
		break;
	case 9:
		rc_write_raw(REG_TIMER_CLOCK, 0x0F);
		rc_write_raw(REG_TIMER_RELOAD, 0x41);
		break;
	case 10:
		rc_write_raw(REG_TIMER_CLOCK, 0x0F);
		rc_write_raw(REG_TIMER_RELOAD, 0x81);
		break;
	case 11:
		rc_write_raw(REG_TIMER_CLOCK, 0x13);
		rc_write_raw(REG_TIMER_RELOAD, 0x11);
		break;
	case 12:
		rc_write_raw(REG_TIMER_CLOCK, 0x13);
		rc_write_raw(REG_TIMER_RELOAD, 0x21);
		break;
	case 13:
		rc_write_raw(REG_TIMER_CLOCK, 0x13);
		rc_write_raw(REG_TIMER_RELOAD, 0x41);
		break;
	case 14:
		rc_write_raw(REG_TIMER_CLOCK, 0x13);
		rc_write_raw(REG_TIMER_RELOAD, 0x81);
		break;
	case 15:
		rc_write_raw(REG_TIMER_CLOCK, 0x09);
		rc_write_raw(REG_TIMER_RELOAD, 0xFF);
		break;
	default:
		rc_write_raw(REG_TIMER_CLOCK, 0x19);
		rc_write_raw(REG_TIMER_RELOAD, tmo_leng);
		break;
	}
	
	rc_write_raw(REG_TIMER_CTRL, 0x06);
}

//密钥算法。。
void getCardKey(unsigned char cardSn[4], unsigned char keyFactor[6], unsigned char key[6])
{
	unsigned char a[4];
  unsigned char Nkey_a[6];
	
	a[0] = cardSn[0]; //04
	a[1] = cardSn[1]; //8D
	a[2] = cardSn[2]; //94
	a[3] = cardSn[3]; //43

  //79 D6 54 70 CD E7 
	Nkey_a[0] = a[0] + a[1] + a[2] + a[3] + keyFactor[0];
	Nkey_a[1] = a[0] ^ a[1] ^ a[2] ^ a[3] ^ keyFactor[1];
	Nkey_a[2] = (unsigned char)(a[0] + a[1]) ^ a[2] ^ a[3] ^ keyFactor[2];
	Nkey_a[3] = (unsigned char)(a[0] + a[1] + a[2]) ^ a[3] ^ keyFactor[3];
	Nkey_a[4] = (unsigned char)(a[0] ^ a[1]) + a[2] + a[3] + keyFactor[4];
	Nkey_a[5] = (unsigned char)(a[0] ^ a[1] ^ a[2] + a[3]) + keyFactor[5];

	memcpy(key, Nkey_a, 6);
}

