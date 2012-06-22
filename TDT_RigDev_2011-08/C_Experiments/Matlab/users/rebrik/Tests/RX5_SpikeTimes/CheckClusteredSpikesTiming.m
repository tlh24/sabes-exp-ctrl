load('RP2_Events');

strTank = 'Try00';
iBlock = input('Enter block number: ');
iLocationID = 1;
strDataDir = 'K:\Data\Try00\';
SpikeArr = RX5_GetClusteredSpikes( strTank, iBlock, iLocationID, strDataDir );

ChnlIdx = find(SpikeArr(:,2) == 1);
dSpTS_Tank = SpikeArr(ChnlIdx,1);
SpIdxTank = find(dSpTS_Tank>dRecOnTS);
dSpTS_Tank = dSpTS_Tank(SpIdxTank);

% %----- for block-52 throw away 2 glitches
dSpTS_Tank = dSpTS_Tank([1:1279 1281:end]);
% %-----


SpIdx = find(dExtTS>dRecOnTS);
dSpTS_RP2 = dExtTS(SpIdx);
dSpTS_RP2 = dSpTS_RP2(1:length(dSpTS_Tank))';


TimeDiffMs = (dSpTS_Tank - dSpTS_RP2)*1000;

figure;
plot(TimeDiffMs);

figure;
hist(TimeDiffMs);


fprintf('Delay (ms): %g\n', mean(TimeDiffMs));
fprintf('Delay std: %g\n', std(TimeDiffMs));
fprintf('Min delay (ms): %g\n', min(TimeDiffMs));
fprintf('Max delay (ms): %g\n', max(TimeDiffMs));
fprintf('Max-min delay (ms): %g\n', max(TimeDiffMs) - min(TimeDiffMs));
