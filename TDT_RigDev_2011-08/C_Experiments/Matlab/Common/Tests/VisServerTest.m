%%
hW  = actxserver('CP_Display.VMain');


%%
hD = actxserver('CP_Display.VDisk');
hD.SetXY([30,30])
hD.Show(1);

%%
hCS = actxserver('CP_Display.VComplexShape');

hCS.SetXY([100 100]);
hCS.SetScale(2); % set the size of the random
pointnum = 100;

%% FROM Xingtao
%% function RandomDots(hW, hCS, pointnum, si)
% parameters:
% hW - the VisWindow Object
% hCS - the VisComplexShape Object
% pointnum - a scalar, the count of the points to be drawn
% si - the size of the random dots
% if ~isempty(hW), hW.batchMode = 1; end; % to avoid multiple drawing
% during setting the params
hCS.SetDrawMode('Points'); % random dots
hCS.SetIndices([]); % don’t reindex the vertices
hCS.SetVertices( randn(2, pointnum) );% set vertices with Gaussian random dots (sigma = 1)
hCS.SetColors([]); % don’t specify the colors of every dot
% if ~isempty(hW), hW.batchMode = 0; end; % turn off batch mode
% dots, and then draw it
hCS.Show(1);
