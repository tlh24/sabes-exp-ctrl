
ServerNamesInclude;

ExperimentTimingUpdate;
disp('wait for 10 seconds...');
pause(10);
ExperimentTimingUpdate;


EventID = 111111;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
hVMain.ResetEventLog;

hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 
dTimeMs = TimeSyncGetTimeMs();
hVDisk.Show(EventID);
[id DisplTime] = hVMain.GetEventLog;
delete(hVDisk);
delete(hVMain);

DisplShowTime = DisplTime(find(id == EventID));
fprintf('Display relative time, ms: %g\n', DisplShowTime-dTimeMs);


hTracker=actxserver(strTrackerName, strTrackerComputer);
hTracker.ConnectTracker;
pause(0.1);

dTimeMs = TimeSyncGetTimeMs();
[iIdx, TrackerTime, Coord ] = invoke( hTracker, 'GetSensorLatest', 1, 1 );
delete(hTracker);

fprintf('Tracker relative time, ms: %g\n', TrackerTime - dTimeMs);



hEye=actxserver('CP_EyeTrack.Application', strEyeTrackComputer);
hEye.ConnectTracker();
pause(0.1)


dTimeMs = TimeSyncGetTimeMs();
[iIdx, EyeTime, Coord ] = invoke( hEye, 'GetDataLatest', 1 );
delete(hEye);

fprintf('Eye relative time, ms: %g\n', EyeTime - dTimeMs);





