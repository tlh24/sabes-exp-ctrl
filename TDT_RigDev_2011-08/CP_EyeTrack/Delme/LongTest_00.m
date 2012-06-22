srvname = 'CP_EyeTrack.Application'

hITrack=actxserver(srvname);
% get(hITrack);
% methods(hITrack);
disp(hITrack.strProgramVersion);

tic
while 1
  hITrack.ConnectISCAN();
  pause(0.1)

  for( i=1:100 )
    [iIdx dData] = hITrack.GetLatestData; 
    if rem(i,10) == 0
      fprintf('%d\t%d\t%.1f\t%g\t%g\t%g\t%g\r', ...
               i, iIdx, dData(1), dData(2), dData(3) , dData(4), dData(5));
    end
    pause(0.05);
  end
  hITrack.DisconnectISCAN();
  toc
end 
delete(hITrack)



