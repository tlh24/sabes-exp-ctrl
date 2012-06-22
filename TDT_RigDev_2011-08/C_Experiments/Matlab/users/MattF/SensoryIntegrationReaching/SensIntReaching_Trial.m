%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% REACH TRIAL FUNCTION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [dat] = SensIntReaching_Trial( dat )

%global ORIGIN BUFFERTIME FRAMERATE
global Params targArray V center
global hStartTrg hReachTrg hFng hRightHandArrowField hText1 hBonusTrg hEyeTrg
global hL hW hEye hMou

DisplayObjectGroupsInclude;

%%%%% Debug flags
DEBUG     = 0;

hW.StartBatchDraw;

%%% FEEDBACK
hFng.SetColor( dat.visFB.RGB.*dat.visFB.bright);%[1 1 1] * dat.feedbackfngbright;
hFng.SetScale( dat.visFB.rad);%dat.feedbackfngrad;
hFng.SetFillFlag( 1);
hFng.SetZ( 0.0);
hFng.Hide;

%%% START TARGET
hStartTrg.SetXY( dat.starttargetpos);
hStartTrg.SetColor( dat.starttargetrgb * dat.starttargetbright);
hStartTrg.SetScale( dat.starttargetrad);
hStartTrg.SetFillFlag( 1);
hStartTrg.SetZ( .5);
hStartTrg.Hide;

%%% REACH TARGET
hReachTrg.SetXY( dat.reachtargetpos);
hReachTrg.SetColor( dat.reachtargetrgb * dat.reachtargetbright);
hReachTrg.SetScale( dat.reachtargetrad);
hReachTrg.SetFillFlag(1);
hReachTrg.SetZ(0);
hReachTrg.Hide;

%%% EYE TARGET
if ~isempty(dat.eyetargetpos)
  hEyeTrg.SetXY( dat.eyetargetpos);
  hEyeTrg.SetColor( dat.eyetargetrgb .* dat.eyetargetbright);
  hEyeTrg.SetScale( dat.eyetargetrad);
  hEyeTrg.SetFillFlag(1);
  hEyeTrg.SetZ(1);
  hEyeTrg.Hide;
end
%%% Arrow Field

hW.FinishBatchDraw;
% invoke(hW,'clrlog');

dat.trialtime = clock; % Start Trial Time
dat.err = 0;
dat.finalreward = 0; % Set final reward to zero
dat.totalreward = 0;

ExperimentTimingUpdate; % update time coeffs on servers

dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Start TimeSyncGetTimeMs];
%%%%%%%%%%%%%% STEP 1 -
% Hear the Start Tone, Hand Reach and Hold Start Target

dat.starttargetwin =  Params.START_TARGET_WIN;
dat.starttargetrad =  Params.START_TARGET_RAD;

dat.starttargetshow     = Params.START_TARGET_SHOW;  % in this way we can change the
%dat.starttargetfeedback = Params.START_TARGET_FEEDBACK; % initial parameters from keyboard
dat.starttargetflashbright = Params.START_TARGET_FLASH_BRIGHT;
dat.starttargethold = Params.START_TARGET_HOLD;

if dat.trialtype == 1
  %  Play a tone sequence to let the monk know that this trial will be a
  %  reach trial with an instructed delay
  for plsi = 1:Params.TRIAL_TYPE_TONE(1).NPULSES
    tic;
    ToneStart(Params.TRIAL_TYPE_TONE(1).FREQ, Params.TRIAL_TYPE_TONE(1).PULSEDUR);

    if plsi<Params.TRIAL_TYPE_TONE(1).NPULSES
      while toc<(Params.TRIAL_TYPE_TONE(1).PULSEDUR + Params.TRIAL_TYPE_TONE(1).IPI)
      end
    end
  end
