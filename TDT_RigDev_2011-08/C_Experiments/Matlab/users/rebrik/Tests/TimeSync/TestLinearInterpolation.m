
load AllTiming_Jarrett_20080129.mat

% load AllTiming_Jarrett_20080117.mat
% load AllTiming_Bessie_20080117.mat

% dEyeFrame dEyeTime dTrackerFrame dTrackerTime dDisplayFrame dDisplayTime



nPoints = length(dEyeFrame);
iRange = 1:nPoints;
dEyeTime =  dEyeTime(iRange); 
dEyeFrame =  dEyeFrame(iRange); 
dC1 = (dEyeTime(end) - dEyeTime(1))/(dEyeFrame(end) - dEyeFrame(1));
dC0 = dEyeTime(1);
dCalcEyeTime = dC0 + dC1 * (dEyeFrame- dEyeFrame(1));

fprintf('IScan frame rate: %g\n', 1000/dC1);

figure;
plot(dEyeTime - dCalcEyeTime);

% figure;
% hist(diff(dEyeTime - dCalcEyeTime));

dC0 = dTrackerTime(1);
dC1 = (dTrackerTime(end) - dTrackerTime(1))/(dTrackerFrame(end) - dTrackerFrame(1));
dC0 = dTrackerTime(1);
dCalcTrackerTime = dC0 + dC1 * (dTrackerFrame- dTrackerFrame(1));

fprintf('Liberty frame rate: %g\n', 1000/dC1);

figure;
plot(dTrackerTime - dCalcTrackerTime);

% figure;
% hist(diff(dTrackerTime - dCalcTrackerTime));

dC0 = dDisplayTime(1);
dC1 = (dDisplayTime(end) - dDisplayTime(1))/(dDisplayFrame(end) - dDisplayFrame(1));
dC0 = dDisplayTime(1);
dCalcDisplayTime = dC0 + dC1 * (dDisplayFrame- dDisplayFrame(1));

fprintf('Display frame rate: %g\n', 1000/dC1);


figure;
plot(dDisplayTime - dCalcDisplayTime);

% figure;
% hist(diff(dTrackerTime - dCalcTrackerTime));



