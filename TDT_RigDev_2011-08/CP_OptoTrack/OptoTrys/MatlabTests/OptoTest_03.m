srvname = 'CP_OptoTrack.Application';
nFrames = 10;
hTracker=actxserver(srvname);

SensorsOn = int32([1 2    % Sensor
                   1 2]); % Transform
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
pause(0.5);
iSensor =  int32(1);
iIdx  = int32(0);

[iIdx] = hTracker.GetDataIndexLatest;
while iIdx < 10
  pause(0.1);
  [iIdx] = hTracker.GetDataIndexLatest;
end

iIdx
for i=1:1000
  [iIdx] = hTracker.GetDataIndexLatest;
  [dTime dData] = invoke( hTracker, 'GetSensorBuffered', iSensor, iIdx-10, 10 );  
end
iIdx
hTracker.DisconnectTracker;
% delete(hTracker);
% clear functions;