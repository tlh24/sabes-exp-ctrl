function dat = LearnToFixate_Trial_w_HandHold_2(dat)
%
%  MF May 16, 2007.
%

global ORIGIN BUFFERTIME FRAMERATE
global Params
global hEyeTrg hStartTrg hRightHandArrowField hReachTrg
global hL hW NO_ISCAN

%NO_ISCAN = 0;  % For Debugging

hL.active  = 1;  %% Activate Liberty

%%%%% SETUP ALL VIS OBJECTS
hW.batchmode = 1;

%%% START TARGET
hStartTrg.pos    = dat.starttargetpos;
hStartTrg.color  = dat.starttargetrgb * dat.starttargetbright;
hStartTrg.scale  = dat.starttargetrad;
hStartTrg.fill   = 1;
hStartTrg.z      = .5;
hStartTrg.show   = 0;

%%% REACH TARGET
hReachTrg.pos    = dat.reachtargetpos;
hReachTrg.color  = dat.reachtargetrgb * dat.reachtargetbright;
hReachTrg.scale  = dat.reachtargetrad;
hReachTrg.fill   = 1;
hReachTrg.z      = 0;
hReachTrg.show   = 0;

%%% EYE TARGET
hEyeTrg.pos    = dat.eyetargetpos;
hEyeTrg.color  = dat.eyetargetrgb .* dat.eyetargetbright;
hEyeTrg.scale  = dat.eyetargetrad;
hEyeTrg.fill   = 1;
hEyeTrg.z      = 1;
hEyeTrg.show   = 0;

hW.drawnow;          %%% Chiara 03-30-05, the VisServer code will log
invoke(hW,'clrlog');

dat.trialtime = clock; % Start Trial Time
dat.err = 0;
dat.finalreward = 0; % Set final reward to zero
dat.totalreward = 0;

%if ~NO_ISCAN
EyeStart;
%end


%-------------------

dat.starttargetwin =  Params.START_TARGET_WIN;
dat.starttargetrad =  Params.START_TARGET_RAD;

dat.starttargetshow     = Params.START_TARGET_SHOW;  % in this way we can change the
dat.starttargetfeedback = 0; %Params.START_TARGET_FEEDBACK; % initial parameters from keyboard
dat.starttargetflashbright = Params.START_TARGET_FLASH_BRIGHT;
dat.starttargethold = Params.START_TARGET_HOLD;


setMultiVisObjects(hRightHandArrowField,'show',1);
hW.drawnow;

