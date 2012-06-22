function H = createVisBlurObject(pstruct,vsip)
%
%
%
%
%
%  MF Feb. 26, 2007
%


cLocs = zeros(pstruct.N,2);

clear H
for i = 1:pstruct.N
    H(i) = actxserver('VisServer.VisPolygon', vsip);
    H(i).points = cVerts;% + repmat(aLocs(:,i)',size(aVerts,1),1);
    H(i).fill = 1;
    H(i).show = 0;
    H(i).pos = cLocs(i,:);
end




function pts = cVerts
ang = [0:2]/3*2*pi;
pts = [cos(ang); sin(ang)]';