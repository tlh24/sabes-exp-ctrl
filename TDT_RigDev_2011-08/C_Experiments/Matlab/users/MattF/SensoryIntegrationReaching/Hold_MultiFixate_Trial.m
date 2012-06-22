function dat = Hold_MultiFixate_Trial(dat)
%
%  MF Sept., 2008.
%

%global ORIGIN BUFFERTIME FRAMERATE
global Params
global hEyeTrg hStartTrg hRightHandArrowField hReachTrg hEye
global hL hW NO_ISCAN hFng hFngRing

DisplayObjectGroupsInclude;

%%  - - - - - - -  SETUP  - - - - - - - - -

hW.StartBatchDraw;

%%% FEEDBACK
updateVisFBParams(hFng,dat.visFB);
hFng.SetZ( 0.0);
hFng.Hide;
updateVisFBParams(hFngRing,dat.visFB);
hFngRing.SetColor([0 0 0]);
hFngRing.SetFillFlag(0);
hFngRing.Hide;


%%% START TARGET
hStartTrg.SetXY( dat.starttargetpos);
hStartTrg.SetColor( dat.starttargetrgb * dat.starttargetbright);
hStartTrg.SetScale( dat.starttargetrad);
hStartTrg.SetFillFlag(1);
hStartTrg.SetZ(.5);
hStartTrg.Hide;

%%% REACH TARGET
%hReachTrg.SetXY( dat.reachtargetpos);
%hReachTrg.SetColor( dat.reachtargetrgb * dat.reachtargetbright);
%hReachTrg.SetScale( dat.reachtargetrad);
%hReachTrg.SetFillFlag(1);
%hReachTrg.SetZ( 1);
hReachTrg.Hide;

%%% EYE TARGET
hEyeTrg.SetXY(dat.eyetargetpos(1,:));
hEyeTrg.SetColor( dat.eyetargetrgb .* dat.eyetargetbright);
hEyeTrg.SetScale(dat.eyetargetrad);
hEyeTrg.SetFillFlag(1);
hEyeTrg.SetZ( 0.25);
hEyeTrg.Hide;

if dat.feedbackfngrad > dat.eyetargetrad
  hEyeTrg.SetZ( 0.0);
  hFng.SetZ( 0.25);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hW.FinishBatchDraw;


dat.err = 0;
dat.finalreward = 0; % Set final reward to zero
dat.totalreward = 0;

dat.trialtime = clock; % Start Trial Time

dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Start TimeSyncGetTimeMs];

%-------------------

% % dat.starttargetwin =  Params.START_TARGET_WIN;
% % dat.starttargetwin2 =  Params.START_TARGET_WIN_2;
dat.starttargetrad =  Params.START_TARGET_RAD;

dat.starttargetshow     = Params.START_TARGET_SHOW;

%%%  TEMPORARY WHILE LEARNING
%%dat.starttargetfeedback = 0; %Params.START_TARGET_FEEDBACK;


dat.starttargetflashbright = Params.START_TARGET_FLASH_BRIGHT;
dat.starttargethold = Params.START_TARGET_HOLD;

ExperimentTimingUpdate; % update time coeffs on servers

%%  -------------------  END SETUP  ---------------------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for plsi = 1:Params.TRIAL_TYPE_TONE(dat.trialtype).NPULSES
  tic;
  ToneStart(Params.TRIAL_TYPE_TONE(dat.trialtype).FREQ, Params.TRIAL_TYPE_TONE(dat.trialtype).PULSEDUR);

  if plsi<Params.TRIAL_TYPE_TONE(dat.trialtype).NPULSES
    while toc<(Params.TRIAL_TYPE_TONE(dat.trialtype).PULSEDUR + Params.TRIAL_TYPE_TONE(dat.trialtype).IPI)
    end
  end
  %ToneStop;
end

handTrajStartIdx = hL.GetDataIndexLatest;
eyeTrajStartIdx = hEye.GetDataIndexLatest;

%%  - - - - -  PHASE 1  - - - - - - -
%%%  Acquisition of Unseen Hand-hold Target
Phase = 1;

% % if 0
% % hStartTrg.SetColor( [0 1 0]);
% % hStartTrg.SetScale( dat.starttargetwin);
% % hStartTrg.Show;
% % hFng.Hide;
% % end

