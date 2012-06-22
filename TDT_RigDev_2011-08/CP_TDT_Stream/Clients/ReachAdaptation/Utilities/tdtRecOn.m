function tdtRecOn

% FUNCTION tdtRecOn
%
% Set TDT to Record Mode
%

global TDTdev

    invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',0);
    invoke(TDTdev,'SetSysMode',0);
    invoke(TDTdev,'SetSysMode',3);

