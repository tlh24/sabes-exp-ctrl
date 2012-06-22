srvname = 'CP_TDT_Stream.Application'

try
  hStream=actxserver(srvname);
%   get(hStream)
%   methods(hStream)
  disp(hStream.strProgramVersion);
  
  hStream.strServerName = 'Local';
  hStream.strDeviceName = 'RP2(1)'; 
  
  % Buffer size should be only smaller than the size 
  % of the SerialBuffer declared in the RCO
  hStream.lngBufferSize = 50000;
  % Buffer should be split into integer number of blocks
  hStream.lngBlockSize = 10000;
  hStream.ConnectTDT_Server();
  
  % Path on the computer where CP_TDT_Stream is running
  hStream.strFilePath = 'd:\tmp\';
  % File name on the computer where CP_TDT_Stream is running.
  % no path included
  hStream.strFileName = 'tmpName.i16';
  TTX = actxcontrol('ttank.x', [1 1 1 1]);

  if (invoke(TTX, 'ConnectServer', 'Local', 'myclient') ~= 1)
    err = 'error connecting to server'
  end

  if ( invoke(TTX,'OpenTank','SP-0001_DT1_051203','R') ~= 1)
    err = 'error connecting to server'
  end


catch
  disp( lasterr ); 
end

  % Get ready to record and wait for the "Record" state 
  % of the TDT device. Recording will stop when the state
  % changes from "Record" to any other state
  hStream.SetArmedState();
  
  disp('press any key to start recording');
  pause;
  
%  tdtRecOn
  
  recblock = invoke(TTX,'GetHotBlock')
  strTDTfile = [recblock '.i16'];
  hStream.strFileName = strTDTfile;  
  
  disp(strTDTfile);
  disp('press any key to exit');
  pause;
  
  
% delete( TTX );  
% delete(hStream)



