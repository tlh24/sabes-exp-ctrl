function [c0 c1] = CalcLinCoeffs(x1, x0, y1, y0)

c1=(y1-y0)/(x1-x0);
c0=(y0*x1-y1*x0)/(x1-x0);
