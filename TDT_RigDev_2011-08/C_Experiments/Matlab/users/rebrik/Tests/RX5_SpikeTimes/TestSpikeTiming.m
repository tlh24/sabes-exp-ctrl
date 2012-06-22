
fprintf('Starting recording on RX5\n');

RecordingStart;
nSeconds = 60;

for i=1:nSeconds
 pause(1);
 fprintf('%d sec of %d\n', i, nSeconds);
end
RecordingStop;

fprintf('Stopped recording on RX5\n');
pause(0.2);
[nExtTS dExtTS] = JuiceGetExtEvents;
[nRecOn, dRecOnTS, nRecOff, dRecOffTS] = RecordingGetEvents;
iBlock = input('Enter block number: ');
dBeginTS = dRecOnTS(end);
dEndTS = dRecOffTS(end);
SpIdx = find(dExtTS>dBeginTS & dExtTS < dEndTS);
dSpTS = dExtTS(SpIdx);
SpikeArr = GetTankSpikes('Try00', iBlock, dBeginTS/1000);
ChnlIdx = find(SpikeArr(:,2) == 1);
dSpTS_Tank = SpikeArr(ChnlIdx,1)*1000;
SpIdxTank = find(dSpTS_Tank>dBeginTS & dSpTS_Tank < dEndTS);
dSpTS_Tank = dSpTS_Tank(SpIdxTank)';
figure;
TimeDiffMs = dSpTS_Tank - dSpTS;
hist(TimeDiffMs);


fprintf('Delay (ms): %g\n', mean(TimeDiffMs));
fprintf('Delay std: %g\n', std(TimeDiffMs));
fprintf('Min delay (ms): %g\n', min(TimeDiffMs));
fprintf('Max delay (ms): %g\n', max(TimeDiffMs));
fprintf('Max-min delay (ms): %g\n', max(TimeDiffMs) - min(TimeDiffMs));
