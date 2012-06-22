strFileName = 'IScanEyeCalib.rs232';


dStd = 10; % standrd variation (noise around the point)

nPointsX = 4;
nPointsY = 3;
nSecondsPerPoint =5;


% one-to-one mapping
% MinX = -90;
% MaxX = 90;
% MinY = 60;
% MaxY = 210;



MinX = 2000;
MaxX = 3600;
MinY = 1000;
MaxY = 1600;

nDataPerPoint = 120 * nSecondsPerPoint; % assumes 120Hz frame rate

% this order makes X change first
[GridY, GridX] = meshgrid(1:nPointsY, 1:nPointsX);


StepX = (MaxX-MinX)/(nPointsX-1);
GridX = (GridX-1) * StepX;
GridX = GridX + MinX;

StepY = (MaxY - MinY)/(nPointsY-1);
GridY = (GridY-1) * StepY;
GridY = MaxY - GridY; % invert Y axis

nPoints = nPointsX * nPointsY;

% plot( GridX(:), GridY(:), '.');

vals = [];

DataX = repmat(GridX(:)', nDataPerPoint, 1);
DataY = repmat(GridY(:)', nDataPerPoint, 1);

DataX = DataX(:);
DataY = DataY(:);

nTotPoints = nPoints*nDataPerPoint;
vals (2, :) = DataX + randn(nTotPoints, 1) * dStd;
vals (3, :) = DataY + randn(nTotPoints, 1) * dStd;;

plot( vals (2, :), vals (3, :), '.');

% sync 
chSync = hex2dec('44');
wSync = chSync + chSync * 256;
vals(1, :) = ones(1, nTotPoints) * wSync;

% frames
vals(4, :) = 1: nTotPoints ;
vals(4, :) = mod( vals(4, :), 16 ) * 10;  % wrap around at 15 ( 4 bits )

hf=fopen( strFileName, 'wb' );
fwrite(hf, vals, 'int16' );
fclose(hf);
 


