strTank = 'Calvin';
iBlock = 31;
iLocationID = 1;
strDataDir = 'C:\Data\';

SpikeArray = RX5_GetClusteredSpikes( strTank, iBlock, iLocationID, strDataDir );
strMatFileName = sprintf('SpikeArray%d', iBlock );
save(strMatFileName, 'SpikeArray');