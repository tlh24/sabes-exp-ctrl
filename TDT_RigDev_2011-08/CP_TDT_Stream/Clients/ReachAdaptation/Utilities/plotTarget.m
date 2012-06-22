%% Setup VisServer with command options: 'on', 'off'
%% Return 1 if successful, 0 otherwise

function plotTarget(command,pos)

global hL hTrg hW hMou

BUFFERTIME = 600;
PREDTIME = 1/75;
FRAMERATE = 240;

status = 1; 

% turn VisServer on

VSIP = '128.218.64.230';

if (strncmp(command, 'on', 2)),
    
    fprintf(1,'Start Up LibertyServer...\n')
    if (isnumeric(hL)) delete(hL); end
    hL = actxserver('LibertyServer.Liberty');
    %% setup
    invoke(hL,'setup',BUFFERTIME,PREDTIME);
    
    fprintf(1,'Start Up VisServer...\n')
    %% FEEDBACK
    hW        = actxserver('VisServer.VisWindow',VSIP); pause(.1);
    fprintf(1,'...1 ')
    hTrg      = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    fprintf(1,'...2 ')
    hMou      = actxserver('VisServer.VisMouse',VSIP); pause(.1);
    fprintf(1,'...3 \n')
    
    ang = [0:30]/30*2*pi;
    pts = [cos(ang); sin(ang)]';
    hTrg.points = pts;

    hL.active = 1;
    
    hTrg.pos   = pos;
    hTrg.fill  = 1;
    hTrg.scale = 10;
    hTrg.show  = 1;
    
    % turn VisServer off
elseif (strncmp(command, 'off', 2)),
    fprintf(1,'Close Down VisServer, IScan and TDT...\n')
    release(hL);
    release(hMou);
    release(hTrg);
    release(hW);

   
else
    disp(['VisSetup: Syntax error\n']);
    status = 0;
end