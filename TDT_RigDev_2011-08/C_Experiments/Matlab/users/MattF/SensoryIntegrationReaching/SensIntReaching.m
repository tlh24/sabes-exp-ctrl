function SensIntReaching(test)

%global ORIGIN BUFFERTIME FRAMERATE
global Data Params Path
global hL hW hEye hMou
global hStartTrg hReachTrg hFng hRightHandArrowField hText1 hFngRing
global NO_ISCAN

ServerNamesInclude;
DisplayObjectGroupsInclude;

DEBUG = 0;
noFigsFlag = 0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% Experiment Setup
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% hText1.SetXY(Params.wsCenter);
% hText1.SetScale( [1 1].*35);
% hText1.SetColor( [0.6 0 0.4]);
% hText1.Hide;
%
% hBonusTrg.SetColor([0.8 0.8 0.8]);
% hBonusTrg.SetZ(1);
% hBonusTrg.Hide;

% hW.FinishBatchDraw;


%%%% Define Data structure

clear dtmp

dtmp.params = [];
dtmp.trial        = [];
dtmp.test         = 0;

dtmp.starttargetpos             = [];
dtmp.starttargetrad             = [];
dtmp.starttargetwin             = [];
dtmp.starttargetwin2            = [];
dtmp.starttargetwin3            = [];
dtmp.starttargetrgb             = [];
dtmp.starttargetbright          = [];
dtmp.starttargetshow            = [];
dtmp.starttargetfeedback        = [];
dtmp.starttargetnb              = [];
dtmp.starttargetposfunc         = [];
dtmp.movementnb                 = [];
dtmp.starttargetflashbright     = [];
dtmp.starttargetvelcrit         = [];
dtmp.starttargetfbholddur       = [];

dtmp.reachtargetnb     = [];
dtmp.reachtargetpos    = [];
dtmp.reachtargetrad    = [];
dtmp.reachtargetwin    = [];
dtmp.reachtargetrgb    = [];
dtmp.reachtargetbright = [];
dtmp.reachtargetposfunc = [];

dtmp.eyetargetpos       = [];
dtmp.eyetargetrad       = [];
dtmp.eyetargetwin       = [];
dtmp.eyetargetrgb       = [];
dtmp.eyetargetbright    = [];
dtmp.eyetargetposfunc   = [];

dtmp.nominalhandcenter = [];
dtmp.nominalreachvect = [];
dtmp.nominalreachdirection = [];
dtmp.relativefixationlocationidx = [];
dtmp.enforceFixationFlag = [];

dtmp.feedbackfngrad    = [];
dtmp.feedbackfngbright = [];
dtmp.fbvelcrit         = [];
dtmp.fngfeedbackfunc   = [];

dtmp.righthandarrowfieldrgb = [];
dtmp.righthandarrowfieldbrightnessfunc = [];

dtmp.smallreward         = [];
dtmp.largereward         = [];
dtmp.intermediaterewards = [];
dtmp.finalreward         = [];
dtmp.totalreward         = [];

dtmp.starttargethold       = [];
dtmp.reachtargethold       = [];
dtmp.eyetargethold         = [];
dtmp.reachdelay            = [];
dtmp.maxmovetimetostarttarget = [];

dtmp.eyetargettimeout       = [];

dtmp.minreachdistance = [];
dtmp.maxreachdistance = [];
dtmp.mineyetoreachdistance = [];

dtmp.fbonreachproportion = [];
%dtmp.fboffreachproportion = [];
dtmp.fboffreachdistance   = [];
dtmp.fbshift = [];
dtmp.relativeshiftdirection = [];

dtmp.reachtrgshowdur = [];

dtmp.reachbonus         = [];
dtmp.donecritspeed      = [];
dtmp.reachbonustau      = [];
dtmp.reachbonusfunc      = [];
dtmp.givebonusfeedbackflag  = [];
dtmp.randbonusc         = [];
dtmp.reachbonus         = [];
dtmp.disterr            = [];
dtmp.distanceerrorforreward     = [];

dtmp.startholdloc = [];  %% where the hand is when he starts holding in the start target
dtmp.traj       = [];  %% hand reach trajectory
dtmp.time       = [];  %% time stamp for each traj point
dtmp.fbpt       = [];  %% point where visual feedback came on
dtmp.fboffpt    = [];
dtmp.endptspeed = [];
dtmp.startpt    = [];  %% start point of reach right arm
dtmp.endpt      = [];  %% end point of reach right arm


dtmp.handtrajectory = [];
dtmp.handtrajectorytime = [];
dtmp.eyebufferatfixation = [];
dtmp.eyebuffertimeatfixation = [];
dtmp.eyetrajectory  = [];
dtmp.eyetrajectorytime = [];

dtmp.err        = [];  %% error
dtmp.errstring  = '';  %% error string
%dtmp.actionlog  = [];  %  Store all events and timestamps in this log.
%dtmp.viseventlog          = [];  %% VisServer Actionlog
dtmp.matlabeventlog       = [];
%dtmp.juiceeventlog        = [];
%dtmp.recordingeventlog    = [];
%dtmp.toneeventlog         = [];

dtmp.trialtime  = [];  %% Trial start time
dtmp.expttime   = [];  %% Experiment Time
dtmp.absolutetime = [];
dtmp.bufferstarttime    = [];
dtmp.bufferstoptime     = [];
dtmp.trialtype  = [];  %%
dtmp.intertrialdelay    = [];

dtmp.TDTTimeAtTrialStart = [];
dtmp.visFB            = [];
dtmp.whichSubWorkspace = [];

dtmp.morphoData = [];

%  - - - Adaptation - - -
dtmp.nthtrialthisblock = [];
dtmp.blocktype = [];
dtmp.usingadaptationparamsflag = [];
dtmp.adaptationonflag = [];
%%%%%

perm([],-1);
Data = struct([]);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% SETUP THE INTERACTIVE GUI
global pauseFlag keyboardFlag %newfileFlag restartFlag newcalibFlag
pauseFlag = 0;
keyboardFlag = 0;
%newfileFlag = 0;
%restartFlag = 0;
%newcalibFlag = 0;
%newfiletemp = 0;
%restarttemp = 0;
if ~noFigsFlag
  figure(1)
  %  set(gcf,'position',[24    71   560   201]);
  set(gcf,'position',[26    23   332   162]);
  pauseGH = uicontrol(gcf,'style','toggle','units','normalized','position',[.1 .4 .3 .2],'string','PAUSE','callback',@pauseCallback);
  keyboardGH = uicontrol(gcf,'style','push','units','normalized','position',[.6 .4 .3 .2],'string','KEYBOARD','callback',@keyboardCallback);
  %newfileGH = uicontrol(gcf,'style','push','units','normalized','position',[.4 .1 .2 .1],'string','NEW FILE','callback',@newfileCallback);
  %restartGH = uicontrol(gcf,'style','push','units','normalized','position',[.7 .1 .2 .1],'string','RESTART','callback',@restartCallback);
  %newcalibGH = uicontrol(gcf,'style','push','units','normalized','position',[.1 .1 .2 .1],'string','NEW EYE CAL','callback',@newcalibCallback);
end
%%%  - - - - - - - -   END GUI CAKE SETUP
%%%  ------------------------------------------------------------------

