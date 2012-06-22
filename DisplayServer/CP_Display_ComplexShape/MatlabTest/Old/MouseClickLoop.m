% VisSrvName = 'VisServer2';
VisSrvName = 'grappelli';

fprintf('Starting VisServer...\n')
fprintf('VisWindow\n')
hW = actxserver('VisServer.VisWindow',VisSrvName); pause(1);
hW.calibrated = 0;
fprintf('VisDisk\n')
hFng = actxserver('VisServer.VisDisk',VisSrvName); pause(1);
fprintf('VisMouse\n')
hMou = actxserver('VisServer.VisMouse',VisSrvName); pause(1);
fprintf('Move and click the mouse on the VisServer. Right-Click to exit. \n')


hFng.show =1;
hMou.capture();
while 1
  click = hMou.click;
  if click(1) 
    pos = hMou.pos;
    hFng.pos = [pos(1) 768 - pos(2)];
    fprintf('X=%g    Y=%g\n', pos(1), pos(2));
  end;
  if click(3) break; end;
  hMou.reset();
  pause(0.2);
end
if iscom(hMou)  release(hMou); end;
if iscom(hFng)  release(hFng); end;
if iscom(hW)  release(hW); end;

