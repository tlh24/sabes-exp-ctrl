function EyeOpen()

% FUNCTION EyeOpen()
%
% Initialize CP_EyeTrack Server (provides connection to Iscan tracker)
%
%
% NOTES: 
% 
%   Things to ensure when trying to read Iscan over the serial port:
%
%    1) Setup in the Iscan software 
%        -  Baud rate matches the value in below (currently 57600)
%               (otherwise get strange values)
%        -  Serial Communication is ON (Serial I/O - Output Active checked)
%        -  On the Auxialliary Output Controls, make sure that the 
%                Output is set to binary, 
%                and the output is Pupil position X and Y, total 2 items)


global hEyeTrack eyeStruct


%% Initialize Eye Data Structure
eyeStruct.error      = 0;
eyeStruct.started    = 0;
eyeStruct.buffer     = 0;
eyeStruct.frames     = 0;     %% SR: Used as index of the latest frame 
eyeStruct.calibrated = 0;
eyeStruct.latest     = [];
eyeStruct.calibCoef  = [];
eyeStruct.calibMean  = [];
eyeStruct.calibStd   = [];
eyeStruct.eyeTime    = {};    %% Use a list to speed up storage
eyeStruct.traj       = {};    %% Use a list to speed up storage
eyeStruct.trajRaw    = {};    %% Use a list to speed up storage


srvname = 'CP_EyeTrack.Application';

hEyeTrack=actxserver(srvname);
pause(0.1)
disp(hEyeTrack.strProgramVersion);
hEyeTrack.ConnectISCAN();
pause(0.1)
