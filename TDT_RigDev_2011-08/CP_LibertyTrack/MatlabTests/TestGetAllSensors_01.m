CompNameInclude;
srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname, strCompName);

if hTracker.GetTrackerState
  hTracker.DisconnectTracker
  pause(0.1);
end

SensorsOn = int32([1 3]);
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
pause(0.1);
iIdxBegin = hTracker.GetDataIndexLatest

pause(4);

% [iIdx1 dTime1 dXYZ1] = invoke(hTracker, 'GetAllSensorsLatest' )  
% [iIdx2 dTime2 dXYZ2] = invoke(hTracker, 'GetAllSensorsLatest', 10 ); 

iIdxEnd = hTracker.GetDataIndexLatest
nFrames = iIdxEnd - iIdxBegin
[dTime_a dXYZ_a dVelXYZ] = invoke(hTracker, 'GetAllSensorsBuffered', iIdxBegin, nFrames );  


nSensors = size(SensorsOn, 2);
nFrames_b = size(dXYZ_a, 2);
% dXYZ = reshape(dXYZ3, [6 2 7] )
dXYZ = reshape(dXYZ_a, [6 nSensors nFrames_b] );

% 
dXYZ_S1 = squeeze(dXYZ(:,1,:));
dXYZ_S2 = squeeze(dXYZ(:,2,:));

hTracker.DisconnectTracker;

% delete(hTracker);
% clear functions;


