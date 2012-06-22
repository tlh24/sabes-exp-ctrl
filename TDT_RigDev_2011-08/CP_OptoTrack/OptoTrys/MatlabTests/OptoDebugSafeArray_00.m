srvname = 'CP_OptoTrack.Application';
nFrames = 10;
hTracker=actxserver(srvname);

% SensorsOn = int32([ 1 2 3 ]);   % Sensor
% hTracker.SetSensors(SensorsOn);
% 
iSensor =  int32(1);
iIdx  = int32(10);

[iIdx0, dTime0 dData0] = invoke( hTracker, 'GetSensorLatest', iSensor );  
[iIdx1, dTime1 dData1] = invoke( hTracker, 'GetAllSensorsLatest' );  
[dTime2 dData2] = invoke( hTracker, 'GetSensorBuffered', iSensor, iIdx1-10, 10 );  
[dTime3 dData3] = invoke( hTracker, 'GetAllSensorsBuffered', iIdx1-10, 10 );  


% delete(hTracker);
% clear functions;