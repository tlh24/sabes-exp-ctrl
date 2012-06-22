global g_ExpData

nSecs = 3600  * 4;  % 4 hours
nSecs = 100;
SecPerStep = 10;

dTrackerFrameRP2 = [];
dTrackerTimeRP2 = [];
dTrackerFrameSrv = [];
dC0 = [];
dC1 = [];

ExperimentTimingUpdate;
pause(5);

for i=1:(nSecs/SecPerStep)
  % [dEyeFrame(i) dEyeTime(i)] = EyeTrackGetTiming;
  % [dDisplayFrame(i) dDisplayTime(i)] = DisplayGetTiming;
  dTrackerFrameSrv1(i) = g_ExpData.hTracker.GetFrameCount();
  [dTrackerFrameRP2(i) dTrackerTimeRP2(i)] = TrackerGetTiming;
  dTrackerFrameSrv2(i) = g_ExpData.hTracker.GetFrameCount();
  [dC0(i) dC1(i)] = g_ExpData.hTracker.GetTimeScale();
  pause(SecPerStep);
  ExperimentTimingUpdate;
  fprintf('Tracker frame count. RP2: %d   Tracker(pre,post): % d   % d \n', ...
                dTrackerFrameRP2(i), dTrackerFrameSrv1(i), dTrackerFrameSrv2(i));
  fprintf('Run %d of % d \n',i, (nSecs/SecPerStep));
end

ExpStopRet = ExperimentStop;

save('ExpAllTiming', 'dTrackerFrameRP2','dTrackerTimeRP2', ...
     'dTrackerFrameSrv1', 'dTrackerFrameSrv2', 'dC0', 'dC1', 'ExpStopRet');
