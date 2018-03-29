
#include "includes.h"


signed char g_bIblock;

struct trans_buff{unsigned char mf_comm;
                              unsigned int  mf_leng;
                              unsigned char mf_data[64];
                             };

signed char PCD_comm_trans(struct trans_buff *pi);




// 寻卡
// 0x52:ALL  寻找感应区内所有符合14443A标准的卡
// 0x26:IDLE 寻找感应区内未进入休眠状态的卡
// 0x4400 mifare_ultralight
// 0x0400 mifare_one s50
// 0x0200 mifare_one s70
// 0x0800 mifare_pro
// 0x0403 mifare_proX
// 0x4403 mifare_desfire
signed char PCD_request(unsigned char req_code, unsigned char *p_tagtype)
{
	int    sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	rc_write_raw(REG_CH_REDUNDANCY, 0x03);
	clr_bit_mask(REG_CTRL, 0x08);
	rc_write_raw(REG_BIT_FRAMING, 0x07);
	set_bit_mask(REG_TX_CTRL, 0x03);
	PCD_set_TMO(4);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 1;
	com_data.mf_data[0] = req_code;
	
	sta = PCD_comm_trans(pi);

	if (!sta) {
		if (com_data.mf_leng != 0x10)
			sta = MI_BIT_COUNT_ERR;
	}
	*p_tagtype     = com_data.mf_data[0];
	*(p_tagtype+1) = com_data.mf_data[1];
	
	return sta;
}


// 防碰撞
signed char PCD_anticoll(unsigned char *p_snr)
{
	signed   char sta;
	unsigned char i;
	unsigned char bits;
	unsigned char bytes;
	unsigned char snr_chk = 0;
	unsigned char coll_pos = 0;
	unsigned char tmp;
	unsigned char snr[5] = {0, 0, 0, 0, 0};
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	rc_write_raw(REG_DECODER_CTRL, 0x28);
	clr_bit_mask(REG_CTRL, 0x08);
	rc_write_raw(REG_CH_REDUNDANCY, 0x03);
	PCD_set_TMO(4);
	
	do {
		bits = coll_pos % 8;
		if (bits != 0) {
			bytes = coll_pos/8 + 1;
			rc_write_raw(REG_BIT_FRAMING, (bits<<4)+bits);
		} else {
			bytes = coll_pos/8;
		}
		
		com_data.mf_comm = PCD_TRANSCEIVE;
		com_data.mf_data[0] = PICC_ANTICOLL1;
		com_data.mf_data[1] = 0x20+((coll_pos/8)<<4)+(bits&0x0F);
		for (i=0; i<bytes; i++)
		com_data.mf_data[i+2] = snr[i];
		com_data.mf_leng = bytes + 2;
		sta = PCD_comm_trans(pi);
		tmp = snr[coll_pos/8];
		if (sta == MI_COLL_ERR)
			{
				for (i=0; i<(5-(coll_pos/8)); i++)
				snr[i+(coll_pos/8)] = com_data.mf_data[i+1];
				snr[coll_pos/8] |= tmp;
				coll_pos = com_data.mf_data[0];
			}
			else if (sta == MI_OK)
				{
					for (i=0; i<(com_data.mf_leng/8); i++)
					snr[4-i] = com_data.mf_data[com_data.mf_leng/8 -i-1];
					snr[coll_pos/8] |= tmp;
				}
	} while (sta == MI_COLL_ERR);
	
	if (sta == MI_OK)
		{
			for (i=0; i<4; i++)
			{
				*(p_snr+i) = snr[i];
				snr_chk   ^= snr[i];
			}
		if (snr_chk != snr[i])
			sta = MI_COMM_ERR;
	}
	
	clr_bit_mask(REG_DECODER_CTRL, 0x20);
	return sta;
}


