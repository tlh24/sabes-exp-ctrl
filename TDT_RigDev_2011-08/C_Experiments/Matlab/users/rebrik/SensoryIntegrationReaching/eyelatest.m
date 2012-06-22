%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% EYE LATEST %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [pos,frame] = eyelatest(new)

global Params
global eyeStruct

if(nargin<1) new=0; end
if(isempty(eyeStruct.started)) started=0; end

[pos, frame] = EyeUpdate; % Get Eye Data

