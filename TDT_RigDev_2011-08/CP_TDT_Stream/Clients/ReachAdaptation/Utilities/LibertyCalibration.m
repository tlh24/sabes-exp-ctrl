function LibertyCalibration(hW,hMou,hL,doDemo)

%% FUNCTION LibertyCalibration(hW,hMou,hL,doDemo)
%%
%%   Calibrate the screen to the table using
%%   a VisWindow.VisCalibrate interface
%%
%%   INPUTS:
%%
%%       hW   - handle to VisServer.VisWindow
%%       hMou - handle to VisServer.VisMouse
%%       hL   - handle to LibertyServer.Liberty
%%       doDemo - Demo flag (default 1) 
%%
%%     If any of the servers is not given or is
%%     not an active server, then CalibrateMouse
%%     will create the server and release it on 
%%     return
%%
%%     Note that if hO is sent, it's also assumed
%%     that setframe has already been run for it.
%%
%%     doDemo: if 1, run a demo of the feedback loop
%%
%%   EXAMPLES:
%%
%%      LibertyCalibration(hW,hMou,hO)
%%
%%         servers were already created, so send
%%         send them as parameters
%%
%%      LibertyCalibration
%%
%%         servers have not been created
%%        
%%      LibertyCalibration(0,0,0,1)
%%
%%         servers have not been created, but
%%         you'd like to see the Demo


global ORIGIN BUFFERTIME FRAMERATE Data
global hW hMou hL hC

visPID = '128.218.64.230';

%%%%%%%%%%%% SETUP/ARGS
if(nargin<1 | isnumeric(hW)),
    hW = actxserver('VisServer.VisWindow',visPID); pause(.1)
    newW = 1;
else
    newW = 0;
end

if(nargin<2 | isnumeric(hMou)),
    hMou = actxserver('VisServer.VisMouse',visPID);
    newM = 1;
else
    newM = 0;
end

if(nargin<3 | isnumeric(hL)),
    hL = actxserver('LibertyServer.Liberty');
    newL = 1;
    invoke(hL,'setup',0,0.04);
else
    newL=0;
end

if(nargin<4) doDemo=1; end

fprintf(1,'Performing Liberty Calibration...\n')
%%%%%%%% Calibrate
hC = actxserver('VisServer.VisCalibrate',visPID);
global posVec
posVec=[];
hL.active=1;
pause(10); %% for running into other room
while(hC.ready>=0),
    pause(1.5);
    while(~hC.ready), end
    beep;
    %%ClickToContinue(hMou);
    done=0;
    while ~done,
        pos = latest;
        if(pos(1,1)>-10000 & pos(1,2)>-10000) done=1; end
    end
    hC.pos =  pos;

    %% Store for doDemo
    posVec(end+1,:)=pos;
end
release(hC)
fprintf(1,'Liberty Calibration Completed.\n\n')

%%%%%%%%%%% Test
doDemo =1;
if(doDemo),
    
    fprintf(1,'Performing Calibration Demo...\n')
    fprintf(1,'To stop demo click VisServer mouse.\n')
    
    hD  = actxserver('VisServer.VisDisk',visPID); 
    hDp = actxserver('VisServer.VisDisk',visPID); % projected position 

    pos = latest;

    %% Finger
    hD.show   = 0;
    hD.radius = 5;
    hD.color  = [1 1 1];
    hD.fill   = 0;
    hD.pos    = pos;

    hDp.show   = 0;
    hDp.radius = 5;
    hDp.color  = [0 1 0];
    hDp.fill   = 0;
    hDp.z      = 1;
    hDp.pos    = pos;

    %% Get Started
    %ClickToContinue(hMou);
    hD.show = 0;
    hDp.show = 1;
    
    invoke(hMou,'reset');  % clear previous button presses
    while sum(hMou.click)==0, 
        [pos,ppos] = latest;
        hD.pos = pos;
        hDp.pos = ppos;
    end
    
    %%%%%%%%% Wrap Up
    release(hD)
    release(hDp)
end

%% CLEAN UP
hL.active=0;

if(newM) release(hMou); end
if(newW) release(hW); end
if(newL) release(hL); end
    


%% LATEST %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [pos,ppos]=latest
global hL
L = hL.latest;  
pos = L(1,[4,3]); 
if(nargout>1) ppos = L(1,[16,15]); end

