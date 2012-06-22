% make calibration grid figure (for printing)
DisplaySizeInclude;

nDisksX = 4;  % N disks horizontally
nDisksY = 3;  % N disks vertically

DiskRadius = 5;  % in pixels
% iDispayWidthPix = 1024;
% iDisplayHeightPix = 768;

% Margin = DiskRadius * 4;
Margin = 20;
GridW = iDispayWidthPix - ( Margin * 2 );
GridH = iDisplayHeightPix - ( Margin * 2 );
GridStepX = GridW / ( nDisksX -1 );
GridStepY = GridH / ( nDisksY -1 );

% calculate coordinates for the disk grid
for i=1:nDisksX
  for j=1:nDisksY
    DiskCoordIJ(j,i, :) = [ Margin + GridStepX * (i-1); Margin + GridStepY * (j-1)];
  end
end
% flatten the array
DiskCoord = reshape(DiskCoordIJ, [nDisksX * nDisksY, 2]);

figure;
plot(DiskCoord(:,1), DiskCoord(:,2), 'o');
axis([0 iDispayWidthPix 0 iDisplayHeightPix])
axis equal;