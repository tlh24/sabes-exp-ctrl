srvname = 'TDevAcc.X'

try
%  hnd=actxserver(srvname)
  hnd=actxcontrol(srvname)
  
  get(hnd)
  methods(hnd)
  invoke(hnd,'ConnectServer','Local')
%  invoke(hnd,'CheckServerConnection')  
%  hnd.CheckServerConnection()
  hnd.AboutBox()
catch
  disp( lasterr ); 
end

delete(hnd)



