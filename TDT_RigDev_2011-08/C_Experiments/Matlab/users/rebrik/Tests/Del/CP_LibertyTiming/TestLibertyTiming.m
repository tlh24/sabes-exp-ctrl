nSeconds = 120;

ExperimentGlobalsInclude;
ExperimentTimingUpdate();
pause(10);

hTracker = g_ExpData.hTracker;
ToneStart( 500, 0.5  );
fprintf('Started\n');


% clear external juice events
TimeSyncClearEvents;

% get Liberty data buffer index
TrackerStartIdx = hTracker.GetDataIndexLatest;

for i=1:nSeconds
 pause(1);
 fprintf('%d sec of %d\n', i, nSeconds);
end

% get Liberty data buffer index
TrackerStopIdx = hTracker.GetDataIndexLatest;
fprintf('Stopped\n');
ToneStart( 500, 0.5  );

ExperimentTimingUpdate();
%read Liberty data buffer
TrackerN_Points = TrackerStopIdx - TrackerStartIdx + 1;
[TrackerTime TrackerXYZ] = invoke( hTracker, 'GetSensorBuffered', 1, TrackerStartIdx, TrackerN_Points );

% Get photodiode events
[nExtOn dExtOnTS nExtOff dExtOffTS] = JuiceGetExtEvents;


% save all in the mat file

save('LibertyTimingTest.mat', 'TrackerTime', 'TrackerXYZ', ... 
     'nExtOn', 'dExtOnTS', 'nExtOff', 'dExtOffTS');
   