function verts = circleVerts(centers,radius)
%  function verts = circleVerts(centers,radius)
%
%  Get the vertices which describe a circle of radius RADIUS, for each circle with centers
%  given by CENTERS.
%
%  CENTERS should be m x n, where m is the dimension of the coords (2 or 3) and n is
%  the desired # of circles.
%
%  MF, Dec. 17, 2006
%
if size(centers,1) ~= 2 & size(centers,1) ~= 3
    error('CENTERS should be [dims x #circles]');
end
if ~isscalar(radius)
    error('RADIUS must be a scalar');
end
Ncircs = size(centers,2);
Nverts = ceil(2*2*pi*radius);
vAngs = [0:Nverts].*2*pi/Nverts;
[x,y] = pol2cart(vAngs,ones(1,Nverts+1)*radius);
z = zeros(1,length(x));

ctrs = permute(centers,[1 3 2]);
if size(centers,1) == 2
    verts = repmat([x; y], [1 1 Ncircs]) + repmat(ctrs,[1 Nverts+1 1]);
else
    verts = repmat([x; y; z], [1 1 Ncircs]) + repmat(ctrs,[1 Nverts+1 1]);
end