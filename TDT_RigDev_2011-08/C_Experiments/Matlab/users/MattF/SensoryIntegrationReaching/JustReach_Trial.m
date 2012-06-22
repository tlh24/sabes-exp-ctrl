function dat = JustReach_Trial(dat)
%
%  MF Oct., 2007.
%

%global ORIGIN BUFFERTIME FRAMERATE
global Params
global hEyeTrg hStartTrg hRightHandArrowField hReachTrg hEye
global hL hW NO_ISCAN hFng

DisplayObjectGroupsInclude;

%%  - - - - - - -  SETUP  - - - - - - - - -

hW.StartBatchDraw;

%%% FEEDBACK
hFng.SetColor( dat.visFB.RGB.*dat.visFB.bright);%[1 1 1] * dat.feedbackfngbright;
hFng.SetScale( dat.visFB.rad);%dat.feedbackfngrad;
hFng.SetFillFlag( 1);
hFng.SetZ( 0.0);
hFng.Hide;

% %%% START TARGET
% hStartTrg.SetXY( dat.starttargetpos);
% hStartTrg.SetColor( dat.starttargetrgb * dat.starttargetbright);
% hStartTrg.SetScale( dat.starttargetrad);
% hStartTrg.SetFillFlag(1);
% hStartTrg.SetZ(.5);
% hStartTrg.Hide;

%%% REACH TARGET
hReachTrg.SetXY( dat.reachtargetpos);
hReachTrg.SetColor( dat.reachtargetrgb * dat.reachtargetbright);
hReachTrg.SetScale( dat.reachtargetrad);
hReachTrg.SetFillFlag(1);
hReachTrg.SetZ( 0);
hReachTrg.Hide;

% %%% EYE TARGET
% hEyeTrg.SetXY(dat.eyetargetpos);
% hEyeTrg.SetColor( dat.eyetargetrgb .* dat.eyetargetbright);
% hEyeTrg.SetScale(dat.eyetargetrad);
% hEyeTrg.SetFillFlag(1);
% hEyeTrg.SetZ( 1);
% hEyeTrg.Hide;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hW.FinishBatchDraw;


dat.err = 0;
dat.finalreward = 0; % Set final reward to zero
dat.totalreward = 0;

dat.trialtime = clock; % Start Trial Time

dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Start TimeSyncGetTimeMs];

%-------------------

dat.starttargetwin =  Params.START_TARGET_WIN;
dat.starttargetrad =  Params.START_TARGET_RAD;

dat.starttargetshow     = Params.START_TARGET_SHOW;

%%%  TEMPORARY WHILE LEARNING
%%dat.starttargetfeedback = 0; %Params.START_TARGET_FEEDBACK;


dat.starttargetflashbright = Params.START_TARGET_FLASH_BRIGHT;
dat.starttargethold = Params.START_TARGET_HOLD;

ExperimentTimingUpdate; % update time coeffs on servers

err = 0;

%%  -------------------  END SETUP  ---------------------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% for plsi = 1:Params.TRIAL_TYPE_TONE(1).NPULSES
%   tic;
%   ToneStart(Params.TRIAL_TYPE_TONE(1).FREQ, Params.TRIAL_TYPE_TONE(1).PULSEDUR);
% 
%   if plsi<Params.TRIAL_TYPE_TONE(1).NPULSES
%     while toc<(Params.TRIAL_TYPE_TONE(1).PULSEDUR + Params.TRIAL_TYPE_TONE(1).IPI)
%     end
%   end
% end

