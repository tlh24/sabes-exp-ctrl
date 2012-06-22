%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% REACH TRIAL FUNCTION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function dat = EyeFixation_ReachTrial( dat )

global ORIGIN BUFFERTIME FRAMERATE 
global Params V  E eyepos reachstart
global hStartTrg  
global hReachTrg 
global hEyeFix 
global hFng
global hL hW hMou

%%%%% Debug flags
DEBUG     = 0; 
NO_ISCAN  = 1 % If =1 eye position check always true (= bypass check)

HAND_FRAMES = 150; % number of frames before updating hand location 
                   % in the plot   

%%%%% Activate Liberty
hL.active  = 1; 

%%%%% Setup Vis Objects counting
hW.batchmode = 1;

%%% FEEDBACK DISK
hFng.color  = [1 1 1] * Params.FEEDBACK_FNG_BRIGHT;
hFng.scale  = Params.FEEDBACK_FNG_RAD;
hFng.fill   = 1;
hFng.z      = 0.7;
hFng.show   = 0;


%%% START TARGETS 
% Start target initial parameters settings 
% (in this way we can change them from keyboard during task)
dat.starttargetwin      = Params.START_TARGET_WIN;
dat.starttargetrad      = Params.START_TARGET_RAD;
dat.starttargetshow     = Params.START_TARGET_SHOW;  

hStartTrg.pos    = dat.starttargetpos;
hStartTrg.color  = [0 1 0] * Params.START_TARGET_BRIGHT;
hStartTrg.scale  = dat.starttargetrad;
hStartTrg.fill   = 1;
hStartTrg.z      = 0.7;
hStartTrg.show   = 0;


%%% EYE FIXATION TARGET
hEyeFix.pos    = dat.eyefixpos;
hEyeFix.color  = [1 0 0] * Params.EYE_FIX_RAD;
hEyeFix.scale  = Params.EYE_FIX_RAD;
hEyeFix.fill   = 1;
hEyeFix.z      = 1;
hEyeFix.show   = 0;


%%% REACH TARGET
hReachTrg.pos    = dat.reachtargetpos; 
hReachTrg.color  = [0 1 0] * Params.REACH_TARGET_BRIGHT; 
hReachTrg.scale  = Params.REACH_TARGET_RAD;
hReachTrg.fill   = 1;  
hReachTrg.z      = 0;
hReachTrg.show   = 0; 

hW.drawnow;          %%% Chiara 03-30-05, the VisServer code will log     
invoke(hW,'clrlog'); 
 
dat.errstring   = '';    % Set to nulll error string                      
dat.trialtime   = clock; % Start Trial Time

%%% Initialize Eye Data Acquisition
EyeStart;

%%%%%%%%%%%%%% STEP 1 - Get to Start Position %%%%%%%%%%
%% Hear the Start Tone, Hand Reach and Hold Start Target
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

err = 0;                          % Set start error to zero

% Start Tone
tdtTone(Params.START_TONE_FREQ);  % Start tone on
pause(Params.START_TONE_TIME);    % Time for which the start tone is on
tdtTone(0);                       % Start tone off

% Show start target and feedback if enabled
if (dat.starttargetshow) 
    hStartTrg.show    = 1;  
end 
if (dat.feedback),
    pos = latest(1);
    feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 1);
end
hW.drawnow;

%%% Acquisition of Start Target. 
done=0; 
gotArm = 0;
tic;
while (~done),
    pos = latest(1);
    % check for acquisition of start target
    posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);
    % Show feedback if enabled
    if(dat.feedback),
        pos = latest(1);
        feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
    end
    hW.drawnow;
    if (~posOk)
        gotArm = 0;
    end
    % Reach to start target OK
    if (posOk),
        if (~gotArm)
            time = toc;
            gotArm = 1;
        elseif ((toc > (time + Params.START_TARGET_HOLD)))
            done = 1;
        end
    end
    if ((toc + Params.START_TARGET_HOLD )>= Params.START_TARGET_TIMEOUT),
        err           = 1;
        dat.err       = err;
        dat.errstring = 'Timeout at Start Position';
        done          = 1;   
    end
end



% if start target not acquired, turn off target and feedback, pause, return
if (err ~=0),
    hStartTrg.show  = 0;
    hFng.show       = 0;
    hW.drawnow;
    feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 0);
    pause(Params.ERROR_PENALTY);
    return
else, % if Start Target acquired, give reward.
    tdtJuice(Params.SMALL_REWARD);
end

%% EYE FEEDBACK PLOT
persistent hpTarg hpEye hpPos armTarg
if(isempty(hpTarg) | isempty(hpEye) | ~ishandle(hpTarg) | ~ishandle(hpEye) | ~ishandle(hpPos))
    %%% fprintf(1,'Plot first time ')
    figure(2); clf; hold on;
    plot(V(:,1),V(:,2),'bo'); plot(E(:,1),E(:,2),'ro');
    a = [0:20]'*2*pi/20;
    x = dat.eyefixpos(1)+Params.EYE_FIX_RAD*cos(a);
    y = dat.eyefixpos(2)+Params.EYE_FIX_RAD*sin(a);
    hpTarg = fill(x,y,'r');
    armTarg = plot(dat.reachtargetpos(1),dat.reachtargetpos(2),'bo','MarkerFaceColor','b');
    eye = eyelatest(1); hpEye = plot(eye(1),eye(2),'r*');
    pos = latest(1);  hpPos = plot(pos(1),pos(2),'g*');    
    plot(dat.starttargetpos(1),dat.starttargetpos(2),'bo')
    plot(dat.reachtargetpos(1),dat.reachtargetpos(2),'bo')    
    figure(2); axis([-150 150 0 300]); axis ij;
    drawnow;
