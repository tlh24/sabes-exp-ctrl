nRuns = 100;
RunDurationSec = 4;

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
pause(0.1);

for iRun = 1:nRuns
  fprintf('Run %d of %d\n', iRun, nRuns);
  iIdxBegin = hTracker.GetDataIndexLatest;

  pause(RunDurationSec);
  iIdxEnd = hTracker.GetDataIndexLatest;
  nFrames = iIdxEnd - iIdxBegin + 1;
  [dTime_a dXYZ_a dVelXYZ] = invoke(hTracker, 'GetSensorBuffered', 1, iIdxBegin, nFrames );  
end

hTracker.DisconnectTracker;

delete(hTracker);
% clear functions;


