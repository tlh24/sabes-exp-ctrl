ServerNamesInclude;

hVPoly = actxserver('CP_Display.VPolygon', strDisplayComputer); 

% get(hVPoly)
% methods(hVPoly)
% methodsview(hVPoly)

hVPoly.SetXY([512,384]);
hVPoly.Scale(20);
hVPoly.Show;
hVPoly.GetVertices
pause(1);
Vertices = [ -10 0 10   
               0 20 0  ];
hVPoly.SetVertices( Vertices);
hVPoly.GetVertices
