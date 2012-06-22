%% START
hVM = actxserver('CP_Display.VMain');

%hD = actxserver('CP_Display.VDisk');
%hD.SetXY([30,30])
%hD.SetScale(10);
%hD.Show();

hM = actxserver('CP_Display.VMotion')

hM.SetNPoints(300)
hM.UseCircle
hM.SetXY([250,250])
hM.SetScaleV([250 250])
hM.SetVelocity ( [1 1]*500/2 )
hM.SetLifetime(0)

% hM.GetVertices

hM.Show();

hM.GetVertices

%% More
hM.SetExact(0);
hM.SetScaleV([200 50])
hM.UseSquare()

%% Coherence and speed
hM.SetCoherence(0);
for i=0:10,
    hM.SetVelocity( i*50*[1 1]);
    pause(1);
end
%% 
hC = actxserver('CP_Display.VComplexShape')
center = hM.GetXY();
width  = hM.GetScale();
vert = [...
    center(1)+[-1 1 1 -1 -1]*width(1); ...
    center(2)+[-1 -1 1 1 -1]*width(2)];
hC.SetVertices(vert);
hC.SetDrawMode('LineLoop')
hC.Show()

%%
hC.SetExact(1);
hM.SetExact(1);
%%
hC.SetExact(0);
hM.SetExact(0);


%% STOP
delete(hM)
delete(hC)
%delete(hD)
delete(hVM)