elseif dat.trialtype == 2
  %     %  Play a tone sequence to let the monk know that this trial will be
  %     %  a RT reach trial with NO instructed delay
  %     for plsi = 1:Params.TRIAL_TYPE_TONE(2).NPULSES
  %         tic;
  %         ToneStart(Params.TRIAL_TYPE_TONE(2).FREQ, Params.TRIAL_TYPE_TONE(2).PULSEDUR);
  %         if plsi<Params.TRIAL_TYPE_TONE(2).NPULSES
  %             while toc<( Params.TRIAL_TYPE_TONE(2).PULSEDUR + Params.TRIAL_TYPE_TONE(2).IPI)
  %             end
  %         end
  %     end
  % else

end

hW.StartBatchDraw;
%invokeMultiVisObjects(hRightHandArrowField,'Show');
invokeMultiVisObjects(hRightHandArrowField,'SetGroupID',VisArrowFieldGroup);
hW.ShowGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Show);
hW.FinishBatchDraw;

%%% Acquisition of Start Target.
%[pos,speed] = latest(1);
pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
initialLoc = pos; initialLocWin = 5; movestartedflag = 0; movestartedtime = inf;
[dummy,initialDist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
done=0; err = 0; dat.errstring = '';
tic; gotArm = 0; %dat.starttargethold = 0.5;
%lastVBupdatetime = toc;
loopct = 0;
while (~done),
  loopct = loopct+1;
  [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
  pos = handxy(end,:);
  speed = norm(handvel);
  %[pos,speed] = latest(1);
  %  Train with Arrow field.  Length and direction of each arrow in field is proportional
  %  to difference vector, (tgtLoc - handLoc).
  [cdang,cddist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
  asize = Params.arrowFieldLength(cddist);

  hW.StartBatchDraw;
  invokeMultiVisObjects(hRightHandArrowField,'SetAngle',cdang.*180/pi);
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

  posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
  speedOk = (speed <= dat.starttargetvelcrit);
  if posOk & hRightHandArrowField(1).GetShowFlag
    %invokeMultiVisObjects(hRightHandArrowField,'Hide');
    hW.HideGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Hide);
  elseif ~posOk
    %        invokeMultiVisObjects(hRightHandArrowField,'Show');
    hW.ShowGroup(VisArrowFieldGroup);
  end

  if (posOk & speedOk),
    if (~gotArm),
      gotArm = 1;
      starthold = toc;
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Acquired TimeSyncGetTimeMs];
          %hW.FinishBatchDraw(Params.EventCodes.StartTarget_Acquired);
    elseif (toc>(starthold+dat.starttargethold))
      done = 1;   % Reach to start target OK
      %    hW.FinishBatchDraw;%(Params.EventCodes.StartTarget_Held);
            dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Held TimeSyncGetTimeMs];
    end
    %        invokeMultiVisObjects(hRightHandArrowField,'Hide');
    if hRightHandArrowField(1).GetShowFlag
    hW.HideGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Hide);
    end

  end

  if gotArm & ~(posOk & speedOk)  %  Once target is acquired properly, it must remain acquired
    done = 1;
    err = 800;
    dat.err = err;
    dat.errstring = 'Start Target Not Held';
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
  end

  if (toc >= Params.REACH_START_TARGET_TIMEOUT),
    err            = 1;
    dat.err        = err;
    dat.errstring  = 'Timeout at Start Position';
    done           = 1;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Timeout TimeSyncGetTimeMs];
  elseif (toc - movestartedtime) > dat.maxmovetimetostarttarget
    err = 5;
    dat.err = err;
    dat.errstring = 'Too slow to reach Start Target';
    done = 1;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.GenericError TimeSyncGetTimeMs];
  end
  hW.FinishBatchDraw;
end
% hW.StartBatchDraw;
% %invokeMultiVisObjects(hRightHandArrowField,'Hide');
% hW.HideGroup(VisArrowFieldGroup);
% hW.FinishBatchDraw;
%dtim = cputime;

% if start target not acquired, turn off feedback, pause
if (err ~=0),
  feval(dat.fngfeedbackfunc, pos, 0, 0);
