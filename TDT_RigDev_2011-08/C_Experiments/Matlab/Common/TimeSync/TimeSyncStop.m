function TimeSyncStop()

ExperimentGlobalsInclude;
ServerNamesInclude;

disp('====== TimeSyncStop ======');

%% Get Com Handle and Make Connection
hDev = g_ExpData.hDev;

if( ~strcmp(class(hDev),'COM.TDevAcc_X') ) % Something happened to the hDev!
  hDev=actxserver('TDevAcc.X');
  g_ExpData.hDev = hDev;
  
  if hDev.ConnectServer( strTDTComputer ) ~= 1
	error('  Error connecting to server: %s   Make sure RZ2_DAQ is on', strRZ2_DaqComputer)
  end
end

%% Get System Mode
% strTDT_Mode = {'Idle'; 
%                'Standby';
%                'Preview';
%                'Record'};

iSysMode = hDev.GetSysMode;


%% Stop
if iSysMode~=3,  % Not in record mode
  disp('  TDT TimeSync is not running');
else
  disp('  Stopping TDT TimeSync/DAQ');
  if hDev.SetSysMode(0) ~= 1   % set to Idle
    disp('  Cannot set RZ2 mode to Idle');
  end
end

hDev.CloseConnection;
release(hDev)
