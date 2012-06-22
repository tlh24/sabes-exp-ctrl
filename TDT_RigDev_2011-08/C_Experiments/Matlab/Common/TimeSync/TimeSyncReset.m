function TimeSyncReset

ExperimentGlobalsInclude;

g_ExpData.hDev.SetTargetVal('RecordingGateIn', 0);   % clear record bit
g_ExpData.hDev.SetTargetVal('PauseGateIn', 0); % clear pause bit

% SoftTrg(1);  % reset triggers/counters
g_ExpData.hDev.SetTargetVal('Trig1', 1);
g_ExpData.hDev.SetTargetVal('Trig1', 0);
