function dExpStartTime = TimeSyncStart(RecoverFlag)

if(nargin<1) RecoverFlag=0; end

ExperimentGlobalsInclude;
ServerNamesInclude;
TimeSyncGlobalsInclude;
TimeSyncConfigInclude;

disp('====== TimeSyncStart ======');

%% Get Com Handle and Make Connection
hDev=actxserver('TDevAcc.X');
g_ExpData.hDev = hDev;

if hDev.ConnectServer( strTDTComputer ) ~= 1
  error('  Error connecting to server: %s   Make sure RZ2_DAQ is on', strTDTComputer)
end

%% Get and Set System Mode
% strTDT_Mode = ['Idle   ';
%                'Standby';
%                'Preview';
%                'Record '];

iSysMode = hDev.GetSysMode;

%% Start
if(RecoverFlag)
  %% In Recovery Mode, don't restart!
  if(iSysMode==3)
    disp('TDT TimeSync is already running');
    disp('Reconnected to TDT TimeSync, keeping time and events');
    dExpStartTime = 0;
  else
    error('TimeSyncStart: TDT TimeSync/DAQ is not running, cannot restart in Recovery Mode.')
  end
  
else
  %% Not in Recovery Mode
  if(iSysMode~=3),  % Not Running
    disp('TDT TimeSync/DAQ is not running');
    disp('Starting TDT TimeSync/DAQ, resetting time, clearing events');
  else
    disp('TDT TimeSync is currently running');
    disp('Restarting TDT TimeSync/DAQ, resetting time, clearing events');
  end
  
  if iSysMode ~= 0   % set to Idle first, to ensure new block
    if hDev.SetSysMode(0) ~= 1   % set to Idle
      hDev.CloseConnection;
      error('  Cannot set RZ2 mode to Idle');
    end
    pause(0.25);
  end
  
  if hDev.SetSysMode(3) ~= 1   % set to Record
    hDev.CloseConnection;
    error('  Cannot set RZ2 mode to Record');
  end
  
  pause(0.5);
  TimeSyncReset;  % to delete spurious events
  dExpStartTime = now;
  
end

%% Sampling Rate
dSampRateHz = hDev.GetDeviceSF(strTDTDevice);
g_dTsTicksToMs = 1000/dSampRateHz;

