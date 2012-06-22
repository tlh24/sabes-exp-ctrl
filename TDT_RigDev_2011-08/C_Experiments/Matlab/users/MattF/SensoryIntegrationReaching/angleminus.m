function d = angleminus(x,y)
%
%  For angles x and y, returns x-y after correcting for 
%  any effects of the discontinuity.  Angles should be in radians.
%   
%  In other words, the absolute angular difference will always be <= 180
%  and the sign will be positive if x is more counter-clockwise than y.
%
%
%  MF May 31, 2008.
%

%  Kloodgy way of forcing everything into (-pi,pi).
x = atan2(sin(x),cos(x));
y = atan2(sin(y),cos(y));
%if any(x>pi), x = x-pi; end
%if any(y>pi), y = y-pi; end

d = x-y;
idx = find(abs(d)>=pi);
d(idx) = -sign(d(idx)).*(2*pi-abs(d(idx)));
