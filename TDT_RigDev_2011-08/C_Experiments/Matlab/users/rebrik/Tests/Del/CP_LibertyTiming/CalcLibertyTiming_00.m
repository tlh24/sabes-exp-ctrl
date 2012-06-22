load LibertyTimingTest_01.mat;

% TrackerTime
% TrackerXYZ
% nExtTS
% dExtTS

dXY = TrackerXYZ(1:2,:);
figure;
plot(dXY(1,:), dXY(2,:));

% convert milliseconds to seconds
dTS = TrackerTime/1000;
dExtOffTS = dExtOffTS/1000;

dXY_Off_1 = zeros(2,nExtOff);
dXY_Off_2 = zeros(2,nExtOff);

for i = 1:nExtOff
 dTS_Idx = find( dTS > dExtOffTS(i));
 Idx = dTS_Idx(1);
 dXY_Off_1(:,i) = dXY(:,Idx-1);
 dXY_Off_2(:,i) = dXY(:,Idx);
 dTS_Off_1(i) = dTS(Idx-1);
 dTS_Off_2(i) = dTS(Idx); 
end

figure;
plot(dXY_Off_1(1,:), dXY_Off_1(2,:), 'r.');
hold on;
plot(dXY_Off_2(1,:), dXY_Off_2(2,:), 'g.');
axis equal;

dV(1,:) = (dXY_Off_2(1,:) - dXY_Off_1(1,:))./(dTS_Off_2 - dTS_Off_1);

PlusVx_idx = find(dV(1,:) > 0);
dXYp_1 = dXY_Off_1(:,PlusVx_idx);
dXYp_2 = dXY_Off_2(:,PlusVx_idx);
dTSp_1 = dTS_Off_1(PlusVx_idx);
dTSp_2 = dTS_Off_2(PlusVx_idx);

dVp(1,:) = (dXYp_2(1,:) - dXYp_1(1,:))./(dTSp_2 - dTSp_1);
dVp(2,:) = (dXYp_2(2,:) - dXYp_1(2,:))./(dTSp_2 - dTSp_1);


dVabs = sqrt(dVp(2,:).^2 + dVp(1,:).^2) ;

figure;
hist( dVabs);


figure;
dMinX = min(dXYp_2(1,:));
dX= dXYp_2(1,:) - dMinX;
plot( dVabs, dX, '.');
c = polyfit(dVabs, dX, 1);




