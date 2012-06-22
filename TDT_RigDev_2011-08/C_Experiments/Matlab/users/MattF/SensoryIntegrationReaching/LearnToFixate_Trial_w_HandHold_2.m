function dat = LearnToFixate_Trial_w_HandHold_2(dat)
%
%  MF May 16, 2007.
%

%global ORIGIN BUFFERTIME FRAMERATE
global Params
global hEyeTrg hStartTrg hRightHandArrowField hReachTrg hEye
global hL hW NO_ISCAN

DisplayObjectGroupsInclude;

%NO_ISCAN = 0;  % For Debugging

% hL.active  = 1;  %% Activate Liberty

%%%%% SETUP ALL VIS OBJECTS
% hW.batchmode = 1;

%%% START TARGET
hStartTrg.SetXY( dat.starttargetpos);
hStartTrg.SetColor( dat.starttargetrgb * dat.starttargetbright);
hStartTrg.SetScale( dat.starttargetrad);
hStartTrg.SetFillFlag(1);
hStartTrg.SetZ(.5);
hStartTrg.Hide;

%%% REACH TARGET
hReachTrg.SetXY( dat.reachtargetpos);
hReachTrg.SetColor( dat.reachtargetrgb * dat.reachtargetbright);
hReachTrg.SetScale( dat.reachtargetrad);
hReachTrg.SetFillFlag(1);
hReachTrg.SetZ( 0);
hReachTrg.Hide;

%%% EYE TARGET
hEyeTrg.SetXY(dat.eyetargetpos);
hEyeTrg.SetColor( dat.eyetargetrgb .* dat.eyetargetbright);
hEyeTrg.SetScale(dat.eyetargetrad);
hEyeTrg.SetFillFlag(1);
hEyeTrg.SetZ( 1);
hEyeTrg.Hide;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

dat.err = 0;
dat.finalreward = 0; % Set final reward to zero
dat.totalreward = 0;

dat.trialtime = clock; % Start Trial Time

dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Start TimeSyncGetTimeMs];

%if ~NO_ISCAN
% EyeStart;
%end


%-------------------

dat.starttargetwin =  Params.START_TARGET_WIN;
dat.starttargetrad =  Params.START_TARGET_RAD;

dat.starttargetshow     = Params.START_TARGET_SHOW;  % in this way we can change the
dat.starttargetfeedback = 0; %Params.START_TARGET_FEEDBACK; % initial parameters from keyboard
dat.starttargetflashbright = Params.START_TARGET_FLASH_BRIGHT;
dat.starttargethold = Params.START_TARGET_HOLD;


%invokeMultiVisObjects(hRightHandArrowField,'show',1);
hW.ShowGroup(VisArrowFieldGroup,Params.EventCodes.ArrowField_Show);
hW.FinishBatchDraw;

