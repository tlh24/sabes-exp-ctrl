function CalibMtx = TrackerGetCalibMatrix( iMatrix )

  strTrackerCalibFilename = TrackerGetCalibFilename();
  load(strTrackerCalibFilename, 'TrackerCalibMtx');
  
  if ndims( TrackerCalibMtx ) < 3  % Single matrix format
    if nargin > 0
      warning('TrackerGetCalibMatrix(): iMatrix argument ignored, only one matrix is available.'); 
    end
    CalibMtx = TrackerCalibMtx;
  else
    if nargin == 1
      CalibMtx = TrackerCalibMtx(:,:,iMatrix);
    else
      CalibMtx = TrackerCalibMtx(:,:,1);
    end    
    
  end
