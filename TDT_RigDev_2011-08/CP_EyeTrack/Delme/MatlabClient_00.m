srvname = 'CP_EyeTrack.Application'

hITrack=actxserver(srvname);
% get(hITrack);
% methods(hITrack);
disp(hITrack.strProgramVersion);

hITrack.ConnectISCAN();
pause(0.1)

CalibMtx = hITrack.GetCalibrationMatrix;
TstCalibMtx = ...
  [822.2246929384734,12.325397148791163;
  -0.479200248296951,-0.073206937866954;
  -0.949284037249709,1.584299036987885;
  0.000083484508809,0.000049127138607;
  0.000219606181675,-0.000429203167066;
  0.000130796947145,-0.000594291358944;];
  

hITrack.PutCalibrationMatrix(TstCalibMtx);

for( i=1:100 )
  [iIdx dData] = hITrack.GetLatestData; 
  if rem(i,10) == 0
    fprintf('%d\t%d\t%.1f\t%g\t%g\t%g\t%g\r', ...
             i, iIdx, dData(1), dData(2), dData(3) , dData(4), dData(5));
  end
  pause(0.05);
end
hITrack.DisconnectISCAN();

delete(hITrack)


