% Check ExperimentRestart

ExperimentRestart

ServerNamesInclude;

EventID = 111111;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
hVMain.ResetEventLog;

hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 
dTimeMs1 = TimeSyncGetTimeMs();
hVDisk.Show(EventID);
dTimeMs2 = TimeSyncGetTimeMs();
[id DisplTime] = hVMain.GetEventLog;
DispShowTime = DisplTime( find(id == EventID));
delete(hVDisk);
delete(hVMain);

fprintf('Display times: %g  %g  %g\n', dTimeMs1, DispShowTime, dTimeMs2);

if DispShowTime < dTimeMs1 || DispShowTime > dTimeMs2 
  disp('Error in dispaly timing!')
end


hTracker=actxserver(strTrackerName, strTrackerComputer);
hTracker.ConnectTracker;
pause(0.1);

dTimeMs1 = TimeSyncGetTimeMs();
[iIdx, TrackerTime, Coord ] = invoke( hTracker, 'GetSensorLatest', 1, 1 );
dTimeMs2 = TimeSyncGetTimeMs();
delete(hTracker);

fprintf('Tracker times: %g  %g  %g\n', dTimeMs1, TrackerTime, dTimeMs2);


if TrackerTime < dTimeMs1 || TrackerTime > dTimeMs2 
  disp('Error in tracker timing!')
end

hEye=actxserver('CP_EyeTrack.Application', strEyeTrackComputer);
hEye.ConnectTracker();
pause(0.1)


dTimeMs1 = TimeSyncGetTimeMs();
[iIdx, EyeTime, Coord ] = invoke( hTracker, 'GetDataLatest', 1 );
dTimeMs2 = TimeSyncGetTimeMs();
delete(hTracker);

fprintf('Eye times: %g  %g  %g\n', dTimeMs1, EyeTime, dTimeMs2);


if EyeTime < dTimeMs1 || EyeTime > dTimeMs2 
  disp('Error in eye timing!')
end




