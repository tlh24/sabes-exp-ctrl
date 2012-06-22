function updateVisFBParams(H,fbparams)
%
%
%
%  MF Nov. 6, 2007.
%

H.SetColor( fbparams.RGB.*fbparams.bright);
H.SetScale( fbparams.rad);
H.SetVertices(fbparams.points);
H.SetFillFlag( fbparams.fill);
H.SetAngle(fbparams.angle);