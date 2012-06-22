#ifndef CP_DAQ_Err_H
#define CP_DAQ_Err_H


// Error codes
#define CP_NO_ERR              0


// CP_DAQ_Engine
#define EN_ERR_BASE            2000
#define EN_IS_WRITING_ERR      (EN_ERR_BASE+1)
#define EN_NOT_WRITING_ERR     (EN_ERR_BASE+2)
#define EN_IS_RUNNING_ERR      (EN_ERR_BASE+3)
#define EN_NOT_RUNNING_ERR     (EN_ERR_BASE+4)
#define EN_COM_FUNC_ERR        (EN_ERR_BASE+5)
#define EN_INVAL_PARAM_ERR     (EN_ERR_BASE+6)
#define EN_TIMEOUT_ERR         (EN_ERR_BASE+7)
#define EN_DLL_LOAD_ERR        (EN_ERR_BASE+8)

#define EN_MEM_ALLOC_ERR       (EN_ERR_BASE+10)
#define EN_THREAD_INIT_ERR     (EN_ERR_BASE+11)
#define EN_NO_ENGINE_ERR       (EN_ERR_BASE+12)

#define EN_FILE_OPEN_ERR       (EN_ERR_BASE+20)
#define EN_FILE_WRITE_ERR      (EN_ERR_BASE+21)
#define EN_FILE_READ_ERR       (EN_ERR_BASE+22)
#define EN_NO_OPEN_FILE_ERR    (EN_ERR_BASE+23)


#define EN_CREATE_MUTEX_ERR    (EN_ERR_BASE+30)
#define EN_SERVER_INSTANCE_ERR (EN_ERR_BASE+31)

// MCastSrv
#define MCS_ERR_BASE           3000
#define MCS_WINSOCK_ERR        (MCS_ERR_BASE+1)
#define MCS_SOCK_FUNC_ERR      (MCS_ERR_BASE+2)
#define MCS_INVAL_SOCK_ERR     (MCS_ERR_BASE+3)
#define MCS_PACKET_SIZE_ERR    (MCS_ERR_BASE+4)
#define MCS_INCOMPL_SEND_ERR   (MCS_ERR_BASE+5)
#define MCS_SEND_ERR           (MCS_ERR_BASE+6)
#define MCS_IS_ON_ERR          (MCS_ERR_BASE+7)
#define MCS_IS_OFF_ERR         (MCS_ERR_BASE+8)

#endif //#ifndef CP_DAQ_Err_H
