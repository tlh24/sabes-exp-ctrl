function SaveLastBlock(strTank, strFname, strDataFormat )

% INPUT:
%  strTank  - tank name 
%  strFname - destination filename
% strDataFormat - data format to use on save, e.g. 'float32','int16'
TTX = actxcontrol('ttank.x');
if (TTX.ConnectServer('Local', '') ~= 1)
	fprintf(1, '\n+++ Error: cannot connect to server.\n');
	return
end
if (TTX.OpenTank( strTank, 'r') ~= 1)
	fprintf(1, '\n+++ Error: cannot open tank %s  \n', strTank);
	return
end

iBlock = 0;
while 1
  strTmp=TTX.QueryBlockName( iBlock);
  % if the system is in preview mode, block name is 'TempBlk'
  if ((length(strTmp) < 1) || strcmp(strTmp,'TempBlk')), break, end   
  strBlock = strTmp;
  iBlock = iBlock + 1;
end

iBlock = iBlock - 1; % Roll back to the valid block index (if any)
if ( iBlock < 1) 
	fprintf(1, '\n+++ Error: no saved blocks found in the tank: %s\n', strTank);
	return
end

fprintf(1,'Tank: %s    Block: %s \n',strTank, strBlock);

%% Select the block (the last one we've just found)
if (TTX.SelectBlock(strBlock) ~= 1)
  fprintf(1, '\n+++ Error: cannot select block  %s  from tank %s  \n', strBlock, strTank );
  return
end

fid = fopen( strFname,'wb');

%% Set the paramters
strStore = 'RAWs';   % store name
iChannel   = 0;      % All Channels
iSortCode  = 0;      % All Sorted Spikes Channels
TimeIntervalSec = 2; % read 2-second intervals
% Each event contains Blk_Size samples (1000 by default) so at 25kHz 
% we have 25 events per second, and N_EventsMax should be bigger 
% than SampRateHz/Blk_Size*TimeIntervalSec
N_EventsMax = 1000;  % max number of events to extract on every read

N_SamplesTot  = 0;
N_EventsTot  = 0;
TimeBegin  = 0;

%% Main loop
while 1
  TimeEnd = TimeBegin + 2.0;  
  % Reads data from the Tank to TTX local memory buffer, 
  % returns number of events within the specified time interval
  N_Events = TTX.ReadEventsV( N_EventsMax, strStore, iChannel,...
                              iSortCode, TimeBegin, TimeEnd, 'ALL');
  if( N_Events < 1 ), break, end   

  % Extract and concatenate waveforms from the memory buffer
  fWave = TTX.ParseEvV(0, N_Events);
% N_Saved = fwrite(fid,fWave,'float32');
% N_Saved = fwrite(fid,fWave,'int16');
  N_Saved = fwrite(fid, fWave, strDataFormat);

  N_SamplesTot = N_SamplesTot + N_Saved;
  N_EventsTot = N_EventsTot + N_Events;
  TimeBegin = TimeEnd;  % to next interval
end

fclose(fid);

fprintf(1,'Read %d events,  Wrote %d samples to %s\n', ...
                  N_EventsTot, N_SamplesTot, strFname)

TTX.CloseTank();
TTX.ReleaseServer();


