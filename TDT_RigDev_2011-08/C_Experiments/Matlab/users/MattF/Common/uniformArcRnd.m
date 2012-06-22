function [X,Y] = uniformArcRnd(Bth,Br, N)
%
%  Pick a position (x*,y*), uniform inside a piece of an annulus.
%  The annulus has inner radius min(Br), outer radius max(Br), and angles
%  >= Bth(1) and <= Bth(2).
%
%
%  if N is passed in, then N samples will be returned.  Otherwise, one
%  sample is returned.
%
%  MF March 15, 2007
%

if Bth(1) == Bth(2), Bth(2)=Bth(2)+2*pi; end
bb = find(Bth>pi);
Bth(bb) = Bth(bb)-2*pi;

if nargin<3, N = 1; end

pk = ((pi*max(Br)^2 - pi*min(Br)^2)*range(Bth)/(2*pi))/(2*pi*max(Br)^2);  %  The expected proportion of points we will not reject.

n = 0;
X = zeros(N,1);
Y = zeros(N,1);
while n<N

    x = rand(ceil(N/pk),1).*max(Br)*2 - max(Br);  %  x in [-r_outer,r_outer]
    y = rand(ceil(N/pk),1).*max(Br)*2 - max(Br);  %  y in [-r_outer,r_outer]
    [th,r] = cart2pol(x,y);
    if Bth(1)>Bth(2)
        ki = r<max(Br) & r>min(Br) & (th>Bth(1) | th<Bth(2));
    else
        ki = r<max(Br) & r>min(Br) & th>Bth(1) & th<Bth(2);
    end

    X(n+1:(n+sum(ki))) = x(ki);
    Y(n+1:(n+sum(ki))) = y(ki);
    n = n+sum(ki);
end
X = X(1:N,1);
Y = Y(1:N,1);
