function EyeTrackClearTiming( )

ExperimentGlobalsInclude;

% Toggle Reset bit
g_ExpData.hDev.SetTargetVal('EyeTimeRst', 1);
pause(0.1);
g_ExpData.hDev.SetTargetVal('EyeTimeRst', 0);
