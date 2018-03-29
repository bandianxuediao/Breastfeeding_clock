#include "includes.h"

unsigned char g_cFWI=0xff;
struct trans_buff{unsigned char mf_comm;
                              unsigned int  mf_leng;
                              unsigned char mf_data[64];
                             };

signed char PCD_comm_trans(struct trans_buff *pi);

//////////////////////////////////////////////////////////////////////
//REQUEST B
//////////////////////////////////////////////////////////////////////
char M531PiccRequestB(unsigned char req_code, 
                      unsigned char AFI, 
                      unsigned char N, 
                      unsigned char *ATQB)
{
    char  status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi=&MfComData;

    clr_bit_mask(REG_CTRL,0x08);      // disable crypto 1 unit   
    
   // SetBitMask(RegTxControl,0x03);      // Tx2RF-En, Tx1RF-En enable

    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 3;
    MfComData.mf_data[0] = ISO14443B_ANTICOLLISION;     	       // APf code
    MfComData.mf_data[1] = AFI;                // 
    MfComData.mf_data[2] = ((req_code<<3)&0x08) | (N&0x07);  // PARAM
 
    status = PCD_comm_trans(pi);

    if (status!=MI_OK && status!=MI_NOTAG_ERR)
    {   status = MI_COLL_ERR;   }
    
    if (MfComData.mf_leng != 96)
    {   status = MI_COMM_ERR;   }
    
    if (status == MI_OK) 
    {	
    	memcpy(ATQB, &MfComData.mf_data[0], 16);
        PCD_set_TMO(ATQB[11]>>4); // set FWT 
    } 	
    return status;
}                      


void request(void)	   // 寻卡(对身份证或其它TYPE B的卡的操作)
{
	unsigned char status;
unsigned char g_cCidNad;                                    //
unsigned char g_cReceBuf[64];                         //和上位机通讯时的缓冲区
//		 uart_puts(" \r\n1.找卡~\r\n");	

	do{

			status = M531PiccRequestB(0, 0, 0, &g_cReceBuf[0]);//寻卡 							 
	   	
	}
	while(status);
//		 uart_puts(" \r\n1.找到卡啦~\r\n");	

     g_cFWI    = 0xFF;
//			uart_putd(g_cFWI);	

     g_cCidNad = 8;
     status = M531PiccAttrib(&g_cReceBuf[1], g_cReceBuf[10]&0x0F, &g_cReceBuf[12]);

	if (status == MI_OK)
	{ 
		if ((status = Get_UID_TypeB(&g_cReceBuf[0])) == MI_OK)  //返回卡号
		{
//			BEEP(10);
//			uart_putd(&g_cReceBuf[0]);	//送显示卡号
		}
	
	}
}


//////////////////////////////////////////////////////////////////////
//SLOT-MARKER
//////////////////////////////////////////////////////////////////////
/*char M531PiccSlotMarker(unsigned char N, unsigned char *ATQB)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;

    PCD_set_TMO(5);

    if(!N || N>15) status = MI_WRONG_PARAMETER_VALUE;	
    else
    {
       MfComData.mf_comm=PCD_TRANSCEIVE;
       MfComData.mf_leng=1;
       MfComData.mf_data[0]=0x05|(N<<4); // APn code
        
       status=PCD_comm_trans(pi);

       if (status == MI_CRCERR) status = MI_COLL_ERR; // collision occurs

       if (status == MI_OK) 
       {	
          memcpy(ATQB, &MfComData.mf_data[0], 16);
          PCD_set_TMO(ATQB[11]>>4); // set FWT 
       } 	
    }
    return status;
}                      
*/
             

