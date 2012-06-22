function [eyeTime, eyeTraj, eyeTrajRaw, error] = EyeBuffer()

% FUNCTION [eyeTime, eyeTraj, eyeTrajRaw, error] = EyeBuffer()
%
% Read all data currently in the Matlab buffer
%
% Return the eye trajectory.
% 
% OUTPUT:
%
%    eyeTime :  Nx1 where N is the number of data points 
%               collected since the last EyeStart. 
%               The time, in seconds, of each data point.
%
%    eyeTraj :     NxD where D is the number of items in each Iscan frame.
%    eyeTrajRaw :  The raw data don't use the software calibration.
%                  if no software calibration is used, these are identical.
%
% NOTES: 
%

global hEyeTrack eyeStruct

%%%%%%% Read Existing Data
EyeUpdate;
pause(.01);  % Otherwise there seems to be some oddness about eyeStruct
             % not having updated in the first if statement (e.g. eyeTime
             % lags eyeTraj)??????

eyeTime=[];
eyeTraj=[];
eyeTrajRaw = [];
error = eyeStruct.error;

%%%%%%% Cat the Data
if(eyeStruct.buffer)
  eyeTime = cat(1,eyeStruct.eyeTime{:});
  eyeTraj = cat(1,eyeStruct.traj{:});
  eyeTrajRaw = cat(1,eyeStruct.trajRaw{:});
end
