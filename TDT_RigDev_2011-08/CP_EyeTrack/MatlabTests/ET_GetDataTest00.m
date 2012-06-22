srvname = 'CP_EyeTrack.Application';

hEye=actxserver(srvname);

hEye.ConnectTracker();
pause(0.5)
iIdx = hEye.GetDataIndexLatest;

nPoints = 10;
iIdx0 = iIdx - nPoints +1;
[dTimeStamps, dTrajectory] = invoke( hEye, 'GetDataBuffered', iIdx0, nPoints  )

% hEye.DisconnectTracker();

% delete(hEye)



