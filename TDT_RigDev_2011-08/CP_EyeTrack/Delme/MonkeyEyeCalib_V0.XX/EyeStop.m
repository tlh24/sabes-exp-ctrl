function [eyeTime, eyeTraj, eyeTrajRaw, error] = EyeStop()

% FUNCTION [eyeTime, eyeTraj, eyeTrajRaw, error] = EyeStop()
%
% Read all data currently in the serial buffer and then 
% stop data buffering from the serial interface to the 
% Iscan tracker. 
%
% Return the eye trajectory.
% 
% OUTPUT:
%
%    eyeTime :  Nx1 where N is the number of data points 
%               collected since the last EyeStart.
%               The time, in seconds, of each data point.
%
%    eyeTraj :     Nx2 
%    eyeTrajRaw :  The raw data don't use the software calibration.
%                  if no software calibration is used, these are identical.
%
% NOTES: 
%

global hEyeTrack eyeStruct


%%%%%%% Read Existing Data
EyeUpdate;

eyeStruct.started = 0;

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


