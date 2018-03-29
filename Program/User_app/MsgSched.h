#ifndef _MSGSCHED_H_
#define _MSGSCHED_H_

#define dim(x) (sizeof(x) / sizeof(x[0])) 

struct SCHED_CODE 
{              
	MSG_CODE code;          
	void (*Fxn)(MSG);
}; 

#define SAVE_STATE_MAX_NUM  10
typedef struct
{
	SYS_STATE state[SAVE_STATE_MAX_NUM];
	u8 num;
}BACKUP_STATE;


extern void SetCurrentState(SYS_STATE state);
extern SYS_STATE GetCurrentState(void);
extern void MsgSched(MSG msg);

extern ErrorStatus BackupState(SYS_STATE state);
extern ErrorStatus RestoreBackupState(SYS_STATE* state);
extern void RemoveBackupState(void);

#endif
