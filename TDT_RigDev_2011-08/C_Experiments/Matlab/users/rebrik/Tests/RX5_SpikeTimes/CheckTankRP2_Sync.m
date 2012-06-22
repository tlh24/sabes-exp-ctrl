
strTank = 'Calvin';
iBlock = 53;

% strTank = 'Try00';
% iBlock = 52;

TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod
TankConfigInclude;  % Tank store strings are defined here

strBlock  = sprintf('Block-%d',iBlock);    % iBlock (case-sensitive!)
fprintf('\nConnecting to   %s   %s  ...  ', strTank, strBlock);

hFig = figure;
hTank = actxcontrol('ttank.x', [20 20 60 60], hFig);

DaqConfigInclude;

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

% Read the RecordingStart event
nEvents = hTank.ReadEventsV( nEventsMax, strRecStartStore, iAllChnls, iAllSortCodes, ... 
                             dTimeStartAll, dTimeEndAll, 'ALL');

if nEvents ~= 1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
  error('Incorrect number of the RecordingStart events: %d  (should be 1)', nEvents);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Get timestamp of the RecordingStart event
dRecStartTS = hTank.ParseEvInfoV( 0, 1, 6); % 0 = startIdx, 1 = nEvents, 6 = get timestamp

fprintf('Got RecordingStart time: %g\n', dRecStartTS);

dTankStartTime = hTank.CurBlockStartTime;   % absolute time relative to Jan 1st 1970
dTankStopTime = hTank.CurBlockStopTime;     % absolute time relative to Jan 1st 1970
fprintf('Total tank duration: %g\n', dTankStopTime - dTankStartTime);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read RP2_ticks events
nEvents = hTank.ReadEventsV( nEventsMax, strRP2_TickStore, iAllChnls, iAllSortCodes, ...
                            dRecStartTS, dTimeEndAll, 'NODATA');
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
dRP2_diff = diff(dRP2_TickTS)*1000;

fprintf('Period (ms): %g\n', mean(dRP2_diff));
fprintf('Period std: %g\n', std(dRP2_diff));
fprintf('Min period (ms): %g\n', min(dRP2_diff));
fprintf('Max period (ms): %g\n', max(dRP2_diff));

fprintf('Period range (ms): %g\n', max(dRP2_diff) - min(dRP2_diff));

% figure;
% hist(dRP2_diff)

% dRecStartGlobTick = dGlobRecStartTS * dGlobClockHz;
% iFirst = ceil(dRecStartGlobTick/iGlobTickPeriod);  % index of the first global tick after the RecordStart
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
fprintf('Timestamp conversion coeff c1:  %.7f\n',  c1);



hTank.CloseTank;
hTank.ReleaseServer;
delete(hFig);





