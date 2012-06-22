load('RP2_Events');

iBlock = input('Enter block number: ');

strTank = 'Try00';
iLocationID = 1;
strDataDir = 'K:\Data\Try00\';
iChannelList = 1;
dTS_Start = dRecOnTS;
dTS_Stop = dRecOnTS + nSeconds;
dGlobRecStartTS = dRecOnTS;


RX5_SaveTankRawData(strTank, iBlock, iLocationID, strDataDir, ...
                         iChannelList, dTS_Start, dTS_Stop, ...
                         dGlobRecStartTS  );