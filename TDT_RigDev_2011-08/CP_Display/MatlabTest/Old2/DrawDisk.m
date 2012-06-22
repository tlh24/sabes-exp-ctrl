% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
hVMain.GetVersion
hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 

get(hVDisk)
methods(hVDisk)

hVDisk.Show;
hVDisk.SetXY([512,384]);
hVDisk.SetRadius(40);
hVDisk.SetColor([1 0 1]);
pause(1.0);
hVDisk.SetN_Vertices(3);
hVDisk.Rotate(-30);
pause(1.0);
hVMain.ScaleGroup(0,4);
