srvname = 'CP_TDT_Stream.Application'

try
  hnd=actxserver(srvname)
  get(hnd)
  methods(hnd)
  
catch
  disp( lasterr ); 
end

delete(hnd)



