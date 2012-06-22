function SetOptoSensorsTransform()

ServerNamesInclude;
DisplaySizeInclude;


hTracker=actxserver(strTrackerName, strTrackerComputer);

[iTrackerID iTrackerState] = hTracker.GetTrackerState;

if iTrackerID ~= 2
  error('Tracker is not OptoTrak!');
end
if iTrackerState ~= 1
  error('OptoTraki is not connected!');
end

mtxTransformIdx = int32([ 1 2 ]);
                
hTracker.SetSensorsTransformIdx(mtxTransformIdx);


delete(hTracker);