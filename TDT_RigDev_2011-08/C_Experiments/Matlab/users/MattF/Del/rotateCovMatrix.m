function rC = rotateCovMatrix(C,th)
%
%
%
%
%
%
%  MF Feb. 19, 2007
%

rmat = [cos(th) -sin(th); sin(th) cos(th)];
[V,D] = eig(C);
rV = rmat*V;
rC = rV*D*inv(rV);