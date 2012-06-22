function err = EyeLoadCalibration(fileroot,filedir)

%% function err = EyeLoadCalibration(fileroot,filedir)
%%
%% will load file 'filedir/fileroot_EyeCal.mat'
%%
%%

global eyeStruct

EYE_CAL_HOME = 'C:\Lab\matlab\MonkeyEyeCalib\';

if(nargin<2) filedir=EYE_CAL_HOME; end
load([filedir,fileroot,'_EyeCal']);

if(exist('eyeCalibration'))
    fprintf(1,'Loading Calibration File \n')
    eyeStruct.calibCoef = eyeCalibration.calibCoef;
    eyeStruct.calibType = eyeCalibration.calibType;
    eyeStruct.calibrated = 1;
    err=0;
else
    err=1;
end
