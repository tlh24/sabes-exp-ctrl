clear
strTank = 'Calvin';
iLocationID = 1;
strDataDir = 'C:\Data\';
iChannelList = [1];


iBlock = 31;
dataset = 'Reach_Calvin-10-Jan-2008-1.mat';
rcdset = 2;
eval(sprintf('load %s',dataset));

events = cat(1,DATA(:).matlabeventlog);
events = unique(events,'rows');
[srt ind] = sort(events(:,2));
events = events(ind,:);

recordstart = Params.EventCodes.Recording_Start;


dGlobRecStartTS = events((events(:,1)==recordstart),2);
dTS_Start = dGlobRecStartTS(rcdset);


SpikeArray = RX5_GetTankSpikes(strTank, iBlock, dTS_Start);

eval(sprintf('save SpikeArray%d SpikeArray',iBlock))