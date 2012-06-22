function RunSIR(name, calibFile)

global Params hMou NO_ISCAN

NO_ISCAN = 0;
if (nargin<1),
    fprintf(1,'\n+++ ERROR: Missing Input Parameters! \n')
    fprintf(1,'You must specify the following:\n')
    fprintf(1,' MonkeyName\n\n');%, EyeCalibFile, Experiment\n\n ')
    return
elseif nargin < 2
    NO_ISCAN = 1;
end

Params.NAME = name;

if ~NO_ISCAN
%%% Load Eye Calibration file 
calibDir = 'C:\Lab\matlab\MonkeyEyeCalib\'; 
fprintf(1,'Load Eye Tracker Calibration File: %s%s_EyeCal.mat... \n',...
        calibDir,calibFile);
EyeLoadCalibration(calibFile,calibDir); 

Params.eyeCalibDir = calibDir;
Params.eyeCalibFile = [calibFile '_EyeCal'];
load(fullfile(calibDir,Params.eyeCalibFile));
Params.eyeCalibration = eyeCalibration;
else
    Params.eyeCalibDir = [];
    Params.eyeCalibFile = [];
end

fprintf(1,'Set Experiment Parameters... \n');
SensIntReaching_Params;

%%% 
fprintf(1,' \n')
fprintf(1,'Starting sensory integration reaching Task...\n')
test = ' ';


%openvar('Params');

fprintf(1,'Start Experiment... \n');
SensIntReaching(test);

