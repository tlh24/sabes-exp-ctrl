VisSrvName = 'VisServer1';
% VisSrvName = 'grappelli';

nFrames = 2000;
%%% Liberty parameters
BUFFERTIME = 600;
PREDTIME   = 1/75;
FRAMERATE  = 240;


fprintf('Starting VisServer...\n')
fprintf('VisWindow\n')
hW = actxserver('VisServer.VisWindow',VisSrvName); 

if ~hW.calibrated 
  fprintf('VisServer is not calibrated. The test is stopped. \n');
  if iscom(hL)  release(hL); end;
  if iscom(hFng)  release(hFng); end;
  if iscom(hW)  release(hW); end;
  return;
end
fprintf('VisDisk\n')
hFng = actxserver('VisServer.VisDisk',VisSrvName); 
hFngPred = actxserver('VisServer.VisDisk',VisSrvName); 

fprintf('LibertyServer...\n');

hL = actxserver('LibertyServer.Liberty');
hL.clearErrs();
hL.setup(BUFFERTIME,PREDTIME); 
pause(0.5);
hL.active =1;
%hL.startBuffer();
fprintf('Move the sensor when the disk appears\n')
hW.batchmode = 1;
fprintf('Pause...\n');
pause(5);

hFng.show =1;
hFngPred.color = [1,0,0]
hFngPred.show =1;

tic
for i=1:nFrames
  batch_mode = hW.batchmode;  % just a read to get synchronized
  L = hL.latest;
  pos = L(1,[4,3]); 
  ppos = L(1,[16,15]); 
  hFng.pos = pos;
  hFngPred.pos = ppos;
  hW.drawnow();
end
toc/nFrames
fprintf('Finished\n');
hL.active = 0;
%hL.stopBuffer();

if iscom(hL)  release(hL); end;
if iscom(hFng)  release(hFng); end;
if iscom(hFngPred)  release(hFngPred); end;

if iscom(hW) 
  hW.drawnow();
  release(hW); 
end;

