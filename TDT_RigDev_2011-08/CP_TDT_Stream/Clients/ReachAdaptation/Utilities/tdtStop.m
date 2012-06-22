function tdtStop

% Stop Juice TDT Interface
global TDTdev

TDTdev = actxcontrol('TDevAcc.X',[0 0 0 0]);
invoke(TDTdev,'ConnectServer','cannonball');
% Put back into idle mode
invoke(TDTdev,'SetSysMode',0);

% Disconnect
invoke(TDTdev,'CloseConnection');

