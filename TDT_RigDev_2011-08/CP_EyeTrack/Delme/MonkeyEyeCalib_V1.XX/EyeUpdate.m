function [ eyePos, frame,  error ] = EyeUpdate()

% FUNCTION [ eyePos, frame,  error ] = EyeUpdate()
%
% Read all data currently in the CP_EyeTrack buffer and return 
% the lastest data point.
%
% OUTPUT:
%
%    eyePos :  1x2,  [horiz vert] position of the eye
%    frame  :  int,  frame count since last start or restart
%    errror :  error code
%
% NOTES: 
%

global hEyeTrack eyeStruct

eyePos = [];
frame = 0;
error = 0;

iLastIdx = eyeStruct.frames;  % Last index read
iLatestIdx  = hEyeTrack.lngLatestDataIndex; % Latest index available
nNew = iLatestIdx - iLastIdx;

% Check if we got new data, return if none is available
if nNew < 1  
  eyePos = eyeStruct.latest; 
  frame  = eyeStruct.frames;
  error  = eyeStruct.error;
  return;
end;

%Check if we still have data in the buffer
nDataMax = hEyeTrack.lngBufferSize;
if( nNew > nDataMax * 0.75 )
  nNew = nDataMax * 0.75;
  iLastIdx = iLatestIdx - nNew;
  fprintf('\n============================\n');
  warning('Some CP_EyeTrack data were missed between calls to EyeUpdate.');
end

% Get new data
dData = hEyeTrack.GetDataBuffer(iLastIdx+1, nNew);
%                                                        Time, ms      Raw_X         Raw_Y         Calib_X       Calib_Y
%  fprintf('%d\t%d\t%.1f\t%g\t%g\r', iLatestIdx, nNew, dData(end,1), dData(end,2), dData(end,3), dData(end,4), dData(end,5) );
eyeStruct.frames = iLatestIdx;

%% Save latest data 
eyeStruct.latestRaw = dData(end,2:3);
eyeStruct.latest = dData(end,4:5);

if(eyeStruct.buffer), 
  eyeStruct.eyeTime{end+1} = dData(:,1)*0.001; % convert from ms to sec
  eyeStruct.trajRaw{end+1} = dData(:,2:3); 
  eyeStruct.traj{end+1} = dData(:,4:5);;
end
    
eyePos = eyeStruct.latest; 
frame  = eyeStruct.frames;
error  = eyeStruct.error;
    
    