%%% Acquisition of Start Target.
%pos = latest(1);
pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
initialLoc = pos; initialLocWin = 5; movestartedflag = 0; movestartedtime = inf;
[dummy,initialDist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
done=0; err = 0; dat.errstring = '';
tic; gotArm = 0; %dat.starttargethold = 0.5;
%lastVBupdatetime = toc;
loopct = 0;
while (~done),
  loopct = loopct+1;
  %    pos = latest(1);
  pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
  %  Train with Arrow field.  Length and direction of each arrow in field is proportional
  %  to difference vector, (tgtLoc - handLoc).
  [cdang,cddist] = cart2pol(dat.starttargetpos(1)-pos(1),dat.starttargetpos(2)-pos(2));
  asize = Params.arrowFieldLength(cddist);

  hW.StartBatchDraw;
  invokeMultiVisObjects(hRightHandArrowField,'SetAngle',cdang.*180/pi);
  invokeMultiVisObjects(hRightHandArrowField,'SetScale',asize);
  invokeMultiVisObjects(hRightHandArrowField,'SetColor',dat.righthandarrowfieldrgb*feval(dat.righthandarrowfieldbrightnessfunc,asize));
  hW.FinishBatchDraw;

  %     if ~hStartTrg.GetShowFlag & Params.AFDeltaReward
  %         if initialDist - cddist >= Params.deltaForReward
  %             JuiceStart(Params.AFDeltaReward);
  %             dat.totalreward = dat.totalreward+Params.AFDeltaReward;
  %             initialDist = cddist;
  %         end
  %     end

  if (dat.maxmovetimetostarttarget < inf ) & ~movestartedflag & ~TrialInBox(pos,initialLoc,initialLocWin)
    %  Once he's moved a small distance away from his initial location,
    %  we start counting time.  He has a max time to get to the start
    %  target location.
    movestartedflag = 1;
    movestartedtime = toc;
  end

  %     if hFng.GetShowFlag  %(dat.starttargetfeedback)
  %         feval(dat.fngfeedbackfunc, pos, 0, 2);
  %         if (toc-lastVBupdatetime) > dat.visBlur.VBUP  %~mod(loopct,dat.visBlur.VBUP)
  %             lastVBupdatetime = toc;
  %             hFng.vertices = updateVisBlurVerts(dat.visBlur.N,dat.visBlur.Nverts,dat.visBlur.dotrad,dat.visBlur.C);
  %         end
  %         hW.FinishBatchDraw;
  %     end
  % check for acquisition of start target
  posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
  if (posOk),
    if (~gotArm),
      gotArm = 1;
      starthold = toc;
      %feval(dat.fngfeedbackfunc, pos, 0, 1);  %  Show the FB during the hold period.
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Acquired TimeSyncGetTimeMs];
    elseif (toc>(starthold+dat.starttargethold))
      done = 1;   % 
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Held TimeSyncGetTimeMs];
    end
    %setMultiVisObjects(hRightHandArrowField,'show',0);
    hW.HideGroup(VisArrowFieldGroup);
    hW.FinishBatchDraw;
  else
    gotArm = 0;
    %setMultiVisObjects(hRightHandArrowField,'show',1);
    hW.ShowGroup(VisArrowFieldGroup);
    %         if ~dat.starttargetfeedback
    %         feval(dat.fngfeedbackfunc, pos, 0, 0);
    %         end
    hW.FinishBatchDraw;
  end

  if (toc >= Params.REACH_START_TARGET_TIMEOUT),
    err            = 1;
    dat.err        = err;
    dat.errstring  = 'Timeout at Start Position';
    done           = 1;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
  elseif (toc - movestartedtime) > dat.maxmovetimetostarttarget
    err = 5;
    dat.err = err;
    dat.errstring = 'Too slow to reach Start Target';
    done = 1;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
  end
end
hW.HideGroup(VisArrowFieldGroup);
%setMultiVisObjects(hRightHandArrowField,'show',0);
hW.FinishBatchDraw;


%  Hold hand at start target, fixate eye target and hold

if(~err)
  %% Show eye target
  hEyeTrg.Show(Params.EventCodes.EyeTarget_Show);
  % tdtSetEyeTarget(dat.reachtargetnb);
%  hW.FinishBatchDraw;
end

done=0;
err = 0;
target_time=0;
loopct = 0;
gotEye = 0;

%[etim,ebuf]=EyeBuffer;
%etim0=etim(end);

tic;
while (~done & ~err),

  pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
  %pos = latest(1);     % get latest pos
  %
  %     if(dat.starttargetfeedback), % Show feedback if enabled
  %         feval(Params.FNG_FEEDBACK_FUNC, pos, 0, 2);
  %     end
  %
  % Update GUI every N loops
  loopct = loopct + 1; % counter to update hand data plot
  %     if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); FinishBatchDraw; end
  %
  %     %%% check if hand is still in start window
  posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
  if (~posOk),
    err            =  3;
    dat.err        = err;
    dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
    %hStartTrg.Hide;
    hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.StartTarget_Unacquired TimeSyncGetTimeMs];
    done           = 1;
  end
  %
  %%% check for eye target acquisition
  if (~err)
    
%    [EyeIdx, EyeT, EyePos] = hEye.GetDataLatest(10);
    %EyePos = EyePos';
     [EyePos,EyeVel,EyeT] = TrialGetEye(hEye,10);
    %[eye,eyeframe] = eyelatest(0);

    % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data

