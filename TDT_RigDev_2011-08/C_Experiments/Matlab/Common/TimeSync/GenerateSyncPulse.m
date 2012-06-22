function dTimeMs = GenerateSyncPulse()

ExperimentGlobalsInclude;

% SoftTrg(7);  
g_ExpData.hDev.SetTargetVal('Trig7', 1);
g_ExpData.hDev.SetTargetVal('Trig7', 0);

dTicks = g_ExpData.hDev.ReadTargetVEX('SyncPulseTime',0,1,'I32','F64');
dTimeMs = dTicks * g_dTsTicksToMs;

