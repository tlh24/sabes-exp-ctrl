function status = createArrows(arrowH,aangle,asize,NarrowsX,NarrowsY,wsBounds)
%
%
%
%
%  MF Jan. 5, 2007
%

Narrows = NarrowsX*NarrowsY;
lRat = 0.3;
hRat = 3;
wsCenter = [mean(wsBounds(:,1)); mean(wsBounds(:,2))];
wsWdth = range(wsBounds(:,1));
wsHght = range(wsBounds(:,2)); 

xLocs = wsWdth/(NarrowsX).*[0:NarrowsX-1];
yLocs = wsHght/(NarrowsY).*[0:NarrowsY-1];
[XLOCS,YLOCS] = meshgrid(xLocs,yLocs);
aLocs = zeros(2,Narrows)+repmat([wsBounds(1,1);wsBounds(1,2)],1,Narrows)+[XLOCS(:)'; YLOCS(:)'];
aVerts = [[cos(aangle) -sin(aangle)];[sin(aangle) cos(aangle)]]*arrowVerts(lRat,hRat).*asize;

verts = repmat(aVerts, [1 1 Narrows]) + repmat(permute(aLocs, [1 3 2]), [1 size(aVerts,2) 1]);

%%
figure;
for i = 1:size(verts,3)
   plot(verts(1,:,i),verts(2,:,i));
   hold on;
end
pause
%%
arrowH.pos = wsCenter;
arrowH.vertices = verts;


return

%%%%%%%%  Subroutines %%%%%%%%%%%%%
function verts = arrowVerts(lRat,hRat)

sHeight = 0.07;
tHeight = sHeight*hRat;
tLength = lRat/(lRat+1);
sLength = 1-tLength;

UL = [-0.5; sHeight/2];
verts = [[UL] ...
    [UL(1)+sLength; UL(2)] ...
    [UL(1)+sLength; tHeight/2] ...
    [-UL(1); 0] ...
    [UL(1)+sLength; -tHeight/2] ...
    [UL(1)+sLength; -sHeight/2] ...
    [UL(1); -sHeight/2] ...
    [UL] ...
    ];
