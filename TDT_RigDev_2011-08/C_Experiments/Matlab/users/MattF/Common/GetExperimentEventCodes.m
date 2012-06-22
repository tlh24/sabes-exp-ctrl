function S = GetExperimentEventCodes(ExperimentName)
%
%  Temporary
%
%

%%% Catchall
GenericError = 9999;

%%%  Actions/Events
%%%  - - User Initiated
Hide      = 0;
Show      = 1;
Off       = Hide;
On        = Show;
Stop      = Hide;
Start     = Show;
Move      = 2;
Rotate    = 3;
SetScale  = 4;
SetColor  = 5;

Pause     = 10;
Resume    = 11;

%%%   - - Subject Initiated
%%% Events
Acquired      = 20;
Unacquired    = 21;
Held          = 22;
Timeout       = 23;

Error         = 30;

%%% Objects --------
%%%   Display Objects
EyeTarget    = 100;
StartTarget  = 200;
ReachTarget  = 300;
VisFB        = 400;

Text         = 800;
ArrowField   = 900;

%%%   Other
Trial         = 1100;
Recording     = 1200;
Tone          = 1300;
Juice         = 1400;
% - - - - - - - -

S.GenericError      = GenericError;

switch ExperimentName

  case 'SensIntReaching'
    S.EyeTarget_Hide        = EyeTarget + Hide;
    S.EyeTarget_Show        = EyeTarget + Show;
    S.EyeTarget_Move        = EyeTarget + Move;
    S.EyeTarget_SetColor    = EyeTarget + SetColor;
    S.EyeTarget_Acquired    = EyeTarget + Acquired;
    S.EyeTarget_Unacquired  = EyeTarget + Unacquired;
    S.EyeTarget_Held        = EyeTarget + Held;
    S.EyeTarget_Timeout     = EyeTarget + Timeout;

    S.StartTarget_Hide        = StartTarget + Hide;
    S.StartTarget_Show        = StartTarget + Show;
    S.StartTarget_Move        = StartTarget + Move;
    S.StartTarget_SetColor    = StartTarget + SetColor;
    S.StartTarget_Acquired    = StartTarget + Acquired;
    S.StartTarget_Unacquired  = StartTarget + Unacquired;
    S.StartTarget_Held        = StartTarget + Held;
    S.StartTarget_Timeout     = StartTarget + Timeout;

    S.ReachTarget_Hide       = ReachTarget + Hide;
    S.ReachTarget_Show        = ReachTarget + Show;
    S.ReachTarget_Move      = ReachTarget + Move;
    S.ReachTarget_SetColor  = ReachTarget + SetColor;
    S.ReachTarget_Acquired    = ReachTarget + Acquired;
    S.ReachTarget_Unacquired  = ReachTarget + Unacquired;
    S.ReachTarget_Held        = ReachTarget + Held;
    S.ReachTarget_Timeout     = ReachTarget + Timeout;

    S.VisFB_Hide            = VisFB + Hide;
    S.VisFB_Show            = VisFB + Show;
    S.VisFB_Move            = VisFB + Move;
    S.VisFB_SetColor        = VisFB + SetColor;

    S.ArrowField_Hide        = ArrowField + Hide;
    S.ArrowField_Show         = ArrowField + Show;
    S.ArrowField_Move       = ArrowField + Move;
    S.ArrowField_SetColor   = ArrowField + SetColor;
    S.ArrowField_Rotate     = ArrowField + Rotate;

    S.Tone_Show             = Tone + Show;
    S.Tone_Hide             = Tone + Hide;
    S.Tone_On               = Tone + On;
    S.Tone_Off              = Tone + Off;

    S.Juice_On              = Juice + On;
    S.Juice_Off             = Juice + Off;

    S.Recording_Start       = Recording + Start;
    S.Recording_Stop        = Recording + Stop;
    S.Recording_Pause       = Recording + Pause;
    S.Recording_Resume      = Recording + Resume;

    S.Trial_Start           = Trial + Start;
    S.Trial_Stop            = Trial + Stop;
    S.Trial_Error           = Trial + Error;
    
  otherwise
    error('Unknown Experiment type');
end
