%  TestDotField.m
%
%
%  MF Dec. 16, 2006
%

global hL hW hMou
global hStartTrg hReachTrg hFng hRightHandDotField hCOTestShape

global DEBUG
global BUFFERTIME PREDTIME FRAMERATE

circleRadii = 2;
closeEnough = 4.5;
causalDots = 1;
tgtLoc = [0 0];

wsCenter = [5 0];
wsRadius = 100;
Ndots = 150;
%dotDistThresh = 20;  %  If the dots are farther than this from their original loc, then put them back there.

IP  = [4,3]; % latest index for position
IPV = [10,9]; % latest index for velocity
%%%%% Debug flags
DEBUG     = 0;

hL.active  = 1;  %% Activate Liberty

%%%%% SETUP ALL VIS OBJECTS
hW.batchmode = 1;

%%  FINGER FB
hFng.color = [1 1 1];
hFng.scale = 1;
hFng.fill = 1;
hFng.show = 1;

%%% START TARGET
hStartTrg.pos    = tgtLoc;%dat.starttargetpos;
hStartTrg.color  = [0 1 0] * 0.5;
hStartTrg.scale  = 3;%dat.starttargetrad;
hStartTrg.fill   = 1;
hStartTrg.z      = .5;
hStartTrg.show   = 0;

% %%% REACH TARGET
% hReachTrg.pos    = [5 5];%dat.reachtargetpos;
% hReachTrg.color  = [0 1 0] *0.9;
% hReachTrg.scale  = 12;%dat.reachtargetrad;
% hReachTrg.fill   = 1;
% hReachTrg.z      = 0;
% hReachTrg.show   = 0;

% %  Triangle
% hCOTestShape.pos = wsCenter;
% hCOTestShape.show = 0;


%  Dot Field
% hRightHandDotField.pos = wsCenter;
% OdotLocs = 4*wsRadius.*(rand(2,Ndots)-0.5);
% dotRadii = sqrt(OdotLocs(1,:).^2 + OdotLocs(2,:).^2);
% OdotLocs = OdotLocs(:,find(dotRadii <= 1.5*wsRadius));
% ndots = size(OdotLocs,2);
% hRightHandDotField.vertices = OdotLocs;
% hRightHandDotField.show = 1;

%  Circle field
hRightHandDotField.pos = wsCenter;
OdotLocs = 4*wsRadius.*(rand(2,Ndots)-0.5);
dotRadii = sqrt(OdotLocs(1,:).^2 + OdotLocs(2,:).^2);
OdotLocs = OdotLocs(:,find(dotRadii <= 1.5*wsRadius));
ndots = size(OdotLocs,2);
vts = circleVerts(OdotLocs,circleRadii);
hRightHandDotField.vertices = vts;
hRightHandDotField.show = 1;

% figure;
% for i = 1:ndots
%     plot(vts(1,:,i),vts(2,:,i));
%     hold on
% end
% axis equal

%lKin= hL.latest;
%lvel = lKin(2,IPV);  %% mm/sec <- mm/msec ????
%lpos = lKin(2,IP);        %% mm

