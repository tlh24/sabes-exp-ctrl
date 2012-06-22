%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% VR FEEDBACK FUNCTION for PrismVsVR Expt
    %% FEEDBACK FUNCS CALLED LIKE THIS:
    %%% fbfunc(pos,pert,flag)
    %%% pos  -- 2x1 posiition vector
    %%% pert -- 2x1 perturbation vector
    %%% flag: 
    %%%   0 -- turn off
    %%%   1 -- turn on & update
    %%%   2 -- update

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function dat = FngReach_FB( pos, pert, flag)

global ORIGIN
global hO hFng hW

if( flag == 0),
    hFng.Hide; % fprintf('FB0\n')
elseif (flag == 1),
    hFng.SetXY(pos+pert); % fprintf('FB1\n')
    hFng.Show;
else    
    hFng.SetXY(pos+pert); % fprintf('FB2\n')
end