// 选定卡片
signed char PCD_select(unsigned char *p_snr, unsigned char *p_size)
{
	unsigned char i;
	int sta;
	unsigned char snr_chk = 0;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	rc_write_raw(REG_CH_REDUNDANCY, 0x0F);
	clr_bit_mask(REG_CTRL, 0x08);
	PCD_set_TMO(4);
	
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 7;
	com_data.mf_data[0] = PICC_ANTICOLL1;
	com_data.mf_data[1] = 0x70;
	for (i=0; i<4; i++) {
		snr_chk ^= *(p_snr+i);
		com_data.mf_data[i+2] = *(p_snr+i);
	}
	com_data.mf_data[6] = snr_chk;
	sta = PCD_comm_trans(pi);
	
	if (sta == MI_OK) {
		if (com_data.mf_leng != 0x08) {
			sta = MI_BIT_COUNT_ERR;
		} else {
			*p_size = com_data.mf_data[0];
		}
	}
	
	return sta;
}


// 转换密钥
signed char change_code_key(unsigned char *uncoded, unsigned char *coded)
{
	unsigned char cnt = 0;
	unsigned char ln  = 0;
	unsigned char hn  = 0;
	
	for (cnt=0; cnt<6; cnt++) {
		ln = uncoded[cnt] & 0x0F;
		hn = uncoded[cnt] >> 4;
		coded[cnt*2+1] = (~ln<<4) | ln;
		coded[cnt*2]   = (~hn<<4) | hn;
	}
	
	return MI_OK;
}


// 将密钥存入RC632的FIFO中
signed char PCD_auth_key(unsigned char *keys)
{
	char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	PCD_set_TMO(4);
	com_data.mf_comm = PCD_LOAD_KEY;
	com_data.mf_leng = 12;
	memcpy(&com_data.mf_data[0], keys, 12);
	sta = PCD_comm_trans(pi);
	
	return sta;
}


// 验证密钥
signed char PCD_auth_state(unsigned char mode, unsigned char block,
		    unsigned char *snr)
{
	signed char sta = MI_OK;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	rc_write_raw(REG_CH_REDUNDANCY, 0x0F);
	PCD_set_TMO(4);
	
	com_data.mf_comm = PCD_AUTH_ENT1;
	com_data.mf_leng = 6;
	com_data.mf_data[0] = mode;
	com_data.mf_data[1] = block;
	memcpy(&com_data.mf_data[2], snr, 4);
	
	sta = PCD_comm_trans(pi); //第一次验证
	if (sta == MI_OK) 
        {
		if (rc_read_raw(REG_SECONDARY_STA) & 0x07) 
                {
			sta = MI_BIT_COUNT_ERR;
		} 
                else  //第二次验证
                {
			com_data.mf_comm = PCD_AUTH_ENT2;
			com_data.mf_leng = 0;
			sta = PCD_comm_trans(pi);
			if (sta == MI_OK) 
                        {
				if (rc_read_raw(REG_CTRL) & 0x08)
					sta = MI_OK;
				else
					sta = MI_AUTH_ERR;
			}
		}
	}
	
	return sta;
}


void flush_FIFO(void)
{
	set_bit_mask(REG_CTRL, 0x01);
}


// 读卡块数据
signed char PCD_read(unsigned char block, unsigned char *buff)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	flush_FIFO();
	PCD_set_TMO(4);
	
	rc_write_raw(REG_CH_REDUNDANCY, 0x0F);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = PICC_READ;
	com_data.mf_data[1] = block;
	
	sta = PCD_comm_trans(pi);
	if (sta == MI_OK) {
		if (com_data.mf_leng != 0x80)
			sta = MI_BIT_COUNT_ERR;
		else
			memcpy(buff, &com_data.mf_data[0], 16);
	}
	
	return sta;
}


