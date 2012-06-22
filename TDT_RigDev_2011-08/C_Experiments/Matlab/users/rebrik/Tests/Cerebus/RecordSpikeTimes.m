% Cerebus is configured to start rec on bit 1 (mask=2)
% RecSyncEvent is sent to bit 3 (mask=8)


TimeSyncClearEvents;
RecordingStart;
disp('press any key to stop recording');
pause();
RecordingStop;
pause(0.1);

[nExtJuiceOnEvents dExtJuiceOnTimes nExtJuiceOffEvents dExtJuiceOffTimes] =  JuiceGetExtEvents;
[nRecordingSyncEvents dRecordingSyncTimes nRecordingOffEvents dRecordingOffTimes ...
 nPauseOnEvents dPauseOnTimes nPauseOffEvents dPauseOffTimes ] = ...
           RecordingGetEvents( );
         
         
fprintf('Got %d TTL-pulses\n', nExtJuiceOnEvents);         
save( 'SpikeTimes003', 'nExtJuiceOnEvents', 'dExtJuiceOnTimes', 'nRecordingSyncEvents', 'dRecordingSyncTimes' );