hW.ShowGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Show + Phase);
pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
initialLoc = pos; initialLocWin = 5; movestartedflag = 0; movestartedtime = inf;
[dummy,initialDist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
done=0; err = 0; dat.errstring = '';
gotArm = 0;
tic;
while ~done
  [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
  pos = handxy(end,:);
  speed = norm(handvel);

  % %     if
  % %       feval(dat.fngfeedbackfunc, pos, dat.fbshift, 1);
  % %     end

  %  Length and direction of each arrow in field is proportional
  %  to difference vector, (tgtLoc - handLoc).
  [cdang,cddist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
  asize = Params.arrowFieldLength(cddist);

  hW.StartBatchDraw;
  invokeMultiVisObjects(hRightHandArrowField,'SetAngle',cdang.*180/pi);%,'SetScale',asize, ...
  %     'SetColor',dat.righthandarrowfieldrgb*feval(dat.righthandarrowfieldbrightnessfunc,asize));
  invokeMultiVisObjects(hRightHandArrowField,'SetScale',asize);
  invokeMultiVisObjects(hRightHandArrowField,'SetColor',dat.righthandarrowfieldrgb*feval(dat.righthandarrowfieldbrightnessfunc,asize));
  hW.FinishBatchDraw;

  if (dat.maxmovetimetostarttarget < inf ) & ~movestartedflag & ~TrialInBox(pos,initialLoc,initialLocWin)
    %  Once he's moved a small distance away from his initial location,
    %  we start counting time.  He has a max time to get to the start
    %  target location.
    movestartedflag = 1;
    movestartedtime = toc;
  end

  %  Check for acquisition of start target
  if gotArm
    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin2);
    % %         %%%%%%
    % %         hStartTrg.SetScale( dat.starttargetwin2);
    % %         %%%%%%
  else
    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
    % %         %%%%%%%%
    % %         hStartTrg.SetScale( dat.starttargetwin);
    % %         %%%%%%%%
  end
  speedOk = (speed <= dat.starttargetvelcrit);
  if posOk & hRightHandArrowField(1).GetShowFlag
    hW.HideGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Hide + Phase);
  elseif ~posOk
    hW.ShowGroup(VisArrowFieldGroup);
  end

  if (posOk & speedOk),
    if (~gotArm),
      gotArm = 1;
      starthold = toc;
      dat.startholdloc = pos;
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Acquired + Phase TimeSyncGetTimeMs];
    elseif (toc>(starthold+dat.starttargethold))
      done = 1;   % Reach to start target OK
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Held + Phase TimeSyncGetTimeMs];
    end
    if hRightHandArrowField(1).GetShowFlag
      hW.HideGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Hide + Phase);
    end

  end

  if gotArm & ~(posOk & speedOk)
    if 1
      gotArm = 0;  %  Allow him to reacquire if time has not run out.
    else
      %  Once target is acquired properly, it must remain acquired
      done = 1;
      err = 800;
      dat.err = err;
      dat.errstring = 'Start Target Not Held';
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired + Phase TimeSyncGetTimeMs];
    end
  end

  if ~(posOk & speedOk) & (toc >= Params.REACH_START_TARGET_TIMEOUT),
    err            = 1;
    dat.err        = err;
    dat.errstring  = 'Timeout at Start Position';
    done           = 1;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
  elseif (toc - movestartedtime) > dat.maxmovetimetostarttarget
    err = 5;
    dat.err = err;
    dat.errstring = 'Too slow to reach Start Target';
    done = 1;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
  end
end
hW.HideGroup(VisArrowFieldGroup);
%%  -----------------  END PHASE 1  ----------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%  - - - - - -  PHASE 2  - - - - - - - - - - - - - -
%%%  Hold hand at Start Target, fixate Eye Target and hold
Phase = 2;

