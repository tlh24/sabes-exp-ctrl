srvname = 'CP_LibertyTrack.Application';

hLiberty=actxserver(srvname);

SensorsOn = [1 0 0 0 ];
hLiberty.SetSensors(SensorsOn);

hLiberty.ConnectTracker;
pause(1);

[iIdx dData] = hLiberty.GetSensorLatest( 1 )  

% hLiberty.DisconnectTracker;
% delete(hLiberty);
% clear functions;