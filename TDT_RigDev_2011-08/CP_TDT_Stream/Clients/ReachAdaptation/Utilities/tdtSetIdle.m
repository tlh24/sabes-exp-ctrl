function tdtSetIdle

% FUNCTION tdtSetIdle
%
% Set TDT to Idle Mode
%

global TDTdev

    invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',0);
    invoke(TDTdev,'SetSysMode',0);
