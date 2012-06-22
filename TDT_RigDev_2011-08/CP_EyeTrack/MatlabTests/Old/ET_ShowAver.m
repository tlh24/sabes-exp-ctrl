srvname = 'CP_EyeTrack.Application';

hITrack=actxserver(srvname);
figure;
hITrack.ConnectTracker();
pause(1)
figure;
hold on;
nPoints = 100;
dDuration = 0;
tic;
while( dDuration < 40 ) % 40 seconds
  [iIdx dTime dData] = invoke( hITrack, 'GetDataLatest', nPoints); 
  [dAver] = mean(dData,2);
  plot(dAver(1), dAver(2), 'r.');
  plot(dData(1,1), dData(2,1), 'g.');
  drawnow;
  pause(0.05);
  dDuration = toc;
end

% hITrack.DisconnectTracker();

% delete(hITrack)



