function RX5_SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
                         iChannelList, dTS_Start, dTS_Stop, ...
                         dGlobRecStartTS  )
% function RX5_SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
%                          iChannelList, dTS_Start, dTS_Stop, ...
%                          dGlobRecStartTS  )
% Read raw data from the Tank and save it into a bin file for clustering
%
% INPUT:
%   strTank - tank name (string)
%   iBlock - iBlock number (integer)
%   iLocationID - Location ID (integer), for refernce, used in the filenames
%   strDataDir  - where to save the file. If empty, current dir is used
%   iChannelList - list of channels to use, e.g. [2,3,4]
%   dTS_Start - global start timestamp (seconds) of this location 
%   dTS_Stop - global end timestamp (seconds) of this location 
%   dGlobRecStartTS - global timestamp (seconds) for the RecordingStart event
%
% OUTPUT:
%   none
%
% SAVES: 
%   binary file of raw data: <Tank>_<BlockNumber>_<LocationID>.i16
%   mat file: <Tank>_<BlockNumber>_<LocationID>_conf.mat
%     with variables:
%       strTank - tank name (string)
%       iBlock - iBlock number (integer)
%       iLocationID - Location ID, for refernce, used in the filename
%       iChannelList - list of channels to use, e.g. [2,3,4]
%       dLocTS_Start - global start timestamp (seconds) of this location 
%       dLocTS_Stop - global end time (seconds)
%       dGlobRecStartTS - global timestamp (seconds) for the RecordingStart event
%       dTS_c0, dTS_c1  - coeffs to convert times of spikes to the global
%                         time (after clustering)
%   ofi file:  <Tank>_<BlockNumber>_<LocationID>.ofi
%       configuration for Plexon OfflineSorter
%  



% strTank = 'Try00';
% iBlock = 38;
% dGlobRecStartTS = 2561.3864960000003;
% dTS_Stop = 2571.39400704;
% iBlock = 39;
% dGlobRecStartTS = 2696.6370713600004;
% dTS_Stop = 2756.7394816;
% iLocationID = 1;
% strDataDir = 'd:\tmp\';
% iChannelList = [1, 2, 3, 4, 5, 6];
% dTS_Start = dGlobRecStartTS;
% dTS_Stop = dTS_Start+10;
% nargin = 8;


if nargin < 8
	fprintf('Use: help SaveTankRawData\n')
	return
end

TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod
TankConfigInclude;  % Tank store strings are defined here
DaqConfigInclude;

dVoltsToIntScale = pow2(iResolutionBits-1)/dMaxV; %    32768/5e-3;  5mV = 32768

strBlock  = sprintf('%s%d', strBlockPrefix, iBlock);    % Block name
strFileName   = sprintf('%s_%04d_%04d', strTank, iBlock, iLocationID);

fprintf('\nConnecting to   %s   %s  ...  ', strTank, strBlock);

hFig = figure;
set(hFig, 'Visible', 'off');
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
% max(diff(dRP2_TickTS)) - min(diff(dRP2_TickTS))

% dRecStartGlobTick = dGlobRecStartTS * dGlobClockHz;
% iFirst = ceil(dRecStartGlobTick/iGlobTickPeriod);  % index of the first global tick after the RecordStart
% iLast = iFirst + nEvents - 1;                      % index of the last global tick
% dFirstGlobTickTS = iFirst * iGlobTickPeriod / dGlobClockHz;
% dLastGlobTickTS = iLast * iGlobTickPeriod / dGlobClockHz;
% dFirstTickTS = dRP2_TickTS(1);
% dLastTickTS = dRP2_TickTS(end);
% 
% % ( dLastGlobTickTS - dFirstGlobTickTS) - (dLastTickTS - dFirstTickTS)
% 
% dTS_c1 = (dLastGlobTickTS - dFirstGlobTickTS)/(dLastTickTS - dFirstTickTS);
% dTS_c0 = (dFirstGlobTickTS * dLastTickTS - dLastGlobTickTS * dFirstTickTS )/(dLastTickTS - dFirstTickTS);

dTank_Duration = dRP2_TickTS(end) - dRP2_TickTS(1); % duration in tank time (sec)
dGlobPeriod = iGlobTickPeriod/dGlobClockHz;
dGlobDuration = dGlobPeriod * ( nEvents - 1); % duration in RP2 time (sec)
dTS_c1 = dGlobDuration / dTank_Duration;  % Global time divided by tank time
dTS_c0 = dGlobRecStartTS - dRecStartTS;


fprintf('Timestamp conversion coeffs, dTS_c0 and dTS_c1:  %.5f  %.7f\n', dTS_c0, dTS_c1);

% read the first raw event
nEvents = hTank.ReadEventsV( 1, strRawStore, iAllChnls, iAllSortCodes, ...
                            dTimeStartAll, dTimeEndAll, 'ALL');  % 
