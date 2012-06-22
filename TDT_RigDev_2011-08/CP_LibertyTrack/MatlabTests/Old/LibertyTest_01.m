srvname = 'CP_LibertyTrack.Application';

hLiberty=actxserver(srvname);

hLiberty.GetTrackerState
SensorsOn = int32([1 3]);
hLiberty.SetSensors(SensorsOn);
SensorsState = hLiberty.GetSensors       

hLiberty.ConnectTracker;
pause(4);
hLiberty.GetTrackerState
SensorsState = hLiberty.GetSensors  

hLiberty.DisconnectTracker;
hLiberty.GetTrackerState
SensorsOn = int32([1 3 4]);
hLiberty.SetSensors(SensorsOn);
SensorsState = hLiberty.GetSensors       

% delete(hLiberty);
% clear functions;