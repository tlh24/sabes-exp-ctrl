[dFrame1 dTime1] = EyeTrackGetTiming;
for i=1:10
  pause(1);
  [dFrame2 dTime2] = EyeTrackGetTiming;
  FrameRateHz(i) = (dFrame2 - dFrame1) /(dTime2 - dTime1) * 1000;
  fprintf('%g\n',FrameRateHz(i));
end

figure;
plot(FrameRateHz);