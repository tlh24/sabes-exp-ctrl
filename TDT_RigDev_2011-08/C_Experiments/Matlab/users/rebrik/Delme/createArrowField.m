function H = createArrowField(NarrowsX,NarrowsY,wsBounds,visServerName)
%function status = createArrows(arrowH,aangle,asize,NarrowsX,NarrowsY,wsBounds)
%
%
%
%
%  MF Jan. 5, 2007
%

Narrows = NarrowsX*NarrowsY;
%lRat = 0.3;
%hRat = 3;
wsCenter = [mean(wsBounds(:,1)); mean(wsBounds(:,2))];
wsWdth = range(wsBounds(:,1));
wsHght = range(wsBounds(:,2));

xLocs = wsBounds(1,1) + wsWdth/(NarrowsX-1).*[0:NarrowsX-1];
yLocs = wsBounds(1,2) + wsHght/(NarrowsY-1).*[0:NarrowsY-1];
[XLOCS,YLOCS] = meshgrid(xLocs,yLocs);
%aLocs = zeros(2,Narrows)+repmat([wsBounds(1,1);wsBounds(1,2)],1,Narrows)+[XLOCS(:)'; YLOCS(:)'];
aLocs = [XLOCS(:)'; YLOCS(:)'];
aVerts = getArrowVerts;%%[[cos(aangle) -sin(aangle)];[sin(aangle) cos(aangle)]]*getArrowVerts.*asize;

clear H
for i = 1:Narrows
    H(i) = actxserver('VisServer.VisPolygon', visServerName);
    H(i).points = aVerts;% + repmat(aLocs(:,i)',size(aVerts,1),1);
    H(i).fill = 1;
    H(i).show = 0;
    H(i).pos = aLocs(:,i)';
end

%verts = repmat(aVerts, [1 1 Narrows]) + repmat(permute(aLocs, [1 3 2]), [1 size(aVerts,2) 1]);
return

%%%% Subroutines  %%%%%%%
function verts = getArrowVerts
% creates arrow of unit length, returns its handle
HeadHalfWidth = .40;
HeadLength = .20;
StemHalfWidth = 0.05;
%% Arrow shape of length 1.0 and center in the middle
verts = [(0.5-HeadLength), StemHalfWidth;...
    (0.5-HeadLength), HeadHalfWidth; ...
    0.5, 0; ...
    (0.5-HeadLength), -HeadHalfWidth;...
    (0.5-HeadLength), -StemHalfWidth; ...
    -0.5, -StemHalfWidth;
    -0.5, 0.05];
%hArrow = actxserver('VisServer.VisPolygon', strVisServerName);
%hArrow.points = ArrowShapePoints;
return
