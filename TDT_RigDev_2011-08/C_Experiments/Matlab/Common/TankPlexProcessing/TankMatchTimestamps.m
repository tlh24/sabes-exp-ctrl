function [Idx1 Idx2] = TankMatchTimestamps(dTS1, dTS2)

dMaxDiff = 0.5;   % Max tolerance in seconds

n1 = length(dTS1);
n2 = length(dTS2);

dTDiff = ones(n1,n2)*1e10; % preallocate, fill with big numbers

for i1 = 1:n1
  for i2 = 1:n2
    dTDiff(i1, i2) =  abs(dTS1(i1)-dTS2(i2));
  end
end


if n1>=n2
  [dTDiffMin Idx1] = min(dTDiff,[],1);
  Idx2 = 1:n2;
else
  [dTDiffMin Idx2] = min(dTDiff,[],2);
  Idx1 = 1:n1;
end

% figure;
% hist(dTDiffMin,20);
fprintf('Matched timestamps. Max diff in timesatmps (sec): %g\n', max(dTDiffMin));

