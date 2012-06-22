% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

hVPoly = actxserver('CP_Display.VPolygon', strDisplayComputer); 

% get(hVPoly)
% methods(hVPoly)
% methodsview(hVPoly)

hVPoly.SetXY([512,384]);
hVPoly.Scale(20);
hVPoly.Show;

a = hVPoly.GetVertices;
Vertices = [ -10 0 10   
               0 20 0  ];
hVPoly.SetVertices( Vertices);
invoke(hVPoly, 'GetVertices')
Vertices = [ 1 2 3 4 5  
             6 7 8 9 10 ];
hVPoly.SetVertices( Vertices);

% hVDisk.Show;
%
% hVDisk.SetRadius(40);
% hVDisk.SetColor([1 0 1]);
% pause(1.0);
% hVDisk.SetN_Vertices(3);
% hVDisk.Rotate(-30);
% pause(1.0);
% hVMain.ScaleGroup(0,4);
