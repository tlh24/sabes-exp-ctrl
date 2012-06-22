function [c0 c1] = ExperimentCalcLinCoeffs(x1, x0, y1, y0)

dX = x1-x0;
dY = y1-y0;
if 0%dY < 2000
  warning('Experiment:ShortUpdateInterval', ...
          'Short time interval in timing update: %g seconds\n', dY/1000);
end

c1=dY/dX;
c0=(y0*x1-y1*x0)/dX;

