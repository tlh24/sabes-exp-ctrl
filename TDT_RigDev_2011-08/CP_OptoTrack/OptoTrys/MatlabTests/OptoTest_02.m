srvname = 'CP_OptoTrack.Application';

hTracker=actxserver(srvname);

SensorsOn = int32(1);    % Sensor 1 using transform 1 on port 1
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
pause(1);
iSensor =  int32(1);
iIdx  = int32(0);


[iIdx dTime dData] = invoke( hTracker, 'GetSensorLatest', iSensor ); 
iIdx
for i=1:100
  [iIdx dTime dData] = invoke( hTracker, 'GetSensorLatest', iSensor );  
end
iIdx
hTracker.DisconnectTracker;
% delete(hTracker);
% clear functions;