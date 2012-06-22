ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
hVMain.GetVersion
while 1
fprintf('press any key to stop sync\n');
pause();
hVMain.StopSync;
fprintf('press any key to start sync\n');
pause();
hVMain.StartSync;
end
if iscom(hVMain)  release(hVMain); end;

