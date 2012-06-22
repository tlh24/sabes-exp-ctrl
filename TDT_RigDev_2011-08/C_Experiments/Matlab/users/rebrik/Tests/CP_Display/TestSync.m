ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 

hVMain.StopSync;

for i = 1:100
  tic;
  hVMain.StartSync;
%  disp('Started');
  pause(1);
  hVMain.StopSync;
  toc
%  disp('Stopped');
  pause(0.1);
end  

%if iscom(hVMain)  release(hVMain); end;

