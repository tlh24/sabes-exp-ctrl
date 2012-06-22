%%
%% VisServer counter test
%%

fprintf(1,'Test for VisServer counter\n')

VSIP = '128.218.64.230';

hW = actxserver('VisServer.VisWindow',VSIP);

hW.counterpos  = [0.5 1-0.028];
hW.countersize = [0.055 0.02];
hW.logmode = 1;

get(hW)

tic;
for i=1:256,
  fprintf(1,'Counter=%d \d',i)  
  hW.counter = i;
  %pause(.01)
end
toc

%hW.actionlog

fprintf(1,'Done.\n\n')
release(hW)