% %%%  Create Arrow Field(s)
hRightHandArrowField = createArrowField(Params.NarrowsX,Params.NarrowsY,Params.wsBounds, strDisplayComputer);% ...
%  Params.rightHandArrowFieldZ, strDisplayComputer);
invokeMultiVisObjects(hRightHandArrowField,'SetGroupID',VisArrowFieldGroup);
hW.HideGroup(VisArrowFieldGroup);
% %%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Experiment Trial Loop
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

TimeStamp = clock;

%  Create the target array
[targetlist] = SIRGetTargs(Params);

%%% Save Non-Data Variables to TEMP directory
eval(sprintf('!mkdir %s_TEMP',Params.FILENAME));
eval(sprintf('save %s_TEMP/VARS Params TimeStamp targetlist',Params.FILENAME));

%%%  Save all the .m files for this task into the data directory to keep a
%%%  record of the code used.
fprintf('\nSaving .m files into data directory ...\n');
D=dir('*.m');
for fi = 1:length(D)
  copyfile(D(fi).name,[Params.FILENAME '_TEMP']);
  fileattrib(fullfile([Params.FILENAME '_TEMP'],D(fi).name),'-w');
end

%%% Put all of the Params into the Data structure so that you can
%%% change them during the expt and keep the record of what happened.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%  TRIAL LOOP
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%clear global Data

hW.HideGroup(0);

NTRIALS = Params.N_TRIALS ;
Data = dtmp;  %  Do this first or the following assignment will fail.
Data(NTRIALS) = dtmp;

trial=0; done=0; trial_error = 0;
% NJOnPrev = 0;
% NRecOnPrev = 0;
% NTOnPrev = 0;
% NJOffPrev = 0;
% NRecOffPrev = 0;
% NTOffPrev = 0;
% NRecPausePrev = 0;
% NRecResumePrev = 0;
TrialGetActionLog('init');

