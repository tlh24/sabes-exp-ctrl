ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 
hVMain.GetVersion
get(hVMain)
methods(hVMain)
methodsview(hVMain)  


%if iscom(hVMain)  release(hVMain); end;

