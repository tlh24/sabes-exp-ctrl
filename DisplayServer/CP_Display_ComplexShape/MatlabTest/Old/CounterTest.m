
strVisServerName ='grappelli';
hW = actxserver('VisServer.VisWindow',strVisServerName);  pause(.1);
h   =.02;
w   =.3;
off =.1;
% Position and size are in fractions of the screen size 
hW.counterpos=[1-w-off 1-h]; 
hW.countersize=[w h];
hW.logmode =1;

for(iCount = 2^5-1:-1:0) 
  fprintf('Counter: %d\n', iCount);
  hW.counter=iCount;
  hW.drawnow();
  pause(1);
end

if iscom(hW)  release(hW); end;


% hW.counterpos=[1-w-off 1-h]; hW.countersize=[w h];
% hW.counter=2^8-1;
% fprintf(1,'Check photodiodes array position and if OK give Enter... \n')
% pause
% hW.counter =0;
% 
% 
% hFng      = actxserver('VisServer.VisPolygon',strVisServerName);  fprintf(1,'...4 '); pause(.1);
% % Points for circles
% ang = [0:30]/30*2*pi;
% pts = [cos(ang); sin(ang)]';
% hStartTrg.points  = pts;
% hStartTrg2.points = pts;
% hStartTrg3.points = pts;
% hReachTrg.points  = pts;
% hEyeFix.points    = pts;
% hEyeFix2.points   = pts;
% hFng.points       = pts;
% hFng2.points      = pts;


% hFng.color  = [1 1 1] * Params.FEEDBACK_FNG_BRIGHT;
% hFng.scale  = Params.FEEDBACK_FNG_RAD;
% hFng.fill   = 1;
% hFng.z      = 1;
% hFng.show   = 0;
