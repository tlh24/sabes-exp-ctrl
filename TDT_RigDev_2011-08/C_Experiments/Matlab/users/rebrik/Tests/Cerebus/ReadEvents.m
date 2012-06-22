filename = 'D:\DataTmp\EventsTest000008.nev';
% filename = 'D:\DataTmp\E071031_M1001.nev'
DLLName = 'nsNEVLibrary.dll';

% Load the appropriate DLL
nsRes = ns_SetLibrary(DLLName);
if (nsRes ~= 0)
    disp('DLL was not found!');
    return
end

% Load data file and display some info about the file
% Open data file
[nsRes, hFile] = ns_OpenFile(filename);
if (nsRes ~= 0)
    disp('Data file did not open!');
    return
end
clear filename;

% Get file information
[nsRes, FileInfo] = ns_GetFileInfo(hFile);
% Gives you EntityCount, TimeStampResolution and TimeSpan
if (nsRes ~= 0)
    disp('Data file information did not load!');
    return
end
   
% Build catalogue of entities
[nsRes, EntityInfo] = ns_GetEntityInfo(hFile, [1 : 1 : FileInfo.EntityCount]);

EventsIdx = find([EntityInfo.EntityType] == 1);


for iEntity = EventsIdx
  if strcmp(EntityInfo(iEntity).EntityLabel,'digin');
    iDigEntity = iEntity;
    break;
  end
end
nDigitalEvents = EntityInfo(iDigEntity).ItemCount;
fprintf('found %d digin events\n', nDigitalEvents );

[nsRes, EventInfo] = ns_GetEventInfo(hFile,iDigEntity);
if ~isequal(EventInfo.EventType,'ns_EVENT_WORD')
  error('Not the correct type of digin data'); 
end

[nsRes, dEventTS, dEventValue] = ns_GetEventData(hFile, iDigEntity, [1:nDigitalEvents] );

dEventValue =  bitand(dEventValue, 15);
Bit3EventIdx = find(diff(dEventValue)==4);
% clear FileInfo;

% hFile

dPauseCbs = dEventTS( Bit3EventIdx + 1 );
%dPauseCbs = 9.363566666666667;
dPauseTdt = (dPauseOnTimes - dRecordingOnTimes)/1000
dPauseTdt - dPauseCbs
