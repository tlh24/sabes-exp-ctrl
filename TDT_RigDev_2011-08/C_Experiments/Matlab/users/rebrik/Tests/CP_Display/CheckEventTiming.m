ServerNamesInclude;

nTimes = 10;
ScreenW = 1024;
ScreenH = 768;
BoxHalfW = 256;
BoxHalfH = 64;

DispOnID = 101;
DispOffID = 102;

TimeSyncClearEvents;
% Connect to the display
hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
TMtx1 = [  0     0
           1     0
           0     1
           0     0
           0     0
           0     0 ];

hVMain.SetTransformMatrix(TMtx1);
hVMain.ResetEventLog;
% [a b] = hVMain.GetTimeScale

hVPoly = actxserver('CP_Display.VPolygon', strDisplayComputer); 
hVPoly.SetXY([ScreenW - BoxHalfW ,ScreenH - BoxHalfH]);
% rectangle
Vertices = [ -BoxHalfW -BoxHalfW BoxHalfW BoxHalfW   
             -BoxHalfH BoxHalfH BoxHalfH -BoxHalfH  ];
hVPoly.SetVertices( Vertices);           
hVPoly.SetColor([1 1 1]);
hVPoly.SetFillFlag(1);

ExperimentTimingUpdate;
for i=1:nTimes
  hVPoly.Show(DispOnID);
  pause(1);
  hVPoly.Hide(DispOffID);
  pause(1);
end 

ExperimentTimingUpdate;
[id DisplTime] = hVMain.GetEventLog;
delete(hVPoly);
delete(hVMain);

[nExtJuiceOnEvents dExtJuiceOnTimes nExtJuiceOffEvents dExtJuiceOffTimes] = JuiceGetExtEvents;

DispOnTimes = DisplTime( find(id == DispOnID));
DispOffTimes = DisplTime( find(id == DispOffID));

DiffOn = dExtJuiceOnTimes - DispOnTimes;
DiffOff = dExtJuiceOffTimes - DispOffTimes;
figure; plot(DiffOn);
% figure;
% hist(DiffOn);
% figure;
% hist(DiffOff);
fprintf('On delay: %g\n', mean(DiffOn));
fprintf('On delay std: %g\n', std(DiffOn));
fprintf('Min On delay: %g\n', min(DiffOn));
fprintf('Max On delay: %g\n', max(DiffOn));
fprintf('Off delay: %g\n', mean(DiffOff));
fprintf('Off delay std: %g\n', std(DiffOff));
fprintf('Min Off delay: %g\n', min(DiffOff));
fprintf('Max Off delay: %g\n', max(DiffOff));
