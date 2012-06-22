function RecordingPause( )

ExperimentGlobalsInclude;
DaqConfigInclude;

g_ExpData.hDev.SetTargetVal('PauseGateIn', 1);

if(blnUseRZ2_Daq)
  disp('RecordingPause: RZ2 recording does not pause (use TimeSyncStop/TimeSyncStart)')
end
