function [nExtJuiceOnEvents dExtJuiceOnTimes nExtJuiceOffEvents dExtJuiceOffTimes] = ...
            JuiceGetExtEvents( )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;
          
nExtJuiceOnEvents = g_ExpData.hDev.GetTargetVal('ExtJuiceOnCnt');
dExtJuiceOnTicks = g_ExpData.hDev.ReadTargetVEX('ExtJuiceOnTimes',...
       0, nExtJuiceOnEvents,'I32','F64');
nExtJuiceOffEvents = g_ExpData.hDev.GetTargetVal('ExtJuiceOffCnt');
dExtJuiceOffTicks = g_ExpData.hDev.ReadTargetVEX('ExtJuiceOffTimes',...
       0, nExtJuiceOffEvents,'I32','F64');

dExtJuiceOnTimes = dExtJuiceOnTicks * g_dTsTicksToMs;
dExtJuiceOffTimes = dExtJuiceOffTicks * g_dTsTicksToMs;

