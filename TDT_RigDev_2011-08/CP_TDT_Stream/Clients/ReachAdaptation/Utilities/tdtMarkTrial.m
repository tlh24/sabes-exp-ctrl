function tdtMarkTrial(mark)

% FUNCTION tdtMarkTrial(mark)
%
% Set tone frequence
%
% mark - scalar
%      - 1   -  mark Start Trial  
%      - 0   -  mark Stop Trial
%

global TDTdev

%% Mark Trial Stop
if( mark == 0 )
    invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',0);
    return
end

%% Mark Trial Start
if( mark == 1 )
    invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',1);
end