//////////////////////////////////////////////////////////////////////
//ATTRIB
//////////////////////////////////////////////////////////////////////
char M531PiccAttrib(unsigned char *PUPI,unsigned char PARAM3,unsigned char *answer)
{
    char  status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
	PUPI=PUPI;
	PARAM3=PARAM3;

    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 9;
    MfComData.mf_data[0] = ISO14443B_ATTRIB;
   // memcpy(&MfComData.mf_data[1], PUPI, 4);
	MfComData.mf_data[1] = 0x00;
	MfComData.mf_data[2] = 0x00;
	MfComData.mf_data[3] = 0x00;
	MfComData.mf_data[4] = 0x00;
    MfComData.mf_data[5] = 0x00;  	    // EOF/SOF required, default TR0/TR1
    MfComData.mf_data[6] = 0x08;//FSDI; // Max frame 64 
    MfComData.mf_data[7] = 0x01;//PARAM3;  	    // Param3, ISO/IEC 14443-4 compliant?
    MfComData.mf_data[8] = 0x08;//1;  	    // CID
    
    status  = PCD_comm_trans(pi);

    if (status == MI_OK)
    {	
    	*answer = MfComData.mf_data[0];
    } 	
    
    return status;
} 
//////////////////////////////////////////////////////////////////////
//REQUEST B
//////////////////////////////////////////////////////////////////////
char Get_UID_TypeB(unsigned char *ATQB1)
{
    char  status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi=&MfComData;

    clr_bit_mask(REG_CTRL,0x08);      // disable crypto 1 unit   
    
   // SetBitMask(RegTxControl,0x03);      // Tx2RF-En, Tx1RF-En enable

    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  =5;
    MfComData.mf_data[0] =0x00; //ISO14443B_ANTICOLLISION;     	       // APf code
    MfComData.mf_data[1] =0x36;// AFI;                // 
    MfComData.mf_data[2] =0x00; //((req_code<<3)&0x08) | (N&0x07);  // PARAM
	MfComData.mf_data[3] =0x00;
	MfComData.mf_data[4] =0x08;
 
    status = PCD_comm_trans(pi);

 /*  if (status!=MI_OK && status!=MI_NOTAG_ERR)
    {   status = MI_COLL_ERR;   }
    
    if (MfComData.mf_leng != 96)
    {   status = MI_COMM_ERR;   }		   		*/
    
    if (status == MI_OK) 
    {	
    	memcpy(ATQB1, &MfComData.mf_data[0], 10);
  //      PCD_set_TMO(ATQB[11]>>4); // set FWT 
    } 	
    return status;
}       

//////////////////////////////////////////////////////////////////////
//HLTB
//////////////////////////////////////////////////////////////////////
char M531PiccHltb(unsigned char *PUPI)
{
    char  status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
  
    PCD_set_TMO(g_cFWI);
				                               // disable, ISO/IEC3390 enable	
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 2;
    MfComData.mf_data[0] = ISO14443B_ATTRIB;
    memcpy(&MfComData.mf_data[1], PUPI, 4);
    
    status = PCD_comm_trans(pi);

    return status;
}                      

/////////////////////////////////////////////////////////////////////
//AT88RF020验证密码
//input:password=8字节密码
/////////////////////////////////////////////////////////////////////
char At88rf020Check(unsigned char *password)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;

    PCD_set_TMO(g_cFWI);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 10;
    MfComData.mf_data[0] = AT88RF020_CHECK_PASSWORD|0x10;
    MfComData.mf_data[1] = 0;
    memcpy(&MfComData.mf_data[2], password, 8);   

    status = PCD_comm_trans(pi);
    
    if ((MfComData.mf_data[1]&0x01) || (MfComData.mf_leng!=0x10))
    {    status = MI_COMM_ERR;    }
    return status;
}

/////////////////////////////////////////////////////////////////////
//读AT88RF020一页数据
//input :addr=页地址
//output:readdata=读出的8字节数据
/////////////////////////////////////////////////////////////////////
char At88rf020Read(unsigned char addr, unsigned char *readdata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(g_cFWI);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 10;
    MfComData.mf_data[0] = AT88RF020_READ|0x10;
    MfComData.mf_data[1] = addr;
    
    status = PCD_comm_trans(pi);
    
    if ((status==MI_OK) && (MfComData.mf_leng==0x50))
    {   memcpy(readdata, &MfComData.mf_data[2], 8);    }
    else
    {   status = MI_COMM_ERR;   }
    
    return status;
}

