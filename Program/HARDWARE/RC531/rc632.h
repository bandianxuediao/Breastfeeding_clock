#ifndef __RC632_H__
#define __RC632_H__

#include "includes.h"


#define RCPIN_CS_LOW   PAout(4) = 0;
#define RCPIN_CS_HIGH  PAout(4) = 1;
//#define INT3  GPIO_ReadInputDataBit(GPIOA,RC531_IRQ) //¶ÁÈ¡Ñ°¿¨µÄÖÐ¶Ï


#define RCPIN_RST_LOW    PAout(8) = 0;
#define RCPIN_RST_HIGH   PAout(8) = 1;

#define PDA_HEAD	    0xA5
#define PDA_COMT_SET	0x57
#define PDA_COMT_REQ	0x52
#define PDA_COMT_AUTO	0x41
#define PACK_HEAD	0
#define PACK_LENG	1
#define PACK_NUMB	2
#define PACK_COMT	3
#define PACK_COMM	4
#define PACK_ACKN	5
#define PACK_DALE	6
#define PACK_DATA	7

#define FSD	64

// RC632 ÃüÁî×Ö
#define PCD_IDLE	      0x00
#define PCD_WRITEE2	    0x01
#define PCD_READE2	    0x03
#define PCD_LOAD_CFG	  0x07
#define PCD_LOAD_KEYE2	0x08
#define PCD_AUTH_ENT1  	0x0C
#define PCD_AUTH_ENT2	  0x14
#define PCD_RECEIVE	    0x16
#define PCD_LOAD_KEY	  0x19
#define PCD_TRANSMIT	  0x1A
#define PCD_TRANSCEIVE	0x1E
#define PCD_RESETPHASE	0x3F
#define PCD_CALC_CRC	  0x12

#define PCD_FIFO_LENG  	64

// RC632 ¼Ä´æÆ÷
// page 0 command and status
#define REG_PAGE		          0x00
#define REG_COMM		          0x01
#define REG_FIFO_DATA		      0x02
#define REG_PRIMARY_STA	      0x03
#define REG_FIFO_LENG	  	    0x04
#define REG_SECONDARY_STA	    0x05
#define REG_IRQ_EN		        0x06
#define REG_IRQ_REQ		        0x07
// page 1 control and status
#define REG_CTRL		          0x09
#define REG_ERR_FLAG		      0x0A
#define REG_COLL_POS		      0x0B
#define REG_TIMER_VAL		      0x0C
#define REG_CRC_RESULT_LSB	  0x0D
#define REG_CRC_RESULT_MSB	  0x0E
#define REG_BIT_FRAMING		    0x0F
// page 2 transmitter and coder control
#define REG_TX_CTRL		        0x11
#define REG_CW_CONDUCTANCE	  0x12
#define REG_MOD_CONDUCTANCE	  0x13
#define REG_CODER_CTRL		    0x14
#define REG_MOD_WIDTH		      0x15
#define REG_MOD_WIDTH_SOF    	0x16
#define REG_TYPEB_FRAMING	    0x17
// page 3 receiver and decoder control
#define REG_RX_CTRL1	     	  0x19
#define REG_DECODER_CTRL	    0x1A
#define REG_BIT_PHASE		      0x1B
#define REG_RX_THRESHOLD  	  0x1C
#define REG_BPSK_DEM_CTRL    	0x1D
#define REG_RX_CTRL2		      0x1E
#define REG_CLOCK_Q_CTRL	    0x1F
// page 4 rf timing and channel redundancy
#define REG_RX_WAIT		        0x21
#define REG_CH_REDUNDANCY	    0x22
#define REG_CRC_PRESET_LSB	  0x23
#define REG_CRC_PRESET_MSB	  0x24
#define REG_TIME_SOLT_PERIOD	0x25
#define REG_MFOUT_SELECT    	0x26
#define REG_PRESET_27		      0x27
// page 5 fifo, timer and IRQ pin configuration
#define REG_FIFO_LEVEL		    0x29
#define REG_TIMER_CLOCK		    0x2A
#define REG_TIMER_CTRL		    0x2B
#define REG_TIMER_RELOAD	    0x2C
#define REG_IRQ_PIN_CFG		    0x2D
#define REG_PRESET_2E	  	    0x2E
#define REG_PRESET_2F	  	    0x2F
// page 7 test control
#define REG_TEST_ANA_SELECT	  0x3A
#define REG_TEST_DIGI_SELECT	0x3D

// RC632 ·µ»ØµÄ´íÎó´úÂë
#define MI_OK			0
#define MI_CHK_OK		0

