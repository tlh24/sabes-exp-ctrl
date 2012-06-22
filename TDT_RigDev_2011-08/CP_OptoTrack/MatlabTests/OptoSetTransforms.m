srvname = 'CP_OptoTrack.Application';
nFrames = 100;
hTracker=actxserver(srvname);

% Set 6 sensors on port 2, transform 1
SensorsOn = int32([ 1 2 3 4 5 6      % Sensor
                    1 1 1 1 1 1      % Transform
                    2 2 2 2 2 2 ]);  % Port
hTracker.SetSensors(SensorsOn);

nSensors = size(SensorsOn,2)

% Set transform to identity
TransformMtx = single([ 1 0 0
                        0 1 0
                        0 0 1
                        0 0 0 ]);
hTracker.SetTransformMatrix(1, TransformMtx);       

hTracker.ConnectTracker;
pause(1);

% Wait for the data
[iIdx] = hTracker.GetDataIndexLatest;
while iIdx < nFrames
  pause(0.1);
  [iIdx] = hTracker.GetDataIndexLatest;
end

[iIdx] = hTracker.GetDataIndexLatest;
[dTime dData] = invoke( hTracker, 'GetAllSensorsBuffered', iIdx-nFrames, nFrames );  

hTracker.DisconnectTracker;

% we have to reshape the data since Matlab 
% does not support 3D arrays in COM
dData  = reshape(dData, [3 nSensors nFrames]);


% get average coordinates of the reference sensors
v1 = mean( dData(:,1,:), 3 );
v2 = mean( dData(:,2,:), 3 );
v3 = mean( dData(:,3,:), 3 );
v4 = mean( dData(:,4,:), 3 );
v5 = mean( dData(:,5,:), 3 );
v6 = mean( dData(:,6,:), 3 );

TransformMtx1 = CalcTransformMtx( v1, v2, v3);
TransformMtx2 = CalcTransformMtx( v4, v5, v6);

hTracker.SetTransformMatrix(1, TransformMtx1);       
hTracker.SetTransformMatrix(2, TransformMtx2);       

% Set 3 sensors to transform 1 and 3 sensors to transform 2
SensorsOn = int32([1 2 3 4 5 6     % Sensor
                   1 1 1 2 2 2     % Transform
                   2 2 2 2 2 2]);  % Port
 
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
