
strDataDir = 'D:\DataTmp\SpikeTimes00\';
strFile = 'SpikeTimes001';
% strFile = 'SpikeTimes002';
% strFile = 'SpikeTimes003';

strMatFile = [strDataDir strFile];
load(strMatFile);
dExtJuiceOnTimes = dExtJuiceOnTimes/1000;
% dExtJuiceOnTimes = dExtJuiceOnTimes(1:end-1)/1000; % remove extra in file 3

strNevFile = [strDataDir strFile '.nev'];
NevSaveSpikeTimes( strNevFile, dRecordingSyncTimes(end)/1000 );

strSpikesFile = [strDataDir strFile '_SpikeArray.mat'];
load(strSpikesFile);

idx = find(SpikeArray(:,1) == 27);
dSpikeTimes = SpikeArray(idx,3)';

dTotalTime = dSpikeTimes(end) - dSpikeTimes(1) 

dTimeDiff = dSpikeTimes - dExtJuiceOnTimes;

figure;
hist(dTimeDiff*1e3);