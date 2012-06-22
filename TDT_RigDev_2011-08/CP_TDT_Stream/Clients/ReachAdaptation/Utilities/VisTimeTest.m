% hV=actxserver('VisServer.VisWindow')
% hD=actxserver('VisServer.VisDisk')
% 
% hD.show=1;
% hD.pos=[0 0];
% hD.color=[1 1 1];
% 
% tic; for i=1:1000, hD.show=1; end; toc
% 
% if(1)
%     release(hV)
%     release(hD)
% end
% 
% 
% 
% 
% 
% 


VSIP = '128.218.64.230';

hW = actxserver('VisServer.VisWindow',VSIP);
hD = actxserver('VisServer.VisDisk',VSIP);

hW.counterpos  = [0.5 1-0.028];
hW.countersize = [0.055 0.02];
hW.logmode = 1;

get(hW)
get(hD)

hD.show=1
hD.pos = [0 0]
tic; for i=1:1000, hD.color=[i/1000 0 0]; end; toc
tic; for i=1:1000, hD.color=[0 i/1000 0]; end; toc
%tic; for i=1:1000, hD.color=[0 0 i/1000]; end; toc
%tic; for i=1:1000, hD.color=[i/1000 i/1000 i/1000]; end; toc


release(hD)
release(hW)
