nSecs = 3600 * 4;  % 4 hours

dEyeFrame = [];
dEyeTime = [];
dTrackerFrame = []; 
dTrackerTime = [];
dDisplayFrame = []; 
dDisplayTime = [];


for i=1:nSecs
  [dEyeFrame(i) dEyeTime(i)] = EyeTrackGetTiming;
  [dTrackerFrame(i) dTrackerTime(i)] = TrackerGetTiming;
  [dDisplayFrame(i) dDisplayTime(i)] = DisplayGetTiming;
  pause(1);
  if mod(i,10) == 0
    fprintf('%d of % d \n',i, nSecs);
  end
end

save dEyeFrame 
save dEyeTime 
save dTrackerFrame 
save dTrackerTime 
save dDisplayFrame 
save dDisplayTime