% %%  - - - - -  PHASE 1  - - - - - - -
% %%%  Acquisition of Unseen Start Target
% hW.ShowGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Show);
% pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
% initialLoc = pos; initialLocWin = 5; movestartedflag = 0; movestartedtime = inf;
% [dummy,initialDist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
% done=0; err = 0; dat.errstring = '';
% gotArm = 0;
% tic;
% while ~done
%   [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
%   pos = handxy(end,:);
%   speed = norm(handvel);
%   %  Length and direction of each arrow in field is proportional
%   %  to difference vector, (tgtLoc - handLoc).
%   [cdang,cddist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
%   asize = Params.arrowFieldLength(cddist);
% 
%   hW.StartBatchDraw;
%   invokeMultiVisObjects(hRightHandArrowField,'SetAngle',cdang.*180/pi);%,'SetScale',asize, ...
%   %     'SetColor',dat.righthandarrowfieldrgb*feval(dat.righthandarrowfieldbrightnessfunc,asize));
%   invokeMultiVisObjects(hRightHandArrowField,'SetScale',asize);
%   invokeMultiVisObjects(hRightHandArrowField,'SetColor',dat.righthandarrowfieldrgb*feval(dat.righthandarrowfieldbrightnessfunc,asize));
%   hW.FinishBatchDraw;
% 
%   if (dat.maxmovetimetostarttarget < inf ) & ~movestartedflag & ~TrialInBox(pos,initialLoc,initialLocWin)
%     %  Once he's moved a small distance away from his initial location,
%     %  we start counting time.  He has a max time to get to the start
%     %  target location.
%     movestartedflag = 1;
%     movestartedtime = toc;
%   end
% 
%   %  Check for acquisition of start target
%   posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
%   speedOk = (speed <= dat.starttargetvelcrit);
%   if posOk & hRightHandArrowField(1).GetShowFlag
%     hW.HideGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Hide);
%   elseif ~posOk
%     hW.ShowGroup(VisArrowFieldGroup);
%   end
% 
%   if (posOk & speedOk),
%     if (~gotArm),
%       gotArm = 1;
%       starthold = toc;
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Acquired TimeSyncGetTimeMs];
%     elseif (toc>(starthold+dat.starttargethold))
%       done = 1;   % Reach to start target OK
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Held TimeSyncGetTimeMs];
%     end
%     if hRightHandArrowField(1).GetShowFlag
%       hW.HideGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Hide);
%     end
% 
%   end
% 
%   if gotArm & ~(posOk & speedOk)  %  Once target is acquired properly, it must remain acquired
%     done = 1;
%     err = 800;
%     dat.err = err;
%     dat.errstring = 'Start Target Not Held';
%     dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
%   end
% 
%   if ~(posOk & speedOk) & (toc >= Params.REACH_START_TARGET_TIMEOUT),
%     err            = 1;
%     dat.err        = err;
%     dat.errstring  = 'Timeout at Start Position';
%     done           = 1;
%     dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
%   elseif (toc - movestartedtime) > dat.maxmovetimetostarttarget
%     err = 5;
%     dat.err = err;
%     dat.errstring = 'Too slow to reach Start Target';
%     done = 1;
%     dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
%   end
% end
% hW.HideGroup(VisArrowFieldGroup);
% %%  -----------------  END PHASE 1  ----------------
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% 
% %%  - - - - - -  PHASE 2  - - - - - - - - - - - - - -
% %%%  Hold hand at Start Target, fixate Eye Target and hold
% 
% if(~err)
%   % Show eye target
%   hEyeTrg.Show(Params.EventCodes.EyeTarget_Show);
% end
% 
% done=0;
% err = 0;
% target_time=0;
% loopct = 0;
% gotEye = 0;
% 
% tic;
% while (~done & ~err),
% 
%   [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
%   pos = handxy(end,:);
%   speed = norm(handvel);
% 
%   % Update GUI every N loops
%   loopct = loopct + 1; % counter to update hand data plot
%   %%     if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); FinishBatchDraw; end
% 
%   %    Check if hand is still in start window
%   posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
%   speedOk = (speed <= dat.starttargetvelcrit);
%   if (~(posOk & speedOk)),
%     err            =  3;
%     dat.err        = err;
%     dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
%     hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
%     dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
%     done           = 1;
%   end
% 
%   % check for eye target acquisition
%   if (~err)
% 
%     [EyePos,EyeVel,EyeT] = TrialGetEye(hEye,10);
% 
%     % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
% 
%     eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
%     if(NO_ISCAN) eyeOk=1; end
% 
%     if (~eyeOk)
%       gotEye = 0;
%     end
%     if (eyeOk), % Eye acquisition accomplished
%       if (~gotEye)
%         time = toc;
%         gotEye = 1;
%         dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Acquired TimeSyncGetTimeMs];
%       elseif (gotEye & (toc >=(time+dat.eyetargethold)))
%         done = 1;
%         EyeFixPt = mean(EyePos,2);
%         dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Held TimeSyncGetTimeMs];
%       end
%     end
% 
%     % Eye acquisition not accomplished
%     if  ~eyeOk & (toc > dat.eyetargettimeout)
%       err               = 21;
%       dat.err           = err;
%       dat.errstring     = 'Timeout to Eye Target';
%       hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
%       done              = 1;
%     end
%   end
% 
% end
% if ~err
%   dat.eyebufferatfixation = EyePos;
%   dat.eyebuffertimeatfixation = EyeT;
% end
% %%  ------------------  END PHASE 2  --------------------
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% %%  - - - - - - - -  PHASE 3  - - - - - - - - - - -
% %%%  Start Target and Eye Target have been acquired and held without FB.
% %%%  Tone signals next phase. Continue holding.  FB on for FB+ trials.
% %%%  Must maintain hand and eye positions.
% 
% if ~err
%   done = 0;
%   tic;
%   ToneStart(Params.EventTone(1).FREQ, Params.EventTone(1).DUR);
%   dat.matlabeventlog(end+1,:) = [Params.EventCodes.Tone_On TimeSyncGetTimeMs];
%   while ~err & ~done
% 
%     [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
%     pos = handxy(end,:);
%     speed = norm(handvel);
% 
%     posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
%     speedOk = (speed <= dat.starttargetvelcrit);
%     if ~(posOk & speedOk)
%       done = 1;
%       err = 900;
%       dat.err = err;
%       dat.errstring = 'Released Start Target During FB Delay';
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
%     else
%       if dat.starttargetfeedback
%         hW.StartBatchDraw;
%         hFng.SetXY(pos);
%         hFng.Show(Params.EventCodes.VisFB_Show);
%         hW.FinishBatchDraw;
%       end
%     end
% 
%     if (~err)
%       EyePos = TrialGetEye(hEye,10);
% 
%       % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
%       eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
%       if(NO_ISCAN) eyeOk=1; end
%       if (~eyeOk)
%         err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
%         dat.err           = err;
%         dat.errstring     = 'Eye Fixation broken during FB delay';
%         hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
%         dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
%         done              = 1;
%       end
%     end
% 
%     if ~err & (toc > dat.starttargetfbholddur)
%       done = 1;
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Held TimeSyncGetTimeMs];
%     end
%   end
% end
% %%  ------------------  END PHASE 3  -----------------------------
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 

