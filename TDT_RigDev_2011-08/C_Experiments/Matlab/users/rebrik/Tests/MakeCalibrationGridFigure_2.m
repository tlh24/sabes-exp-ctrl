DisplaySizeInclude;
% we use these variables from DisplaySizeInclude:
% iDisplayX0 = 300;
% iDispayX1 = 700;
% iDisplayY0 = 200;
% iDispayY1 = 600;
% iDispayWidthPix = 1024;
% iDisplayHeightPix = 768;

% in pixels
DiskRadius = 5;  

nDisksX = 4;  % N disks horizontally
nDisksY = 3;  % N disks vertically

DiskColor = [0.5 0 0];  % dark red
TargetColorBegin = [1 1 1]; % white
TargetColorEnd = [0 1 0]; % green

nDisks = nDisksX * nDisksY;

GridW = iDispayX1 -iDisplayX0;
GridH = iDispayY1 -iDisplayY0;
GridStepX = GridW / ( nDisksX -1 );
GridStepY = GridH / ( nDisksY -1 );

% calculate coordinates for the disk grid
for i=1:nDisksX
  for j=1:nDisksY
    DiskCoordIJ(j,i, :) = [ iDisplayX0 + GridStepX * (i-1); iDisplayY0 + GridStepY * (j-1)];
  end
end
% flatten the array
DiskCoord = reshape(DiskCoordIJ, [nDisksX * nDisksY, 2]);

figure;
plot(DiskCoord(:,1),DiskCoord(:,2), '.b');
axis([0,iDispayWidthPix,0,iDisplayHeightPix])
axis equal;
