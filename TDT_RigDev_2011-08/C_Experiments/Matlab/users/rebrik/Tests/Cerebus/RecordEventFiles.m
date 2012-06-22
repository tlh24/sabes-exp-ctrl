% Test script to start/stop daq
% Cerebus is configured to start rec on bit 1 (mask=2)
% Pause is used for RecStartEvent bit2 (mask=4)
% RecSyncEvent is sent to bit 3 (mask=8)

nEvents = 30
RecordingStart;
pause(0.5);
for iEvent = 1:nEvents
  fprintf('    Event %d of %d\n', iEvent, nEvents);
  RecordingPause;
  pause(0.75);
  RecordingResume;
  pause(0.25);
end
RecordingStop;
pause(0.1);

[nRecordingSyncEvents dRecordingSyncTimes nRecordingOffEvents dRecordingOffTimes ...
 nPauseOnEvents dPauseOnTimes nPauseOffEvents dPauseOffTimes ] = ...
           RecordingGetEvents( );
         
save RP2_EventTimes_01