function Params = SensIntReaching_Params(flag)

%  function Params = SensIntReaching_Params(name,flag)
%
% command - tuning or adaptation

%% NOTES:
% Distances in mm
% Single numbers for windows etc are radii
% Boxes are 1/2 widths
% Timing in msec
global NO_ISCAN

ServerNamesInclude;

if nargin<1, flag = 1; end

if flag

  global NMARKERS
  global Path Params

  %%%%%%% FILENAME
  name = Params.NAME;
  ct=1;
  fname = sprintf('SensInt_%s-%s-%d',name,date,ct);
  while( exist([fname,'.mat']) | exist([fname,'_TEMP']) )
    ct=ct+1;
    fname = sprintf('SensInt_%s-%s-%d',name,date,ct);
  end
  fprintf('Data will be stored to file %s\n\n',fname);

  %Params.NAME                = name;
  Params.FILENAME            = fname;

end

Params.visServerIP = strDisplayComputer;


%%%%%% MARKERS
Params.N_MARKERS          = 1;
Params.FINGER_MARKER      = 1;

%%%%%% TRIAL PARAMETERS
Params.N_TRIALS          = 999; % A little more than the expected number of trials.  This is used to compute how many reaches there are per start target.

% Params.N_PATHS_OCTAGON   = size(Path,4); % number of times the octagon path is repeated
% Params.N_TRIALS_OCTAGON  = size(Path,3); % number of reaches per octagon path

%Params.N_TARGETS         = 8; % nmb reaching targets

%  1. FB (or not) reach with instructed delay (can be zero delay)
%  2. Nothing at the moment
%  3. Fixation training, no hand
%  4. Fixation training.  Fixate eye target while holding hand at unseen start target
%  5. Fixation training.  Hold hand at start and fixate eye target while
%       reach target is shown briefly.
% Params.TRIAL_TYPE_PROBS  = [0 0 1 0 0];%[0.7 0 0.3 0];%[0.4 0 0.1 0.5];%[0.2 0 0.05 0.75]; %
Params.TRIAL_TYPE_PROBS  = [1 0 0 0 0];%[0.7 0 0.3 0];%[0.4 0 0.1 0.5];%[0.2 0 0.05 0.75]; %
%Params.TRIAL_TYPE_PROBS  = [0.4 0 0.1 0.5 0];
%Params.TRIAL_TYPE_PROBS  = [0.0 0 0.0 0.3 0.7];%[0.4 0 0.1 0.5];%[0.2 0 0.05 0.75]; %
%Params.TRIAL_TYPE_PROBS  = [0 0 0 0 1];

if abs(1-sum(Params.TRIAL_TYPE_PROBS)) > eps
  error('Probs don''t add up');
end
Params.N_TRIAL_TYPES     = length(Params.TRIAL_TYPE_PROBS);
Params.MAX_TRIAL_ERR     = 0; % number of times to repeat the same target if there is an error
%Params.N_REFRESH         = 4;  % every N_REFRESH tests give an exposure

Params.PERT = [0 0];

%%% REWARDS scheme and START target (task dependent)

Params.SMALL_REWARD          = 50;
Params.MEDIUM_REWARD         = 0;
Params.LARGE_REWARD          = 300;%250; %350;
Params.EYE_FIX_REWARD        = 150;
Params.EYE_FIX_REWARD2       = 400;
Params.AFDeltaReward         = 0;  %  If monk moves in direction of arrow field give reward (for training)
Params.INTERMEDIATE_REWARDS  = 0; %%intermediate rewards
Params.P_START_TARGET_REWARD = 0;  %  Probabiliy of start tgt reward

Params.useRandomTargetsFlag = 1;    %  Use the target_pos_funcs below (1), or choose from the precomputed list (0); subject to P_randomTarget.
Params.P_randomTarget       = 1;%0.8;%0.85  %  Non test trials.  1-P test trials.
Params.chooseTargetMethod = 1;

Params.INTER_TRIAL_DELAY     = 1500; % delay between each trial (ms)
%Params.INTER_TRIAL_DELAY     = 2000; % delay between each trial (ms)
% Params.INTER_TRIAL_DELAY     = 3000; % delay between each trial (ms)
%Params.INTER_TRIAL_DELAY     = 4000; % delay between each trial (ms)
% Params.INTER_TRIAL_DELAY     = 6000; % delay between each trial (ms)

