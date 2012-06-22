function SpikeArray = TankGetSpikeTimes(strTank, iBlock, dGlobRecSyncTS)
% function SpikeArray = TankGetSpikeTimes(strTank, iBlock, dGlobRecSyncTS )
%
% Read snippets from Tank and return time, channel, cluster 
%
% INPUT:
%   strTank - tank name (string)
%   iBlock - iBlock number (integer)
%   dGlobRecSyncTS - global timestamp (in seconds) for the RecordingSync event
%
% OUTPUT:
% The array SpikeArray(:,3)
%   where 
%     SpikeArray(:,1) -  the global timestamp
%     SpikeArray(:,2) -  input channel (electrode)
%     SpikeArray(:,3) -  cluster 
%

SpikeArray = [];

if nargin < 3
	fprintf('Use: help GetTankSpikes\n')
	return
end

% strTank = 'Try00';
% iBlock = 9;
% dGlobRecSyncTS = 1234;

TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod


DaqConfigInclude;   % Server name
TankConfigInclude;  % Tank store strings are defined here

strBlock  = sprintf('Block-%d',iBlock);    % iBlock (case-sensitive!)
fprintf('\nConnecting to   %s   %s  ...  ', strTank, strBlock);

hFig = figure;
hTank = actxcontrol('ttank.x', [20 20 60 60], hFig);


if hTank.ConnectServer( strRX5_DaqComputer, strRX5_DaqUser) ~= 1
  delete(hFig);
	error('  Error connecting to server: %s', strRX5_DaqComputer)
end

if hTank.OpenTank( strTank, 'r') ~= 1
  hTank.ReleaseServer;
  delete(hFig);
	error('  Error opening tank! Make sure the tank is registered on the server.')
end

if hTank.SelectBlock( strBlock) ~= 1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
	error('  Error selecting block!')
end

fprintf('Ok\n\n');


nEventsMax = 1000000; % max number of events to read
iAllChnls   = 0;    % All Channels
iAllSortCodes  = 0;    % All Sorted Spikes Channels
dTimeStartAll = 0.0;
dTimeEndAll = 0.0;

% Read the RecordingSync event
nEvents = hTank.ReadEventsV( nEventsMax, strRecSyncStore, iAllChnls, iAllSortCodes, ... 
                             dTimeStartAll, dTimeEndAll, 'ALL');

if nEvents ~= 1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
  error('Incorrect number of the RecordingSync events: %d  (should be 1)', nEvents);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Get timestamp of the RecordingSync event
dRecSyncTS = hTank.ParseEvInfoV( 0, 1, 6); % 0 = startIdx, 1 = nEvents, 6 = get timestamp

fprintf('Got RecordingSync time: %g\n', dRecSyncTS);

dTankStartTime = hTank.CurBlockStartTime;   % absolute time relative to Jan 1st 1970
dTankStopTime = hTank.CurBlockStopTime;     % absolute time relative to Jan 1st 1970
fprintf('Total tank duration: %g\n', dTankStopTime - dTankStartTime);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read RP2_ticks events
nEvents = hTank.ReadEventsV( nEventsMax, strRP2_TickStore, iAllChnls, iAllSortCodes, ...
                            dRecSyncTS, dTimeEndAll, 'NODATA');
if nEvents == nEventsMax
  warning('Got max number of %s events in ReadEventsV(), possible loss of data!\n', strRP2_TickStore);
end

if nEvents < 10
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
  error('Not enough RP2 Tick events: %d  ', nEvents);
end

% Get timestamps of RP2 Tick events
dRP2_TickTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, nEvents, 6 = get timestamp

fprintf('Got %d of RP2 Tick events\n', nEvents);

% TODO: use for timing checks:
% max(diff(dRP2_TickTS)) - min(diff(dRP2_TickTS))

% dRecSyncGlobTick = dGlobRecSyncTS * dGlobClockHz;
% iFirst = ceil(dRecSyncGlobTick/iGlobTickPeriod);  % index of the first global tick after the RecordSync
% iLast = iFirst + nEvents - 1;                      % index of the last global tick
% dFirstGlobTickTS = iFirst * iGlobTickPeriod / dGlobClockHz;
% dLastGlobTickTS = iLast * iGlobTickPeriod / dGlobClockHz;
% dFirstTickTS = dRP2_TickTS(1);
% dLastTickTS = dRP2_TickTS(end);
% c1 = (dLastGlobTickTS - dFirstGlobTickTS)/(dLastTickTS - dFirstTickTS);
% c0 = (dFirstGlobTickTS * dLastTickTS - dLastGlobTickTS * dFirstTickTS )/(dLastTickTS - dFirstTickTS);

dTank_Duration = dRP2_TickTS(end) - dRP2_TickTS(1); % duration in tank time (sec)
dGlobPeriod = iGlobTickPeriod/dGlobClockHz;
dGlobDuration = dGlobPeriod * ( nEvents - 1); % duration in RP2 time (sec)
c1 = dGlobDuration / dTank_Duration;  % Global time divided by tank time
c0 = dGlobRecSyncTS - dRecSyncTS;
% ( dLastGlobTickTS - dFirstGlobTickTS) - (dLastTickTS - dFirstTickTS)


fprintf('Timestamp conversion coeffs, c0 and c1:  %.5f  %.7f\n', c0, c1);

% read the first snippet
nEvents = hTank.ReadEventsV( 1, strSnipStore, iAllChnls, iAllSortCodes, ...
                            dTimeStartAll, dTimeEndAll, 'ALL');  % 
if nEvents < 1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
  error('Cannot find snippets!  ');
end

% Get sampling rate
dSamplRate = hTank.ParseEvInfoV( 0, 1, 9); % 0 = startIdx, 1 = nEvents, 9 = get sampling rate
fprintf('Got sampling rate: %.4f\n', dSamplRate);


iChannel = [];
iCluster = [];
dTS = [];

% Read the snippet events
nEvents = hTank.ReadEventsV( nEventsMax, strSnipStore, iAllChnls, iAllSortCodes, ...
                            dTimeStartAll, dTimeEndAll, 'NODATA');  % NODATA = don't get waveforms
if nEvents == nEventsMax
  warning('Got max number of %s events in ReadEventsV(), possible loss of data!\n', strSnipStore );
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

SpikeArray(:,1) = dTS * c1 + c0;
SpikeArray(:,2) = iChannel;
SpikeArray(:,3) = iCluster;


fprintf('Got %d spikes\n', length(iCluster));




