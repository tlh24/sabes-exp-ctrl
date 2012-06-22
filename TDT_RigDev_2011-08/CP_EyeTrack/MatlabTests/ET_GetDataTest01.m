srvname = 'CP_EyeTrack.Application';

hEye=actxserver(srvname);

hEye.ConnectTracker();
pause(0.1)
iIdx0 = hEye.GetDataIndexLatest;

dDuration = 0;
tic;
iCount = 0;
while( dDuration < 30 ) % 30 seconds
  [iIdx dTime dData] = hEye.GetDataLatest; 
  
  if rem(iCount,10) == 0
    fprintf('%d \t%g \t%g \t%g \n', ...
             iIdx, dTime(1), dData(1), dData(2));
  end
  pause(0.05);
  iCount = iCount+1;
  dDuration = toc;
end
iIdx1 = hEye.GetDataIndexLatest;
nPoints = iIdx1 - iIdx0 + 1;
% [dTimeStamps, fTrajectory] = hEye.GetDataBuffered( nPoints, iIdx0 );

[dTimeStamps, dTrajectory] = invoke( hEye, 'GetDataBuffered', iIdx0, nPoints );

figure;
plot(dTrajectory(1,:), dTrajectory(2,:), '.');

figure;
subplot(2,1,1);
plot(dTimeStamps, dTrajectory(1,:));
subplot(2,1,2);
plot(dTimeStamps, dTrajectory(2,:));


% hEye.DisconnectTracker();

% delete(hEye)



