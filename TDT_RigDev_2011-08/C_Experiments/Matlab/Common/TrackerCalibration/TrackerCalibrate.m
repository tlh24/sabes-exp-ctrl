function TrackerCalibrate()

TrackerConfigInclude;

switch strTrackerID
  case 'Liberty'
    TrackerCalibrateLiberty(); 
  case 'Opto'
    TrackerCalibrateOpto();
  otherwise
    error('Invalid tracker ID: %s", strTrackerID');
end



