srvname = 'CP_EyeTrack.Application';

hEye=actxserver(srvname);
figure;
hEye.ConnectTracker();
pause(5)
hold on;
nPoints = 100;
dDuration = 0;
tic;
while( dDuration < 120 ) % 120 seconds
  iIdx = [];
  dTime = [];
  dData = [];
  [iIdx dTime dData] = invoke( hEye, 'GetDataLatest', nPoints); 
  [dAver] = mean(dData,2);
%   plot(dAver(1), dAver(2), 'r.');
%   plot(dData(1,1), dData(2,1), 'g.');
%   drawnow;
  pause(0.05);
  dDuration = toc;
end

% hEye.DisconnectTracker();

% delete(hEye)



