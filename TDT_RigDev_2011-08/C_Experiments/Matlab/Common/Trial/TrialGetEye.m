function [Coords,Vel,Times,iIdx] = TrialGetEye(h,N)
%
%  This is a wrapper function for getting Eye data from the EyeTracker.
%  It invokes the GetDataLatest method.
%
%  There are a few differences between this function and the outputs from
%  GetDataLatest.
%
%  TRIALGETEYE
%  1. Returns an additional output, VEL
%  2. Returns Times in secs, rather than msecs.
%  3. Transposes the Coords matrix so that variables go across the columns.
%
%   ---  INPUTS  ---
%   h:          Handle:     Handle to the Eye Tracker COM object
%   N:          Scalar:     Number of samples to return.
%
%   --- OUTPUTS  ---
%   Coords:     N x 2 array:    The Eye kinematics (mm).
%                               Note that this is the transpose of what the
%                               GetDataLatest method returns.
%   Vel:        1 x m vector:   The average velocity based on the first and
%                               Nth samples.  Converted into mm/sec. N must
%                               be > 1.
%   Times:      N x 1:          Sample Times (secs).
%   iIdx:       N x 1:          Indices of data samples.
%
%
%
%  See also:  TrialGetKin.m
%
if nargin < 2 
  N = 5;
end

Vel = [];

[iIdx, Times, Coords ] = invoke( h, 'GetDataLatest', N);
Coords = Coords';
Times = Times(:)./1000;
iIdx = iIdx(:);

if N > 1
  Vel = (Coords(end,:)-Coords(1,:))./(Times(end)-Times(1));
end