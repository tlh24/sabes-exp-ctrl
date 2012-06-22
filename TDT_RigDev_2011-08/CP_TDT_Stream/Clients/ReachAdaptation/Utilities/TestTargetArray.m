
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
%%% test on display targets array

function TestTargetsArray(startTarget,trgCenter,trgBox,trgGrid)

global V hW hC hD hTxt

if(nargin<4),
    start     = [-70 0];
    trgCenter = [0 0];
    trgBox    = [0 105];
    trgGrid   = [1 7];
end

%fprintf(1,'\n Creating Octagon with the following specifications:\n')
%fprintf(1,'Center= [%d %d], Radius= %d\n\n',center,length)

%%% Determine locations of all vertices



%% Draw octagon on display via VisSever

VSIP = '128.218.64.230';

hW = actxserver('VisServer.VisWindow',VSIP);

hC = actxserver('VisServer.VisDisk',VSIP);
hC.pos  = start;
hC.color = [1 0 0];
hC.show = 1;

hTxt = actxserver('VisServer.VisText',VSIP); 
hTxt.text = num2str(start);
hTxt.scale = [20 20];
hTxt.pos = start + [-20 0];
hTxt.show = 1;


NX = trgGrid(1);
NY = trgGrid(2);

TARG_CTR = trgCenter;
TARG_BOX = trgBox;
it = 0;
for ix=1:NX,
    if(NX>1) x = TARG_CTR(1) + TARG_BOX(1)*(2*ix-NX-1)/(NX-1);
    else     x = TARG_CTR(1);
    end
    for iy=1:NY,

        it = it+1;

        if(NY>1) y = TARG_CTR(2) + TARG_BOX(2)*(2*iy-NY-1)/(NY-1);
        else     y = TARG_CTR(2);
        end
        pos = [x y];
        TA(it,:) = [x y]; 
        
        hTrg{it} = actxserver('VisServer.VisDisk',VSIP);
        hTrg{it}.pos = pos;
        hTrg{it}.color = [0 1 0];
        hTrg{it}.show = 1;

        hT{it} = actxserver('VisServer.VisText',VSIP);
        hT{it}.text = num2str(pos,'%.1f');
        hT{it}.scale = [20 20];
        hT{it}.pos  = pos + [-30 0];
        hT{it}.show = 1;

        pause(0.2);

    end
end

clf
plot(start(1),-1*start(2),'ro'); hold on;
plot(TA(:,1),-1*TA(:,2),'bo')

scale = 0.3;

xmin = -150; 
xmax =  150; 
ymin = -150;
ymax =  150; 
axis([xmin xmax ymin ymax]) 
hold on;


fprintf(1,'Return to quit Test \n')
pause

for i=1:(NX*NY),
    release(hTrg{i});
    release(hT{i});
end
release(hC);
release(hW);



 