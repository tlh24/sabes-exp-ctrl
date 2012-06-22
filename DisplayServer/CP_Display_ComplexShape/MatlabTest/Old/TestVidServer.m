%VisSrvName = 'VisServer2';
VisSrvName = '128.218.66.193';

iNum = input('Enter 1 to start the server, 0 to stop:  ');

if( iNum > 0) 
  fprintf('Starting VisServer...\n')
  hW = 0;
  hFng = 0;
  hTrg = 0;
  hMou = 0;
  hTxt = 0;
  fprintf('VisWindow\n')
  hW = actxserver('VisServer.VisWindow',VisSrvName); pause(1);
  hW.calibrated = 0;
  fprintf('VisDisk\n')
  hFng = actxserver('VisServer.VisDisk',VisSrvName); pause(1);
%   fprintf('VisDisk\n')
%   hTrg = actxserver('VisServer.VisDisk',VisSrvName); pause(1);
%   fprintf('VisMouse\n')
%   hMou = actxserver('VisServer.VisMouse',VisSrvName); pause(1);
%   fprintf('VisText\n')
%   hTxt = actxserver('VisServer.VisText',VisSrvName); pause(1);
  fprintf('Done\n')

else
  if iscom(hTxt)  release(hTxt); end;
  if iscom(hMou)  release(hMou); end;
  if iscom(hTrg)  release(hTrg); end;
  if iscom(hFng)  release(hFng); end;
  if iscom(hW)  release(hW); end;
end