%     % check to see if got into eye window
%     [etim,ebuf]=EyeBuffer;
%     eframes = min(5,length(etim));
%     ebuf = ebuf((end-eframes+1):end,:);
%     etim = etim((end-eframes+1):end,:);
%     if(etim(1)<etim0)
%       ebuf = ebuf(etim>=etim0,:);
%       etim = etim(etim>=etim0,:);
%     end
    eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
    if(NO_ISCAN) eyeOk=1; end

    if (~eyeOk)
      gotEye = 0;
    end
    if (eyeOk), % Eye acquisition accomplished
      if (~gotEye)
        time = toc;
        gotEye = 1;
        dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Acquired TimeSyncGetTimeMs];
      elseif (gotEye&(toc >=(time+dat.eyetargethold)))
        done = 1;
        EyeFixPt = mean(EyePos,2);
        dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Held TimeSyncGetTimeMs];
        %hEyeTrg.Hide;
      end
    end

    % Eye acquisition not accomplished
    if((toc+dat.eyetargethold)>dat.eyetargettimeout),
      err               = 21;
      dat.err           = err;
      dat.errstring     = 'Timeout to Eye Target';
      hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
      %            hStartTrg.Hide;
      done              = 1;
    end
  end
  hW.FinishBatchDraw;

end


if ~err
  dat.eyebufferatfixation = EyePos;
dat.eyebuffertimeatfixation = EyeT;
  
  %    fprintf('\n\t\tMADE IT HERE\n');
  hReachTrg.Show(Params.EventCodes.ReachTarget_Show);
%  hW.FinishBatchDraw;
  done = 0; loopct=0;
  tic;
  while ~done & ~err
    %if loopct==0, fprintf('\n\t\tMADE IT HERE\n'); end

    pos = TrialGetKin(hL,Params.FINGER_MARKER,1);
%    pos = latest(1);     % get latest pos

    % Update GUI every N loops
    loopct = loopct + 1; % counter to update hand data plot
    %     if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); FinishBatchDraw; end
    %
    %     %%% check if hand is still in start window
    posOk = TrialInBox(pos,dat.starttargetpos,dat.starttargetwin);
    if (~posOk),
      err            =  3;
      dat.err        = err;
      dat.errstring  = 'Broke Hand Hold at Start Position During Eye Fixation';
      %hStartTrg.Hide;
      hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
      done           = 1;
    end

    %  Hold hand and eye.  Show reach target.  Must maintain eye and hand
    %  hold.
  %  [eye,eyeframe] = eyelatest(0);

    % set(hpEye,'xdata',eye(1),'ydata',eye(2)); FinishBatchDraw; % plot eye data

%     % check to see if eye is still in window
%     [etim,ebuf]=EyeBuffer;
%     eframes = min(5,length(etim));
%     ebuf = ebuf((end-eframes+1):end,:);
%     etim = etim((end-eframes+1):end,:);
%     if(etim(1)<etim0)
%       ebuf = ebuf(etim>=etim0,:);
%       etim = etim(etim>=etim0,:);
%     end
    %[EyeIdx, EyeT, EyePos] = hEye.GetDataLatest(10);
    EyePos = TrialGetEye(hEye,10);
    
    eyeOk = sum(TrialInBox(EyePos,dat.eyetargetpos,dat.eyetargetwin))>4;
    if(NO_ISCAN) eyeOk=1; end

    if (~eyeOk)
      err               = 23;
      dat.err           = err;
      dat.errstring     = 'Broke Eye Fixation at Show Reach Target';
      hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
      hReachTrg.Hide(Params.EventCodes.ReachTarget_Hide);
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Error TimeSyncGetTimeMs];
            done              = 1;
    end

    if toc >=dat.reachtrgshowdur
      done = 1;
      hReachTrg.Hide(Params.EventCodes.ReachTarget_Hide);
      hEyeTrg.Hide(Params.EventCodes.EyeTarget_Hide);
    end

    hW.FinishBatchDraw;
  end
end
hReachTrg.Hide;
hEyeTrg.Hide;
%hW.FinishBatchDraw;


if (~err), % If aquired eye target give reward
  JuiceStart(Params.EYE_FIX_REWARD2);
  dat.totalreward = dat.totalreward+Params.EYE_FIX_REWARD2;
end

hW.FinishBatchDraw;

% hW.batchmode = 0;
%dat.viseventlog = hW.GetEventLog;

% hL.active = 0;

% EyeStop;

% Pause at end of trials
if(dat.err & dat.err~=1)
  pause((Params.INTER_TRIAL_DELAY + Params.ERR_PENALTY)/1000);
else
  pause(Params.INTER_TRIAL_DELAY/1000);
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EOF
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
