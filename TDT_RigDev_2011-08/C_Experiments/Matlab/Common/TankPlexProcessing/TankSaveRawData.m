function TankSaveRawData(strTank, iBlock, iLocationID, strDataDir, ...
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



TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod
TankConfigInclude;  % Tank store strings are defined here
DaqConfigInclude;

dVoltsToIntScale = pow2(iResolutionBits-1)/dMaxV; %    32768/5e-3;  5mV = 32768

strFileName = TankGetRawDataFilename( strTank, iBlock, iLocationID );


if nargin == 8 % we want to calc from the dGlobRecStartTS
  [dTS_c0 dTS_c1] = TankGetTimeConversion(strTank, iBlock, dGlobRecStartTS);
else % use TimeSync events 
  dGlobRecStartTS = [];
  [dTS_c0 dTS_c1] = TankGetTimeConversion(strTank, iBlock);
end  



[hTank hFig] = TankOpen( strTank, iBlock);



nEventsMax = 1000000; % max number of events to read
iAllChnls   = 0;    % All Channels
iAllSortCodes  = 0;    % All Sorted Spikes Channels
dTimeStartAll = 0.0;
dTimeEndAll = 0.0;

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

if isempty(StartIdx)
  warning('Requested StartTime is before the tank StartTime, using tank StartTime.');
  StartIdx = 1;
else
  StartIdx = StartIdx(end);
end

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



