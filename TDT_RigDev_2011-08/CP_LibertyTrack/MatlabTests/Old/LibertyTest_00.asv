srvname = 'CP_LibertyTrack.Application'

try
  hLiberty=actxserver(srvname);
  hLiberty.strProgramVersion
  get(hLiberty)
  methods(hLiberty)
  methodsview(hLiberty)  
  
catch
  disp( lasterr ); 
end

delete(hLiberty);
