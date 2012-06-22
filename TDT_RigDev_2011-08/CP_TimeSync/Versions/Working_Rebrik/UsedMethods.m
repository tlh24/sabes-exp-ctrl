g_hTimeSync.ConnectRP2(strTimeSyncInterface,iTimeSyncDevice);
iStatus = g_hTimeSync.GetStatus;
g_hTimeSync.ClearCOF;
g_hTimeSync.LoadCOF(strCofFile);
g_hTimeSync.ReadCOF(strCofFile); 
g_hTimeSync.Run;
g_hTimeSync.Halt;
dSampRateHz = g_hTimeSync.GetSFreq;
g_hTimeSync.SoftTrg(1);
g_hTimeSync.SetTagVal('DispTimeRst', 1);
nJuiceOnEvents = g_hTimeSync.GetTagVal('JuiceOnCnt');
dJuiceOnTicks = g_hTimeSync.ReadTagVEX('JuiceOnTimes',...
                  0,nJuiceOnEvents,'I32','F64',1);







    // Methods:
    HRESULT raw_GetError (
        BSTR * _result );
        
    HRESULT raw_Connect (
        long Interface,
        long DevNum,
        long * _result );
    HRESULT raw_SetTagVal (
        BSTR Name,
        float Val,
        long * _result );
    HRESULT raw_LoadCOF (
        BSTR FileName,
        long * _result );
    HRESULT raw_Run (
        long * _result );
    HRESULT raw_Halt (
        long * _result );
    HRESULT raw_SoftTrg (
        long Trg_Bitn,
        long * _result );
    HRESULT raw_GetTagVal (
        BSTR Name,
        float * _result );
    HRESULT raw_ReadTag (
        BSTR Name,
        float * pBuf,
        long nOS,
        long nWords,
        long * _result );
    HRESULT raw_WriteTag (
        BSTR Name,
        float * pBuf,
        long nOS,
        long nWords,
        long * _result );
    HRESULT raw_SendParTable (
        BSTR Name,
        float IndexID,
        long * _result );
    HRESULT raw_SendSrcFile (
        BSTR Name,
        long SeekOS,
        long nWords,
        long * _result );
    HRESULT raw_GetNames (
        BSTR NameList,
        long MaxNames,
        long ObjType,
        long * _result );
    HRESULT raw_ReadTagV (
        BSTR Name,
        long nOS,
        long nWords,
        VARIANT * _result );
    HRESULT raw_WriteTagV (
        BSTR Name,
        long nOS,
        const VARIANT & Buf,
        long * _result );
    HRESULT raw_GetTagSize (
        BSTR Name,
        long * _result );
    HRESULT raw_GetTagType (
        BSTR Name,
        long * _result );
    HRESULT raw_SetSrcFileName (
        BSTR Name,
        BSTR FileName,
        long * _result );
    HRESULT raw_GetNumOf (
        BSTR ObjTypeName,
        long * _result );
    HRESULT raw_GetNameOf (
        BSTR ObjTypeName,
        long Index,
        BSTR * _result );
    HRESULT raw_ReadCOF (
        BSTR FileName,
        long * _result );
    HRESULT raw_ConnectRP2 (
        BSTR IntName,
        long DevNum,
        long * _result );
    HRESULT raw_ConnectRL2 (
        BSTR IntName,
        long DevNum,
        long * _result );
    HRESULT raw_ConnectRA16 (
        BSTR IntName,
        long DevNum,
        long * _result );
    HRESULT raw_ReadTagVEX (
        BSTR Name,
        long nOS,
        long nWords,
        BSTR SrcType,
        BSTR DstType,
        long nChans,
        VARIANT * _result );
    HRESULT raw_GetStatus (
        long * _result );
    HRESULT raw_GetCycUse (
        long * _result );
    HRESULT raw_ClearCOF (
        long * _result );
    HRESULT raw_WriteTagVEX (
        BSTR Name,
        long nOS,
        BSTR DstType,
        const VARIANT & Buf,
        long * _result );
    HRESULT raw_ZeroTag (
        BSTR Name,
        long * _result );
    HRESULT raw_GetSFreq (
        float * _result );
    HRESULT raw_ConnectRV8 (
        BSTR IntName,
        long DevNum,
        long * _result );
    HRESULT raw_GetDevCfg (
        long Addr,
        long Width32,
        long * _result );
    HRESULT raw_SetDevCfg (
        long Addr,
        long Val,
        long Width32,
        long * _result );
    HRESULT raw_LoadCOFsf (
        BSTR FileName,
        float SampFreq,
        long * _result );
    HRESULT raw_DefStatus (
        long DefID,
        long * _result );
    HRESULT raw_GetDefData (
        long DefID,
        VARIANT * _result );
