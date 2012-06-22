function TestLibertyCalibration(hW,hMou,hL,doDemo)

%% FUNCTION TestLibertyCalibration(hW,hMou,hL,doDemo)
%%
%%   Calibrate the screen to the table using
%%   a VisWindow.VisCalibrate interface
%%
%%   INPUTS:
%%
%%       hW   - handle to VisServer.VisWindow
%%       hMou - handle to VisServer.VisMouse
%%       hO   - hangle to OptoServer.OptoServer
%%       doDemo - Demo flag (default 0) 
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
%%      TestLibertyCalibration(hW,hMou,hO)
%%
%%         servers were already created, so send
%%         send them as parameters
%%
%%      TestLibertyCalibration
%%
%%         servers have not been created
%%        
%%      TestLibertyCalibration(0,0,0,1)
%%
%%         servers have not been created, but
%%         you'd like to see the Demo


global ORIGIN BUFFERTIME FRAMERATE 
global hW hMou hL 

%%%%%%%%%%%% SETUP/ARGS
if(nargin<1 | isnumeric(hW)),
    fprintf(1,'Set up VisWindow...\n')
    hW = actxserver('VisServer.VisWindow','128.218.64.230'); pause(.1)
    newW = 1;
else
    newW = 0;
end

if(nargin<2 | isnumeric(hMou)),
    fprintf(1,'Set up VisMouse...\n')
    hMou = actxserver('VisServer.VisMouse','128.218.64.230');
    newM = 1;
else
    newM = 0;
end

if(nargin<3 | isnumeric(hL)),
    fprintf(1,'Set up Liberty...\n')
    hL = actxserver('LibertyServer.Liberty');
    newL = 1;
    invoke(hL,'setup',0,0.04);
else
    newL=0;
end


%%%%%%%%%%% Test

hL.active=1;

fprintf(1,'Performing Calibration Demo\n')
fprintf(1,'Click to continue...\n')
fprintf(1,'Click again to stop Demo.\n')

hD  = actxserver('VisServer.VisDisk','128.218.64.230');
hDp = actxserver('VisServer.VisDisk','128.218.64.230');

pos = latest;

%% Finger
hD.show = 0;
hD.radius = 10;
hD.color = [1 1 1];
hD.pos = pos;

hDp.show = 0;
hDp.radius = 5;
hDp.color = [0 1 0];
hDp.z  = 1;
hDp.pos = pos;

%% Get Started
%% ClickToContinue(hMou);
hD.show = 1;
hDp.show = 1;

keyboard

invoke(hMou,'reset');  % clear previous button presses

while sum(hMou.click)==0,
    [pos,ppos] = latest;
    hD.pos = pos;
    hDp.pos = ppos;
end


%%%%%%%%% Wrap Up
release(hD)
release(hDp)

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

