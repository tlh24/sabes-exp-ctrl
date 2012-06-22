srvname = 'CP_EyeTrack.Application'

try
  hITrack=actxserver(srvname);
  hITrack.strProgramVersion
  get(hITrack)
  methods(hITrack)
  methodsview(hITrack)  
  
catch
  disp( lasterr ); 
end

delete(hITrack);

% clear functions;

