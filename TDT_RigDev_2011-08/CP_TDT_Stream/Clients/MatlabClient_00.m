srvname = 'CP_TDT_Stream.Application'

try
  hnd=actxserver(srvname)
  get(hnd)
  methods(hnd)
  disp(hnd.strProgramVersion);
  
  hnd.strServerName = 'Local';
  hnd.strDeviceName = 'RP2(1)'; 
  
  % Buffer size should be only smaller than the size 
  % of the SerialBuffer declared in the RCO
  hnd.lngBufferSize = 50000;
  % Buffer should be split into integer number of blocks
  hnd.lngBlockSize = 10000;
  hnd.ConnectTDT_Server();
  
  % File name on the computer where CP_TDT_Stream is running
  hnd.strFileName = 'd:\delme_03.i16';
  
  % Get ready to record and wait for the "Record" state 
  % of the TDT device. Recording will stop when the state
  % changes from "Record" to any other state
  hnd.SetArmedState();
  
  disp('press any key to exit');
  pause;

catch
  disp( lasterr ); 
end

delete(hnd)


