
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Create octagon grid and 
%%% test on display

function TestOctagon(name)

global V hW hC hD hTxt


if(nargin<1),
   fprintf(1,'\nERROR: Choose a monkey! (A or C) \n\n')
   return
end

vertices = 8;

if (strncmp(name, 'A', 1 )) %% Abe
   center = [20 0];   
   length = 90;    
elseif (strncmp(name, 'C', 1 )) %% Calvin
   center = [20 100];   
   length = 80;    
end

fprintf(1,'\n Creating Octagon with the following specifications:\n')
fprintf(1,'Center= [%d %d], Radius= %d\n\n',center,length)

%%% Determine locations of all vertices
nVert = vertices;
L = length;
V = zeros(nVert,2);
for i = 1:nVert
    theta = (2*pi/nVert)*(i-1);
    V(i,:)  = center + L*[cos(theta-(pi/2)) sin(theta-(pi/2))];
end

clf
plot(center(1),center(2),'bo'); hold on;
plot(V(:,1),V(:,2),'bo')

scale = 0.3;

xmin = center(1)-length-scale*length;
xmax = center(1)+length+scale*length;
ymin = center(2)-length-scale*length;
ymax = center(2)+length+scale*length;
axis([xmin xmax ymin ymax]) 
hold on;


%% Draw octagon on display via VisSever

VSIP = '128.218.64.230';

hW = actxserver('VisServer.VisWindow',VSIP);

hC       = actxserver('VisServer.VisDisk',VSIP);
hC.pos   = center;
hC.color = [1 0 0];
hC.fill  = 0;
hC.show  = 1;

hTxt       = actxserver('VisServer.VisText',VSIP); 
hTxt.text  = num2str(center);
hTxt.scale = [20 20];
hTxt.pos   = center + [0 20];
hTxt.show  = 1;



hD = {};
for i=1:vertices,
    hD{i}       = actxserver('VisServer.VisDisk',VSIP);
    hD{i}.pos   = [V(i,1) V(i,2)]; 
    hD{i}.color = [1 0 1];
    hD{i}.fill  = 0;
    hD{i}.show  = 1; 
    
    hT{i}       = actxserver('VisServer.VisText',VSIP); 
    pos         = [V(i,1) V(i,2)];
    hT{i}.text  = num2str(pos,'%.1f');
    hT{i}.scale = [20 20];
    hT{i}.pos   = pos + [0 20];
    hT{i}.show  = 1;
    pause(0.1);
end

nVert = vertices;
L     = 0.5*length;
V     = zeros(nVert,2);
for i = 1:nVert
    theta  = (2*pi/nVert)*(i-1);
    V(i,:) = center + L*[cos(theta-(pi/2)) sin(theta-(pi/2))];
end

hD1 = {};
for i=1:vertices,
    hD1{i}       = actxserver('VisServer.VisDisk',VSIP);
    hD1{i}.pos   = [V(i,1) V(i,2)]; 
    hD1{i}.color = [0 1 0];
    hD1{i}.fill  = 0;
    hD1{i}.show  = 1;            
    pause(0.1);
end

nVert = vertices;
L     = 1.5*length;
V     = zeros(nVert,2);
for i = 1:nVert
    theta  = (2*pi/nVert)*(i-1);
    V(i,:) = center + L*[cos(theta-(pi/2)) sin(theta-(pi/2))];
end
% % % hD2 = {};
% % % for i=1:vertices,
% % %     hD2{i} = actxserver('VisServer.VisDisk',VSIP);
% % %     hD2{i}.pos = [V(i,1) V(i,2)]; 
% % %     hD2{i}.color = [0 1 0];
% % %     hD2{i}.show = 1;             
% % %     hT2{i} = actxserver('VisServer.VisText',VSIP); 
% % %     pos = [V(i,1) V(i,2)]*1.5;
% % %     hT2{i}.text = num2str(pos,'%.1f');
% % %     hT2{i}.scale = [20 20];
% % %     hT2{i}.pos  = pos + [0 20];
% % %     hT2{i}.show = 1;
% % %     pause(0.1);
% % % end

fprintf(1,'Return to quit TestOctagon \n')
pause

for i=1:vertices,
    release(hD{i});
    release(hD1{i});
    release(hT{i});
end
release(hC);
release(hW);



 