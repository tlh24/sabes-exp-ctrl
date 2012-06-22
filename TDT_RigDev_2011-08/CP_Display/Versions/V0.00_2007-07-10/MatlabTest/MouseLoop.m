ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
hVMain.GetVersion
hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 
hVMouse = actxserver('CP_Display.VMouse', strDisplayComputer); 

nTimes = 5000;

fprintf('Move the mouse on CP_Display. Click to start. \n')
hVMain.ResetEventLog;
hVMain.StartSync;
hVDisk.Show;

hVDisk.SetRadius(5);
hVDisk.SetColor([0 1 1]);
hVMouse.Show;
hVMouse.ClearEvents;
click(1)=0;
while ~click(1)
  click = hVMouse.GetDownEvents;
end
tic
for i=1:nTimes
  pos = double(hVMouse.GetXY);
%   hVDisk.SetXY([pos(1) 768 - pos(2)], i );
  hVDisk.SetXY([pos(1) 768 - pos(2)]);
end
dTime = toc/nTimes*1000;
fprintf('%g ms per frame\n', dTime);

 hVMouse.Hide;
[eI eT] = hVMain.GetEventLog;
fprintf('Finished\n');
hVMain.StopSync;
if iscom(hVMouse)  release(hVMouse); end;
if iscom(hVDisk)  release(hVDisk); end;
if iscom(hVMain)  release(hVMain); end;

% dT = diff(eT);
% dT = dT(2:end);
% max(dT)
% min(dT)