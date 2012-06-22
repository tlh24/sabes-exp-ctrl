function [dC0 dC1] = TankGetTimeConversion(strTank, iBlock, dGlobRecSyncTS)

TimeSyncConfigInclude; % we use dGlobClockHz and iGlobTickPeriod
dTimeErrWarn = 1e-3;

dC0 = [];
dC1 = [];

[dRecSyncTS, dTimeSyncTS, dRP2_TickTS] = TankGetTimes(strTank, iBlock);

% calc linear conversion from RP2 ticks:
nRP2 = length(dRP2_TickTS);
if nRP2 < 10
  error('Not enough RP2 Tick events: %d  ', nRP2);
end


dTank_Duration = dRP2_TickTS(end) - dRP2_TickTS(1); % duration in tank time (sec)
dTS_Diff = diff(dRP2_TickTS);
dTS_DiffAver = mean(dTS_Diff);
dTS_DiffJitter = abs(dTS_Diff - dTS_DiffAver);
dTS_DiffMax = max(dTS_DiffJitter);
fprintf('Max jitter of RP2 tick pulses (ms):  %f\n', dTS_DiffMax*1000);

if dTS_DiffMax > dTimeErrWarn  
  error('RP2 tick jitter is over %e seconds', dTimeErrWarn);
end

dGlobPeriod = iGlobTickPeriod/dGlobClockHz;
dGlobDuration = dGlobPeriod * ( nRP2 - 1); % duration in RP2 time (sec)
dC1 = dGlobDuration / dTank_Duration;  % Global time divided by tank time

if nargin == 3 % we want to calc from the dGlobRecSyncTS
  if length(dRecSyncTS) ~= 1 || isnan(dRecSyncTS)
    error('Cannot calculate time conversion, there should be exactly one RecStart event in the tank');
  end

  dC0 = dGlobRecSyncTS - dRecSyncTS * dC1;
  fprintf('Timestamp conversion coeffs, c0 and c1:  %.5f  %.7f\n', dC0, dC1);
  return;
end

nLocTS = length(dTimeSyncTS);
if nLocTS < 1  
  error('Cannot calculate time conversion, no TimeSync pulses in the tank');
end

[dTimeSyncGlob dTimeSyncStream] = TankGetTimesync(strTank, iBlock);
nGlobTS = length(dTimeSyncGlob);
if nGlobTS < 1  
  error('Cannot calculate time conversion, no TimeSyncStream records in the tank stream');
end

if nLocTS ~= nGlobTS  
  warning('Mismatch in pulse/stream number of events: %d  %d', nLocTS, nGlobTS  );
  [PulseIdx StreamIdx] = TankMatchTimestamps(dTimeSyncTS, dTimeSyncStream);
  dTimeSyncGlob = dTimeSyncGlob(StreamIdx);
  dTimeSyncTS = dTimeSyncTS(PulseIdx);
end

dTimeSyncGlob = dTimeSyncGlob/1000; % convert to seconds from ms 
dC0 = dTimeSyncGlob(1) - dTimeSyncTS(1) * dC1;

fprintf('Timestamp conversion coeffs, c0 and c1:  %.5f  %.7f\n', dC0, dC1);

% Check fit quality

dCalcErr = abs(dTimeSyncGlob(2:end) - (dC0 + dC1*dTimeSyncTS(2:end))');

fprintf('=== Time conversion check === \n', mean(dCalcErr));
fprintf('Average fit error (sec): %g\n', mean(dCalcErr));
fprintf('Std of fit error: %g\n', std(dCalcErr));
fprintf('Min fit error(sec): %g\n', min(dCalcErr));
dCalcErrMax = max(dCalcErr);
fprintf('Max fit error (sec): %g\n', dCalcErrMax);

if dCalcErrMax > dTimeErrWarn;
  warning('Bad time conversion, max error is over %g sec\n', dTimeErrWarn );
end

% figure;
% hist(dCalcErr, 20);
% figure;
% plot(dTimeSyncGlob,dCalcErr); 