else, % if Start Target acquired, give reward with probability P_START_TARGET_REWARD
  rewThresh = rand(1);
  if(rewThresh<Params.P_START_TARGET_REWARD)
    if starttrgshown | flashstart
      JuiceStart(Params.SMALL_REWARD);
      dat.totalreward = dat.totalreward+Params.SMALL_REWARD;
    else
      JuiceStart(Params.MEDIUM_REWARD);
      dat.totalreward = dat.totalreward+Params.MEDIUM_REWARD;
    end
  end
end

%%%  Start Target has been acquired and held without FB.
%%%  Tone signals next phase. Continue holding.  FB on for FB+ trials.
if ~err
  done = 0;
  tic;
  ToneStart(Params.EventTone(1).FREQ, Params.EventTone(1).DUR);
  while ~err & ~done

    [handxy,handvel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
    pos = handxy(end,:);
    speed = norm(handvel);

    %    [pos,speed] = latest(1);
    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
    speedOk = (speed <= dat.starttargetvelcrit);

    if ~(posOk & speedOk)
      done = 1;
      err = 900;
      dat.err = err;
      dat.errstring = 'Released Start Target During FB Delay';
          dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
    else
      if dat.starttargetfeedback
        feval(dat.fngfeedbackfunc, pos, 0, 1);  %  If he's still holding, and this is a FB+ trial, then turn FB on
            hW.FinishBatchDraw;%(Params.EventCodes.VisFB_Show);
      end
    end

    if toc > dat.starttargetfbholddur
      done = 1;
          dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Held TimeSyncGetTimeMs];
    end
    hW.FinishBatchDraw;

  end
end



%%% Reach next target
%%% Wait at Start target for GO tone
%%% Start position is current finger location
tic;
if (~err)


  if rand(1) <= Params.P_NONZERO_REACH_DELAY %&& dat.test==0
    dat.reachdelay = Params.REACH_DELAY_MIN + ...  %% 3 - Between max and min
      rand*(Params.REACH_DELAY_MAX-Params.REACH_DELAY_MIN);
  else
    dat.reachdelay = 0;
  end
  fprintf(' Del=%.2f ',dat.reachdelay);

  hReachTrg.Show(Params.EventCodes.ReachTarget_Show);
  %hFng.vertices = updateVisBlurVerts(dat.visBlur.N,dat.visBlur.Nverts,dat.visBlur.dotrad,dat.visBlur.C);
  %lastVBupdatetime = 0;
  feval(dat.fngfeedbackfunc, pos, 0, 2);
  hW.FinishBatchDraw(Params.EventCodes.VisFB_Move);

  %vbup = dat.visBlur.VBUP;
  %while (((cputime-dtim) < dat.reachdelay)), %%  This is now a hold during target presentation
  % loopct = 0;
  while (~err & (toc < dat.reachdelay)), %%  This is now a hold during target presentation
    %loopct = loopct+1;

    %%% get hand position at start target
    pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
    %pos = latest(0);
    % check if hand still in start window
    %  if(dat.starttargetfeedback), % Show feedback if enabled
    feval(dat.fngfeedbackfunc, pos, 0, 2);
    %if ~mod(loopct,dat.visBlur.VBUP)
    %%%%%%%%           if (toc-lastVBupdatetime) >= vbup;%dat.visBlur.VBUP  %~mod(loopct,dat.visBlur.VBUP)
    %%%%%%%%               lastVBupdatetime = toc
    %hFng.vertices = updateVisBlurVerts(dat.visBlur.N,dat.visBlur.Nverts,dat.visBlur.dotrad,dat.visBlur.C);
    %%%%%%%%           end
    %   end
    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
    if (~posOk),
      err            = 2;
      dat.err        = err;
      dat.errstring  = 'Broke Hold at Start Position During Reach Delay';
    %  hStartTrg.Hide;
      hReachTrg.Hide;
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
      %hRightHandDotField.show=0;
    end
   % hW.FinishBatchDraw;
  end
