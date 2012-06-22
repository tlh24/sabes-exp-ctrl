strTank = 'Calvin';
iLocationID = 1;
strDataDir = 'C:\Data\';
iChannelList = [1];

iBlock = 25;                                % Name of TDT Block
dataset = 'Reach_Calvin-14-Dec-2007-1.mat'; %name of dataset corresponding to recording
rcdset = 7;                                 %which recording start time corresponds to this block
endrec = 725;                               %what was last trial recording for
eval(sprintf('load %s',dataset));

events = cat(1,DATA(:).matlabeventlog);
events = unique(events,'rows');
[srt ind] = sort(events(:,2));
events = events(ind,:);

recordstart = Params.EventCodes.Recording_Start;
recordstop  = Params.EventCodes.Trial_Stop;


dGlobRecStartTS = events((events(:,1)==recordstart),2);
dRec_Start = dGlobRecStartTS(rcdset);
dTS_Start = dRec_Start;

dRecStop = events((events(:,1)==recordstop),2);
dTS_Stop = dRecStop(endrec);

RX5_SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
                iChannelList, dTS_Start, dTS_Stop, ...
                dRec_Start);
 