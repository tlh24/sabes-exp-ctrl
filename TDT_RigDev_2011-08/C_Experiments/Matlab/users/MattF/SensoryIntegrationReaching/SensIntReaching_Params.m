function Params = SensIntReaching_Params(flag)

%  function Params = SensIntReaching_Params(name,flag)
%
% command - tuning or adaptation

%% NOTES:
% Distances in mm
% Single numbers for windows etc are radii
% Boxes are 1/2 widths
% Timing in msec
global NO_ISCAN;
global NMARKERS;
global Params; %Path

DEBUG = 0;

CalibrateMonkeyFlag = 0;

ServerNamesInclude;
datadir = ExperimentGetDataDir;
%%datadir = 'D:\Users\MattF\Data\';
if nargin<1, flag = 1; end
%%  Directory setup
if flag

  %   global NMARKERS
  %   global Params %Path

  %%%%%%% FILENAME
  name = Params.NAME;
  ct=1;
  fname = fullfile(datadir,'MattF',sprintf('SensInt_%s-%s-%d',name,date,ct));
  %  fname = sprintf('SensInt_%s-%s-%d',name,date,ct);
  while( exist([fname,'.mat']) | exist([fname,'_TEMP']) )
    ct=ct+1;
    fname = fullfile(datadir,'MattF',sprintf('SensInt_%s-%s-%d',name,date,ct));
  end
  fprintf('Data will be stored to file %s\n\n',fname);

  %Params.NAME                = name;
  Params.FILENAME            = fname;
  Params.DATADIRECTORY = fullfile(datadir,'MattF','');

  morphoFile = fullfile(Params.DATADIRECTORY,Params.NAME,'MorphometricData.mat');
  if exist(morphoFile,'file')
    ldtmp = load(morphoFile,'morphoData');
    if strcmpi(ldtmp.morphoData.name,Params.NAME)
      Params.morphoData = ldtmp.morphoData;
    elseif trial<10
      fprintf('\n>>>> %s: Not loading Morpho Data; Names don''t match <<<<\n',mfilename);
    end
    clear ldtmp;
  end
end
if ~isfield(Params,'NAME') | isempty(Params.NAME)
  Params.NAME = 'none';
end


%%
Params.ExperimentName = 'SensIntReaching';
Params.visServerIP = strDisplayComputer;
%%Params.EventCodes     = GetExperimentEventCodes(Params.ExperimentName);
Params.EventCodes   = ExperimentGetEventCodes;
%%%%%% MARKERS
Params.N_MARKERS          = 4;
Params.FINGER_MARKER      = 1;

switch lower(Params.NAME)
  case 'dmitri'
    Params.linkLengths = [120 140 180]; %  [finger->wrist, wrist->elbow, elbow->shoulder]
  case 'test'
    Params.linkLengths = [120 140 180];
  otherwise
    Params.linkLengths = [];
end
%%

%%  Trial Type/Number Setup
%%%%%% TRIAL PARAMETERS
Params.N_TRIALS          = 3000; % A little more than the expected number of trials.  This is used to compute how many reaches there are per start target.

Params.doBlocksFlag = 0;
%%Params.NtrialsPerBlock = [300 35 15 1000 1000];
%Params.NtrialsPerBlock = [500 60 700 1000];
%Params.NtrialsPerBlock = [500 1000];
%Params.NtrialsPerBlock = [2 3 6 2]; %%  TEMP, DEBUG only!
%Params.blockTypes = [1 2 3 4 1];  %  Indices into the block settings below.
%Params.blockTypes = [1 2 4 1];  %  Indices into the block settings below.
% % Params.NtrialsPerBlock = [550 100 750 1000];
% % Params.blockTypes = [5 2 4 5];  %  Indices into the block settings
% below.
if DEBUG
  if 1
    Params.NtrialsPerBlock = [5 5 5];%[10 10 10];
    Params.blockTypes = [7 2 6];  %  Indices into the block settings below.
  else
    Params.NtrialsPerBlock = [10];
    Params.blockTypes = [2];  %  Indices into the block settings below.
  end
else
  Params.NtrialsPerBlock = [1300];  %[750 100 1300];
  Params.blockTypes = [6];  %  Indices into the block settings below.
  % Params.NtrialsPerBlock = [350 150 1300];
  %  Params.blockTypes = [8 2 6];  %  Indices into the block settings below.
