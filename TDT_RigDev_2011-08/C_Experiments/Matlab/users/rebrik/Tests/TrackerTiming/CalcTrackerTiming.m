% The model:
% The sensor is moving along the X - axis with velocity Vx
% If the reported coordinates are delayed relative to the true
% coordinates, the reported coordinate corresponding to the 
% event of crossing point of X0 coordinate will be:
% Xdaq = X0 - Vx * (Tau + Tau_rnd)
% where Tau is the measurement delay,
% Tau_rnd - random delay [+/- 0.5 Tframe] comes from the randomness
% of the On/Off events relative to the tracker measuremnt times
% Note: the photo pair outputs TTL high (On) when blocked

load OptoTimingTest.mat;
% load LibertyTimingTest_01.mat;

% vars in the mat file:
% TrackerTime
% TrackerXYZ
% nExtTS
% dExtTS

dXY = TrackerXYZ(1:2,:);
dTS = TrackerTime/1000; % convert times to seconds
dExtOnTS = dExtOnTS/1000; % convert times to seconds
dExtOffTS = dExtOffTS/1000; % convert times to seconds

% dExtOffTS = dExtOffTS + 10e-3; % sanity check (comment out in the actual calc!)
% dExtOnTS = dExtOnTS + 10e-3;% sanity check (comment out in the actual calc!)
% dTS = dTS - 10e-3;   % sanity check (comment out in the actual calc!)

% remove invalid points (used for OptoTrak, Liberty has no invalid coords)
idxValid = find( (dXY(1,:) > -1e10) & (dXY(2,:) >-1e10) );
dXY = dXY(:, idxValid );
dTS = dTS(idxValid );
fprintf('removed %d invalid points of total %d\n', ...
         length(TrackerTime) - length(idxValid), length(TrackerTime));

% % plot XY trajectories
% figure;
% plot(dXY(1,:), dXY(2,:));
% axis equal;
% title('Trajectories');

%%%%% Process ON events
dXY_1_On = zeros(2,nExtOn);
dXY_0_On = zeros(2,nExtOn);
dTS_1_On = zeros(1,nExtOn);
dTS_0_On = zeros(1,nExtOn);

% find the first trajectory point after the TTL 0->1 transition
% i.e. after UN-blocking the photocouple, 
% save it along the preceding trajectory point
for i = 1:nExtOn
  dTS_Idx = find( dTS > dExtOnTS(i));
  Idx = dTS_Idx(1);
  dXY_1_On(:,i) = dXY(:,Idx); % post
  dXY_0_On(:,i) = dXY(:,Idx-1); % pre
  dTS_1_On(i) = dTS(Idx);
  dTS_0_On(i) = dTS(Idx-1); 
end

%%%%% Process OFF events
dXY_1_Off = zeros(2,nExtOn);
dXY_0_Off = zeros(2,nExtOn);
dTS_1_Off = zeros(1,nExtOn);
dTS_0_Off = zeros(1,nExtOn);

% find the first trajectory point after the TTL 1->0 transition
% i.e. after blocking the photocouple, 
% save it along with the preceding trajectory point
for i = 1:nExtOff
  dTS_Idx = find( dTS > dExtOffTS(i));
  Idx = dTS_Idx(1);
  dXY_1_Off(:,i) = dXY(:,Idx);  % post
  dXY_0_Off(:,i) = dXY(:,Idx-1);  % pre
  dTS_1_Off(i) = dTS(Idx);
  dTS_0_Off(i) = dTS(Idx-1); 
end

% % Subtract the mean
dXY_mean = mean([ dXY_1_On  dXY_0_On dXY_1_Off dXY_0_Off],2);
% dXY_MeanMatOn = repmat(dXY_mean, 1, nExtOn);
% dXY_1_On = dXY_1_On - dXY_MeanMatOn;
% dXY_0_On = dXY_0_On - dXY_MeanMatOn;
% dXY_MeanMatOff = repmat(dXY_mean, 1, nExtOff);
% dXY_1_Off = dXY_1_Off - dXY_MeanMatOff;
% dXY_0_Off = dXY_0_Off - dXY_MeanMatOff;

% % plot on/off point pairs pre - in green, post - in red
% figure;
% hold on;
% axis equal;
% plot(dXY_0_On(1,:), dXY_0_On(2,:), 'go');
% plot(dXY_1_On(1,:), dXY_1_On(2,:), 'ro');
% title('ON Events point pairs pre - in green, post - in red');
% 
% figure;
% hold on;
% axis equal;
% plot(dXY_0_Off(1,:), dXY_0_Off(2,:), 'gx');
% plot(dXY_1_Off(1,:), dXY_1_Off(2,:), 'rx');
% title('OFF Events point pairs pre - in green, post - in red');

% calc velocities along the X-axis
dVx_On = (dXY_1_On(1,:) - dXY_0_On(1,:))./(dTS_1_On - dTS_0_On);
dVx_Off = (dXY_1_Off(1,:) - dXY_0_Off(1,:))./(dTS_1_Off - dTS_0_Off);

