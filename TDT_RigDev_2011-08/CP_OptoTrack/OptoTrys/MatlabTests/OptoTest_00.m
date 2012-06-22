srvname = 'CP_OptoTrack.Application'

try
  hTracker=actxserver(srvname);
  hTracker.strProgramVersion
  get(hTracker)
  methods(hTracker)
  methodsview(hTracker)  
  
catch
  disp( lasterr ); 
end

delete(hTracker);
