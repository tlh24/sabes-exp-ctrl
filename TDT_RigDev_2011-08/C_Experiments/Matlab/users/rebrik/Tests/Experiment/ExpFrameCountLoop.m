
nSeconds = 60;
dSleepSec = 0.2;
FrameMismatchMax = 2;

nTimes = nSeconds/dSleepSec;


ExperimentGlobalsInclude;

hVMain = g_ExpData.hVMain;
hTracker = g_ExpData.hTracker;
hEyeTrack = g_ExpData.hEyeTrack;

fprintf('Will run for %d seconds\n', nSeconds);
for i = 1:nTimes
  %--- Display
  [dDisplayRP2FrameCnt dFrameTimeMs ] = DisplayGetTiming( );
  dDisplayFrameCnt = hVMain.GetFrameCount();


  %--- Tracker
  [dTrackerRP2FrameCnt dFrameTimeMs ] = TrackerGetTiming( );
  dTrackerFrameCnt = hTracker.GetFrameCount();

  %--- EyeTrack
  [dEyeRP2FrameCnt dFrameTimeMs ] = EyeTrackGetTiming( );
  dEyeFrameCnt = hEyeTrack.GetFrameCount();
  if abs(dEyeFrameCnt - dEyeRP2FrameCnt) > FrameMismatchMax
    fprintf('\n==>> Mismatch in frame count for the EyeTrack! RP2: %d,  EyeTrack: %d, Diff: %d\n', ... 
                                                          dEyeRP2FrameCnt, dEyeFrameCnt, dEyeRP2FrameCnt-dEyeFrameCnt );
  end

  pause(dSleepSec);
 
end

