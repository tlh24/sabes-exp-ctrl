function vertices = updateVisBlurVerts(Nd,Nv,r,C)
%
%
%  H    - handle of the viscomplexobject
%  Nd   - number of dots
%  Nv   - number of verts per dot
%  r    - radius of each dot
%  C    - covariance matrix for dot positions
%
%
%  MF March 9, 2007
%

    pctrs = mvnrnd([0 0],C,Nd)';  %  [2 x Nd]
    pctrs = permute(pctrs, [1 3 2]);  %  [2 x 1 x Nd]
    vertices = repmat(pctrs,1,Nv) + repmat(cVerts(Nv,r)', [1 1 Nd]);
    

function pts = cVerts(N,r)

ang = [0:(N-1)]/N*2*pi;
pts = [r.*cos(ang(:)) r.*sin(ang(:))];