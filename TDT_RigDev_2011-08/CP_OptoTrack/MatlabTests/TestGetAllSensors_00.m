ServerNamesInclude;

hTracker=actxserver('CP_OptoTrack.Application', strTrackerComputer);
if hTracker.GetTrackerState
  hTracker.DisconnectTracker
  pause(0.1);
end

SensorsOn = int32([1 2]);
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
pause(0.1);
iIdxBegin = hTracker.GetDataIndexLatest

pause(4);

% [iIdx1 dTime1 dXYZ1] = invoke(hTracker, 'GetAllSensorsLatest' )  
% [iIdx2 dTime2 dXYZ2] = invoke(hTracker, 'GetAllSensorsLatest', 10 ); 

iIdxEnd = hTracker.GetDataIndexLatest
nFrames = iIdxEnd - iIdxBegin + 1
[dTime_a dXYZ_a] = invoke(hTracker, 'GetAllSensorsBuffered', iIdxBegin, nFrames );  


nSensors = size(SensorsOn, 2);
nFrames_b = size(dXYZ_a, 2);
% dXYZ = reshape(dXYZ3, [6 2 7] )
dXYZ = reshape(dXYZ_a, [6 nSensors nFrames_b] );

% 
dXYZ_S1 = squeeze(dXYZ(1:3,1,:));
dXYZ_S2 = squeeze(dXYZ(1:3,2,:));

hTracker.DisconnectTracker;

% delete(hTracker);
% clear functions;


