% Get current dir
strFilePath = [cd '\'];
% Just a name
strFileName = 'DataFile.i16';
strFName = [strFilePath strFileName];

strDCOM_name = 'CP_TDT_Stream.Application';
hStream=actxserver(strDCOM_name);
%   get(hStream)
%   methods(hStream)
disp(hStream.strProgramVersion);

hStream.strServerName = 'Local';
hStream.strDeviceName = 'RX5(1)'; 

% Buffer should be split into integer number of blocks
% Buffer polling rate is 5Hz, so optimal block size should be 
% SamplingRate (floats/sec) * N_Channels / PollingRate = 
% = 25000 * 4 / 5 = 20000
% We will make it a little bit smaller to make sure that 
% we have a new block ready on every check 
hStream.lngBlockSize = 16000;

% Buffer size should be only smaller than the size 
% of the MCSerialBuffer declared in the RCX
hStream.lngBufferSize = 80000;
% Data will be converted before file save
hStream.blnConvertToInt16 = 1;

disp('Start TDT workspace MultiChannel.wsp');
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
vals = fread(hf, inf, 'int16' );
fclose(hf);

N_chan = 4;
N_samp = length(vals)/N_chan
chnls = reshape(vals, N_chan, N_samp );
figure;
plot(chnls');
hold on;

