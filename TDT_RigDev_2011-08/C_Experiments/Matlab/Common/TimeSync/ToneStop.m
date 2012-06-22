function ToneStop( dFreqHz, dDurationSec)

ExperimentGlobalsInclude;

% g_hTimeSync.SoftTrg(4);
g_ExpData.hDev.SetTargetVal('Trig4',1);
g_ExpData.hDev.SetTargetVal('Trig4',0);