if(~err)

  %if dat.enforceFixationFlag
  % Show eye target
  hEyeTrg.Show(Params.EventCodes.EyeTarget_Show + Phase);
  % else
  %  hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
  %end

  done=0;
  err = 0;
  target_time=0;
  loopct = 0;
  gotEye = 0;

  tic;
  while (~done & ~err),

    [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
    pos = handxy(end,:);
    speed = norm(handvel);

    % Update GUI every N loops
    loopct = loopct + 1; % counter to update hand data plot

    %    Check if hand is still in start window
    %    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin2);

    speedOk = (speed <= dat.starttargetvelcrit);
    if (~(posOk & speedOk)),
      err            =  3;
      dat.err        = err;
      dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
      hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired + Phase TimeSyncGetTimeMs];
      done           = 1;
    end

    % check for eye target acquisition
    if (~err)

      [EyePos,EyeVel,EyeT] = TrialGetEye(hEye,10);

      % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data

      eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
      if (NO_ISCAN) eyeOk=1; end

      if (~eyeOk)
        gotEye = 0;
      end
      if (eyeOk), % Eye acquisition accomplished
        if (~gotEye)
          time = toc;
          gotEye = 1;
          dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Acquired + Phase TimeSyncGetTimeMs];
        elseif (gotEye & (toc >=(time+dat.eyetargethold)))
          done = 1;
          EyeFixPt = mean(EyePos,2);
          dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Held + Phase TimeSyncGetTimeMs];
        end
      end

      % Eye acquisition not accomplished
      if  ~eyeOk & (toc > dat.eyetargettimeout(1))
        err               = 21;
        dat.err           = err;
        dat.errstring     = 'Timeout to Eye Target';
        hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
        dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
        done              = 1;
      end
    end

  end
end
if ~err
  dat.eyebufferatfixation = EyePos;
  dat.eyebuffertimeatfixation = EyeT;
end
%%  ------------------  END PHASE 2  --------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%  - - - - - - - -  PHASE 3  - - - - - - - - - - -
%%%  Start Target and Eye Target have been acquired and held without FB.
%%%  FB on for FB+ trials.
%%%  Must maintain hand position and fixate multiple eye targets in sequence, holding fixation briefly at each one.
Phase = 3;

if ~err
  gotEye = 1;

  eyetargi = 0;
  while ~err & (eyetargi<size(dat.eyetargetpos,1))
    eyetargi = eyetargi + 1;
    thiseyetargetpos = dat.eyetargetpos(eyetargi,:);
    hEyeTrg.SetXY(thiseyetargetpos);

    done = 0;
    tic;
    if gotEye, gotEyeTime = toc; end
    % ToneStart(Params.EventTone(1).FREQ, Params.EventTone(1).DUR);
    %  dat.matlabeventlog(end+1,:) = [Params.EventCodes.Tone_On + Phase TimeSyncGetTimeMs];
    while ~err & ~done

      [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
      pos = handxy(end,:);
      speed = norm(handvel);

      %    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
      posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin3);
      speedOk = (speed <= dat.starttargetvelcrit);
      if ~(posOk & speedOk)
        done = 1;
        err = 900;
        dat.err = err;
        dat.errstring = 'Released Start Target During FB Delay';
        dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired + Phase TimeSyncGetTimeMs];
      else
        if dat.starttargetfeedback
          hW.StartBatchDraw;
          hFng.SetXY(pos);
          if ~hFng.GetShowFlag  %  If it's not on, turn it on.
            hFng.Show(Params.EventCodes.VisFB_Show + Phase);
          end
          hW.FinishBatchDraw;
        end
      end

      if (~err)
        EyePos = TrialGetEye(hEye,10);

        % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
        %eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
        eyeOk = sum(TrialInBox(EyePos,thiseyetargetpos,dat.eyetargetwin))>4;
        if (NO_ISCAN) eyeOk=1; end

        if ~gotEye  %  Haven't acquired new eye target yet.
          if eyeOk
            gotEye = 1;
            gotEyeTime = toc;
          else
            if toc > dat.eyetargettimeout(2)
              err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Timeout;
              dat.err           = err;
              dat.errstring     = 'Timeout to Eye Target';
              hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
              dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
              done              = 1;
            end
          end
        else
          if (~eyeOk)
            err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
            dat.err           = err;
            dat.errstring     = 'Eye Fixation broken during FB delay';
            hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
            dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
            done              = 1;
          end
          if ~err & ((toc-gotEyeTime) > dat.eyetargethold)
            done = 1;
            dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Held + Phase TimeSyncGetTimeMs];
          end
        end
      end

    end
    gotEye = 0;
  end

