function dTimeMs = TimeSyncGetTimeMs()

ExperimentGlobalsInclude;

iTime = g_ExpData.hDev.GetTargetVal('TimeTicks');
dTimeMs = iTime * g_dTsTicksToMs;