else
    %%% fprintf(1,'Plot other times ')
    figure(2);
    a = [0:20]'*2*pi/20;
    x = dat.eyefixpos(1)+Params.EYE_FIX_RAD*cos(a);
    y = dat.eyefixpos(2)+Params.EYE_FIX_RAD*sin(a);
    eye = eyelatest(1); set(hpEye,'xdata',eye(1),'ydata',eye(2));
    pos = latest(1);    set(hpPos,'xdata',pos(1),'ydata',pos(2));
    set(armTarg,'xdata',dat.reachtargetpos(1),'ydata',dat.reachtargetpos(2));
    plot(dat.starttargetpos(1),dat.starttargetpos(2),'bo')
    plot(dat.reachtargetpos(1),dat.reachtargetpos(2),'bo')  
    plot(E(:,1),E(:,2),'ro');
    set(hpTarg,'xdata',x,'ydata',y);   
    drawnow;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%% 2: Acquire eye target for the first time
%%%%%%%%% WHILE HOLDING AT START TARGET!
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 %% Show eye target
hEyeFix.show   = 1;
hW.drawnow;
gotEye = 0;
done=0; target_time=0;
loopct = 0;
[etim,ebuf]=EyeBuffer; etim0=etim(end);
tic;
while (~done & ~err),

    loopct = loopct + 1; % to update hand data plot

    %%% check if hand is still in start window
    pos = latest(1);

    if(dat.feedback), % Show feedback if enabled
        feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
    end
    if(~rem(loopct,HAND_FRAMES))   % Update GUI every N (=4?) loops
        set(hpPos,'xdata',pos(1),'ydata',pos(2)); drawnow; % plot hand data
    end

    posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);
    if (~posOk),
        err            =  2;
        dat.err        = err;
        dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
        hStartTrg.show = 0;
        hEyeFix.show   = 0;
        done           = 1;
    end

    %%% check for eye target acquisition
    if (~err)
        [eye,eyeframe] = eyelatest(0);

        if(~isempty(eye))
        set(hpEye,'xdata',eye(1),'ydata',eye(2)); drawnow; % plot eye data
        end

        % check to see if got into eye window
        [etim,ebuf]=EyeBuffer;
        eframes = min(5,length(etim));
        ebuf = ebuf((end-eframes+1):end,:);
        etim = etim((end-eframes+1):end,:);
        if(etim(1)<etim0)
            ebuf = ebuf(etim>=etim0,:);
            etim = etim(etim>=etim0,:);
        end
        eyeOk = sum(INBOX(ebuf,dat.eyefixpos,Params.EYE_FIX_WIN))>4;
        if(NO_ISCAN) eyeOk=1; end

        if (~eyeOk)
            gotEye = 0;
        end

        if (eyeOk), % Eye acquisition accomplished
            if (~gotEye)
                time = toc;
                gotEye = 1;
            elseif (gotEye&(toc >=(time+Params.EYE_FIX_HOLD)))
                done = 1;
                EyeFixPt = mean(ebuf);
            end
        end

        % Eye acquisition not accomplished
        if((toc + Params.EYE_FIX_HOLD)>Params.EYE_FIX_TIMEOUT),
            err               = 3;
            dat.err           = err;
            dat.errstring     = 'Timeout to Fixate Eye Target';
            hEyeFix.show      = 0;
            hStartTrg.show    = 0;
            done              = 1;
        end
    end
    hW.drawnow;
end

if (~err), % If aquired eye target give medium reward
    tdtJuice(Params.EYE_FIX_REWARD);
    dat.totalreward = dat.totalreward+Params.EYE_FIX_REWARD;
end

%%% If eye fixation point acquired, try to hold during target presentation
eyeOk = 0; posOk = 0;

% START Liberty buffer during delay
%%% 4/11/06 Try start buffer here
%%%%%%% ERROR CHECK BUFFER COMMANDS
nE0 = hL.err;
invoke(hL,'startBuffer');
nE1 = hL.err;
if(nE1>nE0)
    for i=(nE0+1):nE1, 
        fprintf(1,'%d: %s',i,hL.getErr(i))
    end
end
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%hold fixation with hand at start target while target comes up
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[etim,ebuf]=EyeBuffer; etim0=etim(end);
tic;
loopct = 0;
TrgON = 0;
trgon = rand;

if (trgon>0.5), trgon = trgon - 0.5; end
trghold = rand*0.2;
if (trghold>0.5),
    trghold = trghold/2;
elseif (trghold<0.05),
    trghold = trghold + 0.05;
