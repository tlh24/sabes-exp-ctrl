function error = EyeStart(bufferFlagy)

% FUNCTION error = EyeStart(bufferFlag)
%
% Start data buffering from the serial interface to the Iscan tracker
%
% INPUT:
%
%   bufferFlag: whether to buffer data  -- default is TRUE (1)
%
% OUTPUT:
%   
%   error :  boolean, as to whether the routine timed-out looking
%              for the correct data format on the stream.
%
% NOTES: 
%
global hEyeTrack eyeStruct


if(nargin<1) bufferFlag=1; end

%% Re-Initialize Eye Data Structure (all except calibrated flag)

eyeStruct.error      = 0;
eyeStruct.started    = 1;
eyeStruct.buffer     = bufferFlag;
eyeStruct.frames     = 0;     %% SR: Used as index of the latest frame 
eyeStruct.latest     = [];
eyeStruct.latestRaw  = [];
eyeStruct.eyeTime    = {};    %% Use a list to speed up storage
eyeStruct.traj       = {};    %% Use a list to speed up storage
eyeStruct.trajRaw    = {};    %% Use a list to speed up storage

if( eyeStruct.calibrated)
  hEyeTrack.PutCalibrationMatrix(eyeStruct.calibCoef);
  hEyeTrack.IsCalibrated = 1;
else
  IdentityMtx = [ 0,0;
                  1,0;
                  0,1;
                  0,0;
                  0,0;
                  0,0;];
                  
  hEyeTrack.PutCalibrationMatrix(IdentityMtx);
  hEyeTrack.IsCalibrated = 0;
end

% Reset the buffer and the timestamps
hEyeTrack.ResetDataBuffer;
pause(0.1)   % SR: do we need this??

EyeUpdate;
error =  eyeStruct.error;
