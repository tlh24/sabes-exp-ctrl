function SpikeArray = TankGetSpikeTimesLocal(strTank, iBlock)
% function SpikeArray = TankGetSpikeTimes(strTank, iBlock )
%
% Read snippets from Tank and return time, channel, cluster 
% 
% INPUT:
%   strTank - tank name (string)
%   iBlock - iBlock number (integer)
%
% OUTPUT:
% The array SpikeArray(:,3)
%   where 
%     SpikeArray(:,1) -  the local timestamp
%     SpikeArray(:,2) -  input channel (electrode)
%     SpikeArray(:,3) -  cluster 
%

SpikeArray = [];

TankConfigInclude;  % Tank store strings are defined here

[hTank hFig] = TankOpen( strTank, iBlock);

nEventsMax = 1000000; % max number of events to read
iAllChnls   = 0;    % All Channels
iAllSortCodes  = 0;    % All Sorted Spikes Channels
dTimeStartAll = 0.0;
dTimeEndAll = 0.0;


iChannel = [];
iCluster = [];
dTS = [];

% Read the snippet events
nEvents = hTank.ReadEventsV( nEventsMax, strSnipStore, iAllChnls, iAllSortCodes, ...
                            dTimeStartAll, dTimeEndAll, 'NODATA');  % NODATA = don't get waveforms
if nEvents == nEventsMax
  warning('Got max number of %s events in ReadEventsV(), possible loss of data!\n', strSnipStore );
end

if nEvents > 0 
  fprintf('Got %d spikes\n', nEvents);
else 
  fprintf('Could not find any spikes in the tank\n');
  hTank.ReleaseServer;
  delete(hFig);
  return;
end



% Get channel
iChannel = hTank.ParseEvInfoV( 0, nEvents, 4); % 0 = startIdx, nEvents, 4 = get channel

% Get cluster
iCluster = hTank.ParseEvInfoV( 0, nEvents, 5); % 0 = startIdx, nEvents, 5 = get cluster

% Get timestamp
dTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, nEvents, 6 = get timestamp


hTank.CloseTank;
hTank.ReleaseServer;
delete(hFig);

SpikeArray(:,1) = dTS;
SpikeArray(:,2) = iChannel;
SpikeArray(:,3) = iCluster;






