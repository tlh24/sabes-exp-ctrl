function [Jct, Jtime] = tdtJuice(time)

% FUNCTION Juice(time)
%
% Give a Juice Reward
% time : scalar, time in ms
%

global TDTdev JuiceTime


if( time~=JuiceTime )
    invoke(TDTdev,'SetTargetVal','RP2(1).JuiceTime',time);
    JuiceTime = time;
end


%% Can't invoke triggers, so just toggle JuiceTrigger
t=invoke(TDTdev,'GetTargetVal','RP2(1).JuiceTrigger');
invoke(TDTdev,'SetTargetVal','RP2(1).JuiceTrigger',~t);

if(nargout>0),
 Jct = invoke(TDTdev,'GetTargetVal','RP2(1).CumRewards');
end

if(nargout>1),
 Jtime = invoke(TDTdev,'GetTargetVal','RP2(1).CumRewardTime');
end
