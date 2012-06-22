ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strVisServerName); 
hVMain.GetVersion
get(hVMain)
methods(hVMain)
methodsview(hVMain)  


%if iscom(hVMain)  release(hVMain); end;

