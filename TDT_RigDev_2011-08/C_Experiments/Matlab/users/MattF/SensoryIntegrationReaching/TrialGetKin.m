function [Coords,Vel,Times,iIdx] = TrialGetKin(h,marker,N,DOFs)
%
%  This is a wrapper function for getting kinematics from the Tracker
%  (Liberty or Optotrak).  It invokes the GetSensorLatest method.
%
%  There are a few differences between this function and the outputs from
%  GETSENSORLATEST.
%
%  TRIALGETKIN
%  1. Returns an additional output, VEL
%  2. Returns Times in secs, rather than msecs.
%  3. Transposes the Coords matrix so that variables go across the columns.
%
%   ---  INPUTS  ---
%   h:          Handle:     Handle to the Tracker COM object
%   marker:     Scalar:     Index of Tracker marker of interest.
%   N:          Scalar:     Number of samples to return.
%   DOFs:       Vector:     Which Degrees of Freedom you want, passed as
%                           indices, e.g., typically [1 2 3] will give you X, Y, Z.
%
%   --- OUTPUTS  ---
%   Coords:     N x m array:    The Kinematics coordinates (mm). m = length(DOFs).
%                               Note that this is the transpose of what the
%                               GetSensorLatest method returns.
%   Vel:        1 x m vector:   The average velocity based on the first and
%                               Nth samples.  Converted into mm/sec. N must
%                               be > 1.
%   Times:      N x 1:          Sample Times (secs).
%   iIdx:       N x 1:          Indices of data samples.
%
%
%  See also:  TrialGetEye.m
%
if nargin < 2
  marker = 1;
end
if nargin < 3
  N = 10;
end
if nargin < 4
  DOFs = [1 2];
end

Vel = [];

[iIdx, Times, Coords ] = invoke( h, 'GetSensorLatest', marker, N);
Coords = Coords(DOFs,:)';
iIdx = iIdx(:);
Times = Times(:)./1000;  %  Convert to secs

if N > 1
  Vel = (Coords(end,:)-Coords(1,:))./(Times(end)-Times(1));
end
