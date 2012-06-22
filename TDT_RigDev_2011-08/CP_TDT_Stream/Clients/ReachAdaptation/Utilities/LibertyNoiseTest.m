
BUFFERTIME = 600;
PREDTIME = 1/75;
FRAMERATE = 240;

hL = actxserver('LibertyServer.Liberty');
%% setup
invoke(hL,'setup',BUFFERTIME,PREDTIME);
hL.active=1;


%% Tone
tdtInit('cannonball');






freq=0;
while(1)

    L=hL.latest;
    dist = L(end-1);
    
    if    (dist==0 & freq~=0)   freq=0; tdtTone(freq); disp(0);
    elseif(dist==1 & freq~=300) freq=300; tdtTone(freq); disp(1);
    elseif(dist==2 & freq~=600) freq=600; tdtTone(freq); disp(2);
    end    
end



tdtStop
release(hL)