%%%  visual FB params
Params.P_visFB = [1 0];

Params.visFB(1).RGB = [1 1 1];
Params.visFB(1).bright = 0.7;
Params.visFB(1).rad = 3;
Params.visFB(1).fill = 1;
Params.visFB(1).FBFunc = 'Fng_FB';

Params.visFB(2).RGB = [1 1 1];
Params.visFB(2).bright = 0.7;
Params.visFB(2).rad = 3;
Params.visFB(2).fill = 1;
Params.visFB(2).FBFunc = 'Fng_FB';
% - - - - - - -

%%%%%% HAND target parameters
Params.START_TARGET_SHOW     = 0;    % Show start target
%Params.START_TARGET_FEEDBACK = 0;    % Feedback ON
Params.P_START_TARGET_FEEDBACK = 0.50;    % P of FB on at start target
Params.START_TARGET_WIN      = 11;
Params.START_TARGET_RAD      = 11;
Params.START_TARGET_VEL_CRIT = 30;%1.1;  %  mm/sec??
Params.START_TARGET_RGB      = [0 1 0];
Params.START_TARGET_BRIGHT   = 0.02; %%.36;
Params.P_START_TARGET_FLASH  = 0.0;
Params.START_TARGET_FLASH_BRIGHT = 0.2;  %  FoR traInInG.  WhEn ThE StaRt tArgEt is VeRy diM, FlaSh it so THe mOnKey KnoWs whEre It iS.
Params.START_TARGET_POS_FUNC = ['[rand(1)*range(Params.wsBounds(:,1))+min(Params.wsBounds(:,1))' ...
  ' rand(1)*range(Params.wsBounds(:,2))+min(Params.wsBounds(:,2))]'];

Params.REACH_TARGET_RAD       = 10.5;%11;
%Params.REACH_TARGET_RAD       = 5;
Params.REACH_TARGET_WIN_FUNC  = inline('reachrad - 0.5*fbrad','reachrad','fbrad');  %9.5;
Params.REACH_TARGET_WIN        = [];
%Params.REACH_TARGET_WIN       = 5;
Params.REACH_TARGET_RGB       = [0 1 0];
Params.REACH_TARGET_BRIGHT    = 0.8; %%.36; % target brightness [0,1]
Params.MIN_REACH_DISTANCE     = 30; %  mm. for random target locations. Min distance from start to reach target
% to declare test trials ok
Params.REACH_TARGET_POS_FUNC = ['[rand(1)*range(Params.wsBounds(:,1))+min(Params.wsBounds(:,1))' ...
  ' rand(1)*range(Params.wsBounds(:,2))+min(Params.wsBounds(:,2))]'];

%%% --  Eye Target Params
Params.EYE_TARGET_WIN       = 45;
Params.EYE_TARGET_RAD       = 4;
Params.EYE_TARGET_RGB       = [1 0 0];
Params.EYE_TARGET_BRIGHT    = 1;
% Params.EYE_TARGET_POS_FUNC  = ['[rand(1)*range(Params.wsBounds(:,1))+min(Params.wsBounds(:,1))' ...
%     ' rand(1)*range(Params.wsBounds(:,2))+min(Params.wsBounds(:,2))]'];
% if ~NO_ISCAN & isfield(Params,'eyeCalibration')
%  Params.eyeWS = Params.eyeCalibration.dataTable;
%  Params.EYE_TARGET_POS_FUNC  = ['[rand(1)*range(Params.eyeWS(:,1))+min(Params.eyeWS(:,1)) ' ...
%    'rand(1)*range(Params.eyeWS(:,2))+min(Params.eyeWS(:,2))]'];
% else
%   Params.EYE_TARGET_POS_FUNC = '';
% end
Params.eyeWS = [20 -30
                60 50];
Params.EYE_TARGET_POS_FUNC  = ['[rand(1)*range(Params.eyeWS(:,1))+min(Params.eyeWS(:,1)) ' ...
    'rand(1)*range(Params.eyeWS(:,2))+min(Params.eyeWS(:,2))]'];
Params.MIN_EYE_TO_REACH_DISTANCE = 50;

