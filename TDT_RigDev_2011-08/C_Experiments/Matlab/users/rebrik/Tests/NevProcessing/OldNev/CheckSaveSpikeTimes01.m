strDataDir = 'D:\DataTmp\recentdata_080211\';
strNevName = 'E080201_M1_PMd001_sorted.nev';

strNevPath = [strDataDir strNevName];
fprintf('Data file: %s\n', strNevPath);

% Params.EventCodes.Recording_Start 12002000 [5685.16411392;]
% Params.EventCodes.Recording_Stop  12001000 

% NevSaveSpikeTimes( strNevPath, 5685.16411392 );
% NevSaveSpikeTimes( strNevPath);  
NevGetTimeConversion( strNevPath, 5685.16411392 ); % c0 and c1:  5684.27548  1.0000040
NevGetTimeConversion( strNevPath, [], []);         % c0 and c1:  5684.27547  1.0000040
