function TrackerClearTiming( )

ExperimentGlobalsInclude;

% Toggle Reset bit
g_ExpData.hDev.SetTargetVal('TrackTimeRst', 1);
pause(0.1);
g_ExpData.hDev.SetTargetVal('TrackTimeRst', 0);

