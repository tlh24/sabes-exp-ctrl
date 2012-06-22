

% strFileName = 'D:\DataTmp\RecTime03\RecTime001.nev';
% strFileName = 'D:\DataTmp\RecTime00\RecTime001.nev';
strFileName = 'D:\DataTmp\E071031_M1001.nev'

dRecOnTS = 0;
dRecOffTS = 0;

[dTS_c0 dTS_c1 dCerebusDuration] = NevCalcTimeCoeffs( strFileName, dRecOnTS, dRecOffTS);
