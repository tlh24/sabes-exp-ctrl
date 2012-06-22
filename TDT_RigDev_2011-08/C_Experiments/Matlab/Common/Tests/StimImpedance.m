%% SETUP
ExperimentGlobalsInclude;
TimeSyncGlobalsInclude;
ServerNamesInclude;

% Get Com Handle and Make Connection
hDev=actxserver('TDevAcc.X');
g_ExpData.hDev = hDev;

if hDev.ConnectServer( strTDTComputer ) ~= 1
  error('  Error connecting to server: %s   Make sure RZ2_DAQ is on', strTDTComputer)
end


CurrVal = ones(96,1)*10000;
% CurrVal = zeros(96,1);

g_ExpData.hDev.WriteTargetVEX([strTDTDevice,'.CurrList'], 0, 'F32', CurrVal);


%% SINGLE SAMPLE
Chan = 1;

Time = 2;
NewCurrVal = CurrVal;
NewCurrVal(Chan) = 0;


Bank = floor((Chan-1)/8);
g_ExpData.hDev.SetTargetVal([strTDTDevice,'.MonBank'],Bank);
pause(1);

g_ExpData.hDev.WriteTargetVEX([strTDTDevice,'.CurrList'], 0, 'F32', NewCurrVal);
pause(Time);
g_ExpData.hDev.WriteTargetVEX([strTDTDevice,'.CurrList'], 0, 'F32', CurrVal);
