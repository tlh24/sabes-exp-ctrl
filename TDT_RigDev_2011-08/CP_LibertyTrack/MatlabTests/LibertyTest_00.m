CompNameInclude;
srvname = 'CP_LibertyTrack.Application'

try
  hTracker=actxserver(srvname, strCompName);
  hTracker.GetVersion
  get(hTracker)
  methods(hTracker)
  methodsview(hTracker)  
  
catch
  disp( lasterr ); 
end

delete(hTracker);
