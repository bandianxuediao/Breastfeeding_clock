#ifndef _CONNECTPROCESS_H_
#define _CONNECTPROCESS_H_

typedef enum 
{
    BLUETOOTH = 0x01,
	RS485,
	USB_HID,
	ADDED_DEV
}CONNECT_SRC;


extern void ConnectPro(MSG msg);

#endif
