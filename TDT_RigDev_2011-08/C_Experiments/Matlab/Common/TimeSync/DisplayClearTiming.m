function DisplayClearTiming( )

ExperimentGlobalsInclude;

% Toggle Reset bit
g_ExpData.hDev.SetTargetVal('DispTimeRst', 1);
pause(0.1);
g_ExpData.hDev.SetTargetVal('DispTimeRst', 0);
