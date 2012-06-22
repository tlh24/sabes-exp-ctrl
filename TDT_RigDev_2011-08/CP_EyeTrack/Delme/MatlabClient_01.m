srvname = 'CP_EyeTrack.Application'

hITrack=actxserver(srvname);
% get(hITrack)
% methods(hITrack)
% disp(hITrack.strProgramVersion);

hITrack.ConnectISCAN();
pause(0.2)

figure;
axis equal
axis manual 
axis([-10 5300 -10 2600]);
axis ij
hold on;

while  isempty(get(gcf,'CurrentCharacter'))
  [iIdx dData] = hITrack.GetLatestData; 
  plot(dData(2), dData(3), 'x');
  drawnow;
%   disp( sprintf('%f\t%d\t%d\r', dT, iX, iY ));
  pause(0.5);
end

hITrack.DisconnectISCAN();
delete(hITrack);

