strDataDir = 'F:\Data\for_Sergei\';

% % RecOff Ok Recording delay: 1.728313
% strMatName = 'E071008_RecStartStop.mat';
% strNevName = 'E071008_PMd001.nev'; 

% % RecOff Ok Recording delay: 588.968130
% strMatName = 'E071011_RecStartStop.mat';
% strNevName = 'sorted_E071011_M1001.nev'; 
% 
% % RecOff Ok Recording delay: 0.027047
% strMatName = 'E071019_RecStartStop.mat';
% strNevName = 'sorted_E071019_M1001.nev'; 
% 
% % RecOff Ok 888 sec delay
% strMatName = 'E071022_RecStartStop.mat';
% strNevName = 'E071022_M1001.nev';  
% 
% % RecOff Ok Rec Delay 648sec
% strMatName = 'E071030_RecStartStop.mat';
% strNevName = 'E071030_M1001.nev'; 
% 
% % RecOff Ok Recording delay: 0.049713
% strMatName = 'E071102_RecStartStop.mat';
% strNevName = 'sorted_E071102_PMd001.nev'; 
% 
% % RecSync Ok Recording delay: 0.0627
% strMatName = 'E071130_RecStartStop.mat';
% strNevName = 'E071130_test.nev'; 
% 
% % RecSync Ok Recording delay: 0.097173
% strMatName = 'E071219_RecStartStop.mat';
% strNevName = 'E071219_M1_PMd001.nev'; 

strMatPath = [strDataDir strMatName];
strNevPath = [strDataDir strNevName];

fprintf('Data file: %s\n', strNevPath);
load(strMatPath);
[dTS_c0 dTS_c1 dRecDelay] = NevCalcTimeCoeffs( strNevPath, RecStart, RecStop);

