function TrackerSaveCalibMatrix( TrackerCalibMtx )

  strTrackerCalbFilename = TrackerGetCalibFilename();
  % Save matrix in the default dir under default name
  save(strTrackerCalbFilename, 'TrackerCalibMtx');
