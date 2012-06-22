hTS = actxserver('CP_TimeSync.Application');

% Connects to  RP2 device #N via Gigabit or USB interface
pause(0.5);
hTS.ConnectRP2('GB',1);
iStatus = hTS.GetStatus;

CurrDir = cd;
strTimeSyncCofFile = [ CurrDir '\TimeSync.rco'];
if iStatus ~= 7
  disp('TDT TimeSync is not running');
  disp('Starting TDT TimeSync, resetting time, clearing events');
  % Clear the buffers and COF files
  hTS.ClearCOF;
  % Load the program
  hTS.LoadCOF(strTimeSyncCofFile);
  % Start the program
  hTS.Run;
  pause(0.5);
  hTS.SoftTrg(1);  % to delete spurious events 
  dExpStartTime = now;
else
  disp('TDT TimeSync is already running');
  disp('Reconnecting to TDT TimeSync, keeping time and events');
  hTS.ReadCOF(strTimeSyncCofFile); % 
  dExpStartTime = 0;
end


dSampRateHz = hTS.GetSFreq;
dTsTicksToMs = 1000/dSampRateHz;