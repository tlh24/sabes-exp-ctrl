% returns frame count and the tick for the latest frame
% we use channel 1 (JA1) for sync of the Display
function [dFrameCnt dFrameTimeMs ] = DisplayGetTiming( )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;

% Note on SerStore:
% Index is actually a counter of items. 
% To get the first value use Index = 0
% The value is valid when Index is > 0
% The latest value is at Index-1

dFrameCnt = g_ExpData.hDev.GetTargetVal('DispFrameCnt');

if dFrameCnt > 0
  dFrameIdx = mod(dFrameCnt-1, 256);
  dFrameTick = g_ExpData.hDev.ReadTargetVEX('DispFrameTimes',dFrameIdx, 1,'I32','F64');
  dFrameTimeMs = dFrameTick * g_dTsTicksToMs;
else
  dFrameTimeMs = NaN;
end