startTrial = 1;
for itrial = startTrial:Params.N_TRIALS,

  hW.ResetEventLog;

  trial = trial + 1;

  %%%%% Data(trial) = dtmp;  % create data

  %  EXPERIMENT INFO

  %  MORPHOMETRIC DATUMS
  morphoFile = fullfile(Params.DATADIRECTORY,Params.NAME,'MorphometricData.mat');
  if exist(morphoFile,'file')
    ldtmp = load(morphoFile,'morphoData');
    if strcmpi(ldtmp.morphoData.name,Params.NAME)
      Data(trial).morphoData = ldtmp.morphoData;
    elseif trial<10
      fprintf('\n>>>> %s: Not loading Morpho Data; Names don''t match <<<<\n',mfilename);
    end
    clear ldtmp;
  end


  %  TRIAL INFO
  ttProbs = cumsum(Params.TRIAL_TYPE_PROBS);
  ttype = min(find(rand(1)<=ttProbs));
  Data(trial).trialtype       = ttype;
  Data(trial).trial           = trial;

  %  TIME
  Data(trial).absolutetime    = clock;
  Data(trial).expttime = etime(Data(trial).absolutetime,Data(1).absolutetime)/60;%[60 1 1/60]*[Data(trial).absolutetime(4:end)']-[60 1 1/60]*Data(1).absolutetime(4:end)';


  getNoAdaptationShiftFlag = ~Params.doBlocksFlag;  % Default.  This can be changed by the adaptation shift code below.
  if Params.doBlocksFlag
    %if Params.doAdaptationFlag
    if trial == 1
      Data(trial).nthtrialthisblock = 1;
      Data(trial).blocktype = 1;
    else
      prevbt = Data(trial-1).blocktype;
      if Data(trial-1).nthtrialthisblock == (Params.NtrialsPerBlock(prevbt))
        %  switch to next block type
        if (prevbt + 1) > length(Params.blockTypes)
          Data(trial).blocktype = 1;
        else
          Data(trial).blocktype = prevbt + 1;
        end
        Data(trial).nthtrialthisblock = 1;
      else
        %  stay with same block type
        Data(trial).blocktype = prevbt;
        Data(trial).nthtrialthisblock = Data(trial-1).nthtrialthisblock + 1;
      end
    end

    %  switch lower(Params.adaptation.blockTypes{Data(trial).blocktype})
    if Data(trial).nthtrialthisblock == 1
      %  Reset the default parameters so that the only changes are the ones
      %  specified here. (i.e., no leftover changes from other blocks).
      SensIntReaching_Params(0);
      %%%
      thisbtidx = Params.blockTypes(Data(trial).blocktype);
      SensIntReaching_updateParamSettings(Params.BlockSettings(thisbtidx),trial);
    end
  end


  Data(trial).starttargetposfunc = Params.START_TARGET_POS_FUNC;
  Data(trial).reachtargetposfunc = Params.REACH_TARGET_POS_FUNC;
  Data(trial).eyetargetposfunc = Params.EYE_TARGET_POS_FUNC;

  %  Keep track of the Params changes
  Data(trial).params = Params;

  % Start Target
  Data(trial).starttargetwin      = Params.START_TARGET_WIN;
  Data(trial).starttargetwin2      = Params.START_TARGET_WIN_2;
  Data(trial).starttargetwin3      = Params.START_TARGET_WIN_3;
  Data(trial).starttargetrad      = Params.START_TARGET_RAD;
  Data(trial).starttargetrgb      = Params.START_TARGET_RGB;
  Data(trial).starttargetbright   = Params.START_TARGET_BRIGHT;
  Data(trial).starttargetshow     = Params.START_TARGET_SHOW;
  Data(trial).starttargetvelcrit = Params.START_TARGET_VEL_CRIT;

  Data(trial).starttargetfeedback = [];%(rand(1)<= Params.P_START_TARGET_FEEDBACK);
  Data(trial).starttargetfbholddur = rand(1)*(Params.START_TARGET_FB_HOLD_DUR_MAX-Params.START_TARGET_FB_HOLD_DUR_MIN)+Params.START_TARGET_FB_HOLD_DUR_MIN;
  %   Data(trial).starttargetfbholddur = Params.START_TARGET_FB_HOLD_DUR;

  % Reach Target
  Data(trial).reachtargetrad    = Params.REACH_TARGET_RAD;
  Data(trial).reachtargetwin    = [];  %  See below, this is now a function
  Data(trial).reachtargetrgb    = Params.REACH_TARGET_RGB;
  Data(trial).reachtargetbright = Params.REACH_TARGET_BRIGHT;

  % Eye Target
  Data(trial).eyetargetrad    = Params.EYE_TARGET_RAD;
  Data(trial).eyetargetwin    = Params.EYE_TARGET_WIN;
  Data(trial).eyetargetrgb    = Params.EYE_TARGET_RGB;
  Data(trial).eyetargetbright = Params.EYE_TARGET_BRIGHT;


  %  Dot Field
  Data(trial).righthandarrowfieldrgb = Params.rightHandArrowFieldRGB;
  Data(trial).righthandarrowfieldbrightnessfunc = Params.rightHandArrowFieldBrightnessFunc;

  %  Performance feedback params
  Data(trial).donecritspeed           = Params.doneCritSpeed;
  Data(trial).reachbonustau           = Params.reachBonusTau;
  Data(trial).reachbonusfunc          = Params.reachBonusFunc;
  Data(trial).givebonusfeedbackflag   = [];%Params.giveBonusFeedbackFlag;
  Data(trial).randbonusc              = Params.randBonusC;
  Data(trial).reachbonus              = 0;  %  Initialize to zero.

  % Rewards
  Data(trial).smallreward         = Params.SMALL_REWARD;
  Data(trial).largereward         = Params.LARGE_REWARD;
  Data(trial).intermediaterewards = Params.INTERMEDIATE_REWARDS;

  % Delay and times
  Data(trial).starttargethold           = Params.START_TARGET_HOLD;
  Data(trial).reachtargethold           = Params.REACH_TARGET_HOLD;
  Data(trial).eyetargethold             = Params.EYE_TARGET_HOLD;
  Data(trial).maxmovetimetostarttarget  = Params.MAX_MOVE_TIME_TO_START_TARGET;

  Data(trial).eyetargettimeout          = Params.EYE_TARGET_TIMEOUT;

  Data(trial).intertrialdelay           = Params.INTER_TRIAL_DELAY;

  if Data(trial).trialtype == 1
    if 1 %Params.useRandomTargetsFlag & (Params.P_randomTarget>=rand(1))  % Non test trials
      Data(trial).fbshift = [0 0];
      %  Visual BLuR
      %vbki = unidrnd(length(Params.visBlur));%1;
      vbki = min(find(cumsum(Params.P_visFB)>=rand(1)));
      %vbki = 1;
      Data(trial).minreachdistance = Params.MIN_REACH_DISTANCE;
      Data(trial).starttargetpos = eval(Data(trial).starttargetposfunc);
      rdist = 0;
      while rdist < Data(trial).minreachdistance
        Data(trial).reachtargetpos = eval(Data(trial).reachtargetposfunc);
        rdist = norm(Data(trial).reachtargetpos - Data(trial).starttargetpos);
      end

      Data(trial).test = 0;
      %       if rand(1)<=Params.P_FullFeedback
      %        % Data(trial).fboffreachproportion = inf;
      %         Data(trial).fboffreachdistance = inf;
      %         vbki = 1;  %
      %       end
    else
      %  Test trials
    end
    Data(trial).visFB = Params.visFB(vbki);
    Data(trial).reachtargetwin    = Params.REACH_TARGET_WIN_FUNC(Data(trial).reachtargetrad,Data(trial).visFB.rad);
    % Feedback
    Data(trial).feedbackfngrad    = Data(trial).visFB.rad;
    Data(trial).feedbackfngbright = Data(trial).visFB.bright;
    Data(trial).fngfeedbackfunc   = Data(trial).visFB.FBFunc;
    Data(trial).fbonreachproportion  = Params.FBonReachProportion;
    %    Data(trial).fboffreachproportion  = Params.FBoffReachProportion;
    Data(trial).fboffreachdistance  = Params.FBoffReachDistance;

    %% Print Some Stuff
    fprintf('%d/%d - VB: %i, FBshift: [%0.2f %0.2f] - ',trial,NTRIALS,vbki,Data(trial).fbshift);
    %fprintf('P%d/T%d - ',iPath,i);
    %fprintf('Move %d-%d - ',startID,stopID);
  elseif Data(trial).trialtype == 2
    Data(trial).reachtargetpos = eval(Data(trial).reachtargetposfunc);
    Data(trial).visFB = Params.visFB(1);
    Data(trial).feedbackfngrad    = Data(trial).visFB.rad;
    Data(trial).feedbackfngbright = Data(trial).visFB.bright;
    Data(trial).fngfeedbackfunc   = Data(trial).visFB.FBFunc;
    Data(trial).reachtargetwin    = Params.REACH_TARGET_WIN_FUNC(Data(trial).reachtargetrad,Data(trial).visFB.rad);
  elseif Data(trial).trialtype == 3
    Data(trial).eyetargetpos = eval(Data(trial).eyetargetposfunc);
    Data(trial).eyetargethold = Params.EYE_TARGET_HOLD_2;
  elseif Data(trial).trialtype == 4
    Data(trial).eyetargetpos = eval(Data(trial).eyetargetposfunc);
    Data(trial).starttargetpos = eval(Data(trial).starttargetposfunc);
    %Data(trial).eyetargethold = 0.5
  elseif Data(trial).trialtype == 5
    Data(trial).mineyetoreachdistance = Params.MIN_EYE_TO_REACH_DISTANCE;
    Data(trial).starttargetpos = eval(Data(trial).starttargetposfunc);
    Data(trial).eyetargetpos = eval(Data(trial).eyetargetposfunc);
    erdist = 0;
    while erdist < Data(trial).mineyetoreachdistance
      Data(trial).reachtargetpos = eval(Data(trial).reachtargetposfunc);
      erdist = norm(Data(trial).reachtargetpos - Data(trial).eyetargetpos);
    end
    Data(trial).reachtrgshowdur = Params.reachTrgShowDur;
    Data(trial).reachtargetbright = Data(trial).reachtargetbright*Params.reachTrgBrightMultiplier; % Dim it for fix learning
  elseif Data(trial).trialtype == 6  %  Hold, Fixate, Reach

    %dat.nominalreachdirection
    Data(trial).enforceFixationFlag = 1;  %  Default setting.  May be changed below.
    Data(trial).minreachdistance = Params.MIN_REACH_DISTANCE;
    Data(trial).mineyetoreachdistance = Params.MIN_EYE_TO_REACH_DISTANCE;
    Data(trial).maxreachdistance = Params.MAX_REACH_DISTANCE;

    isTest = (rand(1) <= Params.P_TestTrial);
    if isTest
      if 0 %rand(1)<0.4
        Data(trial).nominalreachdirection =  Params.adaptation.trainDirs(unidrnd(length( Params.adaptation.trainDirs),1,1));
      else
        Data(trial).nominalreachdirection = Params.reachdirs(unidrnd(length(Params.reachdirs),1,1));
      end
    else
      if ~isempty(Params.NonTestTrialGetTrgFunc)
        Data(trial).nominalreachdirection = -pi + rand(1)*2*pi;
      else
        Data(trial).nominalreachdirection = -pi + rand(1)*2*pi;
      end

    end

    %  rchvct = Data(trial).reachtargetpos - Data(trial).starttargetpos;
    Data(trial).givebonusfeedbackflag = 1; %  Default value.  Can be changed below.

    %  Visual FB
    %vbki = unidrnd(length(Params.visFB));%1;
    vbki = min(find(cumsum(Params.P_visFB)>=rand(1)));
    %vbki = 1;
    %    Data(trial).reachtrgshowdur = Params.reachTrgShowDur;
    Data(trial).visFB = Params.visFB(vbki);
    Data(trial).reachtargetwin    = Params.REACH_TARGET_WIN_FUNC(Data(trial).reachtargetrad,Data(trial).visFB.rad);
    % Feedback
    Data(trial).feedbackfngrad    = Data(trial).visFB.rad;
    Data(trial).feedbackfngbright = Data(trial).visFB.bright;
    Data(trial).fngfeedbackfunc   = Data(trial).visFB.FBFunc;
    Data(trial).starttargetfeedback = (rand(1)<= Data(trial).visFB.P_starttargetfeedback);


    if Params.doBlocksFlag
      if Params.adaptationOnFlag
        Data(trial).adaptationonflag = 1;
        uaprf = ~(rand(1) > Params.adaptation.PadaptationParams);
        %  If this is the first trial in this block then force use of adaptation
        %  params.
        Data(trial).usingadaptationparamsflag = (uaprf | (Data(trial).nthtrialthisblock == 1));

        if ~Data(trial).usingadaptationparamsflag
          %         case 'noshift'
          %           Data(trial).fbshift = [0 0];
          %         case {'shift+noshift'; 'noshift+shift'}
          Data(trial).starttargetfeedback = 1;  %  If he's adapted but we're going to choose a non-adapted shift, then he needs to be able to see it.
          getNoAdaptationShiftFlag = 1;
          %         case 'shift'
        else
          if ~(Data(trial).nthtrialthisblock == 1)
            okflag = 0; gobackn = 1;
            lastadaptparamtrial = [];
            while ~okflag
              lastadaptparamtrial = trial-gobackn;
              if Data(trial-gobackn).usingadaptationparamsflag == 1
                okflag=1;
              end
              gobackn = gobackn + 1;
            end
          end

          if Params.adaptation.doRelativeShiftFlag
            if Data(trial).nthtrialthisblock == 1
              %  Pick a new shift dir and dist
              shdirlist = Params.adaptation.shiftparams{1};
              shdistlist = Params.adaptation.shiftparams{2};
              %shdirlist = Data(trial).visFB.shiftparams{1};
              %shdistlist = Data(trial).visFB.shiftparams{2};
              whdir = unidrnd(length(shdirlist),1,1);
              shdist = min(shdistlist) + rand(1).*range(shdistlist);
              if Params.adaptation.WashInFlag
                nwis = Params.NtrialsPerBlock(Data(trial).blocktype);
                shdist = shdist*(1/nwis); %
              end
              shdir = shdirlist(whdir);
            else
              shdir = Data(trial-1).relativeshiftdirection;
              if Params.adaptation.WashInFlag
                nttb = Data(trial).nthtrialthisblock;
                shdist = norm(Data(lastadaptparamtrial).fbshift) + norm(Data(trial-(nttb-1)).fbshift);
              else
                shdist = norm(Data(lastadaptparamtrial).fbshift);
              end
            end
            Data(trial).relativeshiftdirection = shdir;  %  Direction of shift relative to reach dir
            %[rang,dum] = cart2pol(rchvct(1),rchvct(2));
            rang = Data(trial).nominalreachdirection;
            sang = rang + shdir;  %  make it relative to reach dir
            [shx,shy] = pol2cart(sang,shdist);
            Data(trial).fbshift = [shx shy];
          else
            if Data(trial).nthtrialthisblock == 1
              %  Pick a new shift
              shdirlist = Params.adaptation.shiftparams{1};
              shdistlist = Params.adaptation.shiftparams{2};
              %               shdirlist = Data(trial).visFB.shiftparams{1};
              %               shdistlist = Data(trial).visFB.shiftparams{2};
              whdir = unidrnd(length(shdirlist),1,1);
              shdist = min(shdistlist) + rand(1).*range(shdistlist);
              if Params.adaptation.WashInFlag
                nwis = Params.NtrialsPerBlock(Data(trial).blocktype);
                shdist = shdist*(1/nwis); %
              end
              shdir = shdirlist(whdir);
              [shx,shy] = pol2cart(shdir,shdist);
              Data(trial).fbshift = [shx shy];
            else
              if Params.adaptation.WashInFlag
                nttb = Data(trial).nthtrialthisblock;
                shdist = norm(Data(lastadaptparamtrial).fbshift) + norm(Data(trial-(nttb-1)).fbshift);
                prevshift = Data(lastadaptparamtrial).fbshift;
                Data(trial).fbshift = shdist*(prevshift/norm(prevshift));  %  Keep the direction, rescale
              else
                Data(trial).fbshift = Data(lastadaptparamtrial).fbshift;
              end
            end
          end
          %         otherwise
          %           error('Unknown block type');
          %end


          if ~isempty(Params.adaptation.trainDirs)
            %  If we're doing adaptation with training only in certain reach
            %  directions, look to see if the current reach direction is one of the
            %  training directions. (they may not be exactly equal due to round-off error, so test for
            %  equality with some tolerance).
            istraindir = abs(angleminus(repmat(Data(trial).nominalreachdirection,size(Params.adaptation.trainDirs)),Params.adaptation.trainDirs))<=1e-10;

            if ~any(istraindir)  % then this must be a test direction trial
              %  If we're doing adaptation with training only in certain reach
              %  directions then we don't want to give endpoint feedback on any
              %  trials in the test (i.e., non-training) directions.  But we want to
              %  draw rewards from the baseline visFB- test direction
              %  trials.
              getEndPointFBConditions(trial,4);
              %  And don't give start target feedback on any adapted test
              %  direction trials.
              Data(trial).starttargetfeedback = 0;
            end
          end

        end

      else
        getNoAdaptationShiftFlag = 1;
      end

    end

    if getNoAdaptationShiftFlag
      %  No adaptation (or a no adaptation block of an expt with
      %  adaptation)
      if (rand(1) <= Data(trial).visFB.zeroshiftproportion)%%% | ~Data(trial).starttargetfeedback
        Data(trial).fbshift = [0 0];
        Data(trial).relativeshiftdirection = [];
      else
        %  If this is an adaptation block and we've selected a non-adapted
        %  shift then we've already set the starttargetfeedback=1.
        %  If we're in a non-adapted block and this is a shift trial (which it must be at this point),
        %  then we want the starttargetfeedback=1, so set it.
        Data(trial).starttargetfeedback = 1;
        %  Note: Obviously this means that the only time in which the
        %  Pstarttargetfeedback parameter takes effect is in the case of a
        %  non-adaptation non-shift trial.
        %%%
        if isempty(Data(trial).visFB.shiftdistfunc)
          shdirlist = Data(trial).visFB.shiftparams{1};
          shdistlist = Data(trial).visFB.shiftparams{2};
          whdir = unidrnd(length(shdirlist),1,1);
          shdist = min(shdistlist) + rand(1).*range(shdistlist);
          shdir = shdirlist(whdir);
          if Params.doRelativeShiftFlag
            % [rang,dum] = cart2pol(rchvct(1),rchvct(2));
            rang = Data(trial).nominalreachdirection;
            sang = rang + shdir;
            [shx,shy] = pol2cart(sang,shdist);
            Data(trial).relativeshiftdirection = shdir;
          else
            [shx,shy] = pol2cart(shdir,shdist);
          end
          Data(trial).fbshift = [shx shy];
          if (trial > 1) &  (Data(trial).visFB.zeroshiftproportion > 0.5)
            %  If he experienced a shift on the last (correct) trial, then we don't want one now.
            netrlidx = find([Data(1:trial-1).err]==0); %

            if ~isempty(netrlidx) & any(Data(max(netrlidx)).fbshift)
              Data(trial).fbshift = [0 0];
            end
          end
        else
          Data(trial).fbshift = Data(trial).visFB.shiftdistfunc(Data(trial).visFB.shiftparams{:});
        end
      end

      if Params.randomShiftTrialBonusFlag
        % Note: Because these are set in here, they apply to non-adapted
        % blocks only.  Analogous adapted stuff is set above.
        %
        %  If we're not giving endpoint feedback on shift trials
        if sum(abs(Data(trial).fbshift))
          %  If there's a shift then give random reward (drawn from no-shift/visFB+ trial
          %  rewards) and don't show the endpoint feedback.
          gefcaction = 3;
        else
          if ~isempty(Params.adaptation.trainDirs)
            %  If we're doing adaptation with training only in certain reach
            %  directions, look to see if the current reach direction is one of the
            %  training directions. (they may not be exactly equal due to round-off error, so test for
            %  equality with some tolerance).
            istraindir = abs(angleminus(repmat(Data(trial).nominalreachdirection,size(Params.adaptation.trainDirs)),Params.adaptation.trainDirs))<=1e-10;
          end
          if ~isempty(Params.adaptation.trainDirs) & ~any(istraindir) & ~Data(trial).starttargetfeedback
            %  If we're doing adaptation with training only in certain reach
            %  directions then we don't want to give endpoint feedback on visFB-
            %  trials in the test (i.e., non-training) directions.
            Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
            Data(trial).distanceerrorforreward = nan;  %  This will cause the trial func to use the actual error for the reward
            gefcaction = 0;
          else
            %  If this is a no-shift trial but we are withholding endpoint feedback
            %  for some percentage of no-shift trials.
            gefcaction = 2;
          end
        end
        if gefcaction
          getEndPointFBConditions(trial,gefcaction);
        end
        % % %                 if sum(abs(Data(trial).fbshift))  % If we're giving random bonus for shift trials and there's a shift
        % % %                     Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
        % % %                     %  Choose the reward amount from the no shift trial distribution
        % % %                     nenstrlidx = find(([Data(1:trial-1).err]==0) & ~sum(abs(cat(1,Data(1:trial-1).fbshift)))); %
        % % %                     if ~isempty(nenstrlidx)
        % % %                         eperr = cat(1,Data(nenstrlidx).disterr);
        % % %                         Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
        % % %                     else
        % % %                         %  If there aren't any previous correct no shift trials then just pick an
        % % %                         %  arbitrary error.
        % % %                         Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
        % % %                     end
        % % %                 else % If we're giving random bonus for shift trials and there's no shift
        % % %                     if rand(1) <= Params.P_noShiftTrialNoEndptFBFlag  %  This percentage of no shift trials will have no visual endpt FB
        % % %                         Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
        % % %                         Data(trial).distanceerrorforreward = nan;  %  This will cause the trial func to use the actual error
        % % %                     else
        % % %                         Data(trial).givebonusfeedbackflag = 1;  %
        % % %                     end
        % % %                 end
      end
    end


    %%%%
    if isTest
      Data(trial).test = 1;
      %   if (Data(trial).trialtype == 6) && (Data(trial).test == 1)
      [st,rt,et,swi,nomhc,nomrv,rflidx] = SIRGetTestTrialTargs(Params,Data(trial));
      Data(trial).relativefixationlocationidx = rflidx;
      Data(trial).starttargetpos = st;
      Data(trial).reachtargetpos = rt;
      if isempty(et)
        Data(trial).eyetargetpos = rt;  %  Fixate the reach target
      elseif any(isnan(et))
        Data(trial).eyetargetpos = et;
        Data(trial).enforceFixationFlag = 0;
      else
        Data(trial).eyetargetpos = et;
      end
      Data(trial).whichSubWorkspace = swi;
      Data(trial).nominalhandcenter = nomhc;
      Data(trial).nominalreachvect = nomrv;
      % end
    else
      if ~isempty(Params.NonTestTrialGetTrgFunc)
        [st,rt,et,nomrv,rflidx] = feval(Params.NonTestTrialGetTrgFunc,Params,Data(trial));
        Data(trial).relativefixationlocationidx = rflidx;
        Data(trial).starttargetpos = st;
        Data(trial).reachtargetpos = rt;
        Data(trial).eyetargetpos = et;
        Data(trial).nominalreachvect = nomrv;
        if any(isnan(et))
          Data(trial).enforceFixationFlag = 0;
        end
      else
        Data(trial).eyetargetpos = eval(Data(trial).eyetargetposfunc);
        esdist = 0;
        while (esdist < Params.MIN_EYE_TO_START_DISTANCE)
          Data(trial).starttargetpos = eval(Data(trial).starttargetposfunc);
          esdist = norm(Data(trial).eyetargetpos - Data(trial).starttargetpos);
        end

        if Params.fixateReachTrgFlag
          Data(trial).reachtargetpos = Data(trial).eyetargetpos;
        else
          erdist = 0;rdist = 0;
          while (erdist < Data(trial).mineyetoreachdistance) | (rdist < Data(trial).minreachdistance) | (rdist > Data(trial).maxreachdistance)
            Data(trial).reachtargetpos = eval(Data(trial).reachtargetposfunc);
            erdist = norm(Data(trial).reachtargetpos - Data(trial).eyetargetpos);
            rdist = norm(Data(trial).reachtargetpos - Data(trial).starttargetpos);
          end
        end
        if Params.fixateRelativeToReachTrgFlag  %  Kloogy retrofit
          pidx = find(mnrnd(1,Params.P_relativeFixationLoc));
          Data(trial).eyetargetpos = Params.relativeFixationEyePosFunc(Data(trial).starttargetpos, ...
            Data(trial).reachtargetpos,Params.relativeFixationLocParams{pidx});
        end
      end

    end



    %%%%


    if length(Params.FBonReachProportion)==1
      Data(trial).fbonreachproportion  = Params.FBonReachProportion;
    else
      thisfborp = find(mnrnd(1,Params.P_FBonRP,1));
      Data(trial).fbonreachproportion = Params.FBonReachProportion(thisfborp);
    end
    %    Data(trial).fboffreachproportion  = Params.FBoffReachProportion;
    Data(trial).fboffreachdistance  = Params.FBoffReachDistance;

    if ~noFigsFlag
      sv = circleVerts(Data(trial).starttargetpos(:),Data(trial).starttargetwin);
      rv = circleVerts(Data(trial).reachtargetpos(:),Data(trial).reachtargetwin);
      ev = circleVerts(Data(trial).eyetargetpos(:),Data(trial).eyetargetwin);
      figure(99);
      set(gcf,'position',[28   366   348   286]);
      %     ud = get(gcf,'userdata');
      %     if isempty(ud)
      %       set(gcf,'name','Trial Type 6');
      %       ud.sp = 1;
      %       set(gcf,'userdata',ud);
      %     else
      %       ud.sp = ud.sp + 1;
      %       set(gcf,'userdata',ud);
      %     end
      %
      %     subplot(2,1,mod(ud.sp,2)+1);
      thisshift = Data(trial).fbshift;
      cla;
      plot(sv(1,:),sv(2,:),'b');
      hold on;
      plot(sv(1,:)+thisshift(1),sv(2,:)+thisshift(2),'c--');
      plot(rv(1,:),rv(2,:),'g');
      plot(ev(1,:),ev(2,:),'r');
      rectangle('position',[min(Params.wsBounds,[],1) range(Params.wsBounds,1)]);
      axis equal;
      drawnow;
    end


  elseif Data(trial).trialtype == 7
    Nfixtargs = find(mnrnd(1,Params.Nfixtargspertrial));
    fprintf('Trial Type #7.  %i fixation targets.',Nfixtargs);
    %  Possible eye targets
    allswscenters = cat(1,Params.subWorkspace(:).center);
    eyetargpossibles = allswscenters;
    eyetargpossibles = [eyetargpossibles; mean(allswscenters,1)];
    eyetargpossibles = [eyetargpossibles; ...
      Params.subWorkspace(1).center + [-Params.reachradius Params.reachradius]; ...
      Params.subWorkspace(1).center + [-Params.reachradius -Params.reachradius]; ...
      Params.subWorkspace(2).center + [Params.reachradius Params.reachradius]; ...
      Params.subWorkspace(2).center + [Params.reachradius -Params.reachradius]...
      ];
    %  Possible hand targets
    handtargpossibles = eyetargpossibles;
    %  Choose hand target uniformly
    Data(trial).starttargetpos = handtargpossibles(unidrnd(size(handtargpossibles,1)),:);
    %  Choose eye target(s) uniformly.  Don't allow any eye target to follow immediately after itself in the
    %  sequence.  i.e., the eye must move each time.
    grabetidx = [0 0];
    while any(diff(grabetidx)==0)
      grabetidx = unidrnd(size(eyetargpossibles,1),Nfixtargs,1);
    end
    Data(trial).eyetargetpos = eyetargpossibles(grabetidx,:);
    Data(trial).visFB = Params.visFB(1);
    Data(trial).feedbackfngrad    = Data(trial).visFB.rad;
    Data(trial).feedbackfngbright = Data(trial).visFB.bright;
    Data(trial).fngfeedbackfunc   = Data(trial).visFB.FBFunc;
    Data(trial).starttargetfeedback = (rand(1)<= Data(trial).visFB.P_starttargetfeedback);
    Data(trial).eyetargethold = Params.EYE_TARGET_HOLD_7;
    Data(trial).eyetargettimeout = [Params.EYE_TARGET_TIMEOUT_71 Params.EYE_TARGET_TIMEOUT_72];
  end  %% END IF trialtype



  fprintf('\nTrial type: %i\n',Data(trial).trialtype);
  if NO_ISCAN
    fprintf('\n\nWARNING:  NOT USING ISCAN !!!!!!\n\n');
  end

  %%%  -------------------------------------------------
  %%  - - - - - -  RUN TRIAL - - - - - - - - - - RUN TRIAL - - - - - -

  Data(trial).TDTTimeAtTrialStart = TimeSyncGetTimeMs;  %  Grab the expt time just before the trial starts.

  switch Data(trial).trialtype
    case 1
      Data(trial) = SensIntReaching_Trial( Data(trial) );
    case 2
      Data(trial) = JustReach_Trial( Data(trial) );
    case 3
      Data(trial) = LearnToFixate_Trial(Data(trial));
    case 4
      Data(trial) = LearnToFixate_Trial_w_HandHold(Data(trial));
    case 5
      Data(trial) = LearnToFixate_Trial_w_HandHold_2(Data(trial));
    case 6
      Data(trial) = Hold_Fixate_Reach_Trial(Data(trial));
      % Data(trial) = TEST_trial(Data(trial));
    case 7
      Data(trial) = Hold_MultiFixate_Trial(Data(trial));
    otherwise
      error('Unknown Trial Type');
  end

  hW.HideGroup(0);

  %%%  - - - - - END RUN TRIAL  - - - - - - - - - - - - - -
  %%%  ---------------------------------------------------

  %%%  - - - -  GET EVENT LOG  - - - -
  %
  Data(trial).matlabeventlog = TrialGetActionLog(hW,Params.EventCodes,Data(trial).matlabeventlog);

  %  Data(trial).matlabeventlog = [TrialGetActionLog(hW); Data(trial).matlabeventlog];

  %%% ----------------------------------------------

  %%%  --------------------------------------------------
  %%% - - - -  TRIAL SUMMARY INFO DISPLAY  - - - - - - - - - -

  %% Print More Stuff
  fprintf('Err %d: %s \n',Data(trial).err,Data(trial).errstring);
  try
    fprintf('Blocktype: %i\n',Params.blockTypes(Data(trial).blocktype));
    fprintf('FB: %i\n',Data(trial).starttargetfeedback);
    fprintf('Shift: [%0.2f %0.2f]\n',Data(trial).fbshift);
    fprintf('Disterr: %0.3f; Reach bonus: %0.3f;\n',Data(trial).disterr,Data(trial).reachbonus);
  end
  fprintf('Juice: %0.3f\n\n',Data(trial).totalreward);
  if NO_ISCAN
    fprintf('\n\nWARNING:  NOT USING ISCAN !!!!!!\n\n');
  end

  %Data(trial).actionlog

  %% --------------------------------------
  %%  - - - - - - - SUMMARY FIGURES - - - - - - - - - -
  %% -------------------------------------------------
  if ~noFigsFlag
    if Data(trial).trialtype == 6
      trialType6Plot;
    end
    if Data(trial).trialtype == 7
      trialType7Plot;
    end

    errlist = [Data(:).err];
    trialTypeList = [Data(:).trialtype];
    %% Update Error Summary figure
    if trial > 1 %5
      %     if ~exist('errSummH') | ~ishandle(errSummH)
      %       errSummH = figure;
      %       set(errSummH,'position',[646   708   615   225],'name','Trial Error Summary');
      %     else
      %       figure(errSummH);
      %     end
      %     if length(unique(errlist))>1
      %       [eC,ebc] = hist(errlist,unique(errlist));
      %       bar(ebc,eC);
      %       ylabel('N trials');
      %       xlabel('Error');
      %       title(sprintf('Error Summary (after %i trials)',trial));
      %     end

      %  Correct trial times figure
      if ~exist('crctTrialTimeH') | ~ishandle(crctTrialTimeH)
        crctTrialTimeH = figure;
        %        set(gcf,'position',[181         404        1081         224]);
        set(gcf,'position',[614   666   809   155]);
        cttAx1 = axes;
        cttAx2 = axes('Position',get(cttAx1,'Position'));
      else
        figure(crctTrialTimeH);
      end
      set(gcf,'currentaxes',cttAx1);
      ctidx = find(errlist==0);
      ctetimes = cat(1,Data(ctidx).expttime);
      plot([0;ctetimes], [0:length(ctidx)],'.-');
      xlims = get(gca,'xlim');
      set(gca,'xlim',[0 Data(trial).expttime]);
      xlabel('Expt Time (mins)');
      ylabel('# Correct Trials');
      title(sprintf('%i correct trials; %0.1f total reward time',length(ctidx),sum([Data(:).totalreward])));

      set(gcf,'currentaxes',cttAx2);
      plot(cat(1,Data(:).expttime),cat(1,Data(:).largereward),'r--');
      ylabel('Large reward setting');
      set(gca,'xticklabel','','xlim',get(cttAx1,'xlim'), ...
        'YAxisLocation','right',...
        'Color','none',...
        'YColor','r','Position',get(cttAx1,'Position'));
      % ----------

      %     %  Inter-trial delay figure
      %     if ~exist('intertrialdelayH') | ~ishandle(intertrialdelayH)
      %       intertrialdelayH = figure;
      %       set(gcf,'position',[181         635        1081         200]);
      %     else
      %       figure(intertrialdelayH);
      %     end
      %     plot(cat(1,Data(1:trial).expttime),cat(1,Data(1:trial).intertrialdelay),'k');
      %     xlabel('Expt Time (mins)');
      %     ylabel('Inter-trial delay (ms)');
      %     %  ------------

      if 1
        if 0
          %  Summary of hand target locations figure
          if ~exist('tgtLocH') | ~ishandle(tgtLocH)
            tgtLocH = figure;
            set(gcf,'position',[762    43   447   282],'name','Target Location Summary');
          else
            figure(tgtLocH);
          end
          startposes = cat(1,Data(:).starttargetpos);
          reachposes = cat(1,Data(:).reachtargetpos);
          %  [Xmin Ymin; Xmax Ymax]
          pidx = [trialTypeList~=3 & errlist==0];
          if any(pidx) %any(errlist~=1)
            stp = cat(1,Data(pidx).starttargetpos);
            rtp = cat(1,Data(pidx).reachtargetpos);
            if ~isempty(stp)
              plot(stp(end,1),stp(end,2),'go');
              hold on;
            end
            if ~isempty(rtp)
              plot(rtp(end,1),rtp(end,2),'ro');
              hold on
            end
            %plot(startposes(errlist~=1,1),startposes(errlist~=1,2),'go');
            %plot(reachposes(errlist~=1&errlist~=4,1),reachposes(errlist~=1&errlist~=4,2),'ro');
          end
          hold on;
          % set(gca,'ydir','reverse');
          pidx = [trialTypeList==1 & errlist==1];
          if any(pidx) %any(errlist==1)
            stp = cat(1,Data(pidx).starttargetpos);
            plot(stp(end,1),stp(end,2),'gs');
            hold on;
            %plot(startposes(errlist==1,1),startposes(errlist==1,2),'gs');
          end

          pidx = [trialTypeList==1 & errlist==4];
          if any(pidx) %any(errlist==1)
            rtp = cat(1,Data(pidx).reachtargetpos);
            plot(rtp(end,1),rtp(end,2),'rs');
            hold on;
            %plot(startposes(errlist==1,1),startposes(errlist==1,2),'gs');
          end

          %             if any(errlist==4)
          %                 plot(reachposes(errlist==4,1),reachposes(errlist==4,2),'rs');
          %             end
          % legend('start acq''d', 'start ~acq''d','reach acq''d','reach ~acq''d','Location','Best');
          wsb = Params.wsBounds;
          bboxH = line([wsb(1) wsb(1) wsb(2,1) wsb(2,1); wsb(1,1) wsb(2,1) wsb(2,1) wsb(1,1)], ...
            [wsb(1,2) wsb(2,2) wsb(2,2) wsb(1,2); wsb(2,2) wsb(2,2) wsb(1,2) wsb(1,2)]);
          set(bboxH,'color',[0 0 0]);
          xlabel('X'); ylabel('Y');
          title('Locations of acquired hand targets');
          axis equal;
        end
      end

      if 0
        %  Summary of EYE target locations figure
        if ~exist('eyeTgtLocH') | ~ishandle(eyeTgtLocH)
          eyeTgtLocH = figure;
          set(gcf,'position',[378    66   447   282],'name','Eye Target Location Summary');
        else
          figure(eyeTgtLocH);
        end
        %eyetargetposes = cat(1,Data(:).eyetargetpos);

        %  [Xmin Ymin; Xmax Ymax]
        eyeTrgTrials = [trialTypeList==3 | trialTypeList==4 | trialTypeList==5];
        pidx = [eyeTrgTrials & errlist==0];%setdiff([trialTypeList==3 & errlist~=21],0);
        if any(pidx)
          etp = cat(1,Data(pidx).eyetargetpos);
          plot(etp(end,1),etp(end,2),'go');
          hold on;
          %plot(reachposes(errlist~=1&errlist~=4,1),reachposes(errlist~=1&errlist~=4,2),'ro');
        end
        hold on;
        % set(gca,'ydir','reverse');
        pidx = [eyeTrgTrials & errlist==21];%setdiff([trialTypeList==3 & errlist==21],0);
        if any(pidx)
          etp = cat(1,Data(pidx).eyetargetpos);
          plot(etp(end,1),etp(end,2),'rs');
          hold on;
        end
        %             if any(errlist==4)
        %                 plot(reachposes(errlist==4,1),reachposes(errlist==4,2),'rs');
        %             end
        % legend('start acq''d', 'start ~acq''d','reach acq''d','reach ~acq''d','Location','Best');
        wsb = Params.wsBounds;
        bboxH = line([wsb(1) wsb(1) wsb(2,1) wsb(2,1); wsb(1,1) wsb(2,1) wsb(2,1) wsb(1,1)], ...
          [wsb(1,2) wsb(2,2) wsb(2,2) wsb(1,2); wsb(2,2) wsb(2,2) wsb(1,2) wsb(1,2)]);
        set(bboxH,'color',[0 0 0]);
        xlabel('X'); ylabel('Y');
        title('Locations of acquired eye targets');
        axis equal;
        %        keyboard
      end
    end
  end
  %%  -----------------------------------------------------------------------
  %%  ------------------------ End Figures
  %%  --------------------------------------------------------


  %% Save to TEMP file
  eval(sprintf('DATA_%d = Data(%d);',trial,trial));
  eval(sprintf('save %s_TEMP/DATA_%d DATA_%d',Params.FILENAME,trial,trial));
  eval(sprintf('clear DATA_%d;',trial));

  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % GUI Functions on press button
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  drawnow;
  while( pauseFlag | keyboardFlag ),
    if(keyboardFlag) keyboard; keyboardFlag=0; end
    pause(.1);
  end

  %   %%% Restart button
  %   if (restartFlag),
  %     restartinp = input('Are you sure you want to restart this task without saving the data? (Y/N)', 's');
  %     if (restartinp == 'Y'),
  %       restarttemp = 1;
  %     else
  %       restarttemp = 0;
  %     end
  %     eval(sprintf('!del /Q %s_TEMP\\*.*',Params.FILENAME));
  %     eval(sprintf('save %s_TEMP/VARS Params TimeStamp',Params.FILENAME));
  %     restartFlag = 0;
  %   end

  %     if (newfileFlag),
  %         newfileinp = input('Are you sure you want to restart this task and save old data to file? (Y/N)', 's');
  %         if (newfileinp == 'Y'),
  %             newfiletemp = 1;
  %         else
  %             newfiletemp = 0;
  %         end
  %
  %         if newfiletemp,
  %             ct=1;
  %             fname = sprintf('ReachTuning_%s-%s-%d',Params.NAME,date,ct);
  %             while( exist([fname,'.mat']) | exist([fname,'_TEMP']) )
  %                 ct=ct+1;
  %                 fname = sprintf('ReachTuning_%s-%s-%d',Params.NAME,date,ct);
  %             end
  %             Params.FILENAME = sprintf('ReachTuning_%s-%s-%d',Params.NAME,date,ct);
  %             eval(sprintf('!mkdir %s_TEMP',Params.FILENAME));
  %             eval(sprintf('save %s_TEMP/VARS Params TimeStamp',Params.FILENAME));
  %             fprintf('Data will be stored to file %s\n\n',Params.FILENAME);
  %         end
  %         newfileFlag = 0;
  %     end
  %
  %     if (restarttemp | newfiletemp),
  %         trial = 0;
  %         trial_error = 0;
  %         iPath = 1;
  %         i = 0;
  %         clear Data;
  %         restarttemp = 0;
  %         newfiletemp = 0;
  %     end
  %
  %     if (newcalibFlag),
  %         while (newcalibFlag)
  %             calibFile = input('Please input the name of an eye calibration \n','s');
  %             tempname = sprintf('C:\\Lab\\matlab\\MonkeyEyeCalib\\%s_EyeCal.mat',calibFile);
  %             newcalibFlag = ~exist(tempname);
  %         end
  %         EyeLoadCalibration(calibFile);
  %         fprintf('Load Eye Tracker Calibration File: %s_EyeCal.mat... \n',...
  %             calibFile);
  %     end

  if(done) break; end

