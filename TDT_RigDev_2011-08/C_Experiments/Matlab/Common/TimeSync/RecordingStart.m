function RecordingStart( )

ExperimentGlobalsInclude;
DaqConfigInclude;

g_ExpData.hDev.SetTargetVal('RecordingGateIn', 1);

if(blnUseRZ2_Daq)
  disp('RecordingStart: RZ2 recording starts and stops with TimeSyncStart/TimeSyncStop')
end