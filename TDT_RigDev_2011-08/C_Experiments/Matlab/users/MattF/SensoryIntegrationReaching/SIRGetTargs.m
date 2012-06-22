function targets = SIRGetTargs(Params)
%
%
%
%
%
%  MF March 22, 2007.  Aug 3, 2007.
%



targets = [];
return;

starttrgpos = Params.wsCenter(:)';
Nstarttrgs = 1;

Nrtps = ceil(Params.N_TRIALS/Nstarttrgs);

start = []; reach = [];
for si = 1:size(starttrgpos,1)
    sx = starttrgpos(si,1);
    sy = starttrgpos(si,2);

    %  Generate the reach target locations
    [rx0,ry0] = pol2cart(Params.reachdirs,Params.reachradius);
    rx = rx0 + sx(si);
    ry = ry0 + sy(si);

    ridx = unidrnd(length(rx),Nrtps,1);

    start = [start; repmat([sx sy],length(ridx),1)];
    reach = [reach; rx(ridx)' ry(ridx)'];

end