end
%% - - - Block Setup -- Param settings for each Block type
Params.BlockSettings = struct([]);
if Params.doBlocksFlag
  Params.BlockSettings(1).BlockTypeName = 'NoShift';
  Params.BlockSettings(1).Settings = {                ...
    'Params.adaptationOnFlag = 0;';                 ...
    'Params.visFB(1).zeroshiftproportion = 1;';     ...
    'Params.visFB(1).P_starttargetfeedback = 0.75;';    ...
    };

  Params.BlockSettings(2).BlockTypeName = 'WashIn';
  Params.BlockSettings(2).Settings = {                ...
    'Params.adaptationOnFlag = 1;';                 ...
    'Params.adaptation.WashInFlag = 1;';            ...
    'Params.adaptation.PadaptationParams = 1;';   ...
    'Params.visFB(1).P_starttargetfeedback = 1;';    ...
    'Params.P_FBonRP = [0.7 0.3];';             ...
    'Params.FBonReachProportion = [inf 0.7];';         ...
    'Params.reachdirs = Params.adaptation.trainDirs;';  ... %  WashIn trials should only be in the training directions.
    };

  Params.BlockSettings(3).BlockTypeName = 'Adapt';
  Params.BlockSettings(3).Settings = {                ...
    'Params.adaptationOnFlag = 1;';                 ...
    'Params.adaptation.WashInFlag = 0;';            ...
    'Params.adaptation.PadaptationParams = 1;';   ...
    'Params.visFB(1).P_starttargetfeedback = 1;';   ...
    };

  %   Params.BlockSettings(4).BlockTypeName = 'Adapt+NoShift+NoFB';
  %   Params.BlockSettings(4).Settings = { ...
  %     'Params.adaptationOnFlag = 1;';                 ...
  %     'Params.adaptation.PadaptationParams = 0.85;';   ...
  %     'Params.adaptation.WashInFlag = 0;';            ...
  %     'Params.visFB(1).zeroshiftproportion = 1;';     ...
  %     'Params.visFB(1).P_starttargetfeedback = 0.7;'; ...
  %     };

  Params.BlockSettings(5).BlockTypeName = 'NoShift+Shift';
  Params.BlockSettings(5).Settings = {                ...
    'Params.adaptationOnFlag = 0;';                 ...
    'Params.visFB(1).zeroshiftproportion = 0.75;';     ...
    'Params.visFB(1).P_starttargetfeedback = 0.6;';    ...
    };

  Params.BlockSettings(6).BlockTypeName = 'Adapt+NoFB';
  Params.BlockSettings(6).Settings = { ...
    'Params.adaptationOnFlag = 1;';                 ...
    'Params.adaptation.PadaptationParams = 1;';   ...
    'Params.adaptation.WashInFlag = 0;';            ...
    'Params.visFB(1).P_starttargetfeedback = 1;'; ...
    };

  Params.BlockSettings(7).BlockTypeName = 'Baseline';
  Params.BlockSettings(7).Settings = {                ...
    'Params.adaptationOnFlag = 0;';                 ...
    'Params.visFB(1).zeroshiftproportion = 0.75;';     ...
    'Params.visFB(1).P_starttargetfeedback = 0.6;';    ...
    'saveIntermediateTrialData(Data(1:trial));'; ...
    };

  Params.BlockSettings(8).BlockTypeName = 'Baseline Tuning';
  Params.BlockSettings(8).Settings = {                ...
    'Params.adaptationOnFlag = 0;';                 ...
    'Params.visFB(1).zeroshiftproportion = 1;';     ...
    'Params.visFB(1).P_starttargetfeedback = 0.5;';    ...
    'saveIntermediateTrialData(Data(1:trial));'; ...
    };
end
%%  --- END Block Setup

%  If the current trial type is a trial type which can have test trials,
%  make it a test trial this proportion of the time.  If it becomes a test
%  trial then call the function that generates the test trial parameters (e.g., start and reach locations, eye
%  fixation location, etc.).
Params.P_TestTrial = 1;%0.7;%1;%0.3;
Params.NonTestTrialGetTrgFunc = 'SIRGetTargs2';  % If this is empty it will just use the settings below.
Params.P_visFB = [1 0 0];%[1/3 1/3 1/3];%[0.5 0.25 0.25];

%%  - - - - Adaptation params - - - - - -
Params.adaptationOnFlag = 0;
%%%%Params.doAdaptationFlag = 0;

%Params.adaptation.NtrialsPerBlock = [500 300 40 1000];
% Params.adaptation.blockTypes = {'Shift+NoShift'; 'Shift'; 'NoShift'; 'Shift+NoShift'};
% Params.adaptation.NtrialsPerBlock = [350 350];
%  Params.adaptation.blockTypes = {'NoShift'; 'Shift'}; %{'Shift'; 'NoShift'};

%Params.adaptation.NtrialsPerBlock = [300 35 15 500 1000];
%Params.adaptation.blockTypes = [1 2 3 4 1];

%   Params.adaptation.NtrialsPerBlock = [1000];
% Params.adaptation.blockTypes = {'Shift+NoShift'};
if DEBUG
  Params.adaptation.shiftparams = {0; [60 60]};
else
  %Params.adaptation.shiftparams = {0; [25 25]};
  Params.adaptation.shiftparams = {0; [20 20]};
end
Params.adaptation.WashInFlag = 0;
Params.adaptation.WashOutFlag = 0;
Params.adaptation.doRelativeShiftFlag = 0;
Params.adaptation.PadaptationParams = 1;

%  For adaptation we may want to train on certain directions and test on others.
Params.adaptation.trainDirs = [-pi/4 0 3*pi/4 pi];%[0 pi];  %  Train on these.  The test trials will be the rest of the reach directions.


%%% %  Adjust the nominal hand start location so that:
%%% (0): no adjustment
%%% (1): the target array center is midway between the hand and some specified value,
%%%         OR
%%% (2): Fixed offset from subws center, set by Params.startLocOffset
Params.adjustStartLocForShiftFlag = 0;%2;%0;%2;
%%%
[slox,sloy] = pol2cart(Params.adaptation.shiftparams{1},-Params.adaptation.shiftparams{2}(1)); % Note that the distance here is negative so that the offset is in the correct direction.
Params.startLocOffset = [slox sloy]./2;
%%%%%%%%% ----------------------------------

%% - - - NON-Adaptation shift params - - -
Params.doRelativeShiftFlag = 1;  %  Shift will be relative to reach direction.  i.e., rotated relative to reach dir by specified amount, with specified length

%FBShiftParams = {[0 pi]; [20 20]};
%FBShiftParams = {[-pi/2]; [25 25]};%
%  FBShiftParams = {[0:7].*pi/4; [20 20]};%