end
if err
  hW.StartBatchDraw;
  hStartTrg.Hide;
  hFng.Hide;
  hFngRing.Hide;
  hW.FinishBatchDraw;
end
%%  ------------------  END PHASE 3  -----------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% % % %%  - - - - - - - - - -  PHASE 4  - - - - - - - - - - -
% % % %%%                 REACH, INSTRUCTED DELAY PHASE
% % % %%%  Reach Target shown.  Wait at Start Target during Instructed Delay.  Maintain hand position and
% % % %%%  Eye Fixation.  GO Tone On following delay.
% % % Phase = 4;
% % %
% % % if (~err)
% % %     tic;
% % %     if rand(1) <= Params.P_NONZERO_REACH_DELAY %&& dat.test==0
% % %         dat.reachdelay = Params.REACH_DELAY_MIN + ...  %% 3 - Between max and min
% % %             rand*(Params.REACH_DELAY_MAX-Params.REACH_DELAY_MIN);
% % %     else
% % %         dat.reachdelay = 0;
% % %     end
% % %     fprintf(' Delay=%.2f ',dat.reachdelay);
% % %
% % %     hW.StartBatchDraw;
% % %     hReachTrg.Show(Params.EventCodes.ReachTarget_Show + Phase);
% % %     feval(dat.fngfeedbackfunc, pos+dat.fbshift, 0, 2);
% % %     hW.FinishBatchDraw(Params.EventCodes.VisFB_Move + Phase);
% % %
% % %     while (~err & (toc < dat.reachdelay)), %%  This is now a hold during target presentation
% % %         %loopct = loopct+1;
% % %
% % %         %%% get hand position at start target
% % %         [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
% % %         pos = handxy(end,:);
% % %         speed = norm(handvel);
% % %
% % %         %    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
% % %         posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin2);
% % %
% % %         speedOk = (speed <= dat.starttargetvelcrit);
% % %         if ~(posOk & speedOk)
% % %             err            = 2;
% % %             dat.err        = err;
% % %             dat.errstring  = 'Broke Hold at Start Position During Reach Delay';
% % %             dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired + Phase TimeSyncGetTimeMs];
% % %         end
% % %
% % %         EyePos = TrialGetEye(hEye,10);
% % %         % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
% % %         eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
% % %         if (NO_ISCAN | dat.enforceFixationFlag==0) eyeOk=1; end
% % %         if (~eyeOk)
% % %             err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
% % %             dat.err           = err;
% % %             dat.errstring     = 'Eye Fixation broken during Reach delay';
% % %             dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
% % %         end
% % %
% % %         feval(dat.fngfeedbackfunc, pos+dat.fbshift, 0, 2);
% % %     end
% % % end
% % % if err
% % %     hReachTrg.Hide(Params.EventCodes.ReachTarget_Hide);
% % %     hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
% % % end
% % % %%  -----------------  END PHASE 4  ----------------
% % % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % %
% % %
% % %
% % % %%  - - - - - - - - PHASE 5 - - - - - - - - - - - -
% % % %%%             REACHING PHASE
% % % %%%  Begin reach to Reach Target.  Maintain Fixation for some proportion
% % % %%%  of the reach.
% % % %%%
% % % Phase = 5;
% % %
% % % ReachTrajStartIdx = hL.GetDataIndexLatest;
% % %
% % % if (~err)
% % %     tic;
% % %     dat.startpt = TrialGetKin(hL,Params.FINGER_MARKER,1);  % position of hand before go tone
% % %     ToneStart(Params.GO_TONE_FREQ, Params.GO_TONE_TIME);   % GO signal
% % %     dat.matlabeventlog(end+1,:) = [Params.EventCodes.Tone_On + Phase TimeSyncGetTimeMs];
% % %
% % %     toneOn=1;
% % %     done = 0; target_time=0;
% % %     gotArm=0;
% % %     PRE_REACH_HOLD = Params.REACH_TARGET_TIMEOUT;
% % %     reach_vec = dat.reachtargetpos-dat.startpt;
% % %     FBreach_vec = dat.reachtargetpos-(dat.startpt+dat.fbshift);
% % % end
% % %
% % % loopct = 0; eyetrgturnedoffflag = 0;
% % % while (~done & ~err),
% % %     loopct = loopct+1;
% % %     tim=toc;
% % %
% % %     [handxy,vel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
% % %     pos = handxy(end,:);
% % %
% % %     dist_pct = ((pos+dat.fbshift) - (dat.startpt+dat.fbshift))*FBreach_vec' / (FBreach_vec*FBreach_vec');
% % %     %%dist_pct = ((pos+dat.fbshift) - dat.startpt)*reach_vec' / (reach_vec*reach_vec');
% % %     dist_pct_H = ((pos) - dat.startpt)*reach_vec' / (reach_vec*reach_vec');
% % %     projLength = norm(dist_pct_H.*reach_vec);
% % %
% % %     if ~hFng.GetShowFlag & (dist_pct >= dat.fbonreachproportion)
% % %         hW.StartBatchDraw;
% % %         %updateVisFBParams(hFng,Params.visFB(1));  %  Set it (back) to the veridical cue
% % %         feval(dat.fngfeedbackfunc, pos, dat.fbshift, 1);
% % %         dat.fbpt = pos;
% % %         hW.FinishBatchDraw(Params.EventCodes.VisFB_Show + Phase);
% % %     end
% % %     %     if hFng.GetShowFlag & (dist_pct >= dat.fboffreachproportion) & (dist_pct < dat.fbonreachproportion)
% % %     if hFng.GetShowFlag & (projLength >= dat.fboffreachdistance) & (dist_pct < dat.fbonreachproportion)
% % %         hW.StartBatchDraw;
% % %         feval(dat.fngfeedbackfunc, pos, dat.fbshift, 0);
% % %         dat.fboffpt = pos;
% % %         hW.FinishBatchDraw(Params.EventCodes.VisFB_Hide + Phase);
% % %     end
% % %
% % %     %  If he hasn't reached far enough yet, check for Eye Fixation
% % %     if projLength <= Params.EyeFixationReachDistance
% % %         EyePos = TrialGetEye(hEye,10);
% % %         % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data
% % %         eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
% % %         if (NO_ISCAN | dat.enforceFixationFlag==0) eyeOk=1; end
% % %         if (~eyeOk)
% % %             err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
% % %             dat.err           = err;
% % %             dat.errstring     = 'Eye Fixation broken during Reach';
% % %             dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
% % %         end
% % %     else
% % %         if ~eyetrgturnedoffflag  % If we didn't already turn it off. %hEyeTrg.GetShowFlag
% % %             hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
% % %             eyetrgturnedoffflag = 1;
% % %         end
% % %     end
% % %
% % %     posOk = TrialInBox(pos+dat.fbshift,dat.reachtargetpos,dat.reachtargetwin);
% % %     if Params.useGradedReward && (dist_pct>0.6)
% % %         %  if we're using the graded reward then his endpt is determined by where he
% % %         %  is at the time his speed drops below some criterion (donecritspeed).
% % %         %  At this point, end the reach phase.  Of course, he must have started the reach
% % %         %  otherwise this will end at the beginning reach phase before his hand speed exceeds the
% % %         %  threshold.  Check for this by ensuring that he is at least some part of the way to the
% % %         %  reach target before checking for the speed criterion.
% % %         posOk = 1;
% % %     end
% % %     velOk = (norm(vel)<dat.donecritspeed);%(vel <= 2);  %% MM/SEC
% % %
% % %     feval(dat.fngfeedbackfunc, pos, dat.fbshift, 2);
% % %
% % %
% % %     if posOk & velOk %(dist_pct>0.5) & (norm(vel)<dat.donecritspeed) %posOk
% % %         done = 1;
% % %         dat.endpt = pos;
% % %         dat.endptspeed = norm(vel);
% % %         dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Acquired + Phase TimeSyncGetTimeMs];
% % %     end
% % %
% % %
% % %     % check for TIMEOUT
% % %     if(~done & tim>Params.REACH_TARGET_TIMEOUT_2),
% % %         err           = 4;
% % %         dat.err       = err;
% % %         dat.errstring = 'Timeout to Reach Target';
% % %         done          = 1;
% % %         %         hW.StartBatchDraw;
% % %         %         hReachTrg.Hide;
% % %         %         feval(dat.fngfeedbackfunc, pos, 0, 0);
% % %         %         hW.FinishBatchDraw;
% % %         dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Timeout + Phase TimeSyncGetTimeMs];
% % %     end
% % %
% % % end
% % % if ~Params.MaintainFixationDuringHoldFlag  %  hEyeTrg.GetShowFlag
% % %   hW.StartBatchDraw;
% % %     hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
% % %     hW.FinishBatchDraw;
% % % end
% % % if err
% % %     hW.StartBatchDraw;
% % %     hReachTrg.Hide;
% % %     hEyeTrg.Hide;
% % %     feval(dat.fngfeedbackfunc, pos, 0, 0);
% % %     hW.FinishBatchDraw;
% % % else
% % %     if Params.useGradedReward && ~isempty(dat.endpt) & dat.givebonusfeedbackflag
% % %         hW.StartBatchDraw;
% % %         feval(dat.fngfeedbackfunc, dat.endpt, dat.fbshift, 1);
% % %         hFngRing.SetXY(dat.endpt+dat.fbshift);
% % %         hFngRing.Show
% % %         hW.FinishBatchDraw;
% % %     end
% % % end
% % %
% % %
% % % %%  -------------------  END PHASE 5  ------------------------
% % % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % %
% % %
% % % %%  - - - - - - - - -  PHASE 6  - - - - - - - - - - -
% % % %%%  Hold in Reach Target (or near endpoint)
% % % Phase = 6;
% % %
% % % if (~err)
% % %     %   if Params.useGradedReward
% % %     %     %  He may not be in the reach target, so just make him hold near his endpt.
% % %     tic;
% % %     while ((toc < Params.REACH_TARGET_HOLD) & ~err),
% % %         % Arm Position
% % %         pos = TrialGetKin(hL,Params.FINGER_MARKER,1); %latest;
% % %         if Params.useGradedReward
% % %             %  He may not be in the reach target, so just make him hold near his endpt.
% % %             posOk = TrialInBox(pos,dat.endpt,dat.reachtargetrad);
% % %         else
% % %             feval(dat.fngfeedbackfunc, pos, dat.fbshift, 2);
% % %             posOk = TrialInBox(pos+dat.fbshift,dat.reachtargetpos,dat.reachtargetrad);
% % %         end
% % %
% % %         if Params.MaintainFixationDuringHoldFlag
% % %             EyePos = TrialGetEye(hEye,10);
% % %             eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
% % %             if (NO_ISCAN | dat.enforceFixationFlag==0) eyeOk=1; end
% % %             if (~eyeOk)
% % %                 err               = Params.EventCodes.Error + Params.EventCodes.EyeTarget_Unacquired;
% % %                 dat.err           = err;
% % %                 dat.errstring     = 'Eye Fixation broken during Reach Hold';
% % %                 dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error + Phase TimeSyncGetTimeMs];
% % %             end
% % %         end
% % %
% % %         if (~posOk)
% % %             err            = 10;
% % %             dat.err        = err;
% % %             dat.errstring  = 'Missed Hold at End of Reach';
% % %             hReachTrg.Hide;
% % %             dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Unacquired + Phase TimeSyncGetTimeMs];
% % %         end
% % %     end
% % %     %   else
% % %     %     tic;
% % %     %     while ((toc < Params.REACH_TARGET_HOLD) & ~err),
% % %     %       % Arm Position
% % %     %       pos = TrialGetKin(hL,Params.FINGER_MARKER,1); %latest;
% % %     %       feval(dat.fngfeedbackfunc, pos, dat.fbshift, 2);
% % %     %       %    posOk = TrialInBox(pos,dat.endpt,dat.reachtargetrad);
% % %     %       posOk = TrialInBox(pos+dat.fbshift,dat.reachtargetpos,dat.reachtargetrad);
% % %     %       if (~posOk)
% % %     %         err            = 10;
% % %     %         dat.err        = err;
% % %     %         dat.errstring  = 'Missed Hold at Reach Target';
% % %     %         hReachTrg.Hide;
% % %     %         dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Unacquired + Phase TimeSyncGetTimeMs];
% % %     %       end
% % %     %     end
% % %     %   end
% % % end
%if hEyeTrg.GetShowFlag
hW.StartBatchDraw;
hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide + Phase);
hW.FinishBatchDraw;
%end
if ~err
  dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Held + Phase TimeSyncGetTimeMs];
