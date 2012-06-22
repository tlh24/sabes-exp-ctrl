function S = ExperimentGetEventCodes
%
%
deltaD = 3;
%  NOTE:  the number of digits in any code must not exceed deltaD.

%  Placeholder.  Reserve the first deltaD digits for individual use.  These
%  could be used, e.g. to specify in which phase (e.g. acquire start target, acquire eye target, reach, etc.) of a trial a certain event
%  occurred by adding that number to the code.  For example,
%  S.EyeTarget_On + 3 could specify that the EyeTarget was
%  turned On in PHASE 3 of the trial.
D = 0;
%%%


%%%  Actions/Events
D = D+deltaD;
M = 10^D;
%%%  - - User Initiated
Hide      = 1*M;
Show      = 2*M;
Off       = Hide;
On        = Show;
Stop      = Hide;
Start     = Show;
Move      = 3*M;
Rotate    = 4*M;
SetScale  = 5*M;
SetColor  = 6*M;

Pause     = 10*M;
Resume    = 11*M;

%%%   - - Subject Initiated
%%% Events
Acquired      = 20*M;
Unacquired    = 21*M;
Held          = 22*M;
Timeout       = 23*M;

%Error         = 30*M;

%%% Objects --------
D = D+deltaD;
M = 10^D;
%%%   Display Objects
EyeTarget    = 1*M;
StartTarget  = 2*M;
ReachTarget  = 3*M;
VisFB        = 4*M;
DotField     = 5*M;

Text         = 8*M;
ArrowField   = 9*M;

%%%   Other
Trial         = 11*M;
Recording     = 12*M;
Tone          = 13*M;
Juice         = 14*M;
% - - - - - - - -

%%%  Uber Codes
D = D + deltaD;
M = 10^D;
Error = 1*M;
Success = 2*M;
%%  ------------------  END SPECIFY CODE HIERARCHY  -------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% %%% Catchall
% GenericError = 9999;

%S.GenericError      = GenericError;
S.Error                 = Error;

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

S.DotField_Hide        = DotField + Hide;
S.DotField_Show         = DotField + Show;
S.DotField_Move       = DotField + Move;
S.DotField_SetColor   = DotField + SetColor;
S.DotField_Rotate     = DotField + Rotate;

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
S.Trial_Success         = Trial + Success;

