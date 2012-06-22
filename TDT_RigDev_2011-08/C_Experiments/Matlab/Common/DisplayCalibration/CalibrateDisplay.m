% Display calibration
% Creates claibration matrix DisplayCalibration.mat
% in the directory C:\Experiments\Calibration
function CalibrateDisplay

fprintf('===============================================\n');
fprintf('            Display calibration\n');
fprintf('===============================================\n');

ServerNamesInclude;
DisplaySizeInclude;
% we use these variables from DisplaySizeInclude:
% iDisplayX0 = 300;
% iDispayX1 = 700;
% iDisplayY0 = 200;
% iDispayY1 = 600;
% iDispayWidthPix = 1024;
% iDisplayHeightPix = 768;

% in pixels
DiskRadius = 5;  

iSensorIdx = 1;  % sensor to use
nSamplesPerDisk = 20; % number of measurements per point

nDisksX = 4;  % N disks horizontally
nDisksY = 4;%3;  % N disks vertically

InitialPauseSec = 15 ; % time to run to the rig
ShowTimeSec = 5;  % time to show active target
nShowSteps = 10;  % steps to change target color

DiskColor = [0.5 0 0];  % dark red
TargetColorBegin = [1 1 1]; % white
TargetColorEnd = [0 1 0]; % green


% Disconnect the tracker if necessary
hTracker=actxserver(strTrackerName, strTrackerComputer);
iState = hTracker.GetTrackerState;
if iState
  hTracker.DisconnectTracker;
  pause(0.5);  % give it some time for disconnection
end
% Set the sensor 
SensorsOn = int32([iSensorIdx 1]');
hTracker.SetSensors(SensorsOn);

% Get the transform
% Tracker should be already calibrated:
% (trivial for Liberty, real for OptoTrak)
TrackerCalibMtx = TrackerGetCalibMatrix(); 
hTracker.SetTransformMatrix(TrackerCalibMtx, 1);
% we really need to set only one sensor, but Matlab will complain:
% single value is not a SafeArray
hTracker.SetSensorsTransformIdx( int32([1 1])); 



% % this is an ugly hack to set transform
% % Matlab would not pass 1x1 var as an array
% SensorsOn = int32([1 2 3 4]); 
% hTracker.SetSensors(SensorsOn);


hTracker.ConnectTracker;
pause(0.1);

% Connect to the display
hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 

% use unity transform for the display
% all screen coordinates will be in pixels
mtxUnityTransform  = [ 0  0
                       1  0
                       0  1
                       0  0
                       0  0
                       0  0 ];

hVMain.SetTransformMatrix(mtxUnityTransform);
hVMain.HideGroup(0);  % hide all, just in case
nDisks = nDisksX * nDisksY;

GridW = iDispayX1 -iDisplayX0;
GridH = iDispayY1 -iDisplayY0;
GridStepX = GridW / ( nDisksX -1 );
GridStepY = GridH / ( nDisksY -1 );

% calculate coordinates for the disk grid
for i=1:nDisksX
  for j=1:nDisksY
    DiskCoordIJ(j,i, :) = [ iDisplayX0 + GridStepX * (i-1); iDisplayY0 + GridStepY * (j-1)];
  end
end
% flatten the array
DiskCoord = reshape(DiskCoordIJ, [nDisksX * nDisksY, 2]);

% create and setup the disks
for i=1:nDisks
  hVDisk(i) = actxserver('CP_Display.VDisk', strDisplayComputer); 
  hVDisk(i).SetColor(DiskColor);
  hVDisk(i).SetRadius(DiskRadius);
  hVDisk(i).SetXY( DiskCoord(i,:));
  hVDisk(i).Show;
end

% calc target disk color sequence
for i=1:nShowSteps
  fraction = (i-1) / (nShowSteps-1);
  SequenceColor(i,:) = fraction * TargetColorEnd + (1-fraction)* TargetColorBegin;
end

fprintf('To calibrate the display\n');
fprintf('move sensor #%d to the center of the white circle.\n\n', iSensorIdx);

fprintf('              Press any key to start -\n');
fprintf('calibration will begin %g seconds after the keypress\n',InitialPauseSec );
pause();
PauseTime = ShowTimeSec/nShowSteps;

% show the target, measure coordinates
for i=1:nDisks
  hVDisk(i).SetFillFlag(0);
  hVDisk(i).SetColor(TargetColorBegin);
  if i == 1  
    pause( InitialPauseSec );  % wait longer if the first disk
  end
  for j=1:nShowSteps
    hVDisk(i).SetColor(SequenceColor(j,:));
    pause(PauseTime);
  end
  [iIdx, dTimes, Coordinates(:, :, i) ] = invoke( hTracker, 'GetSensorLatest', int32(iSensorIdx), nSamplesPerDisk );
  hVDisk(i).SetColor(DiskColor);
  hVDisk(i).SetFillFlag(1);
end

hTracker.DisconnectTracker;


X1 = Coordinates(1, :, :);
X1 = X1(:);  % make it 1-D
Y1 = Coordinates(2, :, :);
Y1 = Y1(:);  % make it 1-D

%fprintf('X: %f,  Y: %f\n', mean(X1), mean(Y1));

T0 = ones(size(X1));  % 0 order, to calc offset
X2 = X1.*X1;          % 2nd order

Y2 = Y1.*Y1;

XY = X1.*Y1; % cross - term

% make full matrix of measurements where columns
% represent independent variables, i.e.
% 0,1,2 order and cross-term
Full_mat = [T0 X1 Y1 X2 XY Y2];

% make length of target vars same as input taking into account that
% we have multiple samples at the same target point
X_target = repmat( DiskCoord(:,1), [1 nSamplesPerDisk]);
X_target = X_target';
X_target = X_target(:);  % make it 1-D

Y_target = repmat( DiskCoord(:,2), [1 nSamplesPerDisk]);
Y_target = Y_target';
Y_target = Y_target(:);  % make it 1-D


% calculate multiple linear regression on full second-order model
% NB: regress() is a part of statistics toolbox
[Cx, Cx_range] = regress( X_target, Full_mat);
[Cy, Cy_range] = regress( Y_target, Full_mat);

DispCalibMtx = [Cx Cy]; % combine two columns into calib. matrix

SaveDisplayCalibMatrix( DispCalibMtx );

fprintf('\nNew calibration matrix:\n');
disp(DispCalibMtx);

fprintf('\n95%% confidence intervals for X - column:\n');
disp(Cx_range);

fprintf('\n95%% confidence intervals for Y - column:\n');
disp(Cy_range);

fprintf('Display calibration completed, calibration matrix saved\n');
fprintf('\n\nRun TestDisplayCalibration.m to test\n');

figure;
plot(X1,Y1,'.');
title('Tracker XY, mm');

XY_calc = Full_mat*DispCalibMtx;
figure;
plot(X_target,Y_target, '.b');
hold on;
plot(XY_calc(:,1), XY_calc(:, 2),'.r');
title('Red - calculated XY, Blue - target XY, pix');

