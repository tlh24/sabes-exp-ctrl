function [p,id]=perm(p0,seed)

% FUNCTION  [p,id]=perm(p0,seed)
%
% Randomly permute the rows of p0.
% If seed is given, reseed.  If seed is -1, reseed with clock.
% If no seed, don't reseed.
% Also, can send an empty p0 with seed to reseed only.
%
% id is the permuting vector

%% RANDOMIZE:

if nargin>1,
  if(seed~=-1) rand('seed',seed); 
  else t=clock; rand('seed',t(6));
  end
end

if(isempty(p0)), p=[]; 
else
  [r,i]=sort(rand(size(p0(:,1))));
  p=p0(i,:);
end

if(nargout>1) id=i; end
