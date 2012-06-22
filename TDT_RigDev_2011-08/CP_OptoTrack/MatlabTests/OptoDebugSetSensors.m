srvname = 'CP_OptoTrack.Application';
hTracker=actxserver(srvname);

% SensorsOn = int32([ 1 2 7 4       % Sensor
%                     1 1 1 4]);   % Port
% hTracker.SetSensors(SensorsOn);
% hTracker.GetSensors
% 

SensorsOn = int32([ 3 4 5 6 
                    2 2 2 2 ]);      % Sensor
hTracker.SetSensors(SensorsOn);
hTracker.GetSensors



% delete(hTracker);
% clear functions;