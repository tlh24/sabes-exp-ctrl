srvname = 'CP_EyeTrack.Application';

hEye=actxserver(srvname);

CalibMtx = hEye.GetTransformMatrix;
TstCalibMtx = ...
  [822.2246929384734,12.325397148791163;
  -0.479200248296951,-0.073206937866954;
  -0.949284037249709,1.584299036987885;
  0.000083484508809,0.000049127138607;
  0.000219606181675,-0.000429203167066;
  0.000130796947145,-0.000594291358944;];

hEye.SetTransformMatrix(TstCalibMtx);

hEye.ConnectTracker();
pause(0.1)

for i=1:100 
  [iIdx dTime dData] = hEye.GetDataLatest; 
  
%   [iIdx dData] = invoke( hEye, 'GetDataLatest', 1 ); 
  if rem(i,10) == 0
    fprintf('%d \t%d \t%g \t%g \t%g \n', ...
             i, iIdx, dTime(1), dData(1), dData(2));
  end
  pause(0.05);
end
% hEye.DisconnectTracker();

% delete(hEye)



