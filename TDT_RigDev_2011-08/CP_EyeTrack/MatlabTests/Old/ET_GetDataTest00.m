srvname = 'CP_EyeTrack.Application';

hITrack=actxserver(srvname);

hITrack.ConnectTracker();
pause(0.5)
iIdx = hITrack.GetIndexLatest;

nPoints = 10;
iIdx0 = iIdx - nPoints +1;
[dTimeStamps, fTrajectory] = invoke( hITrack, 'GetDataBuffered', nPoints, iIdx0 );

% hITrack.DisconnectTracker();

% delete(hITrack)



