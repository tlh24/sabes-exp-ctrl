function DispCalibMtx = GetDisplayCalibMatrix( )

  strDisplayCalbFilename = GetDisplayCalibFilename();
  % Save matrix in the default dir under default name
  load(strDisplayCalbFilename, 'DispCalibMtx');
