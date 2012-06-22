ServerNamesInclude;
DisplaySizeInclude;

DurationSec = 60;
nFrames = DurationSec * 240;
DiskRadius = 2;  % in mm
DiskColor = [0 1 0];  % green

hTracker=actxserver(strTrackerName, strTrackerComputer);
hTracker.ConnectTracker;
pause(0.1);

% Connect to the display
hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
DispCalibMtx = GetDisplayCalibMatrix(  );
hVMain.SetTransformMatrix(DispCalibMtx);

hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 
hVDisk.SetColor(DiskColor);
hVDisk.SetRadius(DiskRadius);
hVDisk.SetFillFlag(0);
hVDisk.Show;

tic;
iPrevIdx = 0;
for i=1:nFrames
  while 1
    [iIdx, Times, Coord ] = invoke( hTracker, 'GetSensorLatest', 1, 1 );
    if iIdx ~= iPrevIdx;
      iPrevIdx = iIdx;
      break
    end
  end
  hVDisk.SetXY(double(Coord(1:2)) );
end 
fprintf('Frame time, ms %g\n', toc/nFrames*1000);
delete(hVDisk);
delete(hVMain);
delete(hTracker);
