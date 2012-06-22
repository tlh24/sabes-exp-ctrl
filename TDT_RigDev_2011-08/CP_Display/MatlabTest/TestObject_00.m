ServerNamesInclude;

hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 

get(hVDisk)
methods(hVDisk)


fprintf('ShowFlag\n');
hVDisk.GetShowFlag
hVDisk.SetShowFlag(1);
hVDisk.GetShowFlag
pause(1.0);

fprintf('XY\n');
hVDisk.GetXY 
hVDisk.SetXY([512,384]);
hVDisk.GetXY 
pause(1.0);

fprintf('Z\n');
hVDisk.GetZ
hVDisk.SetZ(1);
hVDisk.GetZ
pause(1.0);
hVDisk.SetZ(0);


fprintf('Scale\n');
hVDisk.GetScale
hVDisk.SetScale(40);
hVDisk.GetScale
pause(1.0);

fprintf('Radius\n');
hVDisk.GetRadius
hVDisk.SetRadius(50);
hVDisk.GetRadius
pause(1.0);

fprintf('Color\n');
hVDisk.GetColor
hVDisk.SetColor([1 0 1]);
hVDisk.GetColor
pause(1.0);

fprintf('Alpha\n');
hVDisk.GetAlpha
hVDisk.SetAlpha(0);
hVDisk.GetAlpha
pause(1.0);
hVDisk.SetAlpha(1);
 
hVDisk.SetN_Vertices(3);
pause(1.0);

fprintf('Angle\n');
hVDisk.GetAngle
hVDisk.SetAngle(30);
hVDisk.GetAngle
pause(1.0);

fprintf('FillFlag\n');
hVDisk.GetFillFlag
hVDisk.SetFillFlag(0)
hVDisk.GetFillFlag
pause(1.0);

fprintf('GroupID\n');
hVDisk.GetGroupID
hVDisk.SetGroupID(11);
hVDisk.GetGroupID
pause(1.0);

fprintf('GetClippedCount\n');
hVDisk.GetClippedCount
hVDisk.SetXY([0,0]);
hVDisk.GetClippedCount
hVDisk.SetXY([512,384]);

 
fprintf('Hide\n');
hVDisk.Hide;
pause(1.0);

fprintf('Show\n');
hVDisk.Show;     
pause(1.0);

fprintf('Move\n');
hVDisk.Move([20 20]);
pause(1.0);

fprintf('Rotate\n');
hVDisk.Rotate(45);
pause(1.0);

fprintf('Scale\n');
hVDisk.Scale(3);


 

