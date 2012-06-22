function JuiceStart( dDurationMs )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;

iTimeTicks = dDurationMs / g_dTsTicksToMs;
g_ExpData.hDev.SetTargetVal('JuiceDurTicks', iTimeTicks);

% g_hTimeSync.SoftTrg(5);
g_ExpData.hDev.SetTargetVal('Trig5',1);
g_ExpData.hDev.SetTargetVal('Trig5',0);
