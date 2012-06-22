strDataDir = 'D:\DataTmp\for_Sergei\';

% % RecOff Ok Recording delay: 1.728313
strMatName{1} = 'E071008_RecStartStop.mat';
strNevName{1} = 'E071008_PMd001.nev'; 

% % RecOff Ok Recording delay: 588.968130
strMatName{2} = 'E071011_RecStartStop.mat';
strNevName{2} = 'sorted_E071011_M1001.nev'; 
% 
% % RecOff Ok Recording delay: 0.027047
strMatName{3} = 'E071019_RecStartStop.mat';
strNevName{3} = 'sorted_E071019_M1001.nev'; 
% 
% % RecOff Ok 888 sec delay
strMatName{4} = 'E071022_RecStartStop.mat';
strNevName{4} = 'E071022_M1001.nev';  
% 
% % RecOff Ok Rec Delay 648sec
strMatName{5} = 'E071030_RecStartStop.mat';
strNevName{5} = 'E071030_M1001.nev'; 
% 
% % RecOff Ok Recording delay: 0.049713
strMatName{6} = 'E071102_RecStartStop.mat';
strNevName{6} = 'sorted_E071102_PMd001.nev'; 
% 
% % RecSync Ok Recording delay: 0.0627
strMatName{7} = 'E071130_RecStartStop.mat';
strNevName{7} = 'E071130_test.nev'; 
% 
% % RecSync Ok Recording delay: 0.097173
strMatName{8} = 'E071219_RecStartStop.mat';
strNevName{8} = 'E071219_M1_PMd001.nev'; 

for i=1:8
  strMatPath = [strDataDir strMatName{i}];
  strNevPath = [strDataDir strNevName{i}];

  fprintf('Data file: %s\n', strNevPath);
  load(strMatPath);
  NevSaveSpikeTimes( strNevPath, RecStart, RecStop);
end