#define MI_NOTAG_ERR		  (-1)
#define MI_CHK_FAILED		  (-1)
#define MI_CRC_ERR	     	(-2)
#define MI_CHK_COMP_ERR		(-2)
#define MI_EMPTY		      (-3)
#define MI_AUTH_ERR	    	(-4)
#define MI_PARITY_ERR		  (-5)
#define MI_CODE_ERR		    (-6)
#define MI_SERNR_ERR	   	(-8)
#define MI_KEY_ERR	    	(-9)
#define MI_NOTAUTH_ERR		(-10)
#define MI_BIT_COUNT_ERR	(-11)
#define MI_BYTE_COUNT_ERR	(-12)
#define MI_IDLE		      	(-13)
#define MI_TRANS_ERR		  (-14)
#define MI_WRITE_ERR	  	(-15)
#define MI_INCR_ERR		    (-16)
#define MI_DECR_ERR		    (-17)
#define MI_READ_ERR	    	(-18)
#define MI_OVFL_ERR		    (-19)
#define MI_POLLING		    (-20)
#define MI_FRAMING_ERR		(-21)
#define MI_ACCESS_ERR	   	(-22)
#define MI_UNKNOWN_COMM		(-23)
#define MI_COLL_ERR	    	(-24)
#define MI_RESET_ERR		  (-25)
#define MI_INIT_ERR	     	(-25)
#define MI_INTERFACE_ERR	(-26)
#define MI_ACCESS_TIMEOUT	(-27)
#define MI_NOBIT_WISE_ANTICOLL	(-28)
#define MI_QUIT		            	(-30)
#define MI_RECBUF_OVERFLOW    	(-50)
#define MI_SEND_BYTE_ERR	      (-51)
#define MI_SEND_BUF_OVERFLOW	  (-53)
#define MI_BAUDRATE_NOT_SUPP	  (-54)
#define MI_SAME_BAUDRATE_REQ	  (-55)
#define MI_WRONG_PARAMETER_VAL	(-60)
#define MI_BREAK		            (-99)
#define MI_NY_IMPLEMENTED	      (-100)
#define MI_NO_MFRC		          (-101)
#define MI_MFRC_NOTAUTH		      (-102)
#define MI_WRONG_DES_MODE	      (-103)
#define MI_HOST_AUTH_FAILED    	(-104)
#define MI_WRONG_LOAD_MODE	    (-106)
#define MI_WRONG_DESKEY		      (-107)
#define MI_MKLOAD_FAILED	      (-108)
#define MI_FIFO_ERR		          (-109)
#define MI_WRONG_ADDR		        (-110)
#define MI_DESKEYLOAD_FAILED	  (-111)
#define MI_WRONG_SEL_CNT       	(-114)
#define MI_WRONG_TEST_MODE    	(-117)
#define MI_TEST_FAILED	      	(-118)
#define MI_TOC_ERR		          (-119)
#define MI_COMM_ABORT		        (-120)
#define MI_INVALID_BASE		      (-121)
#define MI_MFRC_RESET	        	(-122)
#define MI_WRONG_VAL		        (-123)
#define MI_VAL_ERR		          (-124)
#define MI_COMM_ERR		          (-125) //0x83



extern unsigned char iso14443a_cardtype[2];
extern unsigned char iso14443a_cardsnr[4];
extern unsigned char uart_indx, recv_flag;
extern unsigned char RC531_sbuf[50];
extern unsigned char RC531_rbuf[50];
extern void Find_Card_A(void);





extern unsigned char rc_read_raw(unsigned char addr);
extern void rc_write_raw(unsigned char addr, unsigned char val);


extern signed char PCD_reset(void);
extern signed char PCD_AntennaON(void);
extern signed char PCD_AntennaOFF(void);
extern signed char PCD_cfg_iso_type(unsigned char type);
//signed char PCD_comm_trans(struct trans_buff *pi);

extern void rc_init(void);
extern void set_bit_mask(unsigned char reg, unsigned char mask);
extern void clr_bit_mask(unsigned char reg, unsigned char mask);
extern void PCD_set_TMO(unsigned char tmo_leng);
extern void getCardKey(unsigned char cardSn[4], unsigned char keyFactor[6], unsigned char key[6]);
extern void PDA_package(unsigned char num, unsigned char com_type,
		 unsigned char com, unsigned char ack,
		 unsigned char len, unsigned char *dat, unsigned char *buf);
extern unsigned short crc16_table(unsigned char *pcrc, unsigned short cnt);
extern unsigned short crc16_tab[];
#endif


