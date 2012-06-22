nRuns = 100;
nFrames = 10000;
DaqDurationSec = nFrames/240;

CompNameInclude;
srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname, strCompName);

if hTracker.GetTrackerState
  hTracker.DisconnectTracker
  pause(0.1);
end

SensorsOn = int32([1 3]);
hTracker.SetSensors(SensorsOn);

hTracker.ConnectTracker;
pause(DaqDurationSec + 0.5);

for iRun = 1:nRuns
  iIdxBegin = hTracker.GetDataIndexLatest - nFrames;
  [dTime_a dXYZ_a dVelXYZ] = invoke(hTracker, 'GetSensorBuffered', 1, iIdxBegin, nFrames );  
end

hTracker.DisconnectTracker;
fprintf('Run %d of %d\n', iRun, nRuns);

delete(hTracker);
% clear functions;


