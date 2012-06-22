function dTimeSec = JuiceGetTotalTimeSec()

TimeSyncGlobalsInclude;
ExperimentGlobalsInclude;

iTime = g_ExpData.hDev.GetTargetVal('JuiceTotTimeTicks');
dTimeSec = iTime * g_dTsTicksToMs / 1000;
