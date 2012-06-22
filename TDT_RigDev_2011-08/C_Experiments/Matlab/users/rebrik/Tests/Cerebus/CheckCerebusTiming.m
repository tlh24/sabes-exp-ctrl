

strFileName = 'D:\DataTmp\RecTime03\RecTime001.nev';
load('RP2_EventTimes_01.mat');

TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod

[dEventTS, dEventValue] = CerebusReadDigInEvents( strFileName );

dEventValue = bitand(dEventValue, 15);
dMaskedEvents =  bitand(dEventValue, 8);  % keep the RecSyncBit only
RecSyncIdx = find(diff( dMaskedEvents ) == 8);
dRecSyncTS = dEventTS(RecSyncIdx+1);

dMaskedEvents =  bitand(dEventValue, 1);  % keep the RP2_SyncBit only
RP2_SyncIdx = find(diff( dMaskedEvents ) == 1);
RP2_SyncTS = dEventTS(RP2_SyncIdx+1);

dCerebusDuration =  RP2_SyncTS(end) - RP2_SyncTS(1); % in seconds
dGlobPeriod = iGlobTickPeriod/dGlobClockHz;
dGlobDuration = dGlobPeriod * ( length(RP2_SyncTS) - 1); % duration in RP2 time (sec)

dGlobRecSyncTS = dRecordingSyncTimes/1000; % convert to seconds

dTS_c1 = dGlobDuration/dCerebusDuration;
dTS_c0 = dGlobRecSyncTS - dRecSyncTS;

dMaskedEvents =  bitand(dEventValue, 4);  % keep the PauseBit only
PauseOnIdx = find(diff( dMaskedEvents ) == 4);
dPauseOnTS = dEventTS(PauseOnIdx+1);

PauseOffIdx = find(diff( dMaskedEvents ) == -4);
dPauseOffTS = dEventTS(PauseOffIdx+1);

dPauseOnGTS = dPauseOnTS * dTS_c1 + dTS_c0;
dOnTS_diff = dPauseOnGTS - (dPauseOnTimes'/1000);
dOnTS_diff = dOnTS_diff * 1e6

dPauseOffGTS = dPauseOffTS * dTS_c1 + dTS_c0;
dOffTS_diff = dPauseOffGTS - (dPauseOffTimes(2:end-1)'/1000);
dOffTS_diff = dOffTS_diff * 1e6

