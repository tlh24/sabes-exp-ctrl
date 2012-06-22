strVisServerName ='grappelli';

nFrames = 1000;

ArrowLength = 100;

ArrowSpace = 120;
NARROWX = 5;
NARROWY = 5;
NARROWS = NARROWX*NARROWY;

hW = actxserver('VisServer.VisWindow',strVisServerName);  pause(.1);
hW.calibrated = 0;
hW.batchmode =1;

for i=1:NARROWS
  hArrows(i) =  CreateArrow(strVisServerName);
  hArrows(i).scale = ArrowLength;
  hArrows(i).fill = 1;
  hArrows(i).Angle = 0;
  hArrows(i).color = [1 0 0];
end

ARROW_CORNER = [ 200 200 ];
for i=1:NARROWX,  
  for j=1:NARROWY;
    hArrows((i-1)*NARROWY + j).pos= ARROW_CORNER + ArrowSpace*[i-1, j-1];
  end
end 
for i=1:NARROWS
  hArrows(i).show = 1;
end
hW.drawnow();

tic;
for( iFrame = 1:nFrames )
  dummy = hW.batchmode;
  for i=1:NARROWS
    hArrows(i).angle = 360 * iFrame /nFrames;
  end 
  hW.drawnow();
end
toc/nFrames

for i=1:NARROWS
  if iscom(hArrows(i))  release(hArrows(i)); end;
end
hW.drawnow();

if iscom(hW)  release(hW); end;
