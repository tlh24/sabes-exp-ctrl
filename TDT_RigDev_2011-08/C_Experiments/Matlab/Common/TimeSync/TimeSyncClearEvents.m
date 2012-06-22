function TimeSyncClearEvents

ExperimentGlobalsInclude;

% SoftTrg(2);  % reset counters
g_ExpData.hDev.SetTargetVal('Trig2', 1);
g_ExpData.hDev.SetTargetVal('Trig2', 0);