end % end loop over N_TRIALS

Data((trial+1):end)=[];  %% Get rid of rest



%% - - - - - - -   Subroutines   - - - - - - - -
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% UTILITY FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function getEndPointFBConditions(trial,action)

global Params
global Data savedData

if isempty(savedData)
  savedData = Data;
  oldDataEndIdx = trial-1;
else
  oldDataEndIdx = length(savedData);
end

switch action%%%if sum(abs(Data(trial).fbshift))  % If we're giving random bonus for shift trials and there's a shift
  case 1
    Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
    %  Choose the reward amount from the no shift trial distribution
    nenstrlidx = find(([savedData(1:oldDataEndIdx).err]==0) & ~sum(abs(cat(1,savedData(1:oldDataEndIdx).fbshift)))); %
    if ~isempty(nenstrlidx)
      eperr = cat(1,savedData(nenstrlidx).disterr);
      Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
    else
      %  If there aren't any previous correct no shift trials then just pick an
      %  arbitrary error.
      Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
    end
  case 2 % If we're giving random bonus for shift trials and there's no shift
    if rand(1) <= Params.P_noShiftTrialNoEndptFBFlag  %  This percentage of no shift trials will have no visual endpt FB
      Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
      Data(trial).distanceerrorforreward = nan;  %  This will cause the trial func to use the actual error
    else
      Data(trial).givebonusfeedbackflag = 1;  %
    end
  case 3
    Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
    if trial > 1
      %  Choose the reward amount from the no shift/ visFB- trial distribution
      nenstrlidx = intersect(find(([savedData(1:oldDataEndIdx).err]==0)), find(~sum(abs(cat(1,savedData(1:oldDataEndIdx).fbshift)),2))); %
      nstfbidx = find([savedData(1:oldDataEndIdx).starttargetfeedback]==0);
      grabidx = intersect(nenstrlidx,nstfbidx);
    else
      grabidx = [];
    end
    if ~isempty(grabidx)
      eperr = cat(1,savedData(grabidx).disterr);
      Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
    else
      %  If there aren't any previous correct no shift trials then just pick an
      %  arbitrary error.
      Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
    end
  case 4
    Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
    %  Choose the reward amount from the no shift / visFB- / test direction trial distribution
    nenstrlidx = intersect(find(([savedData(1:oldDataEndIdx).err]==0)), find(~sum(abs(cat(1,savedData(1:oldDataEndIdx).fbshift)),2))); %
    nstfbidx = find([savedData(1:oldDataEndIdx).starttargetfeedback]==0);
    grabidx = intersect(nenstrlidx,nstfbidx);

    nomrdirs = [savedData(1:oldDataEndIdx).nominalreachdirection];
    [NRD,ATD] = meshgrid(nomrdirs,Params.adaptation.trainDirs);
    istraindir = reshape(abs(angleminus(NRD(:),ATD(:)))<=1e-10,size(NRD));
    grabidx = find(~sum(istraindir,1));  %  The non-training direction trials.
    if ~isempty(grabidx) & ~isempty(cat(1,savedData(grabidx).disterr))
      eperr = cat(1,savedData(grabidx).disterr);
      Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
    else
      %  If there aren't any previous correct no shift trials then just pick an
      %  arbitrary error.
      Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
    end
  otherwise
    error(mfilename);
