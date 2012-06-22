ServerNamesInclude;

hVDisk1 = actxserver('CP_Display.VDisk', strDisplayComputer); 

hVDisk1.Show;
hVDisk1.SetXY([540,384]);
hVDisk1.SetRadius(40);
hVDisk1.SetColor([1 0 1]);
hVDisk1.SetAlpha(1);
pause(1.0);

hVDisk2 = actxserver('CP_Display.VDisk', strDisplayComputer); 

hVDisk2.SetXY([500,384]);
hVDisk2.SetRadius(40);
hVDisk2.SetAlpha(1);
hVDisk2.SetColor([1 0 0]);
hVDisk2.Show;
pause(1.0);
hVDisk2.SetColor([0 1 0]);
pause(1.0);
hVDisk2.SetAlpha(0.5);
pause(1.0);
hVDisk2.SetColor([0 0 1]);
pause(1.0);
hVDisk2.SetAlpha(0);
