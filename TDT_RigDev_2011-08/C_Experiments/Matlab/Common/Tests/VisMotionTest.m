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
hM.SetScale(250)
hM.SetVelocity ( [1 1]*500/2 )
hM.SetLifetime(0)

% hM.GetVertices

hM.Show();

hM.GetVertices

%% STOP
delete(hM)
%delete(hD)
delete(hVM)