function targets = SIRGetTargs(Params)
%
%
%
%
%
%  MF March 22, 2007.  Aug 3, 2007.
%



if Params.chooseTargetMethod == 1

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

else

    %  Randomly select start targets within the sub-workspace.  Each start
    %  target will have the 8 associated reach targets, and some number of
    %  offset start targets.


    swsBounds = Params.wsBounds + [Params.reachradius Params.reachradius; -Params.reachradius -Params.reachradius];
    sx = rand(Params.Nstarttargets,1).*range(swsBounds(:,1)) + swsBounds(1,1);
    sy = rand(Params.Nstarttargets,1).*range(swsBounds(:,2)) + swsBounds(1,2);

    Nrt = ceil(Params.N_TRIALS / (Params.Nstarttargets*(1+Params.Nshiftsperstarttarget)));
    start = []; reach = [];
    for si = 1:Params.Nstarttargets

        %  Generate the reach target locations
        [rx0,ry0] = pol2cart(Params.reachdirs,Params.reachradius);
        rx = rx0 + sx(si);
        ry = ry0 + sy(si);

        %  Choose the shifted start targets
        done = 0; nsx = [];
        while ~done
            idx = unidrnd(length(Params.FBshiftdirs),Params.Nshiftsperstarttarget,1);
            [svx,svy] = pol2cart(Params.FBshiftdirs(idx),Params.FBshiftradius);
            nsx = [nsx; sx(si) + svx(:) sy(si) + svy(:)];

            ki = (nsx(:,1)>=swsBounds(1,1) & nsx(:,1)<=swsBounds(2,1)) & (nsx(:,2)>=swsBounds(1,2) & nsx(:,2)<=swsBounds(2,2));

            if sum(ki)~=size(nsx,1)
                nsx = nsx(ki,:);
            else
                done = 1;
            end
        end
        nsx = nsx(1:Params.Nshiftsperstarttarget,:);

        NSX = repmat([sx(si) sy(si); nsx],Nrt,1);

        idx = unidrnd(length(rx),size(NSX,1),1);
        RX = rx(idx);
        RY = ry(idx);

        reach = [reach; RX(:) RY(:)];
        start = [start; NSX];
    end


end

rpi = randperm(size(start,1));
reach = reach(rpi,:);
start = start(rpi,:);

targets = [start reach];