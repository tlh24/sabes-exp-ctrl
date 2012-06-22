ServerNamesInclude;

hTracker=actxserver('CP_OptoTrack.Application', strTrackerComputer);

hTracker.ConnectTracker;
pause(1);

% hTracker.ActivateSensors();
% fprintf('Sensors activated. \n');
% fprintf('Press any key to deactivate sensors \n');
% pause;
hTracker.DeactivateSensors();
fprintf('Sensors deactivated. \n');
fprintf('Press any key to activate sensors \n');
pause;
hTracker.ActivateSensors();
fprintf('Sensors activated. \n');