end


if (~err), % If hold at Start Target while fixating is OK, give reward
  if(Params.INTERMEDIATE_REWARDS), JuiceStart(Params.MEDIUM_REWARD);
    dat.totalreward = dat.totalreward+Params.MEDIUM_REWARD;
  end
end

% % % % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % % % %%%%%%% 2: GET HAND TO REACH TARGET
% % % % % Now do reach

%hStartTrg.Hide;
%hW.FinishBatchDraw;


%%%%%% ERROR CHECK BUFFER COMMANDS
% nE0 = hL.err;
%invoke(hL,'startBuffer');
ReachTrajStartIdx = hL.GetDataIndexLatest;
%%dat.bufferstarttime = [];%clock;
% nE1 = hL.err;
%if(nE1>nE0)
%    for i=(nE0+1):nE1,
%        fprintf('%d: %s',i,hL.getErr(i))
%    end
% end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%hFng.vertices = updateVisBlurVerts(dat.visBlur.N,dat.visBlur.Nverts,dat.visBlur.dotrad,dat.visBlur.C);
hW.FinishBatchDraw;

if (~err)
  tic;
  dat.startpt = TrialGetKin(hL,Params.FINGER_MARKER,1); %latest(0);  % position of hand before go tone
  % hFng.Hide; hW.FinishBatchDraw;
  ToneStart(Params.GO_TONE_FREQ, Params.GO_TONE_TIME);              %% go signal  
  % hFng.Show; hW.FinishBatchDraw;
  toneOn=1;
  done = 0; target_time=0;
  gotArm=0;
  PRE_REACH_HOLD = Params.REACH_TARGET_TIMEOUT;

  reach_vec = dat.reachtargetpos-dat.startpt;
end

loopct = 0; %lastVBupdatetime = 0;
while (~done & ~err),
  loopct = loopct+1;
  tim=toc;

  %%% get pos
  [handxy,vel] = TrialGetKin(hL,Params.FINGER_MARKER,5);
  pos = handxy(end,:);

  %  [pos,vel,velpct] = latest(0);

  dist_pct = (pos - dat.startpt)*reach_vec' / (reach_vec*reach_vec');
  projLength = norm(dist_pct.*reach_vec);
  if ~hFng.GetShowFlag & (dist_pct >= dat.fbonreachproportion)
    % lastVBupdatetime = toc;
    %hFng.vertices = updateVisBlurVerts(dat.visBlur.N,dat.visBlur.Nverts,dat.visBlur.dotrad,dat.visBlur.C);
    hW.StartBatchDraw;
    feval(dat.fngfeedbackfunc, pos, 0, 1);
    dat.fbpt = pos;
    hW.FinishBatchDraw;%(Params.EventCodes.VisFB_Show);
  end

  %dist_pct = (pos - dat.startpt)*reach_vec' / (reach_vec*reach_vec');
%  if hFng.GetShowFlag & (dist_pct >= dat.fboffreachproportion) & (dist_pct < dat.fbonreachproportion)
  if hFng.GetShowFlag & (projLength >= dat.fboffreachdistance) & (dist_pct < dat.fbonreachproportion)
    % dat.fbnonconstpt = pos;
    % shiftshiftflag = 1;
    hW.StartBatchDraw;
    feval(dat.fngfeedbackfunc, pos, 0, 0);
    dat.fboffpt = pos;
    hW.FinishBatchDraw(Params.EventCodes.VisFB_Hide);
    % hEyeTrg.Hide;
  end

  %   if hFng.GetShowFlag & (dist_pct >= dat.fboffreachproportion) & (dist_pct < dat.fbonreachproportion)
  %         feval(dat.fngfeedbackfunc, pos, 0, 0);
  %         dat.fboffpt = pos;
  %     end

  posOk = TrialInBox(pos,dat.reachtargetpos,dat.reachtargetwin);
  velOk = (norm(vel)<dat.donecritspeed);%(vel <= 2);  %% MM/SEC

  hW.StartBatchDraw;
  feval(dat.fngfeedbackfunc, pos, 0, 2);
  hW.FinishBatchDraw;


  if posOk & velOk %(dist_pct>0.5) & (norm(vel)<dat.donecritspeed) %posOk
    done = 1;
    dat.endpt = pos;
    dat.endptspeed = norm(vel);
  end


  % check for TIMEOUT
  if(~done & tim>Params.REACH_TARGET_TIMEOUT),
    err           = 4;
    dat.err       = err;
    dat.errstring = 'Timeout to Reach Target';
    done          = 1;    
    hW.StartBatchDraw;
    hReachTrg.Hide;
    feval(dat.fngfeedbackfunc, pos, 0, 0);
    hW.FinishBatchDraw;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Timeout TimeSyncGetTimeMs];
  end

