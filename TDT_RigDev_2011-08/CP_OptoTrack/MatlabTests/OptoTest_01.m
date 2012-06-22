srvname = 'CP_OptoTrack.Application';

hTracker=actxserver(srvname);
hTracker.GetVersion

hTracker.GetTrackerState
SensorsState = hTracker.GetSensors       
SensorsOn = int32([ 1 2 3 3 12       % Sensor
                    1 1 1 2 4  ]);   % Port
				   
hTracker.SetSensors(SensorsOn);
SensorsState = hTracker.GetSensors       

TransformMtx = hTracker.GetTransformMatrix(1)
TransformMtx = hTracker.GetTransformMatrix(2)

TransformMtx = [11 12 13 
                21 22 23 
                31 32 33 
                41 42 43 ];
hTracker.SetTransformMatrix(TransformMtx);       
TransformMtx = hTracker.GetTransformMatrix(1)

hTracker.SetTransformMatrix(TransformMtx,2);       
TransformMtx = hTracker.GetTransformMatrix(2)
