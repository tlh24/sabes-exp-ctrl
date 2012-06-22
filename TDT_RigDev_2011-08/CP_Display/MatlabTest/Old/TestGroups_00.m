% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
% hVMain.GetVersion

nFrames = 1000;

DiskSize = 100;
nVertices = 3;

DiskSpace = 120;
nDisksX = 5;
nDisksY = 5;
nDisks = nDisksX * nDisksY;

hVMain.StartBatchDraw;
for i=1:NARROWS
  hArrows(i) =  CreatePolyArrow(strDisplayComputer);
  hArrows(i).SetScale(ArrowLength);
  hArrows(i).SetAngle(0);
  hArrows(i).SetColor([1 0 0]);
  hArrows(i).SetGroupID(1);
end

for i=2:2:NARROWS
  hArrows(i).SetGroupID(2);
end

ARROW_CORNER = [ 200 200 ];
for i=1:NARROWX,  
  for j=1:NARROWY;
    hArrows((i-1)*NARROWY + j).SetXY( ARROW_CORNER + ArrowSpace*[i-1, j-1]);
  end
end 

for i=1:NARROWS
  hArrows(i).SetTextureFlag(1);
  hArrows(i).Show;
end
hVMain.FinishBatchDraw;

dAngleStep = 360/nFrames;
% tic;
% for iFrame = 1:nFrames
%   hVMain.StartBatchDraw; 
%   for i=1:NARROWS
%     hArrows(i).SetAngle( dAngleStep * iFrame );
%   end 
%   hVMain.FinishBatchDraw;
% end
% toc/nFrames

tic;

for iFrame = 1:nFrames
  hVMain.StartBatchDraw;
  hVMain.RotateGroup(1,dAngleStep);
  hVMain.RotateGroup(2,-dAngleStep);
  hVMain.FinishBatchDraw;
end
toc/nFrames

hVMain.HideGroup(0);
for i=1:NARROWS
  if iscom(hArrows(i))  release(hArrows(i)); end;
end

if iscom(hVMain)  release(hVMain); end;
