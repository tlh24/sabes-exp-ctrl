% Test script to start/stop daq
% Cerebus is configured to start rec on bit 1 (mask=2)
% Pause is used for RecStartEvent bit2 (mask=4)

nRuns = 100
for iRun = 1:nRuns
  fprintf('Run %d of %d\n', iRun, nRuns);
  RecordingStart;
  pause(4);
  RecordingStop;
  pause(2);
end

[nRecordingOnEvents dRecordingOnTimes nRecordingOffEvents dRecordingOffTimes ...
 nPauseOnEvents dPauseOnTimes nPauseOffEvents dPauseOffTimes ] = ...
           RecordingGetEvents( );
         
save RP2_RecordingTimes_04