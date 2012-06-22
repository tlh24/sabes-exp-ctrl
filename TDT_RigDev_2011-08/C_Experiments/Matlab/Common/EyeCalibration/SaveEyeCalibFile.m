function SaveEyeCalibFile( strEyeCalbFilename, EyeCalibStruct )
  
 % Save matrix under the standard name 'EyeCalibStruct'
  save(strEyeCalbFilename, 'EyeCalibStruct');

