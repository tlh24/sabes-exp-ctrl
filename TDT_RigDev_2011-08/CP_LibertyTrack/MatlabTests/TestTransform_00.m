srvname = 'CP_LibertyTrack.Application';

hTracker=actxserver(srvname);

Trans1 = hTracker.GetTransformMatrix  

Trans2 = [ 0     0     1
           0     1     0
           2     0     0
           0     0     0];
hTracker.SetTransformMatrix(Trans2, 2);
Trans3 = hTracker.GetTransformMatrix(2) 

SensorsOn = int32([1 3]);
hTracker.SetSensors(SensorsOn);
TrasformIdx0 = hTracker.GetSensorsTransformIdx  

TrasformIdx1 = [ 1 2 ];
hTracker.SetSensorsTransformIdx(int32( TrasformIdx1 ));  
TrasformIdx2 = hTracker.GetSensorsTransformIdx  

% hTracker.DisconnectTracker;

% delete(hTracker);
% clear functions;


