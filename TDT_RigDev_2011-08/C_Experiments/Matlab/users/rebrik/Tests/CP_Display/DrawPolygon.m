ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
% hVMain.GetVersion
hVPoly = actxserver('CP_Display.VPolygon', strDisplayComputer); 

% get(hVPoly)
% methods(hVPoly)

hVPoly.SetXY([512,384]);
% Square = [ -1  1  1 -1  
%             1  1 -1 -1 ];
% Square = [ -1   1  1 -1  
%            -1  -1  1  1 ];
% hVPoly.SetVertices(Square);

% c1 = sin(pi * 60/180);
% c2 = cos(pi * 60/180);
          
% Hex = [ 0  c1   c1  0 -c1 -c1  
%         1  c2  -c2 -1 -c2  c2 ];
%==       1  2    3   4  5   6
% hVPoly.SetVertices(Hex);

ang = [0:72:360];
ang = ang(1:5);

Pent = [ ones(1,5) .* cos(ang * pi/180)
         ones(1,5) .* sin(ang * pi/180)];
hVPoly.SetVertices(Pent);

hVPoly.SetScale(100);
hVPoly.SetColor([1 0 1]);
hVPoly.Show;
pause(1.0);
hVPoly.SetTextureFlag(1)
pause(1.0);
ang = [0:144:720];
ang = ang(1:5)+18;

Star = [ ones(1,5) .* cos(ang * pi/180)
         ones(1,5) .* sin(ang * pi/180)];
      
% c1 = sin(pi * 72/180);
% c2 = cos(pi * 72/180);
% 
% Star = [ 0  c1   -c2   c2  -c1   
%          1  -c2   c1   c1  -c2 ];
% Star = [ 0  c2   -c1   c1  -c2   
%          1  -c1   c2   c2  -c1 ];
       
hVPoly.SetVertices(Star);
% hVPoly.Rotate(18);
hVPoly.Show;

pause(1.0);
hVPoly.SetFillFlag(1)
pause(1.0);
hVPoly.Rotate(-30);
pause(1.0);
hVMain.ScaleGroup(0,4);

bitmap = [ 1 1 1 1
           0 1 0 0
           0 0 1 0
           0 0 0 1];
texture = ones( 4, 4, 4);
texture(:,:,1) = bitmap * 1;  % R
texture(:,:,2) = bitmap * 1;  % G
texture(:,:,3) = bitmap * 0;  % B
texture(:,:,4) = bitmap * 1;  % A

hVPoly.SetTexture( texture, 0.1);
% image(texture(:,:,[1 2 3])); axis equal;
% % pause(1.0);
% % delete(hVPoly);