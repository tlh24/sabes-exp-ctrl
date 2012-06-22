function [hTank hFig] = TankOpen( strTank, iBlock)

DaqConfigInclude;   % Server name
TankConfigInclude;  % Tank store strings are defined here

strBlock  = sprintf('Block-%d',iBlock);    % iBlock (case-sensitive!)
fprintf('\nConnecting to   %s   %s  ...  ', strTank, strBlock);

hFig = figure;
set(hFig, 'Visible', 'off');

hTank = actxcontrol('ttank.x', [20 20 60 60], hFig);


if hTank.ConnectServer( strRX5_DaqComputer, strRX5_DaqUser) ~= 1
  delete(hFig);
	error('  Error connecting to server: %s', strRX5_DaqComputer)
end

if hTank.OpenTank( strTank, 'r') ~= 1
  hTank.ReleaseServer;
  delete(hFig);
	error('  Error opening tank! Make sure the tank is registered on the server.')
end

if hTank.SelectBlock( strBlock) ~= 1
  hTank.CloseTank;
  hTank.ReleaseServer;
  delete(hFig);
	error('  Error selecting block!')
end

fprintf('Ok\n');
