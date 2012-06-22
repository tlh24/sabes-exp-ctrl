function RecordingStop( )

ExperimentGlobalsInclude;
DaqConfigInclude;

g_ExpData.hDev.SetTargetVal('RecordingGateIn', 0);   % clear record bit
g_ExpData.hDev.SetTargetVal('PauseGateIn', 0); % clear pause bit

if(blnUseRZ2_Daq)
  disp('RecordingStop: RZ2 recording starts and stops with TimeSyncStart/TimeSyncStop')
end