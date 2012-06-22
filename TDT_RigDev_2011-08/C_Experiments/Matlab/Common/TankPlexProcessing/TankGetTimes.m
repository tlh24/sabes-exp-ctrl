function [dRecSyncTS, dTimeSyncTS, dRP2_TickTS] = TankGetTimes(strTank, iBlock)

TankConfigInclude;  % using strStreamStore, strTimeSyncStore
StreamTagsInclude;  

nEventsMax = 1000000; % max number of events to read
iAllChnls   = 0;    % All Channels
iAllSortCodes  = 0;    % All Sorted Spikes Channels
dTimeStartAll = 0.0;
dTimeEndAll = 0.0;

dRecSyncTS = [];
dTimeSyncRX5 = [];


[hTank hFig] = TankOpen( strTank, iBlock);

dTankStartTime = hTank.CurBlockStartTime;   % absolute time relative to Jan 1st 1970
dTankStopTime = hTank.CurBlockStopTime;     % absolute time relative to Jan 1st 1970
fprintf('Total tank duration: %g\n', dTankStopTime - dTankStartTime);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read the RecordingSync event
nEvents = hTank.ReadEventsV( nEventsMax, strRecSyncStore, iAllChnls, iAllSortCodes, ... 
                             dTimeStartAll, dTimeEndAll, 'ALL');

if nEvents >0 
  fprintf('Got %d RecordingSync events\n', nEvents);
else 
  fprintf('Could not find any RecordingSync events\n');
end

% Get timestamps of the RecordingSync event
dRecSyncTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, 1 = nEvents, 6 = get timestamp


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read the TimeSync events
nEvents = hTank.ReadEventsV( nEventsMax, strTimeSyncStore, iAllChnls, iAllSortCodes, ... 
                             dTimeStartAll, dTimeEndAll, 'ALL');

if nEvents >0 
  fprintf('Got %d TimeSync events\n', nEvents);
else 
  fprintf('Could not find any TimeSync events\n');
end

% Get timestamps of TimeSync events
dTimeSyncTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, 1 = nEvents, 6 = get timestamp

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read RP2_ticks events 
nEvents = hTank.ReadEventsV( nEventsMax, strRP2_TickStore, iAllChnls, iAllSortCodes, ...
                            dTimeStartAll, dTimeEndAll, 'NODATA');
if nEvents == nEventsMax
  warning('Got max number of %s events in ReadEventsV(), possible loss of data!\n', strRP2_TickStore);
end

if nEvents >0 
  fprintf('Got %d RP2 Tick events\n', nEvents);
else 
  fprintf('Could not find any RP2 Tick events\n');
end

% Get timestamps of RP2 Tick events
dRP2_TickTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, nEvents, 6 = get timestamp


hTank.CloseTank;
hTank.ReleaseServer;
delete(hFig);

