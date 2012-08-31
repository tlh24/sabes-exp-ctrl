%%
%% Setup VisServer with command options:
%% 'on', 'off', 'calibrate' 'octagon'
%% Return 1 if successful, 0 otherwise

function status = TestSetup(command)

global hL hW hMou
global hStartTrg hReachTrg hFng hRightHandDotField hCOTestShape

global DEBUG
global BUFFERTIME PREDTIME FRAMERATE
global Path V center % octagon properties

%%% Liberty parameters
BUFFERTIME = 600;
PREDTIME   = 1/75;
FRAMERATE  = 240;

status = 1;

if(nargin<1)
    fprintf(1,'+++ ERROR: No command was selected\n')
    fprintf(1,' Options: on, off, calibrate, octagon \n')
    return
end

% turn VisServer on
if (strncmp(command, 'calibrate', 9)),
    fprintf(1,'Start Liberty calibration...\n')
    LibertyCalibration(hW,hMou,hL,1);

    % elseif (strncmp(command, 'octagon', 7)),
    %     fprintf(1,'Creating Octagon Paths...\n')
    %     numPath = 10;
    %     center = [10 10];
    %     vertices = 8;
    %     length = 50;  % in mm
    %     DrawOctagon(center,vertices,length,numPath);

elseif (strncmp(command, 'on', 2)),

    if 1
    %%% LIBERTY
    if (ishandle(hL)),         % check if handle exist
        fprintf(1,'Liberty Already Up and Running! \n');
    else
        fprintf(1,'Start Up LibertyServer...\n')
        hL = actxserver('LibertyServer.Liberty');
        invoke(hL,'setup',BUFFERTIME,PREDTIME); pause(0.5);  % setup
        %%%%%%% ERROR CHECK BUFFER COMMANDS
        nE0 = 0;
        invoke(hL,'startBuffer');
        nE1 = hL.err;
        if(nE1>nE0)
            for i=(nE0+1):nE1,
                fprintf(1,'%d: %s',i,hL.getErr(i))
            end
        else
            fprintf(1,'No errors to report from Liberty.')
        end
        invoke(hL,'stopBuffer');
    end
    fprintf(1,'   Done.\n')
    end


    %%% VISSERVER
    VSIP = '128.218.64.230';

    if (ishandle(hW)), % Don't do anything
        fprintf(1,'VisServer Already Up and Running! \n');
    else
        fprintf(1,'Start Up VisServer...\n')
        hW = actxserver('VisServer.VisWindow',VSIP);  pause(.1);
    end


    if(~ishandle(hReachTrg)), % Reach target handle
        fprintf(1,'...2 ')
        hReachTrg = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end
    if(~ishandle(hStartTrg)), % Start target handle
        fprintf(1,'...3 ')
        hStartTrg = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end
    if(~ishandle(hFng)),      % Feedback finger handle
        fprintf(1,'...4 ')
        hFng      = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end
   % if(~ishandle(hMou)),      % Mouse handle
        fprintf(1,'...5 ')
        hMou      = actxserver('VisServer.VisMouse',VSIP);   pause(.1);
    %end
    
    %  Complex Object Test Shape
%     hCOTestShape  = actxserver('VisServer.VisComplexShape',VSIP);   pause(.1);
%     hCOTestShape.color = [0;1;0];       
%         hCOTestShape.drawMode = 'Triangles'; % random dots
%         hCOTestShape.indices = []; % don�t reindex the vertices
%         hCOTestShape.vertices = [0 5 10;0 5 0];%
    
    %if(~ishandle(hRightHandDotField)),      % Dot field handle
        fprintf(1,'...6 ')
        hRightHandDotField  = actxserver('VisServer.VisComplexShape',VSIP);   pause(.1);
        hRightHandDotField.show = 0;
        hRightHandDotField.drawMode = 'Polygon';
        hRightHandDotField.color = [1 0 0];
%         Ndots = 5000;
%         dotBounds = [];
%         dotSize = 1;
%         dotColor = [1 0 0];
%         %function RandomDots(hW, hComplexShape, pointnum, si)
%         % parameters:
%         % hW - the VisWindow Object
%         % hComplexShape - the VisComplexShape Object
%         % pointnum - a scalar, the count of the points to be drawn
%         % si - the size of the random dots
% %        if ~isempty(hW), hW.batchMode = 1; end; % to avoid multiple drawing
%         % during setting the params
%         hRightHandDotField.color = dotColor;
%        % hRightHandDotField.pointSize = 1;
%         %hRightHandDotField.drawMode = 'Points'; % random dots
%         hRightHandDotField.drawMode = 'Polygon'; % random dots
%         hRightHandDotField.indices = []; % don�t reindex the vertices
%         %hRightHandDotField.vertices = randn(2, Ndots);
%         dotCenters = randn(2, Ndots);        
%         hRightHandDotField.vertices = circleVerts(dotCenters,2);
%         % random dots (sigma = 1)
%         hRightHandDotField.colors = []; % don�t specify the colors of
%         % every dot
%  %       if ~isempty(hW), hW.batchMode = 0; end; % turn off batch mode
%         hRightHandDotField.scale = 1; 

   % end

    ang = [0:30]/30*2*pi;
    pts = [cos(ang); sin(ang)]';
    hReachTrg.points = pts;
    hStartTrg.points = pts;
    hFng.points = pts;
    fprintf(1,'   Done.\n')

if 0
    %%% TDT
    fprintf(1,'Initialize TDT...\n')
    tdtInit('cannonball');
    fprintf(1,'Set TDT in Preview mode...')
    tdtRecOff;
    fprintf(1,'   Done.\n')

    % load Octagon Paths
    %     fname = 'OctagonPaths.mat';
    %     fprintf(1,'\nLoading %s file...\n',fname)
    %     load(sprintf('%s',fname));
    %     fprintf(1,'Octagon properties:\n')
    %     fprintf(1,'Center = [%.2f %.2f]\n',center(1),center(2));
    %
    fprintf(1,'\n\nTo continue the task type in the following\n')
    fprintf(1,' Run(<monkeyName>)\n')
end
    %%%% turn VisServer off
elseif (strncmp(command, 'off', 2)),
    fprintf(1,'Close Down VisServer, IScan and TDT...\n')
    if (ishandle(hL)),        release(hL);        end
    if (ishandle(hW)),        release(hW);        end
    if (ishandle(hStartTrg)), release(hStartTrg); end
    if (ishandle(hReachTrg)), release(hReachTrg); end
    if (ishandle(hFng)),      release(hFng);      end
    if (ishandle(hMou)),      release(hMou);      end

    %%% TDT
    tdtStop;

else
    fprintf(1,'+++ ERROR: Syntax error.\n')
    fprintf(1,'Possible command options: \n ')
    fprintf(1,' on, off, calibrate, octagon \n')
    status = 0;
end