% figure;
% hist(dVx_On, 50);
% title('Velocity_x hist, ON events'); % velocity hist has the same shape
% figure;
% hist(dVx_Off, 50);
% title('Velocity_x hist, OFF events'); % velocity hist has the same shape

% find positive velocities for ON event
PlusVx_idx = find(dVx_On > 0);
% Select corresponding X pre/post coordinates
dXp_1_On = dXY_1_On(1,PlusVx_idx); 
dXp_0_On = dXY_0_On(1,PlusVx_idx);
dTSp_diff = dTS_1_On(PlusVx_idx) - dTS_0_On(PlusVx_idx);
dVxp_On = (dXp_1_On - dXp_0_On)./dTSp_diff;
dXp_On = (dXp_1_On + dXp_0_On)/2;
Cp_On = polyfit(dVxp_On, dXp_On, 1);

dDelayMs_p_On = -Cp_On(1)*1000;
fprintf('Calculated measurement delay for On events, positive velocity, ms: %g\n', ...
         dDelayMs_p_On);

% find positive velocities for OFF event
PlusVx_idx = find(dVx_Off > 0);
% Select corresponding X pre/post coordinates
dXp_1_Off = dXY_1_Off(1,PlusVx_idx);
dXp_0_Off = dXY_0_Off(1,PlusVx_idx);
dTSp_diff = dTS_1_Off(PlusVx_idx) - dTS_0_Off(PlusVx_idx);
dVxp_Off = (dXp_1_Off - dXp_0_Off)./dTSp_diff;
dXp_Off = (dXp_1_Off + dXp_0_Off)/2;
Cp_Off = polyfit(dVxp_Off, dXp_Off, 1); % lin fit of X = c1 * (V) + c2

dDelayMs_p_Off = -Cp_Off(1)*1000;
fprintf('Calculated measurement delay for Off events, positive velocity, ms: %g\n', ...
         dDelayMs_p_Off);

% find negative velocities On event
MinusVx_idx = find(dVx_On < 0);
% Select corresponding X pre/post coordinates
dXm_1_On = dXY_1_On(1,MinusVx_idx);
dXm_0_On = dXY_0_On(1,MinusVx_idx);
dTSm_diff = dTS_1_On(MinusVx_idx) - dTS_0_On(MinusVx_idx);
dVxm_On = (dXm_1_On - dXm_0_On)./dTSm_diff;
dXm_On = (dXm_1_On + dXm_0_On)/2;
Cm_On = polyfit(dVxm_On, dXm_On, 1); % lin fit of X = c1 * (V) + c2

dDelayMs_m_On = -Cm_On(1)*1000;
fprintf('Calculated measurement delay for On events, negative velocity, ms: %g\n', dDelayMs_m_On);

% find negative velocities Off event
MinusVx_idx = find(dVx_Off < 0);
% Select corresponding X pre/post coordinates
dXm_1_Off = dXY_1_Off(1,MinusVx_idx);
dXm_0_Off = dXY_0_Off(1,MinusVx_idx);
dTSm_diff = dTS_1_Off(MinusVx_idx) - dTS_0_Off(MinusVx_idx);
dVxm_Off = (dXm_1_Off - dXm_0_Off)./dTSm_diff;
dXm_Off = (dXm_1_Off + dXm_0_Off)/2;
Cm_Off = polyfit(dVxm_Off, dXm_Off, 1); % lin fit of X = c1 * (V) + c2

dDelayMs_m_Off = -Cm_Off(1)*1000;
fprintf('Calculated measurement delay for Off events, negative velocity, ms: %g\n', dDelayMs_m_Off);


figure;
hold on;
plot( dVxp_On, dXp_On, 'go');  
plot( dVxp_Off, dXp_Off, 'rx');  
plot( dVxm_On, dXm_On, 'go'); 
plot( dVxm_Off, dXm_Off, 'rx');
XX = xlim();
YY = ylim();
Y = polyval(Cp_On, XX);  % calc Y from the reg. coeffs
plot( XX, Y, 'g-');
Y = polyval(Cp_Off, XX);  % calc Y from the reg. coeffs
plot( XX, Y, 'r-');
Y = polyval(Cm_On, XX);  % calc Y from the reg. coeffs
plot( XX, Y, 'g--');
Y = polyval(Cm_Off, XX);  % calc Y from the reg. coeffs
plot( XX, Y, 'r--'); 

plot([0 0], YY, 'm');
legend('ON, V+','OFF, V+','ON, V-','OFF, V-', ...
       'ON, V+','OFF, V+','ON, V-','OFF, V-');

xlabel('X - velocity');
ylabel('X - coordinate');

fprintf('Average measurement delay, ms: %g\n', ...
  (dDelayMs_p_On+dDelayMs_p_Off+dDelayMs_m_On+dDelayMs_m_Off)/4 );

