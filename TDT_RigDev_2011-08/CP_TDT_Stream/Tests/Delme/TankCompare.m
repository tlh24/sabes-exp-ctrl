% Path on the computer where CP_TDT_Stream is running
strFilePath = 'd:\tmp\';
% File name on the computer where CP_TDT_Stream is running.
% no path included
strFileName = 'DataFile.i16';

strSrvname = 'CP_TDT_Stream.Application'
hStream=actxserver(strSrvname);
%   get(hStream)
%   methods(hStream)
disp(hStream.strProgramVersion);

hStream.strServerName = 'Local';
hStream.strDeviceName = 'RP2(1)'; 

% Buffer size should be only smaller than the size 
% of the SerialBuffer declared in the RCO
hStream.lngBufferSize = 50000;

% Buffer polling rate is 5Hz, so optimal block should be 
% StreamingRate (floats/sec) / 5 = 2500
% we will make it a little bit smaller to make sure that 
% we have a new block ready on every check 
% Important: Buffer should be split into an integer number of blocks
hStream.lngBlockSize = 2000;

disp('Start TDT workspace TankCompare.wsp');
disp('Set TDT device to idle mode');
disp('press any key to continue');
pause;

hStream.ConnectTDT_Server();

hStream.strFilePath = strFilePath;
hStream.strFileName = strFileName;

% Get ready to record and wait for the "Record" state 
% of the TDT device. Recording will stop when the state
% changes from "Record" to any other state
hStream.SetArmedState();

disp('Put TDT device into record mode to start writing to file');
disp('Put TDT device to idle mode to stop writing to file');
disp('press any key to exit');
pause;
  
delete(hStream)



