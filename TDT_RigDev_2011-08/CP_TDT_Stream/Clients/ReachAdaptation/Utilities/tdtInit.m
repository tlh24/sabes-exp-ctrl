function tdtInit(server)

% Initialize Juice TDT Interface
global TDTdev JuiceTime

if(nargin<1) server = 'Local'; end

% Create an ActiveX Control that talks to TDT Devices through 
% the OpenWorkbench
%    second arg controls the placement of the icon in the MATLAB figure.
%TDTdev = actxcontrol('TDevAcc.X',[5 5 26 26]);
TDTdev = actxcontrol('TDevAcc.X',[0 0 0 0]);
%title('This Figure hold the (empty??) ActX Control for the TDT');

% Connect to the server (OpenWorkbench)
%invoke(TDTdev,'ConnectServer','Local','OpenWorkbench')
% Documentation is wrong... the following works
fprintf(1,'Connecting to TDT server...')
if(~invoke(TDTdev,'ConnectServer',server))
    error('Can not connect to TDT Server');
end
 
%% System Settings
%  0 = idle
%  1 = standby 
%  2 = preview 
%  3 = record

fprintf(1,' Set TDT System in Idle Mode...')
invoke(TDTdev,'SetSysMode',0);

JuiceTime = 0;
tdtTone(0);
tdtMarkTrial(0);

fprintf(1,'Done.\n')

