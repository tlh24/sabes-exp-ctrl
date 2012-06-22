function PlexSaveClusteredSpikes( strTank, iBlock, iLocationID, strDataDir )

SpikeArray = PlexGetClusteredSpikes( strTank, iBlock, iLocationID, strDataDir );

strFileName = TankGetRawDataFilename( strTank, iBlock, iLocationID );
strFileFullPath = [strDataDir strFileName '_SpikeArray.mat'];
save(strFileFullPath, 'SpikeArray');

fprintf('Saved SpikeArray file: %s  \n', strFileFullPath);
