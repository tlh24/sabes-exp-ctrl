load OptoTimingTestBlockingSensor_00.mat;

% vars in the mat file:
% TrackerTime
% TrackerXYZ
% nExtOn, nExtOff
% dExtOnTS, dExtOffTS

dXY = TrackerXYZ(1:2,:);
dTS = TrackerTime;

% find invalid points, i.e. where the sensor was blocked
idxInvalid = find( (dXY(1,:) < -1e10) | (dXY(2,:) <-1e10) );
fprintf('found %d invalid points\n', length(idxInvalid));
dTS = dTS(idxInvalid);

% group them by time
dTS_Delta = diff(dTS);

idxJump = find(dTS_Delta  > 100 ); % 10 frames threshold
nGroups = length( idxJump ) + 1;
fprintf('Found %d groups of invalid points\n', nGroups );

iGroup = zeros(size(dTS));
iStart = 1;
for i = 1:nGroups-1
  iEnd = idxJump(i);
  iGroup(iStart:iEnd) = i;
  iStart = iEnd+1;
end
iGroup(iStart:end) = nGroups;

dMeanTS = zeros(1, nGroups);
for i = 1:nGroups
  idx = find(iGroup == i);
  dMeanTS(i) = mean(dTS(idx));
end

% group on off by time
% figure; hist(dExtOffTS - dExtOnTS, 100); 
dOnfTS = (dExtOnTS + dExtOffTS)/2; % aver
dTS_Delta = diff(dOnfTS);

idxJump = find(dTS_Delta  > 100 ); % 10 frames threshold

nOnfGroups = length( idxJump ) + 1;
fprintf('Found %d groups of On/Off events\n', nOnfGroups );

iGroup = zeros(size(dOnfTS));
iStart = 1;
for i = 1:nOnfGroups-1
  iEnd = idxJump(i);
  iGroup(iStart:iEnd) = i;
  iStart = iEnd+1;
end
iGroup(iStart:end) = nOnfGroups;

dMeanOnfTS = zeros(1, nOnfGroups);
for i = 1:nOnfGroups
  idx = find(iGroup == i);
  dMeanOnfTS(i) = mean(dOnfTS(idx));
end

dTS_diff = dMeanTS - dMeanOnfTS;
figure; 
hist(dTS_diff,100);
title('Hist of group mean - ON/OFF mean');

fprintf('Average measurement delay, ms: %g\n', ...
            mean(dTS_diff));

          