%%% Acquisition of Start Target.
pos = latest(1);
initialLoc = pos; initialLocWin = 5; movestartedflag = 0; movestartedtime = inf;
[dummy,initialDist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
done=0; err = 0; dat.errstring = '';
tic; gotArm = 0; %dat.starttargethold = 0.5;
lastVBupdatetime = toc;
loopct = 0;
while (~done),
    loopct = loopct+1;
    pos = latest(1);
    %  Train with Arrow field.  Length and direction of each arrow in field is proportional
    %  to difference vector, (tgtLoc - handLoc).
    [cdang,cddist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
    asize = Params.arrowFieldLength(cddist);
    setMultiVisObjects(hRightHandArrowField,'angle',cdang.*180/pi,'scale',asize, ...
        'color',dat.righthandarrowfieldrgb*feval(dat.righthandarrowfieldbrightnessfunc,asize));
    hW.drawnow;

    %     if ~hStartTrg.show & Params.AFDeltaReward
    %         if initialDist - cddist >= Params.deltaForReward
    %             tdtJuice(Params.AFDeltaReward);
    %             dat.totalreward = dat.totalreward+Params.AFDeltaReward;
    %             initialDist = cddist;
    %         end
    %     end

    if (dat.maxmovetimetostarttarget < inf ) & ~movestartedflag & ~INBOX(pos,initialLoc,initialLocWin)
        %  Once he's moved a small distance away from his initial location,
        %  we start counting time.  He has a max time to get to the start
        %  target location.
        movestartedflag = 1;
        movestartedtime = toc;
    end

    %     if hFng.show  %(dat.starttargetfeedback)
    %         feval(dat.fngfeedbackfunc, pos, 0, 2);
    %         if (toc-lastVBupdatetime) > dat.visBlur.VBUP  %~mod(loopct,dat.visBlur.VBUP)
    %             lastVBupdatetime = toc;
    %             hFng.vertices = updateVisBlurVerts(dat.visBlur.N,dat.visBlur.Nverts,dat.visBlur.dotrad,dat.visBlur.C);
    %         end
    %         hW.drawnow;
    %     end
    % check for acquisition of start target
    posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);
    if (posOk),
        if (~gotArm),
            gotArm = 1;
            starthold = toc;
            %feval(dat.fngfeedbackfunc, pos, 0, 1);  %  Show the FB during the hold period.
            hW.drawnow;
        elseif (toc>(starthold+dat.starttargethold))
            done = 1;   % Reach to start target OK
        end
        setMultiVisObjects(hRightHandArrowField,'show',0);
        hW.drawnow;
    else
        gotArm = 0;
        setMultiVisObjects(hRightHandArrowField,'show',1);
        %         if ~dat.starttargetfeedback
        %         feval(dat.fngfeedbackfunc, pos, 0, 0);
        %         end
        hW.drawnow;
    end

    if (toc >= Params.REACH_START_TARGET_TIMEOUT),
        err            = 1;
        dat.err        = err;
        dat.errstring  = 'Timeout at Start Position';
        done           = 1;
    elseif (toc - movestartedtime) > dat.maxmovetimetostarttarget
        err = 5;
        dat.err = err;
        dat.errstring = 'Too slow to reach Start Target';
        done = 1;
    end
end
setMultiVisObjects(hRightHandArrowField,'show',0);
hW.drawnow;




%  Hold hand at start target, fixate eye target and hold

if(~err)
    %% Show eye target
    hEyeTrg.show   = 1;
    % tdtSetEyeTarget(dat.reachtargetnb);
    hW.drawnow;
end

done=0;
err = 0;
target_time=0;
loopct = 0;
gotEye = 0;
[etim,ebuf]=EyeBuffer; etim0=etim(end);
tic;
while (~done & ~err),

    pos = latest(1);     % get latest pos
    %
    %     if(dat.starttargetfeedback), % Show feedback if enabled
    %         feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
    %     end
    %
    % Update GUI every N loops
    loopct = loopct + 1; % counter to update hand data plot
    %     if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); drawnow; end
    %
    %     %%% check if hand is still in start window
    posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);
    if (~posOk),
        err            =  3;
        dat.err        = err;
        dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
        %hStartTrg.show = 0;
        hEyeTrg.show   = 0;
        done           = 1;
    end
    %
    %%% check for eye target acquisition
    if (~err)
        [eye,eyeframe] = eyelatest(0);

        % set(hpEye,'xdata',eye(1),'ydata',eye(2)); drawnow; % plot eye data

        % check to see if got into eye window
        [etim,ebuf]=EyeBuffer;
        eframes = min(5,length(etim));
        ebuf = ebuf((end-eframes+1):end,:);
        etim = etim((end-eframes+1):end,:);
        if(etim(1)<etim0)
            ebuf = ebuf(etim>=etim0,:);
            etim = etim(etim>=etim0,:);
        end
        eyeOk = sum(INBOX(ebuf,dat.eyetargetpos,dat.eyetargetwin))>4;
        if(NO_ISCAN) eyeOk=1; end

        if (~eyeOk)
            gotEye = 0;
        end
        if (eyeOk), % Eye acquisition accomplished
            if (~gotEye)
                time = toc;
                gotEye = 1;
            elseif (gotEye&(toc >=(time+dat.eyetargethold)))
                done = 1;
                EyeFixPt = mean(ebuf);
                %hEyeTrg.show = 0;
            end
        end

        % Eye acquisition not accomplished
        if((toc+dat.eyetargethold)>dat.eyetargettimeout),
            err               = 21;
            dat.err           = err;
            dat.errstring     = 'Timeout to Eye Target';
            hEyeTrg.show      = 0;
            %            hStartTrg.show    = 0;
            done              = 1;
        end
    end
    hW.drawnow;

