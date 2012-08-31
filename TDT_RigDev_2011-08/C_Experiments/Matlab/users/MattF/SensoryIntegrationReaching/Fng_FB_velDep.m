function dat = Fng_FB_velDep( pos, pert, flag, M)

%%% pos  -- 2x1 position vector
%%% pert -- 2x1 perturbation vector
%%% flag:
%%%   0 -- turn off
%%%   1 -- turn on & update
%%%   2 -- update

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%global ORIGIN
global hO hFng hW
global hL Params

persistent cpos
if isempty(cpos), cpos = pos+pert; end

marker = Params.FINGER_MARKER;

[Coords,Vel,Times,iIdx] = TrialGetKin(hL,marker,2,[1 2]);

dx = diff(Coords,1,1);
newPos = cpos + dx*M;
cpos = newPos;

if( flag == 0),
    hFng.Hide; % fprintf('FB0\n')
elseif (flag == 1),
    hFng.SetXY(newPos);
    % hFng.SetXY(pos+pert); % fprintf('FB1\n')
    hFng.Show;
else
    hFng.SetXY(newPos);
    % hFng.SetXY(pos+pert); % fprintf('FB2\n')
end