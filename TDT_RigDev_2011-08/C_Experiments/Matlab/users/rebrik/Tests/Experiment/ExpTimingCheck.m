global g_ExpData
ExperimentTimingUpdate;
d1 = g_ExpData;
pause(1);
ExperimentTimingUpdate;
d2 = g_ExpData;

d2.dDisplayFrameCnt - d1.dDisplayFrameCnt
d2.dTrackerFrameCnt - d1.dTrackerFrameCnt
d2.dEyeTrackFrameCnt - d1.dEyeTrackFrameCnt

% d2.dDisplayFrameTimeMs - d1.dDisplayFrameTimeMs
% d2.dTrackerFrameTimeMs - d1.dTrackerFrameTimeMs
% d2.dEyeTrackFrameTimeMs - d1.dEyeTrackFrameTimeMs

d2.dDisplayFrameTimeMs
d2.dTrackerFrameTimeMs
d2.dEyeTrackFrameTimeMs