end
dat.eyebufferatfixation = ebuf;
dat.eyebuffertimeatfixation = etim;

if ~err
%    fprintf('\n\t\tMADE IT HERE\n');
    hReachTrg.show = 1;
    hW.drawnow;
    done = 0; loopct=0;
    tic;
    while ~done & ~err
        %if loopct==0, fprintf('\n\t\tMADE IT HERE\n'); end
        
        pos = latest(1);     % get latest pos

        % Update GUI every N loops
        loopct = loopct + 1; % counter to update hand data plot
        %     if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); drawnow; end
        %
        %     %%% check if hand is still in start window
        posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);
        if (~posOk),
            err            =  3;
            dat.err        = err;
            dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
            %hStartTrg.show = 0;
            hEyeTrg.show   = 0;
            done           = 1;
        end

        %  Hold hand and eye.  Show reach target.  Must maintain eye and hand
        %  hold.
        [eye,eyeframe] = eyelatest(0);

        % set(hpEye,'xdata',eye(1),'ydata',eye(2)); drawnow; % plot eye data

        % check to see if eye is still in window
        [etim,ebuf]=EyeBuffer;
        eframes = min(5,length(etim));
        ebuf = ebuf((end-eframes+1):end,:);
        etim = etim((end-eframes+1):end,:);
        if(etim(1)<etim0)
            ebuf = ebuf(etim>=etim0,:);
            etim = etim(etim>=etim0,:);
        end
        eyeOk = sum(INBOX(ebuf,dat.eyetargetpos,dat.eyetargetwin))>4;
        if(NO_ISCAN) eyeOk=1; end

        if (~eyeOk)
            err               = 23;
            dat.err           = err;
            dat.errstring     = 'Broke Eye Fixation at Show Reach Target';
            hEyeTrg.show      = 0;
            done              = 1;
            hReachTrg.show = 0;
        end

        if toc >=dat.reachtrgshowdur
            done = 1;
            hReachTrg.show = 0;
            hEyeTrg.show = 0;
        end

        hW.drawnow;
    end
end
hReachTrg.show = 0;
hEyeTrg.show = 0;
hW.drawnow;


if (~err), % If aquired eye target give reward
    tdtJuice(Params.EYE_FIX_REWARD2);
    dat.totalreward = dat.totalreward+Params.EYE_FIX_REWARD2;
