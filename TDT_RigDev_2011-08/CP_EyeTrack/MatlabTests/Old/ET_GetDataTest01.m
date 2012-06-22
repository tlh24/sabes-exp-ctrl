srvname = 'CP_EyeTrack.Application';

hITrack=actxserver(srvname);

hITrack.ConnectTracker();
pause(0.1)
iIdx0 = hITrack.GetIndexLatest;

dDuration = 0;
tic;
iCount = 0;
while( dDuration < 30 ) % 30 seconds
  [iIdx dTime dData] = hITrack.GetDataLatest; 
  
  if rem(iCount,10) == 0
    fprintf('%d \t%g \t%g \t%g \n', ...
             iIdx, dTime(1), dData(1), dData(2));
  end
  pause(0.05);
  iCount = iCount+1;
  dDuration = toc;
end
iIdx1 = hITrack.GetIndexLatest;
nPoints = iIdx1 - iIdx0 + 1;
% [dTimeStamps, fTrajectory] = hITrack.GetDataBuffered( nPoints, iIdx0 );

[dTimeStamps, fTrajectory] = invoke( hITrack, 'GetDataBuffered', nPoints, iIdx0 );

figure;
plot(fTrajectory(1,:), fTrajectory(2,:), '.');

figure;
subplot(2,1,1);
plot(dTimeStamps, fTrajectory(1,:));
subplot(2,1,2);
plot(dTimeStamps, fTrajectory(2,:));


% hITrack.DisconnectTracker();

% delete(hITrack)



