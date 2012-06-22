strTank = 'Calvin';
iLocationID = 1;
strDataDir = 'D:\DataTmp\';
iChannelList = [1];

% iBlock = 38;
% dGlobRecStartTS = 2561.3864960000003;
% dTS_Stop = 2571.39400704;


iBlock = 2;
dGlobRecStartTS = 1865.1717632;
dTS_Stop = 2965.47893248;

dTS_Start = dGlobRecStartTS;

RX5_SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
                iChannelList, dTS_Start, dTS_Stop, ...
                dGlobRecStartTS  );
