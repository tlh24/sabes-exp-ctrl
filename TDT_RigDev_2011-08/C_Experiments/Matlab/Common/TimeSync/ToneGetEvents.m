function [nToneOnEvents dToneOnTimes nToneOffEvents dToneOffTimes] = ...
            ToneGetEvents( )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;
          
nToneOnEvents = g_ExpData.hDev.GetTargetVal('ToneOnCnt');
iToneOnTicks = g_ExpData.hDev.ReadTargetVEX('ToneOnTimes',...
        0,nToneOnEvents,'I32','F64');
nToneOffEvents = g_ExpData.hDev.GetTargetVal('ToneOffCnt');
iToneOffTicks = g_ExpData.hDev.ReadTargetVEX('ToneOffTimes',...
        0,nToneOffEvents,'I32','F64');

dToneOnTimes = double(iToneOnTicks) * g_dTsTicksToMs;
dToneOffTimes = double(iToneOffTicks) * g_dTsTicksToMs;

