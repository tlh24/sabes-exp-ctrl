TimeSyncStop;
TimeSyncStart;
iCount = 0;

while 1
  JuiceStart(100);
  ToneStart(1000, 400);
  RecordingStop;
  RecordingStart;
  DisplayGetTiming;
  EyeTrackGetTiming;
  TrackerGetTiming;
  pause(1);
  JuiceGetEvents;
  JuiceGetExtEvents;
  RecordingGetEvents;
  
  iCount = iCount + 1;
  fprintf('Count: %d\n', iCount);
  
end