%FBShiftParams = {[pi/2 -pi/2]; [25 25]};%
%  FBShiftParams = {[pi/2 -pi/2]; [20 20]};%
%FBShiftParams = {[pi/2 -pi/2]; [12.5 12.5]};%
%FBShiftParams = {[pi/2 -pi/2]; [5 15]};%
%Params.visFB(1).shiftparams ={[pi/2 -pi/2]; [5 15]};%
if DEBUG
  Params.visFB(1).shiftparams ={[pi/2 -pi/2]; [60 60]};%
else
  Params.visFB(1).shiftparams ={[pi/2 -pi/2]; [20 20]};%
end
%%FBShiftParams = {[-pi/2]; [60 60]};%
if CalibrateMonkeyFlag
  Params.visFB(1).zeroshiftproportion = 1; %0.75; %0.7;%0.6;%0.7;%0.3;%0.7;%0.7; %0.80;
else
   %Params.visFB(1).zeroshiftproportion = 1;  % For baseline characterization day.
  Params.visFB(1).zeroshiftproportion = 0.6; %0.75; %0.7;%0.6;%0.7;%0.3;%0.7;%0.7; %0.80;
end

%  If we are not going to give visual endpoint feedback for shifted trials then we also want some percentage of
%  _no-shift_ trials to have no visual endpoint FB.
switch 2
  case 1  %  Just make the proportion of endpt FB- no shift trials = the proportion of shift trials.
    Ps = 1-Params.visFB(1).zeroshiftproportion;
    Params.P_noShiftTrialNoEndptFBFlag = Ps/(1-Ps);  %  Just make the proportion of endpt FB- no shift trials = the proportion of shift trials.
  case 2  %  Fixed percentage of no-shift endptFB- trials.
    %  For the current adaptation paradigm we always want endpt fb for no
    %  shift trials in the training directions.
    if CalibrateMonkeyFlag
      Params.P_noShiftTrialNoEndptFBFlag = 0;
    else
     %  Params.P_noShiftTrialNoEndptFBFlag = 0;  % For baseline characterization day.
      Params.P_noShiftTrialNoEndptFBFlag = 0.1;
    end
  otherwise
    error;
end
%%
% For the adaptation paradigm.  For the baseline block we want mostly
% no-shift/visFB+ trials.  The shift is determined first.  If there is a
% shift then there is always visFB+ (starttargetfeedback is on).
% P_starttargetfeedback determines what proportion of
% no-shift trials have visFB+.
if CalibrateMonkeyFlag
  Params.visFB(1).P_starttargetfeedback = 1;
else
  % Params.visFB(1).P_starttargetfeedback = 1;  %  For baseline characterization day
  Params.visFB(1).P_starttargetfeedback = 0.8;%0.6;%0.85;%%0.75;%1;%0.9;
end
Params.P_subWorkspace = [0.5 0.5];%[0.5 0.5];

adjustSubws2CenterLocFlag = 1;

%  Reach targets
Params.reachradius = 60;  %  Changed to this value on June 6, 2008.
%Params.reachradius = 65;  %  Changed to this value on May 30, 2008.
%Params.reachradius = 70; %  Changed from this value on May 30, 2008.
Params.reachdirs = [0:7].*pi/4;

%%%  Where to fixate?
%%%  1 = fixate reach target
%%%  2 = fixate relative to reach target and/or hand and/or shift (or no fixation)
%%%  3 = random fixation point
%%%  4 = fixate _relative_ to the center of the current subworkspace.
Params.whereToFixateFlag = 4;
%%%%%%%  --------

Params.eyeFixationDrawShiftForNoShiftTrialsFlag = [];  %  Placeholder, don't change here.
Params.relativeFixationLocParams = cell(0);  %  Placeholder, don't change here.
switch Params.whereToFixateFlag

  case 2
    %%% For no shift trials, do we want to put the fixation point relative to where the shift WOULD
    %%% be if there were one?  I.e., draw the relative fixation location from the same distribution
    %%% as the shift trials so we have a direct comparison in which only the visFB location
    %%% differs.
    Params.eyeFixationDrawShiftForNoShiftTrialsFlag = 1;

    %%%  If fixation is relative to reach, specify some params
    if 1
      Params.P_relativeFixationLoc = [0 0 0 1];  %  Today we don't want to enforce fixation.
    else
      Params.P_relativeFixationLoc = [1 0 0 0];  %[0.8 0 0 0.2];%[0.7 0 0 0.3]; % [0.5 0 0.5 0]; %[1 0 0];
    end

    relelfunc1 = inline('st+(rt-st).*p','st','rt','shift','p');
    relelfunc2 = inline('st+shift+(rt-(st+shift)).*p','st','rt','shift','p');
    Params.relativeFixationLocParams(1,:) = [{1} {relelfunc1}];
    Params.relativeFixationLocParams(2,:) = [{0.5} {relelfunc1}];
    Params.relativeFixationLocParams(3,:) = [{0.5} {relelfunc2}];
    Params.relativeFixationLocParams(4,:) = [{nan} {''}];  %  we'll use this to specify no fixation point trials.

  case 4
    if CalibrateMonkeyFlag
      Params.P_relativeFixationLoc = [0 0 1];
    else
      Params.P_relativeFixationLoc = [0 1 0];  %[1 0 0];
    end
    Params.relativeFixationLocParams(1,:) = [{[0 0]}];  %  [Direction Distance], fixate center
    Params.relativeFixationLocParams(2,:) = [{[pi Params.reachradius]}];  %  [Direction Distance], fixate leftward reach target
    Params.relativeFixationLocParams(3,:) = [{nan}];  %  Don't enforce fixation.
