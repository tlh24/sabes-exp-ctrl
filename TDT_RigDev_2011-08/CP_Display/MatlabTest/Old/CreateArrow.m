function hArrow = CreateArrow( strVisServerName )
% creates arrow of unit length, returns its handle
  HeadHalfWidth = .20;
  HeadLength = .20;
  StemHalfWidth = 0.05;
  %% Arrow shape of length 1.0 and center in the middle
  ArrowShapePoints = [(0.5-HeadLength), StemHalfWidth;...
                      (0.5-HeadLength), HeadHalfWidth; ...
                       0.5, 0; ...
                       (0.5-HeadLength), -HeadHalfWidth;...
                       (0.5-HeadLength), -StemHalfWidth; ...
                       -0.5, -StemHalfWidth;
                       -0.5, 0.05];
  hArrow = actxserver('VisServer.VisPolygon', strVisServerName);
  hArrow.points = ArrowShapePoints;

end