function SaveDisplayCalibMatrix( DispCalibMtx )

  strDisplayCalbFilename = GetDisplayCalibFilename();
  % Save matrix in the default dir under default name
  save(strDisplayCalbFilename, 'DispCalibMtx');
