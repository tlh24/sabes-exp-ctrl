function dat = LearnToFixate_Trial(dat)
%
%  MF May 16, 2007.  Dmitri's first learn to fixate task.
%

%global ORIGIN BUFFERTIME FRAMERATE
global Params
global hEyeTrg
global hL hW hEye NO_ISCAN

%NO_ISCAN = 0;  % For Debugging

% hL.active  = 1;  %% Activate Liberty

%%%%% SETUP ALL VIS OBJECTS
hW.StartBatchDraw;

%%% EYE TARGET
hEyeTrg.SetXY(dat.eyetargetpos);
hEyeTrg.SetColor( dat.eyetargetrgb .* dat.eyetargetbright);
hEyeTrg.SetScale(dat.eyetargetrad);
hEyeTrg.SetFillFlag(1);
hEyeTrg.SetZ(1);
hEyeTrg.Show;

hW.FinishBatchDraw;          %%% Chiara 03-30-05, the VisServer code will log
% invoke(hW,'clrlog');

dat.trialtime = clock; % Start Trial Time
dat.err = 0;
dat.finalreward = 0; % Set final reward to zero
dat.totalreward = 0;

% EyeStart;
  dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Start TimeSyncGetTimeMs];

%-------------------
% if(~err)
%% Show eye target
hEyeTrg.Show;
% tdtSetEyeTarget(dat.reachtargetnb);
% hW.FinishBatchDraw;
% end

done=0;
err = 0;
target_time=0;
loopct = 0;
gotEye = 0;
% [etim,ebuf]=EyeBuffer; etim0=etim(end);
startIdx = []; stopIdx = [];
tic;
while (~done & ~err),

  % Update GUI every N loops
  loopct = loopct + 1; % counter to update hand data plot
  %     if(~rem(loopct,HAND_FRAMES)), set(hpPos,'xdata',pos(1),'ydata',pos(2)); drawnow; end
  %%% check for eye target acquisition
  if (~err)

    % check to see if got into eye window
    %%        [EyeIdx, EyeT, EyeXY] = hEye.GetDataLatest(10);
    [EyeXY,Vel,EyeT] = TrialGetEye(hEye,10);
    % EyeXY = EyeXY';
    eyeOk = sum(TrialInBox(EyeXY,dat.eyetargetpos,dat.eyetargetwin))>4;
    if(NO_ISCAN) eyeOk=1; end

    if (~eyeOk)
      gotEye = 0;
    end
    if (eyeOk), % Eye acquisition accomplished
      if (~gotEye)
        time = toc;
        gotEye = 1;
        %hW.FinishBatchDraw(Params.VisCodes.EyeTarget_Acquired);
        dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Acquired TimeSyncGetTimeMs];
        startIdx = hEye.GetDataIndexLatest;
      elseif (gotEye&(toc >=(time+dat.eyetargethold)))
        done = 1;
        EyeFixPt = mean(EyeXY);
        hEyeTrg.Hide;%(Params.VisCodes.EyeTarget_Held);
        dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Held TimeSyncGetTimeMs];
        stopIdx = hEye.GetDataIndexLatest;
      end
    end

    % Eye acquisition not accomplished
    if ~eyeOk & (toc>dat.eyetargettimeout),
      err               = 21;
      dat.err           = err;
      dat.errstring     = 'Timeout to Eye Target';
      hEyeTrg.Hide;
      dat.matlabeventlog(end+1,:) = [Params.EventCodes.EyeTarget_Timeout TimeSyncGetTimeMs];
      %             hStartTrg.Hide;
      done              = 1;
    end
  end
  hW.FinishBatchDraw;

end
dat.eyebufferatfixation = EyeXY;
dat.eyebuffertimeatfixation = EyeT;

if ~(isempty(startIdx) | isempty(stopIdx))
  Nsamps = stopIdx-startIdx;
  [EyeBuffTimes,EyeBuffXY] = hEye.GetDataBuffered(startIdx,Nsamps);
  figure(100);
 % cla;
%   plot(EyeBuffXY(1,:),EyeBuffXY(2,:),'k.');
%  hold on;
  rh = rectangle('position',[dat.eyetargetpos(:)'-dat.eyetargetwin./2 dat.eyetargetwin dat.eyetargetwin], ...
    'curvature',[1 1],'facecolor',[1 0 0]);
  hold on;
  rh2 = rectangle('position',[dat.eyetargetpos(:)'-dat.eyetargetrad./2 dat.eyetargetrad dat.eyetargetrad], ...
    'curvature',[1 1],'facecolor',[1 1 1]);

   plot(EyeBuffXY(1,:),EyeBuffXY(2,:),'k.');
   
   rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
  axis equal;

  %hold off;

end

if (~err), % If aquired eye target give reward
  JuiceStart(Params.EYE_FIX_REWARD);
  dat.totalreward = dat.totalreward+Params.EYE_FIX_REWARD;
    dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Success TimeSyncGetTimeMs];
end

hW.FinishBatchDraw;

%dat.viseventlog = hW.GetEventLog;

%hL.active = 0;

%EyeStop;
%keyboard

% Pause at end of trials
if(dat.err & dat.err~=1)
  pause((Params.INTER_TRIAL_DELAY + Params.ERR_PENALTY)/1000);
else
  pause(Params.INTER_TRIAL_DELAY/1000);
end

  dat.matlabeventlog(end+1,:) = [Params.EventCodes.Trial_Stop TimeSyncGetTimeMs];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EOF
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
