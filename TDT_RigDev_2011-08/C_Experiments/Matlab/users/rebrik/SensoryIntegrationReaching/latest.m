%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%% HAND LATEST %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [pos,vel,velpct] = latest(new)

global hL Params
persistent velmax started

MINVELMAX = 20;
IP  = [4,3]; % latest index for position
IPV = [10,9]; % latest index for velocity

if(nargin<1) new=0; end
if(isempty(started)) started=0; end

[iIdx, Times, Coord ] = invoke( hL, 'GetSensorLatest', Params.FINGER_MARKER, 10 );

pos = Coord(1:2);
% CP_TODO calc velocity
vel = [0,0];
vel = norm(vel);

if(new | ~started),
    %% First time, set to initialize values
    velmax = 0;
    velpct = 1;  %% default high value
    started = 1;
else
    %% Look for maximum velocity during the reach
    if(vel > velmax) velmax = vel; end
    if(velmax<.01) velpct=1;
    else           velpct = vel/velmax;
    end

    %% Check to make sure velmax isnt too small
    %% i.e. if there is dip at start of reach
    %% just set velpct to 1 (default high value)
    if(velmax < MINVELMAX) velpct=1; end
end

