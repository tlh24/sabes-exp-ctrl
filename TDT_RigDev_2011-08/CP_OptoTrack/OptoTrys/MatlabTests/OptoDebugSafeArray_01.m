srvname = 'CP_OptoTrack.Application';
nFrames = 10;
hTracker=actxserver(srvname);

SensorsOn = int32([ 1 2 3 4 5 6      % Marker
                    1 1 1 2 2 2      % Transform
                    2 2 2 2 2 2 ]);   % Port
                    
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker

pause(2);
iSensor =  int32(1);
iIdx  = int32(10);

[iIdx0, dTime0 dData0] = invoke( hTracker, 'GetSensorLatest', iSensor );  
[iIdx1, dTime1 dData1] = invoke( hTracker, 'GetAllSensorsLatest' );  
[dTime2 dData2] = invoke( hTracker, 'GetSensorBuffered', iSensor, iIdx1-10, 10 );  
[dTime3 dData3] = invoke( hTracker, 'GetAllSensorsBuffered', iIdx1-10, 10 );  

dData4  = reshape(dData3, [3 6 10]);
% delete(hTracker);
% clear functions;