

strTank = 'Try00';
iBlock = 39;
iLocationID = 1;
strDataDir = 'd:\tmp\';

strFileName = GetRawDataFilename( strTank, iBlock, iLocationID );


strConfFile = [strDataDir strFileName '_conf.mat'];
load(strConfFile);

SpikeArr = GetTankSpikes(strTank, iBlock, dGlobRecStartTS);

ChIdx = find(SpikeArr(:,2) == 1);  % find snips on ch 1
dSnipTS = SpikeArr(ChIdx, 1);  % in seconds

SnipIdx = find(dSnipTS>dTS_Start & dSnipTS < dTS_Stop);
dSnipTS = dSnipTS(SnipIdx);

SpikeArr_bin = GetClusteredSpikes( strTank, iBlock, iLocationID, strDataDir );
ChIdx = find(SpikeArr_bin(:,2) == 1);  % find spikes on ch 1


dSp_TS_bin = SpikeArr_bin(ChIdx,1);
SpIdx = find(dSp_TS_bin>dTS_Start & dSp_TS_bin < dTS_Stop);
dSp_TS_bin = dSp_TS_bin(SpIdx);

figure;
TimeDiffMks = (dSnipTS - dSp_TS_bin) * 1e6;
hist(TimeDiffMks);


fprintf('Delay (mks): %g\n', mean(TimeDiffMks));
fprintf('Delay std: %g\n', std(TimeDiffMks));
fprintf('Min delay (mks): %g\n', min(TimeDiffMks));
fprintf('Max delay (mks): %g\n', max(TimeDiffMks));
fprintf('Max-min delay (mks): %g\n', max(TimeDiffMks) - min(TimeDiffMks));
