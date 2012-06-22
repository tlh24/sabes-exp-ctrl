
nHours = 4;
nHours = 10/60;
dSleepSec = 10;

nTimes = nHours * 3600 /dSleepSec;
% nTimes = 10;

ExperimentGlobalsInclude;

hVMain = g_ExpData.hVMain;
hTracker = g_ExpData.hTracker;
hEyeTrack = g_ExpData.hEyeTrack;

dDisplayFrameCnt = []; 
dDisplayRP2FrameCnt = [];
dTrackerFrameCnt = []; 
dTrackerRP2FrameCnt = [];
dEyeFrameCnt = [];
dEyeRP2FrameCnt = [];

for i = 1:nTimes
  fprintf('%d of % d \n',i, nTimes);
  %--- Display
  dDisplayFrameCnt0(i) = hVMain.GetFrameCount();
  [dDisplayRP2FrameCnt(i) dFrameTimeMs ] = DisplayGetTiming( );
  dDisplayFrameCnt1(i) = hVMain.GetFrameCount();


  %--- Tracker
  dTrackerFrameCnt0(i) = hTracker.GetFrameCount();
  [dTrackerRP2FrameCnt(i) dFrameTimeMs ] = TrackerGetTiming( );
  dTrackerFrameCnt1(i) = hTracker.GetFrameCount();

  %--- EyeTrack
  dEyeFrameCnt0(i) = hEyeTrack.GetFrameCount();
  [dEyeRP2FrameCnt(i) dFrameTimeMs ] = EyeTrackGetTiming( );
  dEyeFrameCnt1(i) = hEyeTrack.GetFrameCount();

  pause(dSleepSec);
 
end

ExStopRet = ExperimentStop;

save( 'FrameCount','ExStopRet', ...
      'dDisplayFrameCnt0', 'dDisplayRP2FrameCnt', 'dDisplayFrameCnt1', ...
      'dTrackerFrameCnt0', 'dTrackerRP2FrameCnt', 'dTrackerFrameCnt1', ...
      'dEyeFrameCnt0', 'dEyeRP2FrameCnt', 'dEyeFrameCnt1');



