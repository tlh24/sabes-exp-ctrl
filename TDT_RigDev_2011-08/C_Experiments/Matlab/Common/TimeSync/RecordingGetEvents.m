function [nRecordingSyncEvents RecordingSyncTimes nRecordingOffEvents dRecordingOffTimes ...
          nPauseOnEvents dPauseOnTimes nPauseOffEvents dPauseOffTimes ] = ...
            RecordingGetEvents( )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;
          
nRecordingSyncEvents =  g_ExpData.hDev.GetTargetVal('RecSyncCnt');
dRecordingOnTicks = g_ExpData.hDev.ReadTargetVEX('RecSyncTimes',...
       0,nRecordingSyncEvents,'I32','F64');
nRecordingOffEvents = 0;

RecordingSyncTimes = dRecordingOnTicks * g_dTsTicksToMs;
dRecordingOffTimes = [];

nPauseOnEvents =  g_ExpData.hDev.GetTargetVal('PauseOnCnt');
dPauseOnTicks = g_ExpData.hDev.ReadTargetVEX('PauseOnTimes',...
       0,nPauseOnEvents,'I32','F64');
nPauseOffEvents =  g_ExpData.hDev.GetTargetVal('PauseOffCnt');
dPauseOffTicks = g_ExpData.hDev.ReadTargetVEX('PauseOffTimes',...
       0,nPauseOffEvents,'I32','F64');

dPauseOnTimes = dPauseOnTicks * g_dTsTicksToMs;
dPauseOffTimes = dPauseOffTicks * g_dTsTicksToMs;