%%%Params.EYE_TARGET_POS_FUNC  = ['[rand(1)*0.85.*range(Params.wsBounds(:,1))+(1-0.85)/2.*min(Params.wsBounds(:,1))' ...
%%%   ' 0.5.*rand(1)*range(Params.wsBounds(:,2))+(1-0.5)./2.*min(Params.wsBounds(:,2))]'];
% Params.EYE_TARGET_POS_FUNC  = ['[rand(1)*range(Params.wsBounds(:,1))+min(Params.wsBounds(:,1))' ...
%     ' rand(1)*range(Params.wsBounds(:,2))*1+(min(Params.wsBounds(:,2))-range(Params.wsBounds(:,2)*0.1))]'];

% Feedback
%Params.FEEDBACK_FNG_RAD    =  5;
%Params.FEEDBACK_FNG_BRIGHT = .9;       % brightness [0,1]
%Params.FNG_FEEDBACK_FUNC   = 'Fng_FB'; % Finger

%%% DELAYS and PAUSES
Params.START_TARGET_HOLD        = 0.75;%1.0;
Params.REACH_TARGET_HOLD        = 0.5;  % (sec) time must hold to get final reward
Params.EYE_TARGET_HOLD          = 1.5;
Params.START_TARGET_FB_HOLD_DUR = Params.START_TARGET_HOLD;  %  Hold duration during FB (or FB-) delay

Params.P_NONZERO_REACH_DELAY = 0.95;%0.3;  %  Use reach_delay_min and _max criteria on this proportion of trials.  The rest will be zero delay RT trials.
Params.REACH_DELAY_MIN     = 0;%0.2;%0.75;       % Delay hold range after reaching start target and before
Params.REACH_DELAY_MAX     = 1.2;      % go tone signals a move to the reach target.

Params.START_TARGET_PENALTY  = 0;%10;
Params.ERR_PENALTY           = 0;%1000; % MSEC EXTRA (in addition to inter_trial_delay) delay between trials if there is an error.
Params.SWAT_PENALTY          = Params.ERR_PENALTY;%4000; % MSEC delay if velocity is above a certain amount


%%% TIMEOUTS
Params.REACH_START_TARGET_TIMEOUT     = 14; %8; % (sec) max allowed time to position hand at start target
Params.MAX_MOVE_TIME_TO_START_TARGET  = 6;  %  The maximum amount of time allowed to acquire the start target, once he starts moving.
Params.REACH_TARGET_TIMEOUT           = 1.4;%1.75; % (sec) max allowed time to reach reaching target
Params.EYE_TARGET_TIMEOUT             = 4;

%%%%%% Tones Tones Tones Tones Tones Tones Tones Tones Tones Tones Tones

%%%             Event Tones
Params.START_TONE_TIME     =  300;
Params.START_TONE_FREQ     = 300;

Params.GO_PAUSE         = 0.2;
Params.GO_TONE_TIME     = 0.3;
Params.GO_TONE_FREQ     = 750;

Params.EventTone(1).FREQ = 1500;
Params.EventTone(1).DUR = 0.075;

Params.EventTone(2).FREQ = 2000;
Params.EventTone(2).DUR = 0.100;
%  ----
%%%             Trial Type Tones
%  Trial type 1 tone --  Reach with ID
Params.TRIAL_TYPE_TONE(1).FREQ = 200;
Params.TRIAL_TYPE_TONE(1).NPULSES = 2;
Params.TRIAL_TYPE_TONE(1).PULSEDUR = .4;
Params.TRIAL_TYPE_TONE(1).TOTALDUR = 1;
Params.TRIAL_TYPE_TONE(1).IPI = (Params.TRIAL_TYPE_TONE(1).TOTALDUR - ...
  Params.TRIAL_TYPE_TONE(1).PULSEDUR*Params.TRIAL_TYPE_TONE(1).NPULSES) / ...
  (Params.TRIAL_TYPE_TONE(1).NPULSES - 1);
if Params.TRIAL_TYPE_TONE(1).IPI < 0, error('Bad Tone Sequence'); end