// 写块数据
signed char PCD_write(unsigned char block, unsigned char *buff)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	PCD_set_TMO(5);
	rc_write_raw(REG_CH_REDUNDANCY, 0x07);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = PICC_WRITE;
	com_data.mf_data[1] = block;
	
	sta = PCD_comm_trans(pi);
	if (sta != MI_NOTAG_ERR) 
        {
		if (com_data.mf_leng != 4) 
                {
			sta = MI_BIT_COUNT_ERR;
		} 
                else 
                {
			com_data.mf_data[0] &= 0x0F;
			switch (com_data.mf_data[0]) 
                        {
			case 0x00:
				sta = MI_NOTAUTH_ERR;
				break;
			case 0x0A:
				sta = MI_OK;
				break;
			default:
				sta = MI_CODE_ERR;
				break;
			}
		}
	}
	
	if (sta == MI_OK) {
		PCD_set_TMO(5);
		com_data.mf_comm = PCD_TRANSCEIVE;
		com_data.mf_leng = 16;
		memcpy(&com_data.mf_data[0], buff, 16);
		
		sta = PCD_comm_trans(pi);
		if (sta != MI_NOTAG_ERR) {
			com_data.mf_data[0] &= 0x0F;
			switch (com_data.mf_data[0]) {
			case 0x00:
				sta = MI_WRITE_ERR;
				break;
			case 0x0A:
				sta = MI_OK;
				break;
			default:
				sta = MI_CODE_ERR;
				break;
			}
		}
		PCD_set_TMO(4);
	}
	
	return sta;
}


signed char PCD_val_init(unsigned char block, unsigned char *dat)
{
	unsigned char buf[16];
	signed   char sta;
	buf[0] = 0x00;
	buf[1] = 0x00;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = ~dat[0];
	buf[5] = ~dat[1];
	buf[6] = ~dat[2];
	buf[7] = ~dat[3];
	buf[8] = dat[0];
	buf[9] = dat[1];
	buf[10] = dat[2];
	buf[11] = dat[3];
	buf[12] = block;
	buf[13] = ~block;
	buf[14] = block;
	buf[15] = ~block;
	sta = PCD_write(block, buf);
	
	return sta;
}


// 扣款和充值
// 0xC0 扣款
// 0xC1 充值
signed char PCD_value(unsigned char mode, unsigned char block, unsigned char *val)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	PCD_set_TMO(5);
	rc_write_raw(REG_CH_REDUNDANCY, 0x0F);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = mode;
	com_data.mf_data[1] = block;
	
	sta = PCD_comm_trans(pi);
	if (sta != MI_NOTAG_ERR) {
		if (com_data.mf_leng != 4) {
			sta = MI_BIT_COUNT_ERR;
		} else {
			com_data.mf_data[0] &= 0x0F;
			switch (com_data.mf_data[0]) {
			case 0x00:
				sta = MI_NOTAUTH_ERR;
				break;
			case 0x0A:
				sta = MI_OK;
				break;
			case 0x01:
				sta = MI_VAL_ERR;
				break;
			default:
				sta = MI_CODE_ERR;
				break;
			}
		}
	}
	
	if (sta == MI_OK) {
		PCD_set_TMO(5);
		com_data.mf_comm = PCD_TRANSCEIVE;
		com_data.mf_leng = 4;
		pi = &com_data;
		memcpy(&com_data.mf_data[0], val, 4);
		
		sta = PCD_comm_trans(pi);
		if (sta == MI_OK) {
			if (com_data.mf_leng != 4)
				sta = MI_BIT_COUNT_ERR;
			else
				sta = MI_OK;
		} else if (sta == MI_NOTAG_ERR) {
			sta = MI_OK;
		} else {
			sta = MI_COMM_ERR;
		}
	}
	
	if (sta == MI_OK) {
		com_data.mf_comm = PCD_TRANSCEIVE;
		com_data.mf_leng = 2;
		com_data.mf_data[0] = PICC_TRANSFER;
		com_data.mf_data[1] = block;
		
		sta = PCD_comm_trans(pi);
		if (sta != MI_NOTAG_ERR) {
			if (com_data.mf_leng != 4) {
				sta = MI_BIT_COUNT_ERR;
			} else {
				com_data.mf_data[0] &= 0x0F;
				switch (com_data.mf_data[0]) {
				case 0x00:
					sta = MI_NOTAUTH_ERR;
					break;
				case 0x0A:
					sta = MI_OK;
					break;
				case 0x01:
					sta = MI_VAL_ERR;
					break;
				default:
					sta = MI_CODE_ERR;
					break;
				}
			}
		}
	}
	
	return sta;
}


