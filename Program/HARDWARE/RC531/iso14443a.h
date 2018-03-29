#ifndef __SKY_PDA_ISO14443A_H__
#define __SKY_PDA_ISO14443A_H__

extern unsigned char iso14443a_cardtype[2];
extern unsigned char iso14443a_cardsnr[4];

#define PICC_REQIDL		0x26
#define PICC_REQALL		0x52
#define PICC_ANTICOLL1		0x93
#define PICC_ANTICOLL2		0x95
#define PICC_AUTHENT1A		0x60
#define PICC_AUTHENT1B		0x61
#define PICC_READ		0x30
#define PICC_WRITE		0xA0
#define PICC_DECREMENT		0xC0
#define PICC_INCREMENT		0xC1
#define PICC_RESTORE		0xC2
#define PICC_TRANSFER		0xB0
#define PICC_HALT		0x50
#define PICC_RESET		0xE0


extern signed char PCD_request(unsigned char req_code, unsigned char *p_tagtype);
extern signed char PCD_anticoll(unsigned char *p_snr);
extern signed char PCD_select(unsigned char *p_snr, unsigned char *p_size);
extern signed char PCD_halt(void);
extern signed char change_code_key(unsigned char *uncoded, unsigned char *coded);
extern signed char PCD_auth_key(unsigned char *keys);
extern signed char PCD_auth_state(unsigned char mode, unsigned char block,
		    unsigned char *snr);
extern signed char PCD_write(unsigned char block, unsigned char *buff);
extern signed char PCD_read(unsigned char addr, unsigned char *buff);
extern signed char PCD_mfpro_rst(unsigned char par, unsigned char *len, unsigned char *buff);
extern signed char PCD_mfpro_comm(unsigned char cid_nad, unsigned char time_out,
		    unsigned char *len, unsigned char *comm);
		    
extern signed char PCD_val_init(unsigned char block, unsigned char *dat);
extern signed char PCD_value(unsigned char mode, unsigned char block, unsigned char *val);
extern void flush_FIFO(void);

#endif