/////////////////////////////////////////////////////////////////////
//写AT88RF020一页数据
//input :addr=页地址
//       writedata=要写入的8字节数据
/////////////////////////////////////////////////////////////////////
char At88rf020Write(unsigned char addr,unsigned char *writedata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(g_cFWI);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 10;
    MfComData.mf_data[0] = AT88RF020_WRITE|0x10;
    MfComData.mf_data[1] = addr;
    memcpy(&MfComData.mf_data[2], writedata, 8);    

    status = PCD_comm_trans(pi);
    
    if ((MfComData.mf_data[1]&0x01) || (MfComData.mf_leng!=0x10))
    {    status = MI_COMM_ERR;    }
    
    return status;
}
/////////////////////////////////////////////////////////////////////
//AT88RF020一LOCK
//input :lockdata=4字节数据
/////////////////////////////////////////////////////////////////////
char At88rf020Lock(unsigned char *lockdata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(g_cFWI);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 10;
    MfComData.mf_data[0] = AT88RF020_LOCK|0x10;
    MfComData.mf_data[1] = 0;
    memcpy(&MfComData.mf_data[2], lockdata, 4);    

    status = PCD_comm_trans(pi);
    
    if ((MfComData.mf_data[1]&0x01) || (MfComData.mf_leng!=0x10))
    {    status = MI_COMM_ERR;    }
    
    return status;
}
/////////////////////////////////////////////////////////////////////
//AT88RF020计数操作
//input :signature = 6字节签名信息
/////////////////////////////////////////////////////////////////////
char At88rf020Count(unsigned char *signature)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(g_cFWI);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 10;
    MfComData.mf_data[0] = AT88RF020_COUNT|0x10;
    MfComData.mf_data[1] = 0;
    memcpy(&MfComData.mf_data[4], signature, 6);
    
    status = PCD_comm_trans(pi);
    
    if((MfComData.mf_data[1]&0x01) || (MfComData.mf_leng!=0x10))
    {    status = MI_COMM_ERR;    }
    
    return status;
}
/////////////////////////////////////////////////////////////////////
//AT88RF020进入HALT状态
/////////////////////////////////////////////////////////////////////
char At88rf020Deselect(void)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;

    PCD_set_TMO(g_cFWI);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 10;
    MfComData.mf_data[0] = AT88RF020_DESELECT|0x10;
    
    status = PCD_comm_trans(pi);
    if((MfComData.mf_data[1]&0x01) || (MfComData.mf_leng!=0x10))
    {    status = MI_COMM_ERR;    }
    
    return status;
}

//////////////////////////////////////////////////////////////////////
//激活
//////////////////////////////////////////////////////////////////////
char SelectSR(unsigned char *Chip_ID)
{
    char  status = MI_OK;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;

    clr_bit_mask(REG_CTRL,0x08);         // disable crypto 1 unit   
    
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 2;
    MfComData.mf_data[0] = 6;     	       
    MfComData.mf_data[1] = 0;                
    
    status = PCD_comm_trans(pi);

    if (status!=MI_OK && status!=MI_NOTAG_ERR) 
    {   status = MI_COLL_ERR;   }          // collision occurs
    
    if(MfComData.mf_leng != 8)
    {   status = MI_COMM_ERR;   }
    
    if (status == MI_OK)
    {	
         PCD_set_TMO(5);
         MfComData.mf_comm = PCD_TRANSCEIVE;
         MfComData.mf_leng  = 2;
         MfComData.mf_data[1] = MfComData.mf_data[0];     	       
         MfComData.mf_data[0] = 0x0E;                 
         
         status = PCD_comm_trans(pi); 
         
         if (status!=MI_OK && status!=MI_NOTAG_ERR)  // collision occurs
         {   status = MI_COLL_ERR;   }               // collision occurs
         if (MfComData.mf_leng != 8) 
         {   status = MI_COMM_ERR;     }
         if (status == MI_OK)
         {  *Chip_ID = MfComData.mf_data[0];  }
    } 	
    
    return status;
}  

//////////////////////////////////////////////////////////////////////
//SR176卡读块
//////////////////////////////////////////////////////////////////////
char ReadSR176(unsigned char addr,unsigned char *readdata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 2;
    MfComData.mf_data[0] = 8;
    MfComData.mf_data[1] = addr;
  
    status = PCD_comm_trans(pi);
  
    if ((status==MI_OK) && (MfComData.mf_leng!=16))
    {   status = MI_BIT_COUNT_ERR;    }
    if (status == MI_OK)
    {
        *readdata     = MfComData.mf_data[0];
        *(readdata+1) = MfComData.mf_data[1];
    }
    return status;  
}  
//////////////////////////////////////////////////////////////////////
//SR176卡写块
//////////////////////////////////////////////////////////////////////
char WriteSR176(unsigned char addr,unsigned char *writedata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;

    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSMIT;
    MfComData.mf_leng  = 4;
    MfComData.mf_data[0] = 9;
    MfComData.mf_data[1] = addr;
    MfComData.mf_data[2] = *writedata;
    MfComData.mf_data[3] = *(writedata+1);
    status = PCD_comm_trans(pi);
    return status;  
}      

