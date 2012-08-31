

% strFileName = 'D:\DataTmp\RecTime03\RecTime001.nev';
% strFileName = 'D:\DataTmp\RecTime00\RecTime001.nev';
strFileName = 'D:\DataTmp\E071031_M1001.nev'

TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod

[dEventTS, dEventValue] = NevGetDigInEvents( strFileName );

% RP2 Sync events
dMaskedEvents =  bitand(dEventValue, 1);  % keep the RP2_SyncBit only
RP2_SyncIdx = find(diff( dMaskedEvents ) == 1);
nRP2_Sync = length(RP2_SyncIdx);
if nRP2_Sync 
  fprintf('Found %d RP2 sync events\n', nRP2_Sync);
  dRP2_SyncTS = dEventTS(RP2_SyncIdx+1);
end

% RP2_SyncIdx = find(diff( dMaskedEvents ) == -1);
% nRP2_Sync = length(RP2_SyncIdx);
% if nRP2_Sync 
%   fprintf('Found %d RP2 sync events\n', nRP2_Sync);
%   RP2_SyncTS = dEventTS(RP2_SyncIdx+1);
% end


% Recording on/off events
dMaskedEvents =  bitand(dEventValue, 2);  % keep the RecordingBit only

RecOnIdx = find(diff( dMaskedEvents ) == 2);
nRecOn = length(RecOnIdx);
if nRecOn 
  fprintf('Found %d RecOff events\n', nRecOn );
  dRecOnTS = dEventTS(RecOnIdx+1);
end

RecOffIdx = find(diff( dMaskedEvents ) == -2);
nRecOff = length(RecOffIdx);
if nRecOff 
  fprintf('Found %d RecOff events\n', nRecOff );
  dRecOffTS = dEventTS(RecOffIdx+1);
end

% Pause on/off events
dMaskedEvents =  bitand(dEventValue, 4);  % keep the PauseBit only
PauseOnIdx = find(diff( dMaskedEvents ) == 4);
nPauseOn = length(PauseOnIdx);
if nPauseOn 
  fprintf('Found %d PauseOn events\n', nPauseOn );
  dPauseOnTS = dEventTS(PauseOnIdx+1);
end

PauseOffIdx = find(diff( dMaskedEvents ) == -4);
nPauseOff = length(PauseOffIdx);
if nPauseOff 
  fprintf('Found %d PauseOff events\n', nPauseOff );
  dPauseOffTS = dEventTS(PauseOffIdx+1);
end

% Recording sync events
dMaskedEvents =  bitand(dEventValue, 8);  % keep the RecSyncBit only
RecSyncIdx = find(diff( dMaskedEvents ) == 8);
nRecSync = length(RecSyncIdx);
if nRecSync 
  fprintf('Found %d RP2 sync events\n', nRecSync );
  dRecSyncTS = dEventTS(RecSyncIdx+1);
end

% dCerebusDuration =  RP2_SyncTS(end) - RP2_SyncTS(1); % in seconds
% dGlobPeriod = iGlobTickPeriod/dGlobClockHz;
% dGlobDuration = dGlobPeriod * ( length(RP2_SyncTS) - 1); % duration in RP2 time (sec)
% 
% dGlobRecSyncTS = dRecordingSyncTimes/1000; % convert to seconds
% 
% dTS_c1 = dGlobDuration/dCerebusDuration;
% dTS_c0 = dGlobRecSyncTS - dRecSyncTS;
% 
% 
