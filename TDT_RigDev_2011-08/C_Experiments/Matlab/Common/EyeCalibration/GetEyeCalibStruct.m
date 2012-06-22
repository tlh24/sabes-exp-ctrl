function EyeCalibStruct = GetEyeCalibStruct( )

  strEyeCalbFilename = GetEyeCalibFilename();
  load(strEyeCalbFilename, 'EyeCalibStruct');