if nEvents < 1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
  error('Cannot find raw data!  ');
end

% Get sampling rate
dSamplRate = hTank.ParseEvInfoV( 0, 1, 9); % 0 = startIdx, 1 = nEvents, 9 = get sampling rate
fprintf('Got sampling rate: %.4f\n', dSamplRate);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Open bin file in the data dir
% TODO: strDataDir open dir or create 

strFileFullPath = [strDataDir strFileName '.i16'];
hFile = fopen(strFileFullPath,'wb');

if hFile == -1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
  error('Error opening file: %s  ', strFileFullPath);
end

fprintf('Opened file for writing: %s  \n', strFileFullPath);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parse raw data 

% Read timestamps of the raw events on all channels 
nEvents = hTank.ReadEventsV( nEventsMax, strRawStore, iAllChnls, iAllSortCodes, ...
                            dTimeStartAll, dTimeEndAll, 'NODATA');  % NODATA = don't get waveforms
if nEvents == nEventsMax
  warning('Got max number of %s events in ReadEventsV(), possible loss of data!\n', strSnipStore );
end

% Get timestamps
dTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, nEvents, 6 = get timestamp
% Get channels
iChannel = hTank.ParseEvInfoV( 0, nEvents, 4); % 0 = startIdx, nEvents, 4 = get channel

% find first channel timestamps
iChEvIdx = find( iChannel == iChannelList(1));
dChTS = dTS(iChEvIdx);
dGlobChTS = dChTS * dTS_c1 + dTS_c0;  % convert to global time

% find packets containing start/stop timestamps
StartIdx = find(dGlobChTS <= dTS_Start);
StartIdx = StartIdx(end);

StopIdx = find(dGlobChTS < dTS_Stop);
StopIdx = StopIdx(end);
dFileStartTS = dGlobChTS(StartIdx);

ChunkList = StartIdx : StopIdx;
nChannels = length(iChannelList);
dMin = 1e10;
dMax = -1e10;

for ChunkIdx = ChunkList;
  dChunkTS =  dChTS(ChunkIdx);
  dRawChunk = [];
  for ChnlIdx = 1:nChannels; 
    % Read the raw blocks events
    nEvents = hTank.ReadEventsV( 1, strRawStore, iChannelList(ChnlIdx), iAllSortCodes, ...
                                 dChunkTS, dTimeEndAll, 'ALL');
    if nEvents ~= 1
      fclose(hFile);
      hTank.CloseTank;
      hTank.ReleaseServer;
      delete(hFig);
      error('  Got incorrect number of raw events: %d, should be 1', nEvents)
    end
    dRawChunk(:,ChnlIdx) = hTank.ParseEvV(0, 1);
  end
  dChunkMin = min(min(dRawChunk));
  dMin = min(dChunkMin, dMin);
  dChunkMax = max(max(dRawChunk));
  dMax = max(dChunkMax, dMax);
  
  % save chunk to file
  dRawChunk = dRawChunk * dVoltsToIntScale;  % scale
   
	nWritten = fwrite(hFile, dRawChunk', 'int16'); % convert to int16 and write
  if nWritten ~= length(dRawChunk(:))
    hTank.CloseTank;
    hTank.ReleaseServer;
    delete(hFig);
    error('Error writing data to file! %d ints written instead of %d  ', nWritten, length(dRawChunk(:)));
  end
end

fclose(hFile);
hTank.CloseTank;
hTank.ReleaseServer;
delete(hFig);

nChannels = size(dRawChunk,2);
fprintf('Wrote %d chunks of  %d channels  by   %d samples\n', ... 
           length(ChunkList), nChannels, size(dRawChunk,1));

strFileFullPath = [strDataDir strFileName '.ofi'];
hFile = fopen(strFileFullPath,'wb');

if hFile == -1
  error('Error opening file: %s  ', strFileFullPath);
end

fprintf(hFile, 'Freq=%.6f\n', dSamplRate );
fprintf(hFile, 'MaxMV=%.6f\n', dMaxV * 1000 );  
fprintf(hFile, 'NChan=%d\n', nChannels);
fprintf(hFile, 'Offset=0\n');
fprintf(hFile, 'ResolutionBits=%d\n', iResolutionBits); 
fprintf(hFile, 'Swap=0\n');

fclose(hFile);
fprintf('Saved OfflineSorter config file: %s  \n', strFileFullPath);

strFileFullPath = [strDataDir strFileName '_conf.mat'];
save(strFileFullPath, 'strTank', 'iBlock', 'iLocationID', 'iChannelList', 'dTS_Start', ...
     'dTS_Stop', 'dGlobRecStartTS', 'dTS_c0', 'dTS_c1', 'dFileStartTS');

fprintf('Saved Matlab file: %s  \n', strFileFullPath);



