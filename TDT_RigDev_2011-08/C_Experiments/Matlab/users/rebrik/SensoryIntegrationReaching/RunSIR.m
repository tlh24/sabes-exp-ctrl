function RunSIR(name, calibFile)

global Params hMou NO_ISCAN

NO_ISCAN = 0;
if (nargin<1),
    fprintf('\n+++ ERROR: Missing Input Parameters! \n')
    fprintf('You must specify the following:\n')
    fprintf(' MonkeyName\n\n');%, EyeCalibFile, Experiment\n\n ')
    return
% elseif nargin < 2
%    NO_ISCAN = 1;
end
NO_ISCAN = 0;
Params.NAME = name;

if ~NO_ISCAN
%%% Load Eye Calibration file 
% calibDir = 'C:\Lab\matlab\MonkeyEyeCalib\'; 
% fprintf('Load Eye Tracker Calibration File: %s%s_EyeCal.mat... \n',...
%         calibDir,calibFile);
% EyeLoadCalibration(calibFile,calibDir); 

% Params.eyeCalibDir = calibDir;
% Params.eyeCalibFile = [calibFile '_EyeCal'];
% load(fullfile(calibDir,Params.eyeCalibFile));
% Params.eyeCalibration = eyeCalibration;
else
    Params.eyeCalibDir = [];
    Params.eyeCalibFile = [];
end

fprintf('Set Experiment Parameters... \n');
SensIntReaching_Params;

%%% 
fprintf(' \n')
fprintf('Starting sensory integration reaching Task...\n')
test = ' ';


%openvar('Params');

fprintf('Start Experiment... \n');
SensIntReaching(test);

