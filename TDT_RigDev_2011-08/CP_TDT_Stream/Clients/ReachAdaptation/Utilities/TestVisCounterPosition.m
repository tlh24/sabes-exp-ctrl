% Counter Test

global hW

fprintf(1,'Testing VisServer counter position...\n')

% Initialize VisServer
VSIP = '128.218.64.230';
hW = actxserver('VisServer.VisWindow',VSIP);

hW.logmode =1;

% Big pixel array (with ONOFF_FRAC = 0.5 or 1.5)
 h   =.02;
 w   =.3;
 off =.1;
 

hD      = actxserver('VisServer.VisPolygon',VSIP)
ang = [0:30]/30*2*pi;
pts = [cos(ang); sin(ang)]';
hD.points = pts;
hD.show = 1;
hD.fill =1;
hD.color=[1 0 0];

hW.counterpos  = [1-w-off 1-h]; 
hW.countersize = [w h]; 
hW.counter     = 2^8-1;

fprintf(1,'Check photodiodes array position... \n')
fprintf(1,'Hit Enter to stop Test...\n\n')


pause
fprintf(1,'Test Done.\n\n')
release(hW)
