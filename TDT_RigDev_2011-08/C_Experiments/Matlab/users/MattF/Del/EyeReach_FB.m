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
function dat = EyeReach_FB( pos, pert, flag)

%global ORIGIN
%global hO hEye hW

if( flag == 0),
    hEye.show=0;
elseif (flag == 1),
    hEye.pos=pos+pert;
    hEye.show=1;
else    
    hEye.pos=pos+pert;
end