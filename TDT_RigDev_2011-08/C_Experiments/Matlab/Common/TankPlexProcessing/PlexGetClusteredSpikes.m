function SpikeArray = PlexGetClusteredSpikes( strTank, iBlock, iLocationID, strDataDir )

% strTank = 'Try00';
% iBlock = 29;
% iLocationID = 1;
% strDataDir = 'd:\tmp\';

SpikeArray = [];

strFileName = TankGetRawDataFilename( strTank, iBlock, iLocationID );
strSpikesFile = [strDataDir strFileName '.mat'];
strConfFile = [strDataDir strFileName '_conf.mat'];


ChnlStruct = load(strSpikesFile);
ChnlNames = fieldnames(ChnlStruct);
nChannels = length(ChnlNames);

if nChannels < 1 
  warning('No spike channels found, spike array is empty!');
  return
end

% concatenate all channels into one array
SpArr = [];
for iChnl = 1:nChannels
  SpArr = [SpArr; getfield(ChnlStruct, ChnlNames{iChnl})];
end
% clear ChnlStruct;

load(strConfFile);


% remap channels (column 2) back to the DAQ numbering
iDaqCh = iChannelList(SpArr(:,2));
SpArr(:,2) = iDaqCh;

[tmp SortIdx] = sort(SpArr(:,1));  % sort by timestamp 

SpikeArray = [SpArr(SortIdx,1) SpArr(SortIdx,2) SpArr(SortIdx,3)];

SpikeArray(:,1) = SpikeArray(:,1) * dTS_c1 + dFileStartTS;  % convert to global time
% 
% 
% 
% dSp_TS_bin = Channel01(:,1) + dFileStartTS/1000;
% SpIdx = find(dSp_TS_bin>dTS_Start/1000 & dSp_TS_bin < dTS_Stop/1000);
% dSp_TS_bin = dSp_TS_bin(SpIdx);
