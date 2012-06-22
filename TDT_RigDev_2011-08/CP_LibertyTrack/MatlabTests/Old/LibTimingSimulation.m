dTotalTime = 100;
dSampInterval = 0.099; % 99 ms
dFrameInterval = 1/240; % 240 Hz

nSamps = floor(dTotalTime / dSampInterval);
nFrames = floor(dTotalTime / dFrameInterval);

iSamps = 1:nSamps;
dSampTimes = iSamps * dSampInterval;

iFrames = 1:nFrames;
dFrameTimes = iFrames * dFrameInterval;


iSampFrames = zeros(1,nSamps);
for i=iSamps
  idx = find( dFrameTimes < dSampTimes(i));
  iSampFrames(i) = max(idx);
  
end


coeffs = polyfit(iSampFrames,dSampTimes,1); 
dShift = coeffs(2);
dCalcFrameInterval = coeffs(1);

% calc time from from frame number.
% dCalcFrameInterval/2 is the bias due to uncertainty of one frame
dCalcFrameTimes = iFrames * dCalcFrameInterval + dShift - dCalcFrameInterval/2;



figure;
stairs(iSampFrames,dSampTimes);
hold on
plot(iFrames, dFrameTimes, '.r');
plot(iFrames, dCalcFrameTimes, 'xg');

figure;
hist(dCalcFrameTimes-dFrameTimes);