end
%%%%


%%  Trial Type Function Selection
%  1. FB (or not) reach with instructed delay (can be zero delay)
%  2. Just reach to a target.  No delay, no fixation.
%  3. Fixation training, no hand
%  4. Fixation training.  Fixate eye target while holding hand at unseen start target
%  5. Fixation training.  Hold hand at start and fixate eye target while
%       reach target is shown briefly.
%  6.  Hold, Fixate, Reach
%  7. Hand hold, multiple eye fixations.

% Params.TRIAL_TYPE_PROBS  = [0 0.7 0.3 0 0 0];  %  Test Eye and Hand workspace
Params.TRIAL_TYPE_PROBS  = [0 0 0 0 0 1 0];
%Params.TRIAL_TYPE_PROBS  = [0 0 0 0 0 0 1];


if abs(1-sum(Params.TRIAL_TYPE_PROBS)) > eps
  error('Probs don''t add up');
end
Params.N_TRIAL_TYPES     = length(Params.TRIAL_TYPE_PROBS);


%%


%%Params.MAX_TRIAL_ERR     = 0; % number of times to repeat the same target if there is an error
%Params.N_REFRESH         = 4;  % every N_REFRESH tests give an exposure

%%Params.PERT = [0 0];

%% REWARDS scheme

Params.SMALL_REWARD          = 150;
Params.MEDIUM_REWARD         = 0;
Params.LARGE_REWARD          = 500;%250;%350%;%250; %350;
Params.EYE_FIX_REWARD        = 150;
Params.EYE_FIX_REWARD2       = 450;  %  Also used for trial type #7.
Params.AFDeltaReward         = 0;  %  If monk moves in direction of arrow field give reward (for training)
Params.INTERMEDIATE_REWARDS  = 0; %%intermediate rewards
Params.P_START_TARGET_REWARD = 0;  %  Probabiliy of start tgt reward

%%  Inter-trial Stuff
%Params.INTER_TRIAL_DELAY     = 1900; % delay between each trial (ms)
Params.INTER_TRIAL_DELAY     = 1300;%1300; % delay between each trial (ms)
%Params.INTER_TRIAL_DELAY     = 2000; % delay between each trial (ms)
%Params.INTER_TRIAL_DELAY     = 3000; % delay between each trial (ms)
%Params.INTER_TRIAL_DELAY     = 4000; % delay between each trial (ms)
% Params.INTER_TRIAL_DELAY     = 6000; % delay between each trial (ms)

if DEBUG
  fprintf('\n\nWARNING:  DEBUG flag is on in Params\n\n');
  pause(0.5);
  Params.INTER_TRIAL_DELAY     = 100;
end
if CalibrateMonkeyFlag
  fprintf('\n\nWARNING:  CalibrateMonkey flag is on in Params\n\n');
  pause(0.5);
end
%%


%
%Params.useRandomTargetsFlag = 1;    %  Use the target_pos_funcs below (1), or choose from the precomputed list (0); subject to P_randomTarget.
%Params.P_randomTarget       = 1;%0.8;%0.85  %  Non test trials.  1-P test trials.
%Params.chooseTargetMethod = 1;
%%


%%%% - - - Don't change these flags here
switch Params.whereToFixateFlag
  case 1
    Params.fixateReachTrgFlag = 1;
    Params.fixateRelativeToReachTrgFlag = 0;
  case 2
    Params.fixateRelativeToReachTrgFlag = 1;
    Params.fixateReachTrgFlag = 0;
  case 3
    Params.fixateRelativeToReachTrgFlag = 0;
    Params.fixateReachTrgFlag = 0;
end
%Params.relativeFixationEyePosFunc = inline('st+(rt-st).*p','st','rt','p');
%%%%  ----------------------------------------------

%%  WORKSPACE

%%%  - - - -  Hand Workspace  - - - -
%Params.wsBounds = [-65 -80; 125 70];%[-65 -55; 125 85];%[-70 -70; 125 110];%%[-48 -49; 99 89];  %  [Xmin Ymin; Xmax Ymax]
if 1
  Params.wsBounds = [-92 -95; 177 80];  %  [Xmin Ymin; Xmax Ymax]
else
  %  For testing ws boundaries
  %Params.wsBounds = [-125 -125; 200 125]; %  [Xmin Ymin; Xmax Ymax]
  Params.wsBounds = [-125 -95; 200 125]; %  [Xmin Ymin; Xmax Ymax]
end
%%%%%%%
Params.wsCenter = mean(Params.wsBounds,1);
Params.wsRadius = mean([range(Params.wsBounds(:,1)) range(Params.wsBounds(:,2))])/2;
Params.wsHalfWidths = [range(Params.wsBounds(:,1)) range(Params.wsBounds(:,2))]./2;

%%%  - - - -  Eye workspace  - - - -
Params.eyeWS = [[Params.wsCenter(1)-Params.wsHalfWidths(1)/2; Params.wsCenter(1)+Params.wsHalfWidths(1)/2] ...
  [Params.wsCenter(2)-Params.wsHalfWidths(2)/2; Params.wsCenter(2)+Params.wsHalfWidths(2)/2] ...
  ];  %%%[20 -30     60 50];

