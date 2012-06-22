function [nJuiceOnEvents dJuiceOnTimes nJuiceOffEvents dJuiceOffTimes] = ...
            JuiceGetEvents( )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;
          
nJuiceOnEvents = g_ExpData.hDev.GetTargetVal('JuiceOnCnt');
dJuiceOnTicks = g_ExpData.hDev.ReadTargetVEX('JuiceOnTimes',...
       0, nJuiceOnEvents,'I32','F64');
nJuiceOffEvents = g_ExpData.hDev.GetTargetVal('JuiceOffCnt');
dJuiceOffTicks = g_ExpData.hDev.ReadTargetVEX('JuiceOffTimes',...
       0, nJuiceOffEvents,'I32','F64');

dJuiceOnTimes = dJuiceOnTicks * g_dTsTicksToMs;
dJuiceOffTimes = dJuiceOffTicks * g_dTsTicksToMs;

