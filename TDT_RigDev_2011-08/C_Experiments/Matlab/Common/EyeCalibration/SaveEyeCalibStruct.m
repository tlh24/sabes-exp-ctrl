function SaveEyeCalibStruct( EyeCalibStruct )
  
  % get old calibration 
  OldEyeCalibStruct = GetEyeCalibStruct( );
  
  strEyeCalbBackupFilename =  GetEyeCalibBackupFilename();
  % parse the name into path, name, ext, version
  [strPath, strName, strExt, strVer ] = fileparts(strEyeCalbBackupFilename);
  dTime = datevec(OldEyeCalibStruct.DateTime);
  dTime(6) = floor(dTime(6)); % round-off seconds
  strFileSuffix = sprintf('_%04d-%02d-%02d_%02d-%02d-%02d', dTime); 
  % insert file suffix
  strOldCalbFilename = [ strPath '\' strName strFileSuffix strExt ];
  % Save old structure in the backup dir
  SaveEyeCalibFile(strOldCalbFilename, OldEyeCalibStruct);

  % Finally save the new structure
  strEyeCalbFilename = GetEyeCalibFilename();
  SaveEyeCalibFile(strEyeCalbFilename, EyeCalibStruct);
