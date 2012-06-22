function strFileName = RX5_GetRawDataFilename( strTank, iBlock, iLocationID )


TankConfigInclude;  % Tank store strings are defined here

strBlock  = sprintf('%s%d', strBlockPrefix, iBlock);    % Block name
strFileName   = sprintf('%s_%04d_%04d', strTank, iBlock, iLocationID);