// 将卡一块数据调入卡缓冲区
signed char PCD_restore(unsigned char block)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	PCD_set_TMO(4);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = PICC_RESTORE;
	com_data.mf_data[1] = block;
	
	sta = PCD_comm_trans(pi);
	if (sta != MI_NOTAG_ERR) {
		if (com_data.mf_leng != 4) {
			sta = MI_BIT_COUNT_ERR;
		} else {
			com_data.mf_data[0] &= 0x0F;
			switch (com_data.mf_data[0]) {
			case 0x00:
				sta = MI_NOTAUTH_ERR;
				break;
			case 0x0A:
				sta = MI_OK;
				break;
			case 0x01:
				sta = MI_VAL_ERR;
				break;
			default:
				sta = MI_CODE_ERR;
				break;
			}
		}
	}
	
	if (sta == MI_OK) {
		PCD_set_TMO(4);
		com_data.mf_comm = PCD_TRANSCEIVE;
		com_data.mf_leng = 4;
		com_data.mf_data[0] = 0;
		com_data.mf_data[1] = 0;
		com_data.mf_data[2] = 0;
		com_data.mf_data[3] = 0;
		
		sta = PCD_comm_trans(pi);
		if (sta == MI_NOTAG_ERR)
			sta = MI_OK;
	}
	
	return sta;
}


// 将卡缓冲区中数据保存到块
signed char PCD_transfer(unsigned char block)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	PCD_set_TMO(5);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = PICC_TRANSFER;
	com_data.mf_data[1] = block;
	
	sta = PCD_comm_trans(pi);
	if (sta != MI_NOTAG_ERR) {
		if (com_data.mf_leng != 4) {
			sta = MI_BIT_COUNT_ERR;
		} else {
			com_data.mf_data[0] &= 0x0F;
			switch (com_data.mf_data[0]) {
			case 0x00:
				sta = MI_NOTAUTH_ERR;
				break;
			case 0x0A:
				sta = MI_OK;
				break;
			case 0x01:
				sta = MI_VAL_ERR;
				break;
			default:
				sta = MI_CODE_ERR;
				break;
			}
		}
	}
	
	return sta;
}


// 命令卡进入休眠状态
signed char PCD_halt(void)
{
	signed char sta = MI_OK;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = PICC_HALT;
	com_data.mf_data[1] = 0;
	
	sta = PCD_comm_trans(pi);
	if (sta) {
		if (sta==MI_NOTAG_ERR || sta==MI_ACCESS_TIMEOUT)
			sta = MI_OK;
	}
	rc_write_raw(REG_COMM, PCD_IDLE);
	return sta;
}


// 复位CPU卡
signed char PCD_mfpro_rst(unsigned char par, unsigned char *len, unsigned char *buff)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	pi = &com_data;
	
	PCD_set_TMO(15);
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = 2;
	com_data.mf_data[0] = PICC_RESET;
	com_data.mf_data[1] = par;
	g_bIblock = 0;
	
	sta = PCD_comm_trans(pi);
	if ((*len=com_data.mf_leng/8) <= FSD)
		memcpy(buff, &com_data.mf_data[0], *len);
	else
		sta = MI_COMM_ERR;
	return sta;
}