end


% % % switch action%%%if sum(abs(Data(trial).fbshift))  % If we're giving random bonus for shift trials and there's a shift
% % %   case 1
% % %     Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
% % %     %  Choose the reward amount from the no shift trial distribution
% % %     nenstrlidx = find(([Data(1:trial-1).err]==0) & ~sum(abs(cat(1,Data(1:trial-1).fbshift)))); %
% % %     if ~isempty(nenstrlidx)
% % %       eperr = cat(1,Data(nenstrlidx).disterr);
% % %       Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
% % %     else
% % %       %  If there aren't any previous correct no shift trials then just pick an
% % %       %  arbitrary error.
% % %       Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
% % %     end
% % %   case 2 % If we're giving random bonus for shift trials and there's no shift
% % %     if rand(1) <= Params.P_noShiftTrialNoEndptFBFlag  %  This percentage of no shift trials will have no visual endpt FB
% % %       Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
% % %       Data(trial).distanceerrorforreward = nan;  %  This will cause the trial func to use the actual error
% % %     else
% % %       Data(trial).givebonusfeedbackflag = 1;  %
% % %     end
% % %   case 3
% % %     Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
% % %     if trial > 1
% % %       %  Choose the reward amount from the no shift/ visFB- trial distribution
% % %       nenstrlidx = intersect(find(([Data(1:trial-1).err]==0)), find(~sum(abs(cat(1,Data(1:trial-1).fbshift)),2))); %
% % %       nstfbidx = find([Data(1:trial-1).starttargetfeedback]==0);
% % %       grabidx = intersect(nenstrlidx,nstfbidx);
% % %     else
% % %       grabidx = [];
% % %     end
% % %     if ~isempty(grabidx)
% % %       eperr = cat(1,Data(grabidx).disterr);
% % %       Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
% % %     else
% % %       %  If there aren't any previous correct no shift trials then just pick an
% % %       %  arbitrary error.
% % %       Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
% % %     end
% % %   case 4
% % %     Data(trial).givebonusfeedbackflag = 0;  %  Don't give visual feedback of the endpoint error.
% % %     %  Choose the reward amount from the no shift / visFB- / test direction trial distribution
% % %     nenstrlidx = intersect(find(([Data(1:trial-1).err]==0)), find(~sum(abs(cat(1,Data(1:trial-1).fbshift)),2))); %
% % %     nstfbidx = find([Data(1:trial-1).starttargetfeedback]==0);
% % %     grabidx = intersect(nenstrlidx,nstfbidx);
% % %
% % %     nomrdirs = [Data(1:trial-1).nominalreachdirection];
% % %     [NRD,ATD] = meshgrid(nomrdirs,Params.adaptation.trainDirs);
% % %     istraindir = reshape(abs(angleminus(NRD(:),ATD(:)))<=1e-10,size(NRD));
% % %     grabidx = find(~sum(istraindir,1));  %  The non-training direction trials.
% % %     if ~isempty(grabidx) & ~isempty(cat(1,Data(grabidx).disterr))
% % %       eperr = cat(1,Data(grabidx).disterr);
% % %       Data(trial).distanceerrorforreward = eperr(unidrnd(length(eperr)));
% % %     else
% % %       %  If there aren't any previous correct no shift trials then just pick an
% % %       %  arbitrary error.
% % %       Data(trial).distanceerrorforreward = Data(trial).reachtargetwin/2;
% % %     end
% % %   otherwise
% % %     error(mfilename);
% % % end

return

function pauseCallback(hObject, eventdata, handles)

global pauseFlag

button_state = get(hObject,'Value');
if button_state == get(hObject,'Max')
  pauseFlag=1;
elseif button_state == get(hObject,'Min')
  pauseFlag=0;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function keyboardCallback(hObject, eventdata, handles)

global keyboardFlag

keyboardFlag=1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function restartCallback(hObject, eventdata, handles)

global restartFlag

restartFlag=1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function newfileCallback(hObject, eventdata, handles)

global newfileFlag

newfileFlag=1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function newcalibCallback(hObject, eventdata, handles)

global newcalibFlag

newcalibFlag=1;