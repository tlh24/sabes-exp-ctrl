function TrackerCalibrateOpto()

ServerNamesInclude;

fprintf('===============================================\n');
fprintf('            OptoTrack calibration\n');
fprintf('===============================================\n');

nFrames = 100;
hTracker=actxserver(strTrackerName, strTrackerComputer);
hTracker.DisconnectTracker;

% Set 6 sensors on port 2, transform 1
SensorsOn = int32([ 1 2 3 4 5 6      % Sensor
                    2 2 2 2 2 2 ]);  % Port
hTracker.SetSensors(SensorsOn);

hTracker.SetSensorsTransformIdx( int32([1 1 1 1 1 1]) );

nSensors = size(SensorsOn,2);

% Set transform to identity
TransformMtx = [ 1 0 0
                 0 1 0
                 0 0 1
                 0 0 0 ];
hTracker.SetTransformMatrix(TransformMtx,1);       

hTracker.ConnectTracker;
pause(1);

% Wait for the data
[iIdx] = hTracker.GetDataIndexLatest;
while iIdx < nFrames
  pause(0.1);
  [iIdx] = hTracker.GetDataIndexLatest;
end

[iIdx] = hTracker.GetDataIndexLatest;
[dTime dData0] = invoke( hTracker, 'GetAllSensorsBuffered', iIdx-nFrames, nFrames );  

hTracker.DisconnectTracker;
delete(hTracker);
% we have to reshape the data since Matlab 
% does not support 3D arrays in COM
dData = reshape(dData0, [6 nSensors nFrames]);
dData = dData(1:3, :, :);  % remove angles 

% get average coordinates of the reference sensors
v1 = mean( dData(:,1,:), 3 );
v2 = mean( dData(:,2,:), 3 );
v3 = mean( dData(:,3,:), 3 );
v4 = mean( dData(:,4,:), 3 );
v5 = mean( dData(:,5,:), 3 );
v6 = mean( dData(:,6,:), 3 );

TrackerCalibMtx(:,:,1) = TrackerCalcTransformMtx( v1, v2, v3);
TrackerCalibMtx(:,:,2) = TrackerCalcTransformMtx( v4, v5, v6);

TrackerSaveCalibMatrix( TrackerCalibMtx );













