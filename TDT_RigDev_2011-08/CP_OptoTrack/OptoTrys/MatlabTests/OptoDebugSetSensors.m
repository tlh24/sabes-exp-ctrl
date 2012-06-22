srvname = 'CP_OptoTrack.Application';
hTracker=actxserver(srvname);

SensorsOn = int32([ 1 2 7 4       % Sensor
                    1 2 1 2      % Transform
                    1 1 1 4]);   % Port
hTracker.SetSensors(SensorsOn);
hTracker.GetSensors

SensorsOn = int32([ 1 2 3 4       % Sensor
                    1 2 1 2 ]);      % Transform
hTracker.SetSensors(SensorsOn);
hTracker.GetSensors

SensorsOn = int32([ 1 2 3 7 ]);      % Sensor
hTracker.SetSensors(SensorsOn);
hTracker.GetSensors



% delete(hTracker);
% clear functions;