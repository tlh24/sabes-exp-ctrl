function xy = drawfromellipse(rad)
%
%  MF July 11, 2008.
%

%  For an ellipse x^2/a^2 + y^2/b^2 = 1; inside the ellipse this is < 1.
%  We can flip into another space, where x_ = x^2/a^2, and y_ = y^2/b^2,
%  and then find the points such that x_ + y_ < 1, and x_, y_ both >=0.
%  Then just flip back into x,y space.
%

R = inline('(Lx^2 + Ly^2)^-1.*[Lx^2-Ly^2 2*Lx*Ly; 2*Lx*Ly Ly^2-Lx^2];','Lx','Ly');  %  Matrix for reflection about a line through the origin.

%  Choose a point inside a unit square centered on the origin.
%  A uniform sample in this space will not be uniform when we flip back
%  into the other space.  In fact, the points will be pushed away from the
%  origin.  Fix this by squaring the values here since squaring is an
%  expansive function and will put more points near zero.
xy_ = -0.5 + rand(1,2).^2;

if sum(xy_)>0
  %  We want the left-lower half of the box.  If it's in the Right-upper
  %  half then just reflect it around the line of slope = -1 through the
  %  origin, i.e., the box diagonal.
  xy_ = (R(-1,1)*xy_')';
end
xy_ = xy_ + [0.5 0.5];  % Shift the box back so that its diagonal is x+y=1.

%  Flip back into x,y space.
xy0 = sqrt([rad(1)^2*xy_(1) rad(2)^2*xy_(2)]);

%  Since we squared to get into the other space the sign is indeterminate
%  and we should choose them with equal probability.
chooseSgn = 2.*binornd(1,0.5,1,2)-1;
xy = chooseSgn.*xy0;


% % dn = 0;
% % while ~dn
% %   xy = [-rad + 2.*rad.*rand(1,2)];
% %   d = xy(1).^2/rad(1).^2 + xy(2).^2./rad(2).^2;
% %   if d<=1, dn = 1; end
% % end

return