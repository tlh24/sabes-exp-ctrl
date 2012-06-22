% strDisplayComputer = 'VisServer1';
strDisplayComputer = 'localhost';

hVMouse = actxserver('CP_Display.VMouse', strDisplayComputer); 

% get(hVMouse)
% methods(hVMouse)
% methodsview(hVMouse)  

hVMouse.GetAllEvents
hVMouse.ClearEvents
display('Click on the CP_Display window to check events');
pause(10)
hVMouse.GetAllEvents
display('Move mouse on CP_Display window to check coordinates');
pause(1)
for(i=1:100)
  hVMouse.GetXY
end

hVMouse.GetUpEvents
hVMouse.GetDownEvents
hVMouse.GetDblclickEvents

%if iscom(hVMouse)  release(hVMouse); end;
