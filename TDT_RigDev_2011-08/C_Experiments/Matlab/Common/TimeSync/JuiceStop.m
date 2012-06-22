function JuiceStop()
ExperimentGlobalsInclude;

% g_hTimeSync.SoftTrg(6);
g_ExpData.hDev.SetTargetVal('Trig6',1);
g_ExpData.hDev.SetTargetVal('Trig6',0);
