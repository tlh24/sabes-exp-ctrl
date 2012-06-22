% strVisServerName = 'VisServer1';
strDisplayComputer = 'localhost';

hVMain = actxserver('CP_Display.VMain'); 
hVMain.GetVersion
get(hVMain)
methods(hVMain)
methodsview(hVMain)  


%if iscom(hVMain)  release(hVMain); end;

