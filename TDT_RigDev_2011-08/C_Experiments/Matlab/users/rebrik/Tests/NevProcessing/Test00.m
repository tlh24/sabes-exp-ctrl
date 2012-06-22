strDataDir = 'D:\Data\Cerebus\recentdata_080211\';
strNevName = 'E080201_M1_PMd001_sorted.nev';

strNevPath = [strDataDir strNevName];
fprintf('Data file: %s\n', strNevPath);

fprintf('===========================================================\n');
fprintf('Using old format: external RecSync global time\n');
fprintf('===========================================================\n');
NevGetTimeConversion( strNevPath, 5685.16411392 ); % c0 and c1:  5684.27548  1.0000040

fprintf('===========================================================\n');
fprintf('Using new format: self-contained\n');
fprintf('===========================================================\n');
NevGetTimeConversion( strNevPath, [], []);         % c0 and c1:  5684.27547  1.0000040
