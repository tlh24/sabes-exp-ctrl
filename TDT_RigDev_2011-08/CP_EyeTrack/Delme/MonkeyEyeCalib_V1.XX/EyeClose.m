function EyeClose()

% FUNCTION EyeClose()
%
% Close CP_EyeTrack server (the interface to the Iscan tracker)
%
%
% NOTES: 
%

global hEyeTrack eyeStruct

hEyeTrack.DisconnectISCAN();
pause(0.1)

delete(hEyeTrack);
clear hEyeTrack
clear eyeStruct