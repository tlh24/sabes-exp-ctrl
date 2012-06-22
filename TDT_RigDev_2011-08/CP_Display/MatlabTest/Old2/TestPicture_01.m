% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

TxW = 512; % should be power of 2
TxH = 512; % should be power of 2

[ImageRGB, ClrMap] = imread('banana.gif');
ImageRGB = ind2rgb(ImageRGB, ClrMap);

% image(ImageRGB); axis equal;
H = size(ImageRGB,1);
W = size(ImageRGB,2);

TxtrRGBA = zeros(TxH, TxW, 4);
PadX = (TxW-W)/2;
PadY = (TxH-H)/2;
TxtrRGBA(PadY+1:PadY+H, PadX+1:PadX+W, 1:3) = ImageRGB;

TxtrAlpha = ones(H,W);
WhiteIdx = find( sum(ImageRGB,3) > 2.6);
TxtrAlpha(WhiteIdx) = 0;

TxtrRGBA(PadY+1:PadY+H, PadX+1:PadX+W, 4 ) = TxtrAlpha;

hVPoly1 = actxserver('CP_Display.VPolygon', strDisplayComputer); 

hVPoly1.SetXY([580,300]);
HalfW = W/2;
HalfH = H/2;

Box =  [ -HalfW  HalfW  HalfW -HalfW  
          HalfH  HalfH -HalfH -HalfH ];
hVPoly1.SetVertices(Box);
hVPoly1.SetFillFlag(1);
hVPoly1.SetTextureFlag(1);
hVPoly1.SetTexture( TxtrRGBA, TxW);
hVPoly1.Scale(0.25);
hVPoly1.Rotate(-90);
hVPoly1.Show;

[Arr1D tW tH dW ] = hVPoly1.GetTexture;

TxtrIn = reshape(Arr1D, [4 tW tH]);
TxtrIn = permute(TxtrIn, [3 2 1]);
image(TxtrIn(:,:,1:3)); axis equal;

% hVPoly1.Rotate(180);
