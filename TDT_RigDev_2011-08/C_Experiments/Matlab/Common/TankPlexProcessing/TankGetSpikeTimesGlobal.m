function SpikeArray = TankGetSpikeTimesGlobal(strTank, iBlock, dGlobRecStartTS)
% function SpikeArray = TankGetSpikeTimes(strTank, iBlock )
%
% Read snippets from Tank and return time, channel, cluster 
% 
% INPUT:
%   strTank - tank name (string)
%   iBlock - iBlock number (integer)
%   dGlobRecStartTS - RecStart global time (optional)
%
% OUTPUT:
% The array SpikeArray(:,3)
%   where 
%     SpikeArray(:,1) -  the global timestamp
%     SpikeArray(:,2) -  input channel (electrode)
%     SpikeArray(:,3) -  cluster 
%

if nargin == 3 % we want to calc from the dGlobRecStartTS
  [dC0 dC1] = TankGetTimeConversion(strTank, iBlock, dGlobRecStartTS);
else % use TimeSync events 
  [dC0 dC1] = TankGetTimeConversion(strTank, iBlock);
end  

SpikeArray = TankGetSpikeTimesLocal(strTank, iBlock);

if ~isempty(SpikeArray)
  SpikeArray(:,1) = SpikeArray(:,1) * dC1 + dC1;
end