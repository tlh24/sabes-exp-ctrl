strTank = 'Try00';
iBlock = 29;
iLocationID = 1;
strDataDir = 'd:\tmp\';
iChannelList = [1, 2, 3, 4, 5, 6];
dGlobRecStartTS = 540697.64096;
dTS_Start = dGlobRecStartTS;
dTS_Stop = 550720.63488;
nargin = 8;


SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
               iChannelList, dTS_Start, dTS_Stop, ...
               dGlobRecStartTS  );