end
%ReachTrajStopIdx = hL.GetDataIndexLatest;
handTrajStopIdx = hL.GetDataIndexLatest;
eyeTrajStopIdx = hEye.GetDataIndexLatest;

pause(0.3);  %  Make sure the eye target has a chance to turn off before the reward.

%%%  Reward and error feedback
if ~err
  %     if ~isempty(dat.endpt)
  %         dat.disterr = norm(dat.reachtargetpos - (dat.endpt + dat.fbshift));  %  Keep track of the real error, whether we use it for the reward or not.
  %     end
  %     %  Give performance feedback
  %     if ~isempty(dat.endpt) && Params.useGradedReward
  %         if ~dat.givebonusfeedbackflag & ~isnan(dat.distanceerrorforreward) %%any(dat.fbshift)  %  Give random bonus feedback for trials with a feedback shift
  %             %%norm(mvnrnd([0 0],dat.randbonusc));
  %             dat.reachbonus = dat.reachbonusfunc(dat.distanceerrorforreward,dat.reachbonustau);
  %         else
  %             dat.reachbonus = dat.reachbonusfunc(dat.disterr,dat.reachbonustau);
  %         end

  %   finalrew = Params.LARGE_REWARD*dat.reachbonus;
  %   JuiceStart(finalrew);

  %   pause(Params.performanceFBPause);
  % else
  finalrew = Params.EYE_FIX_REWARD2;
  JuiceStart(finalrew);
  % end
  %%%
  dat.totalreward = dat.totalreward+finalrew;