end

%%% This will make reach target turn on and off at the same time (not show)
% trghold = 0;
%%%

if (~err) 
    while ((toc < Params.FIXATION_HOLD & ~err)), %%  Hold during target presentation
        loopct = loopct + 1; % counter to update hand data plots

        pos = latest(1);
        if(dat.feedback), % Show feedback if enabled
            feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
        end
        
        if ((toc>trgon)& (~TrgON))
            hReachTrg.show = 1;
            TrgON = 1;
%         elseif (toc>(trgon+trghold))
%             hReachTrg.show = 0;
        end

        %%% get eye position
        [etim,ebuf]=EyeBuffer;
        eye = ebuf(end,:);
        if(~isempty(eye))
        set(hpEye,'xdata',eye(1),'ydata',eye(2)); drawnow; % plot eye data
        end

        eyeOk = mean(INBOX(eye,EyeFixPt,Params.EYE_FIX_WIN./2))>.4;
        if(NO_ISCAN) eyeOk=1; end

        if (~eyeOk),             % allow to move eye outside window
            eframes = min(10,length(etim));
            ebuf = ebuf((end-eframes+1):end,:);
            etim = etim((end-eframes+1):end,:);
            if(etim(1)<etim0)
                ebuf = ebuf(etim>=etim0,:);
                etim = etim(etim>=etim0,:);
            end            
            eyeOk = mean(INBOX(ebuf,EyeFixPt,Params.EYE_FIX_WIN./2))>.4;
        end
        
        if (~eyeOk &  (size(ebuf,1)>5)  )
            err            = 4;
            dat.err        = err;
            dat.errstring  = 'Missed Hold at Eye Fixation Point during Delay';
            hStartTrg.show = 0;
            hEyeFix.show  = 0;
             hReachTrg.show = 0;
             hFng.show=0;
             hW.drawnow;
             %%%%%%%
             pause(5);
             %%%%%%%
%         else
% %             give tiny rewards for keeping fixation
%             tdtJuice(0.5*Params.SMALL_REWARD); 
%             pause(0.1)
        end


        %%% get hand position at start target
        %%% and check if hand still in start window
        pos = latest(1);
        if(dat.feedback), % Show feedback if enabled
            feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
        end
        posOk = INBOX(pos,dat.starttargetpos,dat.starttargetwin);

        if(~rem(loopct,HAND_FRAMES))   % Update GUI every N (=4?) loops
            set(hpPos,'xdata',pos(1),'ydata',pos(2)); drawnow; % plot hand data
        end

        if (~posOk),
            err            = 5;
            dat.err        = err;
            dat.errstring  = 'Broke Hold at Start Position While Holding Eye Fixation';
            hStartTrg.show = 0;
            hEyeFix.show  = 0;
            hReachTrg.show = 0;
        end
        hW.drawnow;
    end
end

if (~err), % If hold at Start Target is OK, give reward
    tdtJuice(Params.LARGE_REWARD);
end



%%%%%%% Liberty stop buffer and errors check
nE0 = hL.err;
invoke(hL,'stopBuffer');
nE1 = hL.err;
if(nE1>nE0)
    for i=(nE0+1):nE1,
        fprintf(1,'%d: %s',i,hL.getErr(i))
    end
end
%%%%


% Switch off all targets and FB
hReachTrg.show  = 0;
hStartTrg.show  = 0;
hFng.show       = 0;
hEyeFix.show    = 0;
hW.drawnow;

%%% move left arm back to side here

% Get ActionLog
hW.batchmode    = 0;
dat.actionlog   = hW.actionlog;

% Save some more stuff
dat.err = err;


% Get trajectory from Liberty Buffer and error check
for i=1:Params.N_MARKERS
    nE0 = hL.err;
    traj     = invoke(hL,'getBuffer',i);
    nE1 = hL.err;
    if(nE1>nE0)
        for i=(nE0+1):nE1,
            fprintf(1,'%d: %s',i,hL.getErr(i))
        end
    end
    dat.traj = [traj(:,4,i), traj(:,3,i)];
    sync = traj(:,8:9,1);
end
dat.time = [0:(size(dat.traj,1)-1)]' / FRAMERATE;

% Switch off Liberty
hL.active = 0;

% Switch off Eye buffer
EyeStop;

% Pause at end of trials
% if(dat.err & dat.err~=1) pause(Params.ERROR_PENALTY/1000);
if(dat.err & dat.err~=1) pause(Params.ERROR_PENALTY);
else                     pause(Params.INTER_TRIAL_DELAY/1000);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% SUPPORT FUNCTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%% HAND LATEST %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [pos,vel,maxvel,velpct] = latest(new)

global hL Params
persistent velmax started

MINVELMAX = 20; % Minimum of peak velocty (mm/sec)
IP  = [4,3];    % latest index for position
IPV = [10,9];   % latest index for velocity

if(nargin<1) new=0; end 
if(isempty(started)) started=0; end

pos = hL.latest;
vel = pos(1,IPV);  %% mm/sec 
pos = pos(1,IP);   %% mm 
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

maxvel = velmax;

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
% EOF
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