% %  Trial type 2 tone --  RT reach without ID
% Params.TRIAL_TYPE_TONE(2).FREQ = 400;
% Params.TRIAL_TYPE_TONE(2).NPULSES = 4;
% Params.TRIAL_TYPE_TONE(2).PULSEDUR = 0.2;
% Params.TRIAL_TYPE_TONE(2).TOTALDUR = 1;
% Params.TRIAL_TYPE_TONE(2).IPI = (Params.TRIAL_TYPE_TONE(1).TOTALDUR - ...
%     Params.TRIAL_TYPE_TONE(1).PULSEDUR*Params.TRIAL_TYPE_TONE(1).NPULSES) / ...
%     (Params.TRIAL_TYPE_TONE(1).NPULSES - 1);
% if Params.TRIAL_TYPE_TONE(2).IPI < 0, error('Bad Tone Sequence'); end
%%%% ----------------------------------------
%  Workspace
Params.wsBounds = [-65 -80; 125 70];%[-65 -55; 125 85];%[-70 -70; 125 110];%%[-48 -49; 99 89];  %  [Xmin Ymin; Xmax Ymax]
Params.wsCenter = mean(Params.wsBounds,1);
Params.wsRadius = mean([range(Params.wsBounds(:,1)) range(Params.wsBounds(:,2))])/2;
Params.wsHalfWidths = [range(Params.wsBounds(:,1)) range(Params.wsBounds(:,2))]./2;

% %  Sub workspace - initial hand locs will be in here
% Params.swsRelativeCenter = [-50 200]; %  WRT cyc eye .  Just a guess for now.
% %Params.swsCov = [3 0; 0 3];  %  locations will be chosen within 1 SD from center of this dist
% Params.swsRadii = [3 23];  %  Centered on fixation point
% Params.swsThetaHalfWidth = pi/8;  %[pi/4 3*pi/4];
% %Params.swsLocFunc = 'boundedNormalRnd';
% Params.swsLocFunc = 'uniformArcRnd';  %sprintf('uniformArcRnd([%0.4f %0.4f],[%0.4f %0.4f]);',Params.swsTheta,Params.swsRadii);

%  Arrow Field Params
Params.NarrowsX = 4;
Params.NarrowsY = 4;
Params.arrowFieldLength = inline('max(2,min(0.3*x,70))','x');
%%%  Right Hand arrows
%Params.rightHandArrowFieldBrightness = 0.2;
Params.rightHandArrowFieldBrightnessFunc = inline('max(0.2,min(0.8,2/x))','x');
Params.rightHandArrowFieldRGB = [0 1 0];
Params.rightHandArrowFieldZ = 0;

%  Arrow Field training params
%Params.deltaForReward = 20;  %  Move X mm toward start target and get reward.

%  Start targets
Params.Nstarttargets = 10;
%Params.Nshiftsperstarttarget = 2;

%  Reach targets
Params.reachradius = 60;  %10;
Params.reachdirs = [0:7].*pi/4;
%Params.relreachdirs = [-pi/4 -pi/2 -pi];
%Params.Preachtrginset = 0.9;  %  Given that there is an FB shift, this is the proportion of reach targets that are drawn from the set of
%  relative reach directions.  The rest are drawn uniformly from the other possible targets.

Params.FBonReachProportion = 0.6;  %  How far into the reach the FB comes back on (for training).  It is turned off at FBoffReachProportion.
Params.FBoffReachProportion = 0.02;

%  FB shifts
%Params.FBshiftrate = 0.2;  %  cm of shift / cm of hand movement
%Params.FBshiftradius = 2;
Params.FBshiftradius = 15;
Params.FBshiftdirs = [0:7].*pi/4;%[pi/4 pi/2 pi -pi/4];%Params.reachdirs([1:2:end]);%Params.FBshiftdirs = [0:3].*pi/2;  %  These should be chosen from the set of reach trg directions
Params.P_FBshift = 0;%0.7;  %  Probability of having an FB shift, given that trial is a test trial.

%  Learning eye fixation while reaching
Params.reachTrgShowDur = 0.7;
Params.reachTrgBrightMultiplier = 0.1;%0.25;  %  For learning to fixate trials.  Reach target will be dimmed by this multiple

%  Reach Performance Feedback
Params.doneCritSpeed = 2;  %  mm/s, speed below which we consider the reach to be complete.
Params.reachBonusTau            = 20;
Params.reachBonusFunc           = inline('100./exp(t./tau.^0.95);','t','tau');
Params.giveBonusFeedbackFlag    = 1;
Params.performanceFBPause       = 1.75;
Params.randBonusC               = [];%[37 -4; -4 28].*0.4;  %  For shifted trials, draw a position error from ~N(0,randBonusC), and use that to give a bonus score.

Params.P_FullFeedback = 0;%0.02;  %  Proportion of non-test trials on which FB is not exinguished.  Does not apply to test trials.
