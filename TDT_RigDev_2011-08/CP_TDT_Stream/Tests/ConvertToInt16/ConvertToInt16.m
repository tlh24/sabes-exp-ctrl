% Get current dir
strFilePath = [cd '\'];
% Just a name
strFileName = 'DataFile.i16';
strFullFName = [strFilePath strFileName];

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
% Data will be converted before file save
hStream.blnConvertToInt16 = 1;

% Buffer should be split into integer number of blocks
% Buffer polling rate is 5Hz, so optimal block size should be 
% SamplingRate (floats/sec) / 5 = 5000
% We will make it a little bit smaller to make sure that 
% we have a new block ready on every check 

hStream.lngBlockSize = 4000;

disp('Start TDT workspace ConvertToInt16.wsp');
disp('Set TDT device to idle mode');
disp('press any key to continue');
pause;

delete(strFullFName);  % CP_TDT_Stream cannot overwrite files

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
strFNameTank = [strFullFName '.tank'];
SaveLastBlock('ConvertToInt16', strFNameTank, 'int16')

max_len = 100000;  % 4 sec at 25kHz
hf=fopen(strFullFName);
vals1 = fread(hf, max_len, 'int16' );
fclose(hf);
hf=fopen(strFNameTank);
vals2 = fread(hf, max_len, 'int16' );
fclose(hf);
% figure;
% plot(vals1);
% figure;
% plot(vals2);
vals1(1:10)
vals2(1:10)

len1 = length(vals1);
len2 = length(vals2);
len = min( len1, len2);
vals1 = vals1(1:len);
vals2 = vals2(1:len);

ch_diff = vals1 - vals2;
figure;
plot(ch_diff(1:len));

% non0diff = find(ch_diff~=0);
% hist(ch_diff(non0diff));
figure;
hist(ch_diff);


