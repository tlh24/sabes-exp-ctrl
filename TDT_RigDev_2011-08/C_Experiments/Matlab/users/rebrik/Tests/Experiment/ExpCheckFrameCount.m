% load FrameCount_Jimi_2008-05-07
load FrameCount_Axl_2008-05-07
% load FrameCount_H1_2008-08-08b.mat

DispDiff0 = dDisplayRP2FrameCnt - dDisplayFrameCnt0;
figure; hist(DispDiff0); title('Display: RP2-FrameCountPre');

DispDiff1 = dDisplayRP2FrameCnt - dDisplayFrameCnt1;
figure; hist(DispDiff1); title('Display: RP2-FrameCountPost');


TrackerDiff0 = dTrackerRP2FrameCnt - dTrackerFrameCnt0;
figure; hist(TrackerDiff0); title('Tracker: RP2-FrameCountPre');

TrackerDiff1 = dTrackerRP2FrameCnt - dTrackerFrameCnt1;
figure; hist(TrackerDiff1); title('Tracker: RP2-FrameCountPost');

EyeDiff0 = dEyeRP2FrameCnt - dEyeFrameCnt0;
figure; hist(EyeDiff0); title('EyeTrack: RP2-FrameCountPre');

EyeDiff1 = dEyeRP2FrameCnt - dEyeFrameCnt1;
figure; hist(EyeDiff1); title('EyeTrack: RP2-FrameCountPost');