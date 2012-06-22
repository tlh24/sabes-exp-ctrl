function TrialFngFB(fhandle,pos,pert,flag)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% VR FEEDBACK FUNCTION%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fhandle - handle to the finger object
% pos - 2x1 vector position of the finger object
% pert - 2x1 vector of desired FB perturbation
% flag:  0 - turn off
%        1 - turn on and update position of FB
%        2 (or anything else) - just update position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if(flag==0)
    fhandle.Hide;
else
    fhandle.SetXY(pos+pert);
    if(flag==1)
    fhandle.Show;
    end
end