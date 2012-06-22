% Artifical spikes should be sent to the input of RA16
% RX5 should be in the preview mode
% Spikes should be thresholded in the workbench
% TTL sync pulses should be sent to JA8 on RP2 - external juice events
% Note: the width of the TTL pulse is insufficient to be 
% reliably recorded on RP2, use Frame counter as pulse extender


fprintf('Starting recording on RX5\n');
nSeconds = 1000;

TimeSyncClearEvents;
RecordingStart;

for i=1:nSeconds
 pause(1);
 if mod(i,10) == 0
   fprintf('%d sec of %d\n', i, nSeconds);
 end
end
RecordingStop;

fprintf('Stopped recording on RX5\n');
pause(0.2);
[nExtJuiceOnEvents dExtJuiceOnTimes nExtJuiceOffEvents dExtJuiceOffTimes] = JuiceGetExtEvents;
[nRecOn, dRecOnTS, nRecOff, dRecOffTS] = RecordingGetEvents;
dRecOnTS = dRecOnTS(end)/1000;
dExtTS = dExtJuiceOnTimes/1000;

save('RP2_Events',  'dExtTS', 'dRecOnTS', 'nSeconds');
