% Creates calibration matrix TrackerCalibration.mat
% in the directory C:\Experiments\Calibration
% DEFAULT Liberty transform will:
% 1) swap X and Z axes
% 2) invert Y axis
% 3) convert coordinates from cm to mm
%
%  July 15, 2009.  MF added second calibration matrix (for Axl rig)
%

function TrackerCalibrateLiberty()

fprintf('===============================================\n');
fprintf('           LibertyTrack calibration\n');
fprintf('===============================================\n');
fprintf('This function saves default Liberty transform.\n');
fprintf('0: DEFAULT Liberty transform will:\n');
fprintf('\t1) swap X and Z axes\n');
fprintf('\t2) invert Y axis\n');
fprintf('\t3) convert coordinates from cm to mm\n');
fprintf('1: New Liberty transform (Axl rig, July 17, 2009; (MF)) will:\n');
fprintf('\t1) swap X and Z axes\n');
fprintf('\t2) invert Y axis\n');
fprintf('\t3) convert coordinates from cm to mm\n');
fprintf('\t1) rotate axes to align with table\n\n');


if exist('rigConfigInclude','file')
  rigConfigInclude;
  if 1 & isequal(strRigName,'Axl')
    whichMatrix = 1;
  else
    whichMatrix = 0;
  end
else
  whichMatrix = 0;
end
fprintf('\n\t%s:  Using Matrix #%i\n\n',mfilename,whichMatrix);

switch whichMatrix
  case 0  %  Default Matrix
    TrackerCalibMtx = [  0     0     10
      0   -10     0
      10     0     0
      0     0     0 ];
  case 1  %  New matrix for Axl rig, July 17, 2009. (MF)
    %  Swap X & Z, and invert Y
    TrackerCalibMtx0 = [  0     0     10
      0   -10     0
      10     0     0
      0     0     0 ];
    
    %  Angles guesstimated empirically, July 21, 2009 (MF).
    rotangxy = -0.0818378;  %  Rotate XY plane about the z-axis so that the x- & y- axes are parallel with the table edges.
    %  The following 2 rotations align the XY plane with the table top.
    rotangxz = 0.003; %0.005 %  Rotate coord frame around y-axis.
    rotangyz = 0.015; %0.011;  %  Rotate coord frame around x-axis.
    rotmatxy = inline('[cos(x) -sin(x) 0; sin(x) cos(x) 0; 0 0 1]','x');
    rotmatxz = inline('[cos(x) 0 -sin(x); 0 1 0; sin(x) 0 cos(x)]','x');
    rotmatyz = inline('[1 0 0; 0 cos(x) -sin(x); 0 sin(x) cos(x)]','x');
    
    TrackerCalibMtx = TrackerCalibMtx0*rotmatxy(rotangxy)*rotmatxz(rotangxz)*rotmatyz(rotangyz);
    
  otherwise
    error('Huh?');
end

TrackerSaveCalibMatrix( TrackerCalibMtx );