end


if ~err
  % dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Held + Phase TimeSyncGetTimeMs];
  dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Success TimeSyncGetTimeMs];
end
% Switch off all targets and FB
hW.StartBatchDraw;
hStartTrg.Hide;
%hReachTrg.Hide;
hFng.Hide;
hFngRing.Hide;
hW.FinishBatchDraw;
%%  -------------------  END PHASE 6  ---------------


dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Stop TimeSyncGetTimeMs];


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%  - - - - - - - - -  GET BUFFERED DATA  - - - - - - - - - - -
Phase = 7;


%ReachTrajN_Points   = ReachTrajStopIdx  -  ReachTrajStartIdx + 1;
handTrajN_Points    = handTrajStopIdx   -  handTrajStartIdx + 1;
eyeTrajN_Points     = eyeTrajStopIdx    -  eyeTrajStartIdx + 1;

ExperimentTimingUpdate;  %  update time coeffs on servers

% Get trajectory from Liberty Buffer and error check
for i=1:Params.N_MARKERS
  fm = Params.FINGER_MARKER;
  % [TrackerTime TrackerXYZ] = invoke(hL, 'GetSensorBuffered', i, ReachTrajStartIdx, ReachTrajN_Points );
  %  dat.traj(i, :, :) = TrackerXYZ(1:6,:);

  [handTrajTime TrackerXYZ] = invoke(hL, 'GetSensorBuffered', i, handTrajStartIdx, handTrajN_Points );
  dat.handtrajectory(i, :, :) = TrackerXYZ(1:6,:);
end
%dat.time = TrackerTime;
dat.time = handTrajTime;
dat.handtrajectorytime = handTrajTime;

dat.bufferstarttime = dat.time(1);
dat.bufferstoptime  = dat.time(end);

[eyetime eyexy] =  invoke(hEye, 'GetDataBuffered', eyeTrajStartIdx, eyeTrajN_Points );
dat.eyetrajectory = eyexy;
dat.eyetrajectorytime = eyetime;

%%  - - - - - - - - -  FINALIZE TRIAL  - - - - - - - -

% Save some more stuff
dat.err = err;

% Switch off all targets and FB
hW.HideGroup(0);

% Pause at end of trials
if(dat.err & dat.err~=1)
  pause((dat.intertrialdelay + Params.ERR_PENALTY)/1000);
else
  pause(dat.intertrialdelay/1000);
end


return;





