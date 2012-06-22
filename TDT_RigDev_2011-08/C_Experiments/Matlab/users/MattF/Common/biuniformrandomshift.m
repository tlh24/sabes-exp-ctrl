function U = biuniformrandomshift(B)
%
%  Helper function for generating FB shifts for cueReliability task.
%
%
%
%  MF Oct. 1, 2007.
%
U = [0 0];

Xbnds = B(1,:);
x0 = (Xbnds(4)-Xbnds(3) - (Xbnds(1)-Xbnds(2))).*rand(1) + (Xbnds(1)-Xbnds(2));
if x0 < 0
U(1) = x0 + Xbnds(2);    
else
    U(1) = x0 + Xbnds(3);
end


Ybnds = B(2,:);
y0 = (Ybnds(4)-Ybnds(3) - (Ybnds(1)-Ybnds(2))).*rand(1) - (Ybnds(1)-Ybnds(2));
if y0 < 0
U(2) = y0 + Ybnds(2);    
else
    U(2) = y0 + Ybnds(3);
end
