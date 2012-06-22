function X = boundedNormalRnd(C)
%
%
%
%
%
%  MF March 9, 2007.
%

crit = 0.0965;

X = [];
while isempty(X)
    x = mvnrnd([0 0],C,100);
    p = mvnpdf(x,[0 0],C);
    X = x(min(find(p>=crit)),:);
end