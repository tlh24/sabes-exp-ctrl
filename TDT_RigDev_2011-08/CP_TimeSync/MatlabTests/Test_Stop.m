hTS = actxserver('CP_TimeSync.Application');
pause(0.5);
% Connects to  RP2 device #N via Gigabit or USB interface
hTS.ConnectRP2('GB',1);
iStatus = hTS.GetStatus;

if iStatus == 7
  disp('Stopping TDT TimeSync');
  % Stop the program
  hTS.Halt;
  pause(0.1);
else
  disp('TDT TimeSync is not running');
end

delete(hTS);