if isequal(hRightHandDotField.drawmode,'Polygon')
    if causalDots  %  Move the dots with vel proportional to the diff vector -(hand - target)
        velGain = 0.4;
        dotLocs = OdotLocs;
        hMou.reset;
        Mclick = hMou.click;
        while ~Mclick(1)
            lKin= hL.latest;
            lPos = lKin(2,IP);
            hFng.pos = lPos;
            % lVel = -1*[-1 1].*lKin(2,IPV);  %% mm/sec <- mm/msec ????
            diffVect = -(lPos - tgtLoc).*[1 -1];
            if norm(diffVect)>closeEnough
                dotVel = diffVect./norm(diffVect)*velGain*sqrt(norm(diffVect));%dotVelGain;
            else
                dotVel = [0 0];
            end

            dotLocs = dotLocs + repmat(dotVel',1,ndots);
            hRightHandDotField.vertices = circleVerts(dotLocs,circleRadii); 
            %dotLocs = hRightHandDotField.vertices;
            dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
            idx = find((dotRadii > 1.5*wsRadius) & (dotLocs'*dotVel' > 0)');
            dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
            %if toc > mousePollPeriod
            hW.drawnow;
            % tic;
            Mclick = hMou.click;
            % end
        end

    else
        %  Link the dot field velocity to the cursor (Liberty)
        %Emou = get(hMou,'events');
        dotLocs = OdotLocs;
        mousePollPeriod = 0.02;
        %dotVelGain = 0.3;
        hMou.reset;
        Mclick = get(hMou,'click');
        %MprevPos = hMou.pos;
        tic;
        while ~Mclick(1)
            lKin= hL.latest;
            lVel = -1*[-1 1].*lKin(2,IPV);  %% mm/sec <- mm/msec ????

            if norm(lVel)>0
                dotVel = -lVel./norm(lVel).*0.5*sqrt(norm(lVel));%dotVelGain;
            else
                dotVel = [0 0];
            end

            hRightHandDotField.vertices = dotLocs + repmat(dotVel',1,ndots);

            dotLocs = hRightHandDotField.vertices;
            %dotDists = sqrt(sum((dotLocs-OdotLocs).^2,1));  %  Dot distances from their original locations.
            %idx = dotDists>(0.3+0.7*rand(1,length(dotDists)).*dotDistThresh);
            %dotLocs(:,idx) = OdotLocs(:,idx);
            dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
            idx = find((dotRadii > 1.5*wsRadius) & (dotLocs'*dotVel' > 0)');
            dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
            if toc > mousePollPeriod
                hW.drawnow;
                %     MprevPos = hMou.pos;
                tic;
                Mclick = hMou.click;
            end
        end

    end

else
    if causalDots  %  Move the dots with vel proportional to the diff vector -(hand - target)
        velGain = 0.4;
        dotLocs = OdotLocs;
        hMou.reset;
        Mclick = hMou.click;
        while ~Mclick(1)
            lKin= hL.latest;
            lPos = lKin(2,IP);
            hFng.pos = lPos;
            % lVel = -1*[-1 1].*lKin(2,IPV);  %% mm/sec <- mm/msec ????
            diffVect = -(lPos - tgtLoc).*[1 -1];
            if norm(diffVect)>closeEnough
                dotVel = diffVect./norm(diffVect)*velGain*sqrt(norm(diffVect));%dotVelGain;
            else
                dotVel = [0 0];
            end

            hRightHandDotField.vertices = dotLocs + repmat(dotVel',1,ndots);
            dotLocs = hRightHandDotField.vertices;
            dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
            idx = find((dotRadii > 1.5*wsRadius) & (dotLocs'*dotVel' > 0)');
            dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
            %if toc > mousePollPeriod
            hW.drawnow;
            % tic;
            Mclick = hMou.click;
            % end
        end

    else
        %  Link the dot field velocity to the cursor (Liberty)
        %Emou = get(hMou,'events');
        dotLocs = OdotLocs;
        mousePollPeriod = 0.02;
        %dotVelGain = 0.3;
        hMou.reset;
        Mclick = get(hMou,'click');
        %MprevPos = hMou.pos;
        tic;
        while ~Mclick(1)
            lKin= hL.latest;
            lVel = -1*[-1 1].*lKin(2,IPV);  %% mm/sec <- mm/msec ????

            if norm(lVel)>0
                dotVel = -lVel./norm(lVel).*0.5*sqrt(norm(lVel));%dotVelGain;
            else
                dotVel = [0 0];
            end

            hRightHandDotField.vertices = dotLocs + repmat(dotVel',1,ndots);

            dotLocs = hRightHandDotField.vertices;
            %dotDists = sqrt(sum((dotLocs-OdotLocs).^2,1));  %  Dot distances from their original locations.
            %idx = dotDists>(0.3+0.7*rand(1,length(dotDists)).*dotDistThresh);
            %dotLocs(:,idx) = OdotLocs(:,idx);
            dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
            idx = find((dotRadii > 1.5*wsRadius) & (dotLocs'*dotVel' > 0)');
            dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
            if toc > mousePollPeriod
                hW.drawnow;
                %     MprevPos = hMou.pos;
                tic;
                Mclick = hMou.click;
            end
        end

    end
end
% %  Link the dot field velocity to the cursor (mouse)
% %Emou = get(hMou,'events');
% dotLocs = OdotLocs;
% mousePollPeriod = 0.05;
% %dotVelGain = 0.3;
% hMou.reset;
% Mclick = get(hMou,'click');
% MprevPos = hMou.pos; tic;
% while ~Mclick(1)
%
%     mVel = hMou.pos - MprevPos;
%     if norm(mVel)>0
%     dotVel = -mVel./norm(mVel).*0.5*sqrt(norm(mVel));%dotVelGain;
%     else
%         dotVel = [0 0];
%     end
%
%     hRightHandDotField.vertices = dotLocs + repmat(dotVel',1,ndots);
%
%     dotLocs = hRightHandDotField.vertices;
%     %dotDists = sqrt(sum((dotLocs-OdotLocs).^2,1));  %  Dot distances from their original locations.
%     %idx = dotDists>(0.3+0.7*rand(1,length(dotDists)).*dotDistThresh);
%     %dotLocs(:,idx) = OdotLocs(:,idx);
%     dotRadii = sqrt(dotLocs(1,:).^2 + dotLocs(2,:).^2);
%     idx = find((dotRadii > 1.5*wsRadius) & (dotLocs'*dotVel' > 0)');
%     dotLocs(:,idx) = -dotLocs(:,idx);%./repmat(dotRadii(idx),2,1).*1.5*wsRadius;
%     if toc > mousePollPeriod
%         hW.drawnow;
%         MprevPos = hMou.pos;
%         tic;
%         Mclick = hMou.click;
%     end
% end
%
