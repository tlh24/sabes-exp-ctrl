% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

hVDisk1 = actxserver('CP_Display.VDisk', strDisplayComputer); 
% methods(hVDisk1)

hVDisk1.SetXY([540,384]);
hVDisk1.SetRadius(40);
hVDisk1.SetColor([1 0 1]);
hVDisk1.Show;
hVDisk1.SetZ(0.5);
pause(1.0);

hVDisk2 = actxserver('CP_Display.VDisk', strDisplayComputer); 

hVDisk2.Show;
hVDisk2.SetXY([500,384]);
hVDisk2.SetRadius(40);
hVDisk2.SetColor([1 0 0]);
pause(1.0);
hVDisk2.SetZ(1);
pause(1.0);
hVDisk2.SetZ(0.5);
pause(1.0);
hVDisk2.SetZ(0);
