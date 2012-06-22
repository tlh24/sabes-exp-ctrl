strDataDir = 'D:\Data\Cerebus\recentdata_080211\';
strNevName = 'E080201_M1_PMd001_sorted.nev';

strNevPath = [strDataDir strNevName];
fprintf('Data file: %s\n', strNevPath);


fprintf('===========================================================\n');
fprintf('Using new format: self-contained\n');
fprintf('===========================================================\n');
NevSaveSpikeTimes( strNevPath );   
