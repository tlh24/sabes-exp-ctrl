function [dTS, strTags, strValues] = TankGetStream(strTank, iBlock)
% function [dTS, fData] = TankGetStream(strTank, iBlock)

TankConfigInclude;  % using strStreamStore, strTimeSyncStore
StreamTagsInclude;  

nEventsMax = 1000000; % max number of events to read
iAllChnls   = 0;    % All Channels
iAllSortCodes  = 0;    % All Sorted Spikes Channels
dTimeStartAll = 0.0;
dTimeEndAll = 0.0;

dTimeSyncRX5 = [];
dTS = [];
strTags = [];
strValues = [];


[hTank hFig] = TankOpen( strTank, iBlock);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read the Stream events
nEvents = hTank.ReadEventsV( nEventsMax, strStreamStore, iAllChnls, iAllSortCodes, ... 
                             dTimeStartAll, dTimeEndAll, 'NODATA');
if nEvents >0 
  fprintf('Got %d Stream events\n', nEvents);
else 
  fprintf('Could not find any Stream events\n');
  hTank.ReleaseServer;
  delete(hFig);
  return;
end

% Get timestamps
dTS = hTank.ParseEvInfoV( 0, nEvents, 6); % 0 = startIdx, nEvents, 6 = get timestamp

% Get data
for iEvent = 1:nEvents
  nEv(iEvent) = hTank.ReadEventsV( 1, strStreamStore, iAllChnls, iAllSortCodes, ...  % 1=read one event
                               dTS(iEvent), dTimeEndAll, 'ALL');   % dTS() - start time
  fData = hTank.ParseEvV( 0, 1); % 0 = startIdx, nEvents
  strText = char(fData');
  SepIdx = find( strText == strStreamSeparator);
  strTags{iEvent} = strText(1:SepIdx-1);
  strValues{iEvent} = strText(SepIdx+1:end);
end
hTank.ReleaseServer;
delete(hFig);

