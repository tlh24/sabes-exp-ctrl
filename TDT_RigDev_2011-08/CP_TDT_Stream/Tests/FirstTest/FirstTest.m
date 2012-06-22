% Get current dir
strFilePath = [cd '\'];
% Just a name
strFileName = 'DataFile.f32';
strFName = [strFilePath strFileName];

strDCOM_name = 'CP_TDT_Stream.Application';
hStream=actxserver(strDCOM_name);
%   get(hStream)
%   methods(hStream)
disp(hStream.strProgramVersion);

hStream.strServerName = 'Local';
hStream.strDeviceName = 'RP2(1)'; 

% Buffer size should be only smaller than the size 
% of the SerialBuffer declared in the RCO
hStream.lngBufferSize = 40000;

% Buffer should be split into integer number of blocks
% Buffer polling rate is 5Hz, so optimal block size should be 
% SamplingRate (floats/sec) / 5 = 5000
% We will make it a little bit smaller to make sure that 
% we have a new block ready on every check 

hStream.lngBlockSize = 4000;

disp('Start TDT workspace FirstTest.wsp');
disp('Set TDT device to idle mode');
disp('press any key to continue');
pause;

delete(strFName);  % CP_TDT_Stream cannot overwrite files

hStream.ConnectTDT_Server();
hStream.strFilePath = strFilePath;
hStream.strFileName = strFileName;
% Get ready to record and wait for the "Record" state 
% of the TDT device. Recording will stop when the state
% changes from "Record" to any other state
hStream.SetArmedState();
disp('Apply test signal ( e.g. sine wave 20 Hz )to ADC Channel 1');
disp('Put TDT device into record mode to start writing to file');
disp('After about 2 seconds put TDT device to idle mode to stop writing to file');
disp('After that, press any key to continue:');
disp('we will read and display the recorded file');
pause;
  
delete(hStream)
hf=fopen(strFName);
vals = fread(hf, inf, 'float32' );
fclose(hf);

figure;
plot(vals);

