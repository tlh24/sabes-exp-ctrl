function ExpData = ExperimentStop()

ExperimentGlobalsInclude;

hVMain = g_ExpData.hVMain;
hTracker = g_ExpData.hTracker;
hEyeTrack = g_ExpData.hEyeTrack;

if iscom(hVMain)
  hVMain.StopSync;
  delete( hVMain );
end

if iscom(hTracker)
  hTracker.DisconnectTracker;
  delete( hTracker );
end

if iscom(hEyeTrack)
  hEyeTrack.DisconnectTracker;
  delete( hEyeTrack );
end


%--- Get final timing
[dFrameCnt dFrameTimeMs ] = DisplayGetTiming( );
g_ExpData.dDisplayFrameCnt = dFrameCnt;
g_ExpData.dDisplayFrameTimeMs = dFrameTimeMs;

[dFrameCnt dFrameTimeMs ] = TrackerGetTiming( );
g_ExpData.dTrackerFrameCnt = dFrameCnt;
g_ExpData.dTrackerFrameTimeMs = dFrameTimeMs;

[dFrameCnt dFrameTimeMs ] = EyeTrackGetTiming( );
g_ExpData.dEyeTrackFrameCnt = dFrameCnt;
g_ExpData.dEyeTrackFrameTimeMs = dFrameTimeMs;


TimeSyncStop;

ExpData = g_ExpData;
clear g_ExpData;

