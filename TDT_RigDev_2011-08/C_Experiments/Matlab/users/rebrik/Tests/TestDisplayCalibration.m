function TestDisplayCalibration()

ServerNamesInclude;
DisplaySizeInclude;

DurationSec = 60;
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

fprintf('Test will run for %d seconds.\n', DurationSec);


tic;
iPrevIdx = 0;
nFrames = 0;
while toc < DurationSec
  while 1
    [iIdx, Times, Coord ] = invoke( hTracker, 'GetSensorLatest', 1, 1 );
    if iIdx ~= iPrevIdx;
      iPrevIdx = iIdx;
      nFrames=nFrames+1;
      break
    end
  end
  hVDisk.SetXY(Coord(1:2));
end 


fprintf('Got %d frames,  %g ms per frame\n', nFrames, toc/nFrames*1000);
delete(hVDisk);

delete(hVMain);
delete(hTracker);