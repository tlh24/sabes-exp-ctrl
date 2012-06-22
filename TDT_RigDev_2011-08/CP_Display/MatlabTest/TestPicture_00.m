ServerNamesInclude;

TxW = 512; % should be power of 2
TxH = 512; % should be power of 2

ImageRGB = imread('Bush.jpg');

% image(ImageRGB); axis equal;
H = size(ImageRGB,1);
W = size(ImageRGB,2);

ImageRGB_Dbl = double(ImageRGB)/255;  % normalize to 0-1 range

TxtrRGBA = zeros(TxH, TxW, 4);
PadX = (TxW-W)/2;
PadY = (TxH-H)/2;
TxtrRGBA(PadY+1:PadY+H, PadX+1:PadX+W, 1:3) = ImageRGB_Dbl;

TxtrAlpha = ones(H,W);
DarkIdx = find( sum(ImageRGB_Dbl,3) < 0.01);
TxtrAlpha(DarkIdx) = 0;

TxtrRGBA(PadY+1:PadY+H, PadX+1:PadX+W, 4 ) = TxtrAlpha;

hVPoly = actxserver('CP_Display.VPolygon', strDisplayComputer); 

hVPoly.SetXY([512,384]);
HalfW = W/2;
HalfH = H/2;

Box =  [ -HalfW  HalfW  HalfW -HalfW  
          HalfH  HalfH -HalfH -HalfH ];
hVPoly.SetVertices(Box);
hVPoly.SetFillFlag(1);
hVPoly.Show;
pause(1);
hVPoly.SetTextureFlag(1);
pause(1);
hVPoly.SetTexture( TxtrRGBA, TxW);
% image(TxtrRGBA(:,:,1:3)); axis equal;

% hVPoly.Rotate(180);
% hVPoly.Scale(2);