%%  - - - - - - - - - -  PHASE 4  - - - - - - - - - - -
%%%                 REACH, INSTRUCTED DELAY PHASE
%%%  Reach Target shown.  Wait at Start Target during Instructed Delay.  Maintain hand position and
%%%  Eye Fixation.  GO Tone On following delay.

%if (~err)
  tic;
  %if rand(1) <= Params.P_NONZERO_REACH_DELAY %&& dat.test==0
%     dat.reachdelay = Params.REACH_DELAY_MIN + ...  %% 3 - Between max and min
%       rand*(Params.REACH_DELAY_MAX-Params.REACH_DELAY_MIN);
%   else
    dat.reachdelay = 0;
%   end
  fprintf(' Delay=%.2f ',dat.reachdelay);
[handxy,vel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
  pos = handxy(end,:);
  hW.StartBatchDraw;
  hReachTrg.Show(Params.EventCodes.ReachTarget_Show);
  
  feval(dat.fngfeedbackfunc, pos, 0, 1);
  hW.FinishBatchDraw(Params.EventCodes.VisFB_Move);

%   while (~err & (toc < dat.reachdelay)), %%  This is now a hold during target presentation
%     %loopct = loopct+1;
% 
%     %%% get hand position at start target
%     [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
%     pos = handxy(end,:);
%     speed = norm(handvel);
% 
%     posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
%     speedOk = (speed <= dat.starttargetvelcrit);
%     if ~(posOk & speedOk)
%       err            = 2;
%       dat.err        = err;
%       dat.errstring  = 'Broke Hold at Start Position During Reach Delay';
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
%     end
% 
% %     EyePos = TrialGetEye(hEye,10);
% %     % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
% %     eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
% %     if(NO_ISCAN) eyeOk=1; end
% %     if (~eyeOk)
% %       err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
% %       dat.err           = err;
% %       dat.errstring     = 'Eye Fixation broken during Reach delay';
% %       dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
% %     end
% 
%     feval(dat.fngfeedbackfunc, pos, 0, 2);
%   end
% end
% if err
%   hReachTrg.Hide(Params.EventCodes.ReachTarget_Hide);
%   hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
% end
% %%  -----------------  END PHASE 4  ----------------
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 


%%  - - - - - - - - PHASE 5 - - - - - - - - - - - -
%%%             REACHING PHASE
%%%  Begin reach to Reach Target.  Maintain Fixation for some proportion
%%%  of the reach.  Continue reach with free-viewing.
%%%

ReachTrajStartIdx = hL.GetDataIndexLatest;

if (~err)
  tic;
  dat.startpt = TrialGetKin(hL,Params.FINGER_MARKER,1);  % position of hand before go tone
  ToneStart(Params.GO_TONE_FREQ, Params.GO_TONE_TIME);   % GO signal

  toneOn=1;
  done = 0; target_time=0;
  gotArm=0;
  PRE_REACH_HOLD = Params.REACH_TARGET_TIMEOUT;
  reach_vec = dat.reachtargetpos-dat.startpt;
end

loopct = 0;
while (~done & ~err),
  loopct = loopct+1;
  tim=toc;

  [handxy,vel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
  pos = handxy(end,:);

%   dist_pct = (pos - dat.startpt)*reach_vec' / (reach_vec*reach_vec');
%   projLength = norm(dist_pct.*reach_vec);
% 
%   if ~hFng.GetShowFlag & (dist_pct >= dat.fbonreachproportion)
%     hW.StartBatchDraw;
%     feval(dat.fngfeedbackfunc, pos, 0, 1);
%     dat.fbpt = pos;
%     hW.FinishBatchDraw(Params.EventCodes.VisFB_Show);
%   end
%   %     if hFng.GetShowFlag & (dist_pct >= dat.fboffreachproportion) & (dist_pct < dat.fbonreachproportion)
%   if hFng.GetShowFlag & (projLength >= dat.fboffreachdistance) & (dist_pct < dat.fbonreachproportion)
%     hW.StartBatchDraw;
%     feval(dat.fngfeedbackfunc, pos, 0, 0);
%     dat.fboffpt = pos;
%     hW.FinishBatchDraw(Params.EventCodes.VisFB_Hide);
%   end
% 
%   %  If he hasn't reached far enough yet, check for Eye Fixation
%   if projLength <= Params.EyeFixationReachDistance
%     EyePos = TrialGetEye(hEye,10);
%     % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
%     eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
%     if(NO_ISCAN) eyeOk=1; end
%     if (~eyeOk)
%       err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
%       dat.err           = err;
%       dat.errstring     = 'Eye Fixation broken during Reach';
%       dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
%     end
%   else
%     hEyeTrg.Hide;
%   end

  posOk = TrialInBox(pos,dat.reachtargetpos,dat.reachtargetwin);
  velOk = (norm(vel)<dat.donecritspeed);%(vel <= 2);  %% MM/SEC

  feval(dat.fngfeedbackfunc, pos, 0, 2);


  if posOk & velOk %(dist_pct>0.5) & (norm(vel)<dat.donecritspeed) %posOk
    done = 1;
    dat.endpt = pos;
    dat.endptspeed = norm(vel);
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Acquired TimeSyncGetTimeMs];
  end


  % check for TIMEOUT
  if(~done & tim>Params.REACH_TARGET_TIMEOUT_2),
    err           = 4;
    dat.err       = err;
    dat.errstring = 'Timeout to Reach Target';
    done          = 1;
    %         hW.StartBatchDraw;
    %         hReachTrg.Hide;
    %         feval(dat.fngfeedbackfunc, pos, 0, 0);
    %         hW.FinishBatchDraw;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Timeout TimeSyncGetTimeMs];
  end

