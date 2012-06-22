srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname);

hTracker.GetTrackerState
SensorsOn = int32([1 3]);
hTracker.SetSensors(SensorsOn);
SensorsState = hTracker.GetSensors       

hTracker.ConnectTracker;
pause(4);
hTracker.GetTrackerState
hTracker.GetBufferSize 
SensorsState = hTracker.GetSensors  

hTracker.DisconnectTracker;

hTracker.GetTrackerState
SensorsOn = int32([1 3 4]);
hTracker.SetSensors(SensorsOn);
SensorsState = hTracker.GetSensors       

% delete(hTracker);
% clear functions;