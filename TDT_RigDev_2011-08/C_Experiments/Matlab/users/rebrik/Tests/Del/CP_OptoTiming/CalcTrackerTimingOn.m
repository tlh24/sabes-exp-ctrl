load OptoTimingTest_01.mat;

% vars in the mat file:
% TrackerTime
% TrackerXYZ
% nExtTS
% dExtTS

dXY = TrackerXYZ(1:2,:);
dTS = TrackerTime/1000; % convert times to seconds
% dTS = dTS + 10e-3;   % hack
% remove invalid points (useful for OptoTrak only)
idxValid = find( (dXY(1,:) > -1e10) & (dXY(2,:) >-1e10) );
dXY = dXY(:, idxValid );
dTS = dTS(idxValid );
fprintf('removed %d invalid points\n', length(idxValid));

% plot XY trajectories
figure;
plot(dXY(1,:), dXY(2,:));
axis equal;

dExtOnTS = dExtOnTS/1000; % convert times to seconds

dXY_On_1 = zeros(2,nExtOn);
dXY_On_2 = zeros(2,nExtOn);

% find the first trajectory point after the TTL 1->0 transition
% i.e. after covering the photodiode, 
% save it along the preceding trajectory point
for i = 1:nExtOn
  dTS_Idx = find( dTS > dExtOnTS(i));
  Idx = dTS_Idx(1);
  dXY_1(:,i) = dXY(:,Idx-1);
  dXY_0(:,i) = dXY(:,Idx);
  dTS_1(i) = dTS(Idx-1);
  dTS_0(i) = dTS(Idx); 
end

% plot off points in green, on points in red
figure;
plot(dXY_0(1,:), dXY_0(2,:), 'g.');
hold on;
plot(dXY_1(1,:), dXY_1(2,:), 'r.');
axis equal;


dVx = (dXY_0(1,:) - dXY_1(1,:))./(dTS_0 - dTS_1);

% figure;
% hist(dTS_On_2 - dTS_On_1);
% hist(dXY_On_2(1,:) - dXY_On_1(1,:), 50);


PlusVx_idx = find(dVx > 0);
dXp_1 = dXY_1(1,PlusVx_idx);
dXp_0 = dXY_0(1,PlusVx_idx);
dTSp_diff = dTS_0(PlusVx_idx) - dTS_1(PlusVx_idx);
dVxp = (dXp_0 - dXp_1)./dTSp_diff;
Cp = polyfit(dVxp, dXp_0, 1);


figure;
hold on;
plot( dVxp, dXp_0, 'g.');
plot( dVxp, dXp_1, 'r.');
XX = xlim();
YY = polyval(Cp, XX);
plot( XX, YY, 'k-');

dDelayMs_p = -Cp(1)*1000;
fprintf('Calculated measurement delay for positive velocity, ms: %g\n', dDelayMs_p);


MinusVx_idx = find(dVx < 0);
dXm_1 = dXY_1(1,MinusVx_idx);
dXm_0 = dXY_0(1,MinusVx_idx);
dTSm_diff = dTS_0(MinusVx_idx) - dTS_1(MinusVx_idx);
dVxm = (dXm_0 - dXm_1)./dTSm_diff;
Cm = polyfit(dVxm, dXm_0, 1);


figure;
hold on;
plot( dVxm, dXm_0, 'g.');
plot( dVxm, dXm_1, 'r.');
XX = xlim();
YY = polyval(Cm, XX);
plot( XX, YY, 'k-');

dDelayMs_m = -Cm(1)*1000;
fprintf('Calculated measurement delay for negative velocity, ms: %g\n', dDelayMs_m);