//////////////////////////////////////////////////////////////////////
//取SR176卡块锁定状态
//////////////////////////////////////////////////////////////////////                            
char GetProtSR176(unsigned char lockreg)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSMIT;
    MfComData.mf_leng  = 2;
    MfComData.mf_data[0] = 8;
    MfComData.mf_data[1] = 0x0f;
    status = PCD_comm_trans(pi);
    if (status == MI_OK) { lockreg = MfComData.mf_data[1];  }
    return status;  
}   	
//////////////////////////////////////////////////////////////////////
//SR176卡块锁定
//////////////////////////////////////////////////////////////////////
char ProtectSR176(unsigned char lockreg)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSMIT;
    MfComData.mf_leng  = 4;
    MfComData.mf_data[0] = 9;
    MfComData.mf_data[1] = 0x0F;
    MfComData.mf_data[2] = 0;
    MfComData.mf_data[3] = lockreg;
    status = PCD_comm_trans(pi);
    return status;  
}   

//////////////////////////////////////////////////////////////////////
//COMPLETION ST
//////////////////////////////////////////////////////////////////////
char CompletionSR(void)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSMIT;
    MfComData.mf_leng  = 1;
    MfComData.mf_data[0] = 0x0F;
    status = PCD_comm_trans(pi);
    return status;  
}                                          

//////////////////////////////////////////////////////////////////////
//SRIX4K卡读块
//////////////////////////////////////////////////////////////////////
char ReadSR4K(unsigned char addr,unsigned char *readdata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 2;
    MfComData.mf_data[0] = 8;
    MfComData.mf_data[1] = addr;
    status = PCD_comm_trans(pi);
    if (status!=MI_OK) status = MI_COLL_ERR; // collision occurs
    if (MfComData.mf_leng!=32) status = MI_COMM_ERR;
    if (status == MI_OK)
    {
        *readdata     = MfComData.mf_data[0];
        *(readdata+1) = MfComData.mf_data[1];
        *(readdata+2) = MfComData.mf_data[2];
        *(readdata+3) = MfComData.mf_data[3];
    }
    return status;  
}

//////////////////////////////////////////////////////////////////////
//SR176卡写块
//////////////////////////////////////////////////////////////////////
char WriteSR4K(unsigned char addr,unsigned char *writedata)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSMIT;
    MfComData.mf_leng  = 6;
    MfComData.mf_data[0] = 9;
    MfComData.mf_data[1] = addr;
    MfComData.mf_data[2] = *writedata;
    MfComData.mf_data[3] = *(writedata+1);
    MfComData.mf_data[4] = *(writedata+2);
    MfComData.mf_data[5] = *(writedata+3);
    status = PCD_comm_trans(pi);
    return status;  
} 

//////////////////////////////////////////////////////////////////////
//SR176卡鉴别
//////////////////////////////////////////////////////////////////////
char AuthSR4K(unsigned char *rnd,unsigned char *sig)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    PCD_set_TMO(9);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 7;
    MfComData.mf_data[0] = 0x0A;
    memcpy(&MfComData.mf_data[1], rnd, 6);
    
    status = PCD_comm_trans(pi);
    
    if (status!=MI_OK) status = MI_COLL_ERR; // collision occurs
    if (MfComData.mf_leng!=24) status=MI_COMM_ERR;
    if (status == MI_OK)
    {
        * sig    = MfComData.mf_data[0];
        *(sig+1) = MfComData.mf_data[1];
        *(sig+2) = MfComData.mf_data[2];
    }
    return status;  
}  

//////////////////////////////////////////////////////////////////////
//SR176卡读UID
//////////////////////////////////////////////////////////////////////
char GetUIDSR4K(unsigned char *UID)
{
    signed char status;
    unsigned char i;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(5);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 1;
    MfComData.mf_data[0] = 0x0B;
 
    status = PCD_comm_trans(pi);

    if (MfComData.mf_leng!=64) status = MI_COMM_ERR;
    if (status == MI_OK)
    {
        for(i=0;i<8;i++)
        {  *(UID+7-i) = MfComData.mf_data[i];  }
    }
    return status;  
}                                         



//////////////////////////////////////////////////////////////////////
//ISO14443 DESELECT
//////////////////////////////////////////////////////////////////////
char CL_Deselect(unsigned char CID)
{
    signed char status;
    struct trans_buff MfComData;
    struct trans_buff *pi;
    pi = &MfComData;
    
    PCD_set_TMO(4);
    MfComData.mf_comm = PCD_TRANSCEIVE;
    MfComData.mf_leng  = 2;
    MfComData.mf_data[0] = 0xca;
    MfComData.mf_data[1] = CID;
    status = PCD_comm_trans(pi);
    return status;
}


