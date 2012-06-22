function U = birandomshift(whichFunc,whichWay,dparms,B)
%
%  Helper function for generating FB shifts for cueReliability task.
%
%
%  MF Nov. 7, 2007.
%

if isequal(lower(whichFunc),'none')
    U = [0 0];
    return
else

    switch lower(whichFunc)

        case 'flat'

            Xbnds = B(1,:);
            Ybnds = B(2,:);

            x0 = (Xbnds(4)-Xbnds(3) - (Xbnds(1)-Xbnds(2))).*rand(1) + (Xbnds(1)-Xbnds(2));
            if x0 < 0
                U(1) = x0 + Xbnds(2);
            else
                U(1) = x0 + Xbnds(3);
            end


            y0 = (Ybnds(4)-Ybnds(3) - (Ybnds(1)-Ybnds(2))).*rand(1) - (Ybnds(1)-Ybnds(2));
            if y0 < 0
                U(2) = y0 + Ybnds(2);
            else
                U(2) = y0 + Ybnds(3);
            end

        case 'linear'
            fh = @(l,u,lr) lineardist(lower(whichWay),dparms,l,u,lr);
            U = buildshift(fh,B);

        case 'halfgauss'

            fh = @(l,u,lr) halfgaussdist(lower(whichWay),dparms,l,u,lr);
            U = buildshift(fh,B);

        case 'exponential'

        otherwise
            error(sprintf('%s: Unknown distribution function',mfilename));
    end
end

return

%%  - - - - - -
function shift = buildshift(fH,bnds)

shift = [inf inf];
for xyi = 1:2
    b = bnds(xyi,:);

    dlts = [range(b([1 2])) range(b([3 4]))];
    p = dlts./sum(dlts);
    lri = (rand(1)<=p(1));

    shift(xyi) = fH(b(2*lri + 1),b(2*lri+2),lri);
end

return
%% ------------


%%  - - - - - - 
function shift = lineardist(ww,parms,lower,upper,lr)

d = range([lower upper]);
u = rand(1);

x = sqrt((u)*2/parms(1))/sqrt(2/parms(1));
if (~lr & isequal(ww,'inside')) | (lr & isequal(ww,'outside'))
    
else
    x = 1-x;
end
s = x*d;
shift = lower + s;

return
%%  --------------



%%  - - - - - - 
function shift = halfgaussdist(ww,parms,lower,upper,lr)


return
%%  -----------