
strFileName = 'D:\DataTmp\SerTest007.nev';

[dTS, strTags, strValues] = NevGetStream( strFileName );
[dSerialTS, dTimeSyncGlobal] = NevGetTimeSync( dTS, strTags, strValues );

[dRP2_SyncUpTS dRP2_SyncDwnTS ...
          dRecOnTS dRecOffTS ...
          dPauseOnTS dPauseOffTS ...
          dRecSyncTS dTimeSyncTS]  =  NevGetParsedDigInEvents( strFileName );
        
% hist(diff(dTimeSyncTS*1000) - diff(dTimeSyncGlobal));
% 
% plot(dTimeSyncGlobal, dTimeSyncTS, '.');

dC0 = dTimeSyncGlobal(1);
dC1 = (dTimeSyncGlobal(end) - dTimeSyncGlobal(1))/(dTimeSyncTS(end) - dTimeSyncTS(1));
dC0 = dTimeSyncGlobal(1);
dCalcTime = dC0 + dC1 * (dTimeSyncTS - dTimeSyncTS(1));

figure;
plot(dTimeSyncGlobal - dCalcTime);