%%  - - - - Subworkspaces for test trials  - - - -
%Params.P_subWorkspace = [0.5 0.5];
% Params.P_subWorkspace = [0 1];% [1 0];%[0.5 0.5];
%
%
if 1
  Params.subWorkspace(1).radius = [5 5+max(abs(Params.visFB(1).shiftparams{2}))];%0.5;%15;  %  mm.  Semi-arbitrary.
  %  The point of the start ellipse is to ensure that during no-shift
  %  trials we sample the space of possible hand & visFB start locations during
  %  shift trials.  This way, when fitting behavioral initial angle biases,
  %  or neural tuning curves for no-shift trials we are not extrapolating
  %  when comparing with shift trials.  Therefore, enforce a small boundary
  %  around the edge of the ellipse so that shift trial starts will always
  %  be a subset of the support for no-shift trials.
  Params.subWorkspace(1).shiftTrialStartEllipseEdgeBufferProportion = 0.975;  %  Proportion of the axes lengths to use for the ellipse edge buffer.
else
  Params.subWorkspace(1).radius = 5;%0.5;%15;  %  mm.  Semi-arbitrary.
  Params.subWorkspace(1).shiftTrialStartEllipseEdgeBufferProportion = [];
end

%edgebuffer = [22 10];
Params.WSedgebuffer = [23 12];  %  Changed to these values on June 6, 2008.

%  Maximize the use of space by picking the subworkspace center so that the
%  upward and leftward reach targets fall on the edges of the reachable workspace.
Params.subWorkspace(1).center = [min(Params.wsBounds(:,1))+Params.reachradius+Params.subWorkspace(1).radius(1)+Params.WSedgebuffer(1) ...
  min(abs(Params.wsBounds(:,2)))-(Params.reachradius+Params.subWorkspace(1).radius(1)+Params.WSedgebuffer(2))];

toCtr = Params.wsCenter - Params.subWorkspace(1).center;

switch Params.whereToFixateFlag
  case 1
    Params.subWorkspace(1).EyeTargetPos = [];
  case 2
    Params.subWorkspace(1).EyeTargetPosFunc = '';
    %Params.subWorkspace(1).EyeTargetPosFunc = Params.relativeFixationEyePosFunc;
  case 3
    %  Choose the eye fixation location on a line passing through the
    %  subworkspace center and the overall workspace center.  Make sure it is
    %  outside of the circle defined by the reach targets.
    Params.subWorkspace(1).EyeTargetPos = 0.333.*(Params.reachradius+Params.subWorkspace(1).radius).*(toCtr./norm(toCtr))+Params.wsCenter;
end

% % if Params.fixateReachTrgFlag
% %   Params.subWorkspace(1).EyeTargetPos = [];
% % elseif Params.fixateRelativeToReachTrgFlag
% %   Params.subWorkspace(1).EyeTargetPosFunc = '';
% %   %Params.subWorkspace(1).EyeTargetPosFunc = Params.relativeFixationEyePosFunc;
% % else
% %   %  Choose the eye fixation location on a line passing through the
% %   %  subworkspace center and the overall workspace center.  Make sure it is
% %   %  outside of the circle defined by the reach targets.
% %   Params.subWorkspace(1).EyeTargetPos = 0.333.*(Params.reachradius+Params.subWorkspace(1).radius).*(toCtr./norm(toCtr))+Params.wsCenter;
% % end


%  For the second subworkspace, just reflect everything around the vertical
%  line through the workspace center.
Params.subWorkspace(2) = Params.subWorkspace(1);
Params.subWorkspace(2).center(1) = Params.wsCenter(1) + (Params.wsCenter(1)-Params.subWorkspace(1).center(1));
Params.subWorkspace(2).center(2) = Params.subWorkspace(1).center(2);
if flag  %  Otherwise the morphoData, which the following function call depends on, will not have been loaded.
  switch adjustSubws2CenterLocFlag
    case 1
      %  Adjust the subws2 location so that it's center is on the arc centered at
      %  the cyc. eye and passing through the center of subws1.
      newLoc = getSubworkspaces(1);  %
      Params.subWorkspace(2).center = newLoc;
    otherwise
  end
end

switch Params.whereToFixateFlag
  case 1
    Params.subWorkspace(2).EyeTargetPos = [];
  case 2
    Params.subWorkspace(2).EyeTargetPosFunc = Params.subWorkspace(1).EyeTargetPosFunc;
  case 3
    Params.subWorkspace(2).EyeTargetPos(1) = Params.wsCenter(1) + (Params.wsCenter(1)-Params.subWorkspace(1).EyeTargetPos(1));
    Params.subWorkspace(2).EyeTargetPos(2) = Params.subWorkspace(1).EyeTargetPos(2);
end
%%%% --------------------------------

%%  FB params
%shiftdistfunc = @birandomshift;
ang = [0:30]/30*2*pi;
circlepts = [cos(ang); sin(ang)];
sqrpts = [1/2 0; 0 1/2; -1/2 0; 0 -1/2]';
circlerad = 6;% 3;
sqrside = sqrt(pi*circlerad^2);
sqrscale = sqrt(2*sqrside^2);
triangleside = sqrt(4*pi*circlerad^2/sqrt(3));
thght = sqrt(triangleside^2*3/4);
trianglepts = [0 0.5*thght; 0.5*triangleside -0.5*thght; -0.5*triangleside -0.5*thght]';

%%%  visual FB params
%  This is now set above.
%%%Params.P_visFB = [1 0 0];%[1/3 1/3 1/3];%[0.5 0.25 0.25];

