% VisSrvName = 'VisServer2';
VisSrvName = 'grappelli';

fprintf('Starting VisServer...\n')
fprintf('VisWindow\n')
hW = actxserver('VisServer.VisWindow',VisSrvName); 
hW.calibrated = 0;
fprintf('VisDisk\n')
hFng = actxserver('VisServer.VisDisk',VisSrvName); 
fprintf('VisMouse\n')
hMou = actxserver('VisServer.VisMouse',VisSrvName); 
fprintf('Move the mouse on the VisServer. Click to start. \n')

hW.batchmode = 0;
hFng.show =1;
hMou.capture();

click(1)=0;
while ~click(1)
  click = hMou.click;
end
tic
for i=1:1000
  batch_mode = hW.batchmode;  % just a read to get synchronized
  pos = hMou.pos;
  hFng.pos = [pos(1) 768 - pos(2)];
%  hW.drawnow();
end
toc/1000
fprintf('Finished\n');
if iscom(hMou)  release(hMou); end;
if iscom(hFng)  release(hFng); end;
if iscom(hW)  release(hW); end;

