srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname);

nFrames0 = hTracker.GetFrameCount()

pause(1);

hTracker.ConnectTracker;
nFrames1 = hTracker.GetFrameCount()

pause(2);

nFrames2 = hTracker.GetFrameCount()

pause(2);

nFrames3 = hTracker.GetFrameCount()

hTracker.DisconnectTracker;
nFrames4 = hTracker.GetFrameCount()
pause(1);
nFrames5 = hTracker.GetFrameCount()

delete(hTracker);