%%%  FB #1
Params.visFB(1).RGB = [1 1 1];
Params.visFB(1).bright = 0.7;
Params.visFB(1).points = circlepts;
Params.visFB(1).rad = circlerad;
Params.visFB(1).fill = 1;
Params.visFB(1).angle = 0;

Params.visFB(1).FBFunc = 'Fng_FB';
% % vvrotth = -pi/4;
% % M = [cos(vvrotth) -sin(vvrotth); sin(vvrotth) cos(vvrotth)];
% % Params.visFB(1).FBFunc = @(pos,pert,flag) Fng_FB_velDep( pos, pert, flag, M);

%Params.visFB(1).shiftparams = {[[0 0 0 0];[0 0 0 0]]};  %[[Xlow_lower Xlow_upper Xhigh_lower Xhigh_upper];[Ylow_lower ...]]
%Params.visFB(1).shiftparams2 = [];
%Params.visFB(1).shiftdistfunc = @(sparms) birandomshift('none','none',Params.visFB(1).shiftparams2,sparms);%shiftdistfunc;

% Params.visFB(1).shiftparams = {[0]; [10 10]};  %  [Dirs] [distance_min distance_max]

%  - - - For consistency.  These are now set up above.
Params.visFB(1).shiftparams = Params.visFB(1).shiftparams;
Params.visFB(1).zeroshiftproportion = Params.visFB(1).zeroshiftproportion;
Params.visFB(1).P_starttargetfeedback = Params.visFB(1).P_starttargetfeedback;
%Params.visFB(1).zeroshiftproportion = 1;%0.6;%0.7;%0.3;%0.7;%0.7; %0.80;
%Params.visFB(1).P_starttargetfeedback = 0.85;%%0.75;%1;%0.9;
% -----------
%Params.visFB(1).shiftparams = FBShiftParams; %{[0 pi]; [20 20]};  %  [Dirs] [distance_min distance_max]
%Params.visFB(1).shiftparams = {[0]; [50 50]};  %  [Dirs] [distance_min distance_max]
Params.visFB(1).shiftparams2 = [];
Params.visFB(1).shiftdistfunc = [];

%%%  FB #2
if 1
  Params.visFB(2) = Params.visFB(1);
else
  %  squares
  Params.visFB(2).RGB = [1 1 0];
  Params.visFB(2).bright = 0.7;
  Params.visFB(2).points = sqrpts;
  Params.visFB(2).rad = sqrscale;
  Params.visFB(2).angle = 45;%pi/4;
  Params.visFB(2).fill = 1;
  Params.visFB(2).FBFunc = 'Fng_FB';
  %Params.visFB(2).shiftparams = {[[-20 -10 10 20];[0 0 0 0]]};  %[[Xlow_lower Xlow_upper Xhigh_lower Xhigh_upper];[Ylow_lower ...]]
  %  For early training only
  Params.visFB(2).shiftparams = {[[0 0 0 0];[0 0 0 0]]};  %[[Xlow_lower Xlow_upper Xhigh_lower Xhigh_upper];[Ylow_lower ...]]
  %  -----
  Params.visFB(2).shiftparams2 = [];%[2 0];
  %Params.visFB(2).shiftdistfunc = @(sparms) birandomshift('linear','inside',Params.visFB(2).shiftparams2,sparms); %shiftdistfunc;
  Params.visFB(2).shiftdistfunc = [];%@(sparms) birandomshift('none','none',sparms); %shiftdistfunc;
  %  Proportion of trials with no FB shift.  For testing variance (neural or
  %  behavioral) of this cue.
  Params.visFB(2).zeroshiftproportion = 1;
  Params.visFB(2).P_starttargetfeedback = 1;
end

%%%  FB #3
if 1
  Params.visFB(3) = Params.visFB(1);
else
  Params.visFB(3).RGB = [0 1 1];
  Params.visFB(3).bright = 0.7;
  Params.visFB(3).points = sqrpts;%trianglepts;%pts;
  Params.visFB(3).rad = sqrscale;
  Params.visFB(3).angle = 0;
  Params.visFB(3).fill = 1;
  Params.visFB(3).FBFunc   = 'Fng_FB';
  %  For early training only
  Params.visFB(3).shiftparams = {[[0 0 0 0];[0 0 0 0]]};  %[[Xlow_lower Xlow_upper Xhigh_lower Xhigh_upper];[Ylow_lower ...]]
  %  -----
  Params.visFB(3).shiftparams2 = [];%[2 0];
  %Params.visFB(3).shiftdistfunc = @(sparms) birandomshift('linear','outside',Params.visFB(3).shiftparams2,sparms); %shiftdistfunc;
  %Params.visFB(3).shiftparams = {[[-40 -10 10 40];[0 0 0 0]]};  %[[Xlow_lower Xlow_upper Xhigh_lower Xhigh_upper];[Ylow_lower ...]]
  Params.visFB(3).shiftdistfunc =  [];%@(sparms) birandomshift('none','none',sparms); %shiftdistfunc;
  %  Proportion of trials with no FB shift.  For testing variance (neural or
  %  behavioral) of this cue.
  Params.visFB(3).zeroshiftproportion = 1;
  Params.visFB(3).P_starttargetfeedback = 1;
end
% - - - - - - -
%%

