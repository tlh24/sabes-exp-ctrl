strFileNameBase = 'D:\DataTmp\RecTime04\RecTime';
load('RP2_RecordingTimes_04.mat');


nRuns = 100

TimeSyncConfigInclude;
dRP2_delay = 12000/dGlobClockHz;
for iRun = 1:nRuns
  strFileName = sprintf('%s%03d.nev',strFileNameBase, iRun);
  [dEventTS, dEventValue] = CerebusReadDigInEvents( strFileName );

  dBit3Events =  bitand(dEventValue, 8);
  Bit3EventIdx = find(dBit3Events==8);
  Bit3EventIdx = Bit3EventIdx(1);
  dRecSyncTS = dEventTS(Bit3EventIdx);
  dRecDelay(iRun) = dRP2_delay - dRecSyncTS;
end


OkIdx = find(dRecDelay<50e-3);

dDelayMs = dRecDelay(OkIdx) * 1e3;


fprintf('Delay (ms): %g\n', mean(dDelayMs));
fprintf('Delay std: %g\n', std(dDelayMs));
fprintf('Min delay (ms): %g\n', min(dDelayMs));
fprintf('Max delay (ms): %g\n', max(dDelayMs));
fprintf('Max-min delay (ms): %g\n', max(dDelayMs) - min(dDelayMs));


hist(dDelayMs,20);

dBit1Idx =  find( diff( dEventValue ) == 1);
dBit1Idx = dBit1Idx + 1;  % diff is off by 1
dRp2_Period = dEventTS(dBit1Idx(2))  - dEventTS(dBit1Idx(1));