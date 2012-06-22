% Counter Test

global hW

fprintf(1,'Testing VisServer counter...\n')

% Initialize VisServer
VSIP = '128.218.64.230';
hW = actxserver('VisServer.VisWindow',VSIP);

hW.logmode =1;

tdtOn = 0;

% DEFAULT for small pixel array (with ONOFF_FRAC = 3)
% h   =.02; % heigth
% w   =.05; % width
% off =.1;  % offset from corner of display 

% Big pixel array (with ONOFF_FRAC = 0.5)
% h   =.05;
% w   =.3;
% off =.1;

h   =.05;
w   =.3;
off =.1;



hW.counterpos=[1-w-off 1-h]; hW.countersize=[w h]; hW.counter=2^8-1;

fprintf(1,'Check photodiodes array position... \n')
pause


%for i=1:100, b=rand(4,1)<.5;  hW.counter=[1 2 4 8]*b; display([1 4 16 64]*b); pause; end

% Initialize TDT
if(tdtOn),
 tdtInit('cannonball')
 tdtRecOff
end


%% Loop flags
loop1 = 0; % Loop for walking one
loop2 = 1; % Loop from 1 to 255
loop3 = 0; % Loop for walking zero 

hW.counter=0;
fprintf(1,'Test for zero counter. Hit <Enter> to continue...\n')
pause

% Loop for walking one
if(loop1), 
    fprintf(1,'Walking ones test...\n')
    for i=0:3,
        hW.counter=2^i;
        disp(2^i);
        pause
    end
end

% Loop from 1 to 255
if(loop2),
    fprintf(1,'Normal counter test...\n')
    tic
    for i=1:16,
        hW.counter = i;
        disp(i);
        pause
    end
    toc
end

% Loop for walking zero
if(loop3),
    fprintf(1,'Walking zeros test...\n')
    hW.counter = 0;
    for i=0:3,
        hW.counter=2^4 - 2^i - 1;
        disp(2^4 - 2^i - 1);
        pause
    end
end

fprintf(1,'Hit <Enter> to stop Test now...\n\n')
pause
fprintf(1,'Done.\n\n')
release(hW)
if(tdtOn),
    tdtStop;
end
