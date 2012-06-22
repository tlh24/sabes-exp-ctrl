function tdtTrialSetup(status,moveID,startID,stopID,trial)

% FUNCTION tdtTrialSetup(status,target)
%
% startus - scalar
%      - 1   -  mark Start Trial  
%      - 0   -  mark Stop Trial
%
% target  - scalar
%      - 1-32 - movement ID in Octagon 
%      - 1-7  - target ID in Target Array
%
% trial   - trial number

global TDTdev


if(nargin>1&status == 1), % start of trial
    invoke(TDTdev,'SetTargetVal','RP2(1).TargetID',moveID);
    invoke(TDTdev,'SetTargetVal','RP2(1).StartID',startID);
    invoke(TDTdev,'SetTargetVal','RP2(1).StopID',stopID);
    invoke(TDTdev,'SetTargetVal','RP2(1).TrialNumber',trial);
    invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',1); %% Mark Trial Start
else
    invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',0);
end
