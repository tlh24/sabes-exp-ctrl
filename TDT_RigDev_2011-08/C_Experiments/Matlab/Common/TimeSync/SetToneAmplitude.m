function SetToneAmplitude( ToneAmp  )

ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;
ServerNamesInclude;

g_ExpData.hDev.SetTargetVal([strTDTDevice,'.ToneAmp'], ToneAmp);
g_ExpData.hDev.GetTargetVal([strTDTDevice,'.ToneAmp']);

