load('RP2_Events');


iBlock = input('Enter block number: ');
SpikeArr = RX5_GetTankSpikes('Try00', iBlock, dRecOnTS);
ChnlIdx = find(SpikeArr(:,2) == 1);
dSpTS_Tank = SpikeArr(ChnlIdx,1);
dSpTS_Tank = dSpTS_Tank - dRecOnTS;
SpIdxTank = find(dSpTS_Tank>0);
dSpTS_Tank = dSpTS_Tank(SpIdxTank);

% %----- for block-52 throw away 2 glitches
dSpTS_Tank = dSpTS_Tank([1:1110 1112:3786 3788:end]);
% %-----

dExtTS = dExtTS-dRecOnTS;
SpIdx = find(dExtTS>0);
dSpTS_RP2 = dExtTS(SpIdx);
dSpTS_RP2 = dSpTS_RP2';
dSpTS_RP2 = dSpTS_RP2(1:length(dSpTS_Tank));



TimeDiffMs = (dSpTS_RP2 - dSpTS_Tank)*1000;
figure;
hist(TimeDiffMs);

figure;
plot(TimeDiffMs);

fprintf('Delay (ms): %g\n', mean(TimeDiffMs));
fprintf('Delay std: %g\n', std(TimeDiffMs));
fprintf('Min delay (ms): %g\n', min(TimeDiffMs));
fprintf('Max delay (ms): %g\n', max(TimeDiffMs));
fprintf('Max-min delay (ms): %g\n', max(TimeDiffMs) - min(TimeDiffMs));
