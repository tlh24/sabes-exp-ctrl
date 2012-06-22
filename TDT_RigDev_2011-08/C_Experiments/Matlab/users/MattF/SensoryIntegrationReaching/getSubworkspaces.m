function newLoc = getSubworkspaces(doWhich)
%
%
%
%
%  MF July 15, 2008.
%
global Params

DEBUG = 1;

%%doWhich = 1;

wsrange = range(Params.wsBounds,1);

switch doWhich

  case 1
    %  Find the arc (centered on the cyc. eye) radius that places the center of subws1 on it.
    %  Choose the center of subws2 to be also on the arc and at a fixed
    %  distance from the center of subws1, assuming that doesn't put it
    %  outside of the workspace.

    cycEyeLoc = Params.morphoData.CycEyeLoc;
    rightShoulderLoc = Params.morphoData.RightShoulderLoc;
    tableCoords = Params.morphoData.TableCoords;
    mirrorCoords = Params.morphoData.MirrorCoords;

    tableZFnc = tpaps(tableCoords(:,[1 2])',tableCoords(:,3)');
    mirrorZFnc = tpaps(mirrorCoords(:,[1 2])',mirrorCoords(:,3)');

    EtoSWS1vect = Params.subWorkspace(1).center - cycEyeLoc([1 2]);
    SWS1toSWS2vect = Params.subWorkspace(2).center - Params.subWorkspace(1).center;
    radE = norm(EtoSWS1vect);
    radS = norm(SWS1toSWS2vect);
    dTh = acos(1-0.5*radS^2/radE^2);
    th2 = atan2(EtoSWS1vect(2),EtoSWS1vect(1)) + [dTh -dTh];  %  Circles intersect in 2 places.
    [Xc_, Yc_] = pol2cart(th2,radE);
    Xc_ = Xc_ + cycEyeLoc(1);
    Yc_ = Yc_ + cycEyeLoc(2);

    delt = repmat(Params.subWorkspace(2).center,2,1) - [Xc_(:) Yc_(:)];
    deltmagsq = sum(delt.^2,2);
    [dum, mdmi] = min(deltmagsq);

    newX = Xc_(mdmi);
    newY = Yc_(mdmi);

    %  Check to make sure the subws is contained within the ws, i.e. all of
    %  its reach targets are within the WS bounds.
    [RD,RR] = meshgrid(Params.reachdirs,Params.reachradius);
    [rtx,rty] = pol2cart(RD(:),RR(:));
    rtx = rtx + newX;
    rty = rty + newY;
    chck = TrialInBox([rtx rty],Params.wsCenter,Params.wsHalfWidths);
    if ~all(chck)
      error('New Subws is outside of WS');
    end
    newLoc = [newX newY];
    
    if DEBUG
figure(77);
      EtoCvect = Params.wsCenter - cycEyeLoc([1 2]);

      arcth = [(3*pi/4):(-pi/32):(pi/4)];
      [arcX,arcY] = pol2cart(arcth,norm(EtoSWS1vect));
      arcX = arcX + cycEyeLoc(1);
      arcY = arcY + cycEyeLoc(2);
      [sharcX, sharcY] = pol2cart(arcth,sum(Params.linkLengths));
      sharcX = sharcX + rightShoulderLoc(1);
      sharcY = sharcY + rightShoulderLoc(2);


      rH = rectangle('position',[Params.wsBounds(1,1) min(Params.wsBounds(:,2)) wsrange]);
      axis equal;
      hold on;
      plot(arcX,arcY,'k--');
      plot(sharcX,sharcY,'k:');
      plot(newX,newY,'ks','markersize',8);
      plot(rtx,rty,'gs');
      for swi = 1:2
        plot(Params.subWorkspace(swi).center(1),Params.subWorkspace(swi).center(2),'o');
      end
      plot(cycEyeLoc(1),cycEyeLoc(2),'ro');
      text(cycEyeLoc(1),cycEyeLoc(2),'E');
      plot(rightShoulderLoc(1),rightShoulderLoc(2),'rs');
      text(rightShoulderLoc(1),rightShoulderLoc(2),'Sh');

    end

  otherwise
    error('Unknown subWS type');
end







