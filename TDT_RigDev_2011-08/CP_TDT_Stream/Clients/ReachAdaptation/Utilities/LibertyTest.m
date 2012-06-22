hL = actxserver('LibertyServer.Liberty');
invoke(hL,'setup',0,0.015);

n0=1;
n=hL.errCount; for i=n0:n, fprintf(1,'%d: %s\n',i,hL.getErr(i)); end; n0=n+1;
hL.active=1;
n=hL.errCount; for i=n0:n, fprintf(1,'%d: %s\n',i,hL.getErr(i)); end; n0=n+1;

%pause(1)
hL.latest
n=hL.errCount; for i=n0:n, fprintf(1,'%d: %s\n',i,hL.getErr(i)); end; n0=n+1;

if(1)
    hL.startBuffer;
    n=hL.errCount; for i=n0:n, fprintf(1,'%d: %s\n',i,hL.getErr(i)); end; n0=n+1;
    pause(1);
    hL.stopBuffer;
    n=hL.errCount; for i=n0:n, fprintf(1,'%d: %s\n',i,hL.getErr(i)); end; n0=n+1;
    t=invoke(hL,'getBuffer',1)
    n=hL.errCount; for i=n0:n, fprintf(1,'%d: %s\n',i,hL.getErr(i)); end; n0=n+1;
    hL.active=0;
    return
end



%%%%%%%%%%%%%%%%%%%%% GET AND PLOT SOME DATA!!

%%%%%%%%%%%% LATEST
%% Plot Latest
hL.activeSensors=[1 0 0 0];
clear L
f0=hL.latest;
tic
for(i=1:240), 
    f1=hL.latest;
    while(f1(1)==f0(1)) f1=hL.latest; end
    L(i,:)=f1;
    f0=f1;
end
tcpu=toc;
fprintf(1,'CPU Time: %.3f\n',tcpu)
fprintf(1,'LIB Time: %.3f\n',L(end,1)-L(1,1))

figure(1); clf
T=L(:,1);
for d=1:6,
    if(d<=3)  subplot(5,3,d);  str=sprintf('Pos%d',d);
    else     subplot(5,3,d+3);   str=sprintf('Ori%d',d);
    end
    hold on
    set(plot(T,L(:,d+1),'r-'),'marker','o','markerfac','r')
    set(plot(T,L(:,d+13),'b-'),'marker','o')
    title(str)

    if(d<=3)  subplot(5,3,d+3);   str=sprintf('PosVel%d',d);
    else      subplot(5,3,d+6);   str=sprintf('OriVel%d',d);
    end
    hold on
    set(plot(T,L(:,d+7),'r-'),'marker','o','markerfac','r')
    title(str)
end

subplot(5,2,9); 
set(plot(T,L(:,20),'r-'),'marker','o','markerfac','r')
title('Distortion')

subplot(5,2,10); 
set(plot(T,L(:,21),'r-'),'marker','o','markerfac','r')
title('Error')


%%%%%%%%%%%% BUFFER
%% Plot Latest
%% Get buffer for BufferTime

BufferTime = 1; % sec 
hL.activeSensors=[1 0 0 0];
invoke(hL,'startBuffer'); pause(BufferTime); invoke(hL,'stopBuffer')
B=invoke(hL,'getBuffer',1);
fprintf(1,'Total buffer length = %d\n',length(B))
 
figure(2); clf
T=B(:,1);
for d=1:6, % Loop over x,y,z and angles
    if(d<=3)  subplot(3,3,d);  str=sprintf('Pos%d',d);
    else      subplot(3,3,d);  str=sprintf('Ori%d',d);
    end
    hold on
    set(plot(T,B(:,d+1),'r-'),'marker','.','markerfac','r')
    title(str)
end

subplot(3,2,5); 
set(plot(T,B(:,8),'r-'),'marker','.','markerfac','r')
title('Distortion')

subplot(3,2,6); 
set(plot(T,B(:,9),'r-'),'marker','.','markerfac','r')
title('Error')

% To Quit:
% release(hL)