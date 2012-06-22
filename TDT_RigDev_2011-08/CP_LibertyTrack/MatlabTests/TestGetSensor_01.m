srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname);

SensorsOn = int32([1 2]);
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
pause(2);
iIdxBegin = hTracker.GetDataIndexLatest

pause(4);
[iIdx1 dTime1 dXYZ1] = invoke(hTracker, 'GetSensorLatest', 1 )  
[iIdx2 dTime2 dXYZ2] = invoke(hTracker, 'GetSensorLatest', 2 )  

[iIdx1 dTime1 dXYZ1] = invoke(hTracker, 'GetSensorLatest', 1, 5 );  
[iIdx2 dTime2 dXYZ2] = invoke(hTracker, 'GetSensorLatest', 2, 10 );  

iIdxEnd = hTracker.GetDataIndexLatest
nFrames = iIdxEnd - iIdxBegin + 1;
[dTime_b1 dXYZ_b1] = invoke(hTracker, 'GetSensorBuffered', 1, iIdxBegin, nFrames );  
[dTime_b2 dXYZ_b2] = invoke(hTracker, 'GetSensorBuffered', 2, iIdxBegin, nFrames );  

hTracker.DisconnectTracker;
% delete(hTracker);
% clear functions;