%%  Target Object Setup
%%%%%% HAND target parameters
Params.START_TARGET_SHOW     = 0;    % Show start target
%Params.START_TARGET_FEEDBACK = 0;    % Feedback ON
%Params.P_START_TARGET_FEEDBACK = 0.50;    % P of FB on at start target
Params.START_TARGET_WIN      = 6;%8;  %  This determines when he has acquired the start target
Params.START_TARGET_WIN_2    = 13;  %  This determines whether he leaves it, once it has been acquired but before FB comes on.
Params.START_TARGET_WIN_3    = 7;  %  This determines whether he leaves it, once it has been acquired and the FB has come on.
Params.START_TARGET_RAD      = Params.START_TARGET_WIN_2;%12;
Params.START_TARGET_VEL_CRIT = 45;%50;%30;%1.1;  %  mm/sec??
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
% to declare test trials ok
Params.REACH_TARGET_POS_FUNC = ['[rand(1)*range(Params.wsBounds(:,1))+min(Params.wsBounds(:,1))' ...
  ' rand(1)*range(Params.wsBounds(:,2))+min(Params.wsBounds(:,2))]'];

%%% --  Eye Target Params
Params.EYE_TARGET_WIN       = 17.5;%15;%25;%25;%20;%25;%45;
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

Params.EYE_TARGET_POS_FUNC  = ['[rand(1)*range(Params.eyeWS(:,1))+min(Params.eyeWS(:,1)) ' ...
  'rand(1)*range(Params.eyeWS(:,2))+min(Params.eyeWS(:,2))]'];

%%

%% DELAYS and PAUSES
Params.START_TARGET_HOLD        = 0.7;% 0.5;%0.75;%1.0;  %  Initial hold before eye target comes on
Params.REACH_TARGET_HOLD        = 0.5;  % (sec) time must hold to get final reward
%%%
if 0  %  for training purposes make this longer for now.
  Params.EYE_TARGET_HOLD          = 0.5;
else  %  change back to this
  Params.EYE_TARGET_HOLD          = 0.25;%1.0;  %  (if fixation is always at the reach target, this is when he first gets info about its location)
end
%%%
Params.EYE_TARGET_HOLD_2          = 2.75;  %  For Learn_to_Fixate trials
if 1
  Params.START_TARGET_FB_HOLD_DUR_MIN = 0.8 %  Hold duration during FB (or FB-) delay
Params.START_TARGET_FB_HOLD_DUR_MAX = Params.START_TARGET_FB_HOLD_DUR_MIN;% + 0.5;
else
Params.START_TARGET_FB_HOLD_DUR_MIN = Params.EYE_TARGET_HOLD;%Params.START_TARGET_HOLD;  %  Hold duration during FB (or FB-) delay
Params.START_TARGET_FB_HOLD_DUR_MAX = Params.START_TARGET_FB_HOLD_DUR_MIN;% + 0.5;
end

Params.P_NONZERO_REACH_DELAY = 1;%0.95;%0.95;%0.3;  %  Use reach_delay_min and _max criteria on this proportion of trials.  The rest will be zero delay RT trials.
Params.REACH_DELAY_MIN     = 0.7;%0.15;%0.2;%0.75;       % Delay hold range after reaching start target and before
Params.REACH_DELAY_MAX     = 1.6;%1.3;      % go tone signals a move to the reach target.

Params.START_TARGET_PENALTY  = 0;%10;
Params.ERR_PENALTY           = 0;%1000; % MSEC EXTRA (in addition to inter_trial_delay) delay between trials if there is an error.
Params.SWAT_PENALTY          = Params.ERR_PENALTY;%4000; % MSEC delay if velocity is above a certain amount


%%% TIMEOUTS
if DEBUG
  Params.REACH_START_TARGET_TIMEOUT     = 3;
else
  Params.REACH_START_TARGET_TIMEOUT     = 14; %8; % (sec) max allowed time to position hand at start target
end
Params.MAX_MOVE_TIME_TO_START_TARGET  = 6;  %  The maximum amount of time allowed to acquire the start target, once he starts moving.
Params.REACH_TARGET_TIMEOUT           = 1.4;%1.75; %???????? (sec) max allowed time to reach reaching target
Params.REACH_TARGET_TIMEOUT_2         = 1.5;%1.1; % (sec) max allowed time to reach reaching target
Params.EYE_TARGET_TIMEOUT             = 4;
%%

%% Tones

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
%%

%%  Reach Phase Parameters
%  Start targets
Params.Nstarttargets = [];%10;
%Params.Nshiftsperstarttarget = 2;

Params.P_FBonRP = [1];
%Params.FBonReachProportion = 0.5;  %  How far into the reach the FB comes back on.  It is turned off at FBoffReachProportion.
Params.FBonReachProportion = inf;  %  How far into the reach the FB comes back on.  It is turned off at FBoffReachProportion.
%Params.FBonReachProportion = 0.75;  %  How far into the reach the FB comes back on.  It is turned off at FBoffReachProportion.

%Params.FBoffReachProportion = 0.02;

Params.FBoffReachDistance = 1.5;

%  FB shifts
%Params.FBshiftrate = 0.2;  %  cm of shift / cm of hand movement
%Params.FBshiftradius = 2;
Params.FBshiftradius = [];%15;
Params.FBshiftdirs = [];%[0:7].*pi/4;%[pi/4 pi/2 pi -pi/4];%Params.reachdirs([1:2:end]);%Params.FBshiftdirs = [0:3].*pi/2;  %  These should be chosen from the set of reach trg directions
Params.P_FBshift = [];%0;%0.7;  %

%  Learning eye fixation while reaching
Params.reachTrgShowDur = [];%1.5;
Params.reachTrgBrightMultiplier = [];%1;%0.25;  %  For learning to fixate trials.  Reach target will be dimmed by this multiple

