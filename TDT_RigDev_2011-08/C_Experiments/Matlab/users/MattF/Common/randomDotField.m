%function randomDotField(varargin)
function randomDotField(resetFlag,hDF,lKin,Ndots,dotSize,wsCenter,wsRadius,toggle,tgtLoc,velGain)
%
%  resetFlag    -  if 1, reset circle positions.
%  hDF          -  The handle to the dot field object
%  lKin         -  Most recent hand kinematics sample. This should be a
%                   velocity vector if calling a 'follow' field, and a
%                   position vector if calling a 'lead' field.
%  Ndots        -  approximate # of dots that will be drawn
%  dotSize      -  diameter of the dots
%  wsCenter     -  Center of workspace
%  wsRadius     -  The radius around the workspace center in which the dots
%                   will be drawn.
%  toggle       -  Toggle between 'lead' and 'follow'.  'lead' means that
%                   the dot field moves so as to lead the hand to the
%                   tgtLoc.  'follow' means the dot field moves with
%                   velocity proportional to the hand velocity.
%  tgtLoc       -  Argument used only with 'lead' option.  The dot field
%                   velocity will be proportional to the sqrt of the difference between
%                   the tgtLoc and the current hand location.
%                   0.4*sqrt(norm((tgtLoc-handLoc)).
%
%  NOTE:  You must call hW.drawnow from outside this function for the
%  screen to update.
%
%
%  MF Dec. 17, 2006
%
global Params
persistent dotLocs

if isequal(toggle,'lead') & nargin < 8
    error('Must input tgtLoc arg with ''lead'' dot field');
end

if ~exist('velGain'), velGain = 0.4; end
wsRadiusGain = 2;
%circleRadii = 2;
%closeEnough = 4.5;

%IP  = Params.IP;%[4,3]; % latest index for position
%IPV = Params.IPV;%[10,9]; % latest index for velocity

%  Circle field
%hDF.pos = wsCenter;
hDF.pos = wsCenter(:);
if ~exist('dotLocs') | isempty(dotLocs) | resetFlag
    dotLocs = repmat(wsCenter(:),1,Ndots) + 4*wsRadius.*(rand(2,Ndots)-0.5);
    dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
    dotLocs = dotLocs(:,find(dotRadii <= wsRadiusGain*wsRadius));
    vts = circleVerts(dotLocs,dotSize);
    hDF.vertices = vts;
end

ndots = size(dotLocs,2);
%hDF.show = 1;


%if isequal(hDF.drawmode,'Polygon')
if isequal(toggle,'lead')  %  Move the dots with vel proportional to the diff vector -(hand - target)
    %velGain = 0.4;
    %dotLocs = OdotLocs;
    % hMou.reset;
    %Mclick = hMou.click;
    %while ~Mclick(1)
    %lKin= hL.latest;
    lPos = lKin;
    diffVect = -(lPos - tgtLoc).*[1 -1];

    %while (norm(diffVect)>closeEnough
    %lKin= hL.latest;
    % lPos = lKin(2,IP);
    %   hFng.pos = lPos;
    diffVect = -(lPos - tgtLoc).*[1 -1];
    if norm(diffVect)>0
        dotVel = diffVect./norm(diffVect)*velGain*sqrt(norm(diffVect));%dotVelGain;
    else
        dotVel = [0 0];
    end

    dotLocs = dotLocs + repmat(dotVel',1,ndots);
    hDF.vertices = circleVerts(dotLocs,dotSize);
    %dotLocs = hDF.vertices;
    dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
    idx = find((dotRadii > wsRadiusGain*wsRadius) & (dotLocs'*dotVel' > 0)');
    dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
    %if toc > mousePollPeriod
    % hW.drawnow;
    % tic;
    %   Mclick = hMou.click;
    % end
    % end

else
    %  Link the dot field velocity to the cursor (Liberty)
    %Emou = get(hMou,'events');
    % dotLocs = OdotLocs;
    %mousePollPeriod = 0.02;
    %dotVelGain = 0.3;
    %hMou.reset;
    %Mclick = get(hMou,'click');
    %MprevPos = hMou.pos;
    %tic;
    %while ~Mclick(1)
    %lKin= hL.latest;
    lVel = -1*[-1 1].*lKin;  %% mm/sec <- mm/msec ????

    if norm(lVel)>0
        dotVel = -lVel./norm(lVel).*velGain*sqrt(norm(lVel));%dotVelGain;
    else
        dotVel = [0 0];
    end

    dotLocs = dotLocs + repmat(dotVel',1,ndots);
    hDF.vertices = circleVerts(dotLocs,dotSize);
    %hDF.vertices = dotLocs + repmat(dotVel',1,ndots);
    %dotLocs = hDF.vertices;
    %dotDists = sqrt(sum((dotLocs-OdotLocs).^2,1));  %  Dot distances from their original locations.
    %idx = dotDists>(0.3+0.7*rand(1,length(dotDists)).*dotDistThresh);
    %dotLocs(:,idx) = OdotLocs(:,idx);
    dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
    idx = find((dotRadii > wsRadiusGain*wsRadius) & (dotLocs'*dotVel' > 0)');
    dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
    %   if toc > mousePollPeriod
    %     hW.drawnow;
    %     MprevPos = hMou.pos;
    %      tic;
    %    Mclick = hMou.click;
    % end
    %end

end
return