// cid_nad是否包含CID或NAD
// time_out帧等待时间的整数
// leng命令长度
// commCOS命令
signed char PCD_mfpro_comm(unsigned char cid_nad, unsigned char time_out,
		                       unsigned char *len, unsigned char *comm)
{
	signed char sta;
	struct trans_buff com_data;
	struct trans_buff *pi;
	unsigned char i, cid_nad_lg, pcb_i, pcb_r;
	unsigned char send_lg_ok, send_lg_now, send_lg_sum;
	unsigned char recv_lg_now, recv_lg_sum;
	
	recv_lg_now = 0x00;
	recv_lg_sum = 0x00;
	send_lg_now = 0x00;
	send_lg_ok  = 0x00;
	send_lg_sum = *len;
	pcb_r       = 0xA2;
	PCD_set_TMO(time_out);
	
	if (cid_nad & 0xF0)
		cid_nad_lg = 1;
	else
		cid_nad_lg = 0;
	
	if (send_lg_sum > FSD-1-cid_nad_lg) {
		send_lg_now  = FSD-1-cid_nad_lg;
		send_lg_sum -= send_lg_now;
		pcb_i = 0x12 ^ g_bIblock;
	} else {
		send_lg_now = send_lg_sum;
		pcb_i = 0x02 ^ g_bIblock;
	}
	
	g_bIblock = !g_bIblock;
	com_data.mf_comm = PCD_TRANSCEIVE;
	com_data.mf_leng = send_lg_now + cid_nad_lg + 1;
	com_data.mf_data[0] = (cid_nad_lg<<3) | pcb_i;
	for (i=0; i<cid_nad_lg; i++)
		com_data.mf_data[i+1] = 1;
	memcpy(&com_data.mf_data[cid_nad_lg+1], comm, send_lg_now);
	send_lg_ok += send_lg_now;
	pi = &com_data;
	sta = PCD_comm_trans(pi);
	
	while (sta == MI_OK) {
		if (com_data.mf_leng/8-1-cid_nad_lg > FSD) {
			sta = MI_COMM_ERR;
			break;
		}
		
		if ((com_data.mf_data[0] & 0xF0) == 0x00) {
			recv_lg_now = com_data.mf_leng/8 - 1 - cid_nad_lg;
			memcpy(comm+recv_lg_sum, &com_data.mf_data[cid_nad_lg+1], recv_lg_now);
			recv_lg_sum += recv_lg_now;
			*len = recv_lg_sum;
			break;
		}
		
		if ((com_data.mf_data[0] & 0xF0) == 0xF0) {
			com_data.mf_comm = PCD_TRANSCEIVE;
			recv_lg_now = com_data.mf_leng/8 - 1 - cid_nad_lg;
			com_data.mf_leng = recv_lg_now + cid_nad_lg + 1;
			
			pi = &com_data;
			sta = PCD_comm_trans(pi);
			continue;
		}
		
		if ((com_data.mf_data[0] & 0xF0) == 0xA0) {
			com_data.mf_comm = PCD_TRANSCEIVE;
			for (i=0; i<cid_nad_lg; i++)
				com_data.mf_data[i+1] = 0;
			pcb_i ^= 1;
			if (send_lg_sum > FSD-1-cid_nad_lg) {
				send_lg_now  = FSD-1-cid_nad_lg;
				send_lg_sum -= send_lg_now;
				pcb_i |= 0x10 ^ g_bIblock;
				g_bIblock = !g_bIblock;
			} else {
				send_lg_now = send_lg_sum;
				pcb_i &= 0xEF;
				pcb_i |= g_bIblock;
				g_bIblock = !g_bIblock;
			}
			com_data.mf_leng = send_lg_now + cid_nad_lg + 1;
			com_data.mf_data[0] = 0x02 | (cid_nad<<3) | pcb_i;
			
			memcpy(&com_data.mf_data[cid_nad_lg+1], comm+send_lg_ok, send_lg_now);
			send_lg_ok += send_lg_now;
			pi = &com_data;
			sta = PCD_comm_trans(pi);
			continue;
		}
		
		if ((com_data.mf_data[0] & 0xF0) == 0x10) {
			recv_lg_now = com_data.mf_leng/8 - 1 - cid_nad_lg;
			memcpy(comm+recv_lg_sum, &com_data.mf_data[cid_nad_lg+1], recv_lg_now);
			recv_lg_sum += recv_lg_now;
			
			com_data.mf_comm = PCD_TRANSCEIVE;
			for (i=0; i<cid_nad_lg; i++)
				com_data.mf_data[i+1] = 0;
			com_data.mf_leng = cid_nad_lg + 1;
			if (com_data.mf_data[0] & 0x01)
				pcb_r &= 0xFE;
			else
				pcb_r |= 0x01;
			com_data.mf_data[0] = pcb_r | (cid_nad<<3) & 0xFB;
			pi = &com_data;
			sta = PCD_comm_trans(pi);
			continue;
		}
		
		sta = MI_COMM_ERR;
		break;
	}
	return sta;
}


