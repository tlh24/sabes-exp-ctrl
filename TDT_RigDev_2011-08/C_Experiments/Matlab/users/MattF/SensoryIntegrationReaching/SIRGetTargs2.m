function [start,reach,eye,nomrvect,pidx] = SIRGetTargs2(Params,dat)
%
%
%
%
%
%  MF March 22, 2007.  Aug 3, 2007.
%  June 20, 2008.
%

curshift = dat.fbshift;
reachrad = Params.reachradius;

%  Choose the start target so that the reach target is guaranteed to be within the workspace.
startBounds = [[Params.wsBounds(:,1) + [reachrad; -reachrad]] [Params.wsBounds(:,2) + [reachrad; -reachrad]]];
start = [rand(1)*range(startBounds(:,1))+min(startBounds(:,1)) ...
  rand(1)*range(startBounds(:,2))+min(startBounds(:,2))];

%%rdir = -pi + rand(1).*2*pi;  %  Choose direction uniformly around the circle
rdir = dat.nominalreachdirection;

[reachx, reachy] = pol2cart(rdir,reachrad);

nomrvect = [reachx reachy];
reach = start + nomrvect;

if Params.fixateRelativeToReachTrgFlag
  pidx = find(mnrnd(1,Params.P_relativeFixationLoc));
  % eye = Params.relativeFixationEyePosFunc(start,reach,Params.relativeFixationLocParams{pidx});
  if isnan(Params.relativeFixationLocParams{pidx,1})
    eye = [nan nan];  %  Don't enforce fixation on this trial
  else
    efunc = Params.relativeFixationLocParams{pidx,2};
    eyeposuseshift = curshift;
    if Params.eyeFixationDrawShiftForNoShiftTrialsFlag
      if ~sum(abs(curshift))
        if isempty(dat.visFB.shiftdistfunc)
          shdirlist = dat.visFB.shiftparams{1};
          shdistlist = dat.visFB.shiftparams{2};
          whdir = unidrnd(length(shdirlist),1,1);
          shdist = min(shdistlist) + rand(1).*range(shdistlist);
          shdir = shdirlist(whdir);
          if Params.doRelativeShiftFlag
            % [rang,dum] = cart2pol(rchvct(1),rchvct(2));
            rang = dat.nominalreachdirection;
            sang = rang + shdir;
            [shx,shy] = pol2cart(sang,shdist);
          else
            [shx,shy] = pol2cart(shdir,shdist);
          end
          eyeposuseshift = [shx shy];
        else
          eyeposuseshift = dat.visFB.shiftdistfunc(dat.visFB.shiftparams{:});
        end
      end
    end
    eye = efunc(start,reach,eyeposuseshift,Params.relativeFixationLocParams{pidx});
  end
elseif Params.fixateReachTrgFlag
  eye = reach;
else
  eye = eval(dat.eyetargetposfunc);
  esdist = 0;
  while (esdist < Params.MIN_EYE_TO_START_DISTANCE)
    eye = eval(dat.eyetargetposfunc);
    esdist = norm(eye - start);
  end
end


return