srvname = 'CP_EyeTrack.Application';

try
  hEye=actxserver(srvname);
  get(hEye)
  methods(hEye)
  methodsview(hEye)  
  
catch
  disp( lasterr ); 
end

delete(hEye);

% clear functions;