end
% %%% If eye fixation point acquired, give small reward and try to hold
% %%% while hand target comes up
% eyeOk = 0; posOk = 0;
%
% % START Liberty buffer during delay (here since 4/11/06)
% %%%%%%% ERROR CHECK BUFFER COMMANDS
% % nE0 = hL.err;
% % invoke(hL,'startBuffer');
% % nE1 = hL.err;
% % if(nE1>nE0)
% %     for i=(nE0+1):nE1,
% %         fprintf(1,'%d: %s',i,hL.getErr(i))
% %     end
% % end
%
% [etim,ebuf]=EyeBuffer; etim0=etim(end);
% tic;
% loopct = 0;
% if (~err)
%
% %     %%% REACH DELAY
% %     dat.reachdelay = Params.REACH_DELAY_MIN + ...
% %         rand*(Params.REACH_DELAY_MAX-Params.REACH_DELAY_MIN);
% %
% % %     dat.reachdelay = 0;
% %
% %     % in some trials, the delay will be longer than the max
% %     longDelay = 0;
% %     r = rand;
% %     if (r>0.95),
% %         dat.reachdelay = 1.50;
% %         longDelay = 1; % flag to enable extra reward for long waiting
% %     end
%
%     fprintf(1,' Del=%.2f ',dat.reachdelay)
%
%     while ((toc < dat.eyetargethold)), %%  Hold at eye target
%
% %         %%% get hand position at start target
% %         %%% and check if hand still in start window
% %         pos = latest(1);
% %         if(dat.starttargetfeedback), % Show feedback if enabled
% %             feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
% %         end
% %         posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);
%
% %         % Update GUI every N loops
% %         loopct = loopct + 1; % counter to update hand data plots
% %         if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); drawnow; end
% %
% %         if (~posOk),
% %             err            = 6;
% %             dat.err        = err;
% %             dat.errstring  = 'Broke Hold at Start Position While Holding Eye Fixation';
% %             hStartTrg.show = 0;
% %             hEyeFix2.show  = 0;
% %         end
%
%         %%% get eye position at reach target
%         %%% and check is eye still in target window
%         [etim,ebuf]=EyeBuffer;
%         eye = ebuf(end,:);
%       %  set(hpEye,'xdata',eye(1),'ydata',eye(2)); drawnow; % plot eye data
%
%         eyeOk = INBOX(eye,dat.eyetargetpos,dat.eyetargetwin);
% %         if(NO_ISCAN) eyeOk=1; end
%
%         if (~eyeOk),             % allow to move eye outside window
%              done = 1;
%              dat.err = 22;
%              dat.errstring = 'Broke eye fixation';
% %             eframes = min(10,length(etim));
% %             ebuf = ebuf((end-eframes+1):end,:);
% %             etim = etim((end-eframes+1):end,:);
% %             if(etim(1)<etim0)
% %                 ebuf = ebuf(etim>=etim0,:);
% %                 etim = etim(etim>=etim0,:);
% %             end
% %             eyeOk = mean(INBOX(ebuf,dat.eyetargetpos,dat.eyetargetwin))>.4;
% %         else
% %             tdtJuice(5);
%         end
%
%     hW.drawnow;
%     end % while loop
% end
%
%
% % ---------------
%
% % %  Get eye to eye target
% % hEyeTrg.show = 1;
% % hW.drawnow;
% % done = 0;
% % tic;
% % while ~done & ~dat.err
% %     [pos,frame] = eyelatest;
% %
% %     if toc > dat.eyetargettimeout
% %         done = 1;
% %         dat.err = 21;
% %         dat.errstring = 'Timeout to eye target';
% %     end
% %
% %     if INBOX(pos,dat.eyetargetpos,dat.eyetargetwin)
% %        done = 1;
% %     end
% % end
% %
% % %  Hold in eye target
% % done = 0;
% % tic;
% % while ~done & ~dat.err
% %     if ~INBOX(pos,dat.eyetargetpos,dat.eyetargetwin)
% %        done = 1;
% %        dat.err = 22;
% %        dat.errstring = 'Broke hold at eye target';
% %     end
% %     if toc >= dat.eyetargethold
% %        done = 1;
% %     end
% % end
% % hEyeTrg.show = 0;
% % hW.drawnow;
%
% %  Get reward
% if (~err ), % Final reward during TUNING task
%     tdtJuice(Params.LARGE_REWARD);  %%%
%     dat.totalreward = dat.totalreward+Params.LARGE_REWARD;
% end

hW.drawnow;

hW.batchmode = 0;
dat.actionlog = hW.actionlog;

hL.active = 0;

EyeStop;

% Pause at end of trials
if(dat.err & dat.err~=1)
    pause((Params.INTER_TRIAL_DELAY + Params.ERR_PENALTY)/1000);
else
    pause(Params.INTER_TRIAL_DELAY/1000);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% SUPPORT FUNCTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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


lKin = hL.latest;
vel = lKin(Params.FINGER_MARKER,IPV);  %% mm/sec <- mm/msec ????
pos = lKin(Params.FINGER_MARKER,IP);        %% mm

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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% EYE LATEST %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [pos,frame] = eyelatest(new)

global Params
global eyeStruct

if(nargin<1) new=0; end
if(isempty(eyeStruct.started)) started=0; end

[pos, frame] = EyeUpdate; % Get Eye Data


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% INBOX %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function in = INBOX(pos,boxpos,win)

if (length(win) == 1),
    in = sqrt( (pos(:,1)-boxpos(1)).^2 + (pos(:,2)-boxpos(2)).^2 ) < win;
else
    in = abs(pos(:,1)-boxpos(:,1)) < win(1) & abs(pos(:,2)-boxpos(:,2)) < win(2);
end




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EOF
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
