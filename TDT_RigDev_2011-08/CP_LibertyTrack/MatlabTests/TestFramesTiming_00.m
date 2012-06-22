srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname);

SensorsOn = int32([1; 1]);
hTracker.SetSensors(SensorsOn);
hTracker.SetTimeScale( 0, 1);
hTracker.ConnectTracker;
pause(3);

iIdx = hTracker.GetDataIndexLatest
[dTime1 dXYZ1] = invoke(hTracker, 'GetSensorBuffered', 1, 0, iIdx+1 );  
hTracker.DisconnectTracker;


% hTracker.DisconnectTracker;
% delete(hTracker);
% clear functions;