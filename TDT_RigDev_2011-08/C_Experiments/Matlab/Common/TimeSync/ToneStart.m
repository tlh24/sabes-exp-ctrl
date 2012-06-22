function ToneStart( dFreqHz, dDurationSec  )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;

g_ExpData.hDev.SetTargetVal('ToneFreqHz', dFreqHz);

iTimeTicks = dDurationSec * 1000 / g_dTsTicksToMs;
g_ExpData.hDev.SetTargetVal('ToneDurTicks', iTimeTicks);

% g_hTimeSync.SoftTrg(3);
g_ExpData.hDev.SetTargetVal('Trig3',1);
g_ExpData.hDev.SetTargetVal('Trig3',0);