end
%invokeMultiVisObjects(hRightHandArrowField,'Hide');
if err, feval(dat.fngfeedbackfunc, pos, 0, 0); end
hW.FinishBatchDraw;


toneOn=0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% 3: HOLD ALL: both start target and fixation
%%% If target 1 acquired,  give reward

if (~err),
  %% if Reach Target acquired, give reward
  if(Params.INTERMEDIATE_REWARDS) JuiceStart(Params.MEDIUM_REWARD); dat.totalreward = dat.totalreward+Params.MEDIUM_REWARD;end
  tic;
  %lastVBupdatetime = 0;
  while ((toc < Params.REACH_TARGET_HOLD) & ~err),
    loopct = loopct+1;

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
      %            hEyeFix.Hide;
      %  hRightHandDotField.show = 0;
    end
  end
  hW.FinishBatchDraw;
end

if ~err
  dat.matlabeventlog(end+1,:) = [Params.EventCodes.ReachTarget_Held TimeSyncGetTimeMs];
end

% Switch off all targets and FB and get actionlog
hStartTrg.Hide;
hReachTrg.Hide;
hFng.Hide;
hW.FinishBatchDraw;

%----------------------------
% Trial closing sequence

%dat.bufferstoptime = clock;

ReachTrajStopIdx = hL.GetDataIndexLatest;
ReachTrajN_Points = ReachTrajStopIdx - ReachTrajStartIdx + 1;

ExperimentTimingUpdate; % update time coeffs on servers

% Get trajectory from Liberty Buffer and error check
for i=1:Params.N_MARKERS
  [TrackerTime TrackerXYZ] = invoke(hL, 'GetSensorBuffered', i, ReachTrajStartIdx, ReachTrajN_Points );
  dat.traj(i, :, :) = TrackerXYZ(1:2,:);
  %sync = traj(:,8:9,1);
end
dat.time = TrackerTime;

dat.bufferstarttime = dat.time(1);
dat.bufferstoptime  = dat.time(end);

% % Get events from CP_Display
% dat.viseventlog = hW.GetEventLog;

% Save some more stuff
dat.err = err;

% End of Trial closing sequence
%----------------------------


if (~err ), % Final reward
  JuiceStart(Params.LARGE_REWARD);  %%%
  dat.totalreward = dat.totalreward+Params.LARGE_REWARD;
end


%disp('Where the heck am I?');

% Switch off all targets and FB
hW.HideGroup(0);
% hStartTrg.Hide;
% hReachTrg.Hide;
% hFng.Hide;


% Pause at end of trials
if(dat.err==10)
  %     pause((Params.INTER_TRIAL_DELAY + Params.SWAT_PENALTY)/1000);
  pause((dat.intertrialdelay + Params.SWAT_PENALTY)/1000);
elseif(dat.err & dat.err~=1)
  %pause((Params.INTER_TRIAL_DELAY + Params.ERR_PENALTY)/1000);
  pause((dat.intertrialdelay + Params.ERR_PENALTY)/1000);
else
  %pause(Params.INTER_TRIAL_DELAY/1000);
  pause(dat.intertrialdelay/1000);
end


