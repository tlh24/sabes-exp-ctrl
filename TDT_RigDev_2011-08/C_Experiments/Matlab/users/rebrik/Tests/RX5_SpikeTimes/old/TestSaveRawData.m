strTank = 'Try00';
iLocationID = 1;
strDataDir = 'd:\tmp\';
iChannelList = [1, 2, 3, 4];

% iBlock = 38;
% dGlobRecStartTS = 2561.3864960000003;
% dTS_Stop = 2571.39400704;

iBlock = 39;
dGlobRecStartTS = 2696.6370713600004;
dTS_Stop = 2756.7394816;

dTS_Start = dGlobRecStartTS;

RX5_SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
                iChannelList, dTS_Start, dTS_Stop, ...
                dGlobRecStartTS  );