end
if err
  hW.StartBatchDraw;
  hReachTrg.Hide;
  hEyeTrg.Hide;
  feval(dat.fngfeedbackfunc, pos, 0, 0);
  hW.FinishBatchDraw;
end
%%  -------------------  END PHASE 5  ------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%  - - - - - - - - -  PHASE 6  - - - - - - - - - - -
%%%  Hold in Reach Target

if (~err),
  tic;
  while ((toc < Params.REACH_TARGET_HOLD) & ~err),
    %% Arm Position
    pos = TrialGetKin(hL,Params.FINGER_MARKER,1); %latest;
    feval(dat.fngfeedbackfunc, pos, 0, 2);
    %    posOk = TrialInBox(pos,dat.endpt,dat.reachtargetrad);
    posOk = TrialInBox(pos,dat.reachtargetpos,dat.reachtargetrad);
    if (~posOk)
      err            = 10;
      dat.err        = err;
      dat.errstring  = 'Missed Hold at Reach Target';
      hReachTrg.Hide;
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Unacquired TimeSyncGetTimeMs];
    end
  end
end
ReachTrajStopIdx = hL.GetDataIndexLatest;
if ~err
  dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Held TimeSyncGetTimeMs];
end
% Switch off all targets and FB
hStartTrg.Hide;
hReachTrg.Hide;
hFng.Hide;
%%  -------------------  END PHASE 6  ---------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%  - - - - - - - - -  GET BUFFERED DATA  - - - - - - - - - - -


ReachTrajN_Points = ReachTrajStopIdx - ReachTrajStartIdx + 1;

ExperimentTimingUpdate;  %  update time coeffs on servers

% Get trajectory from Liberty Buffer and error check
for i=1:Params.N_MARKERS
  [TrackerTime TrackerXYZ] = invoke(hL, 'GetSensorBuffered', i, ReachTrajStartIdx, ReachTrajN_Points );
  dat.traj(i, :, :) = TrackerXYZ(1:2,:);
end
dat.time = TrackerTime;

dat.bufferstarttime = dat.time(1);
dat.bufferstoptime  = dat.time(end);


%%  - - - - - - - - -  FINALIZE TRIAL  - - - - - - - -

% Save some more stuff
dat.err = err;

if (~err ), % Final reward
  JuiceStart(Params.SMALL_REWARD);  %%%
  dat.totalreward = dat.totalreward+Params.LARGE_REWARD;
end

% Switch off all targets and FB
hW.HideGroup(0);

% Pause at end of trials
if(dat.err & dat.err~=1)
  pause((dat.intertrialdelay + Params.ERR_PENALTY)/1000);
else
  pause(dat.intertrialdelay/1000);
end


return;