%  Set the initial distance of the reach over which he has to maintain Eye Fixation
%  This should be at least as long as FBoffReachDistance
Params.EyeFixationReachDistance = inf;%65;%25;%%50;%2; %0.5;
%Params.EyeFixationReachProportion = 0.01;%-inf;%0.05;
Params.MaintainFixationDuringHoldFlag = 1;

Params.P_FullFeedback = 0;%0.02;  %  Proportion of non-test trials on which FB is not exinguished.  Does not apply to test trials.

Params.MIN_EYE_TO_REACH_DISTANCE = Params.EYE_TARGET_WIN.*1.5;%30;
Params.MIN_REACH_DISTANCE     = 30; %  mm. for random target locations. Min distance from start to reach target
Params.MIN_EYE_TO_START_DISTANCE = 40;
Params.MAX_REACH_DISTANCE = 100;

%%

%%  Performance Feedback
Params.useGradedReward = 1;
Params.doneCritSpeed = 2;  %  mm/s, speed below which we consider the reach to be complete.
Params.reachBonusTau            = 15;%20;
Params.reachBonusFunc           = inline('1./exp(t./tau.^0.95);','t','tau');
%Params.giveBonusFeedbackFlag    = 1;
Params.performanceFBPause       = 0.75;%0.2;%1.75;
Params.randBonusC               = [];%[37 -4; -4 28].*0.4;  %  For shifted trials, draw a position error from ~N(0,randBonusC), and use that to give a bonus score.
%  Do we give normal feedback for shift trials, or draw the reward from the no shift trial
%  distribution?  If we're not giving normal feedback then we also don't want to show the
%  endpoint location.
Params.randomShiftTrialBonusFlag = 1;
%%

%%  Params specific for Trial Type #7
Params.Nfixtargspertrial = [0 3 3 1 1 0];  % Relative proportion
Params.Nfixtargspertrial = Params.Nfixtargspertrial./sum(Params.Nfixtargspertrial);

Params.EYE_TARGET_HOLD_7 = 0.7;
Params.EYE_TARGET_TIMEOUT_71             = 4;
Params.EYE_TARGET_TIMEOUT_72             = 1.75;%0.75;

%  Trial type 7 tone --  Hand hold, multiple fixation targets
Params.TRIAL_TYPE_TONE(7).FREQ = 300;
Params.TRIAL_TYPE_TONE(7).NPULSES = 3;
Params.TRIAL_TYPE_TONE(7).PULSEDUR = .1;
Params.TRIAL_TYPE_TONE(7).TOTALDUR = 0.5;
Params.TRIAL_TYPE_TONE(7).IPI = (Params.TRIAL_TYPE_TONE(7).TOTALDUR - ...
  Params.TRIAL_TYPE_TONE(7).PULSEDUR*Params.TRIAL_TYPE_TONE(7).NPULSES) / ...
  (Params.TRIAL_TYPE_TONE(7).NPULSES - 1);
if Params.TRIAL_TYPE_TONE(7).IPI < 0, error('Bad Tone Sequence'); end

%%

%%  Other Objects Setup
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
%%

if DEBUG
  fprintf('\n\n- - - - WARNING: DEBUG MODE ON ---------\n');
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%  - - - - - -   Subfunctions  - - - -

function U = birandomshift(whichFunc,whichWay,dparms,B)
%
%  Helper function for generating FB shifts for cueReliability task.
%
%
%  MF Nov. 7, 2007.
%

if isequal(lower(whichFunc),'none')
  U = [0 0];
  return
else

  switch lower(whichFunc)

    case 'flat'

      Xbnds = B(1,:);
      Ybnds = B(2,:);

      x0 = (Xbnds(4)-Xbnds(3) - (Xbnds(1)-Xbnds(2))).*rand(1) + (Xbnds(1)-Xbnds(2));
      if x0 < 0
        U(1) = x0 + Xbnds(2);
      else
        U(1) = x0 + Xbnds(3);
      end

      y0 = (Ybnds(4)-Ybnds(3) - (Ybnds(1)-Ybnds(2))).*rand(1) - (Ybnds(1)-Ybnds(2));
      if y0 < 0
        U(2) = y0 + Ybnds(2);
      else
        U(2) = y0 + Ybnds(3);
      end

    case 'linear'
      fh = @(l,u,lr) lineardist(lower(whichWay),dparms,l,u,lr);
      U = buildshift(fh,B);

    case 'halfgauss'

      fh = @(l,u,lr) halfgaussdist(lower(whichWay),dparms,l,u,lr);
      U = buildshift(fh,B);

    case 'exponential'

    otherwise
      error(sprintf('%s: Unknown distribution function',mfilename));
  end
end

return

%%  - - - - - -
function shift = buildshift(fH,bnds)

shift = [inf inf];
for xyi = 1:2
  b = bnds(xyi,:);

  dlts = [range(b([1 2])) range(b([3 4]))];
  p = dlts./sum(dlts);
  lri = (rand(1)<=p(1));

  shift(xyi) = fH(b(2*lri + 1),b(2*lri+2),lri);
end

return
%% ------------


%%  - - - - - -
function shift = lineardist(ww,parms,lower,upper,lr)

d = range([lower upper]);
u = rand(1);

x = sqrt((u)*2/parms(1))/sqrt(2/parms(1));
if (~lr & isequal(ww,'inside')) | (lr & isequal(ww,'outside'))

else
  x = 1-x;
end
s = x*d;
shift = lower + s;

return
%%  --------------



%%  - - - - - -
function shift = halfgaussdist(ww,parms,lower,upper,lr)


return
%%  -----------