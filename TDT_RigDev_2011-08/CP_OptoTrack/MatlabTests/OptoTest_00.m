srvname = 'CP_OptoTrack.Application'

try
  hTracker=actxserver(srvname);
  hTracker.GetVersion
  get(hTracker)
  methods(hTracker)
  methodsview(hTracker)  
  
catch
  disp( lasterr ); 
end

delete(hTracker);
