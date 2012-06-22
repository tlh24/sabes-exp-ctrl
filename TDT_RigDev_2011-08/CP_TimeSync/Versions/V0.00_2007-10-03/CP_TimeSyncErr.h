#ifndef CP_TDT_Err_H
#define CP_TDT_Err_H


// Error codes
#define CP_NO_ERR              0

#define ERR_BASE            2000
#define NOT_IDLE_ERR        (ERR_BASE+1)

#define MEM_ALLOC_ERR       (ERR_BASE+10)
#define THREAD_INIT_ERR     (ERR_BASE+11)

#define FILE_OPEN_ERR       (ERR_BASE+20)
#define FILE_WRITE_ERR      (ERR_BASE+21)
#define FILE_READ_ERR       (ERR_BASE+22)
#define NO_OPEN_FILE_ERR    (ERR_BASE+23)

#define CREATE_MUTEX_ERR    (ERR_BASE+30)
#define SERVER_INSTANCE_ERR (ERR_BASE+31)

#endif //#ifndef CP_TDT_Err_H
