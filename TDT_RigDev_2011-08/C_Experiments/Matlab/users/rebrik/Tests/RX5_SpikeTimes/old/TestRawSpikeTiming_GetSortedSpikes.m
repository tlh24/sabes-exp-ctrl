

strTank = 'Try00';
iBlock = 29;
iLocationID = 1;
strDataDir = 'd:\tmp\';

strFileName = GetRawDataFilename( strTank, iBlock, iLocationID );


strConfFile = [strDataDir strFileName '_conf.mat'];
load(strConfFile);

strSpikesFile = [strDataDir strFileName '.mat'];
load(strSpikesFile);

SpikeArr = GetTankSpikes(strTank, iBlock, dGlobRecStartTS/1000);
dSnipTS = SpikeArr(:,1);  % in seconds


SnipIdx = find(dSnipTS>dTS_Start/1000 & dSnipTS < dTS_Stop/1000);
dSnipTS = dSnipTS(SnipIdx);


dSp_TS_bin = Channel01(:,1) + dFileStartTS/1000;
SpIdx = find(dSp_TS_bin>dTS_Start/1000 & dSp_TS_bin < dTS_Stop/1000);
dSp_TS_bin = dSp_TS_bin(SpIdx);


figure;
hist(diff(dSp_TS_bin - dSnipTS));
