% Check TimeSync granularity
nTimes = 10000;

dTimeMs = zeros(nTimes,1);

tic;
for i = 1:nTimes
  dTimeMs(i) = TimeSyncGetTimeMs;
end
dTime = toc;
fprintf('Matlab time, ms: %g\n', dTime * 1000);
fprintf('TDT time, ms: %g\n', (dTimeMs(nTimes) - dTimeMs(1)));
figure;
dDiffTimeMs = diff(dTimeMs);
hist(dDiffTimeMs,100);
nOver1ms = length(find(dDiffTimeMs>1));
fprintf('Times over 1ms: %d  out of %d\n', nOver1ms, nTimes);