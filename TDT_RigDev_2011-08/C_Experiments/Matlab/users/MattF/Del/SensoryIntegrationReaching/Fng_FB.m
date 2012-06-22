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
    hFng.show=0; % fprintf(1,'FB0\n')
elseif (flag == 1),
    hFng.pos=pos+pert; % fprintf(1,'FB1\n')
    hFng.show=1;
else    
    hFng.pos=pos+pert; % fprintf(1,'FB2\n')
end