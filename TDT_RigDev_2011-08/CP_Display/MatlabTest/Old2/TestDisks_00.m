% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
% hVMain.GetVersion

nFrames = 1000;
nDisks = 20;

for i=1:nDisks
  hDsk(i) = actxserver('CP_Display.VDisk', strDisplayComputer); 
end
disk_params = rand(5, nDisks, nFrames);
scale_vect = [1023 767 1 1 1]';
scale_mat = repmat(scale_vect, [1, nDisks, nFrames]); 
disk_params = scale_mat .* disk_params; % X,Y-coord, RGB

hVMain.StartBatchDraw;
for i=1:nDisks
  hDsk(i).SetColor([disk_params(3:5,i,1)]);
  hDsk(i).SetN_Vertices(40);
  hDsk(i).Show;
end

tic
for j=1:nFrames
  hVMain.StartBatchDraw;
  for i = 1:nDisks
    hDsk(i).SetXY([disk_params(1:2,i,j)]);
  end
  hVMain.FinishBatchDraw;
end
dT = toc/nFrames*1000;
fprintf('%g ms per frame\n', dT);

for i=1:nDisks
  if iscom(hDsk(i))  release(hDsk(i)); end;
end
if iscom(hVMain)  release(hVMain); end;

