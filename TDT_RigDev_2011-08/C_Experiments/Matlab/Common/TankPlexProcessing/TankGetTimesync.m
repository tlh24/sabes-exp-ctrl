function [dTimeSyncGlob dTimeSyncStream] = TankGetTimeSync(strTank, iBlock)

StreamTagsInclude;

dTimeSyncGlob = [];
dTimeSyncStream = [];

[dTS, strTags, strValues] = TankGetStream(strTank, iBlock);

% find tags of the TimeSync record
TsIdx = find(strcmp( strTags, strStreamTimesyncTag ));

nVals = length(TsIdx);
if nVals > 0 
  fprintf('Got %d TimeSync records in the stream\n', nVals);
else 
  fprintf('Could not find any TimeSync records in the stream\n');
  return;
end

dTimeSyncStream = dTS(TsIdx);
for iVal = 1:nVals
  dTimeSyncGlob(iVal) = sscanf(strValues{TsIdx(iVal)}, '%f');
end

dTimeSyncGlob = dTimeSyncGlob';