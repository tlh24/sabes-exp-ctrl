%%
%% Setup VisServer with command options:
%% 'on', 'off', 'calibrate' 'octagon'
%% Return 1 if successful, 0 otherwise

function status = SensIntReaching_Setup(command)

global hL hW hMou NO_ISCAN
global hStartTrg hReachTrg hFng hRightHandArrowField hBonusTrg hText1 hEyeTrg
global eyeStruct

global DEBUG
global BUFFERTIME PREDTIME FRAMERATE
global Path V center % octagon properties

randn('state',sum(100*clock));
rand('state',sum(100*clock));

Params = SensIntReaching_Params(0);

%%% Liberty parameters
BUFFERTIME = 600;
PREDTIME   = 1/75;
FRAMERATE  = 240;

status = 1;

if(nargin<1)
    fprintf(1,'+++ ERROR: No command was selected\n')
    fprintf(1,' Options: on, off, calibrate\n')
    return
end

% turn VisServer on
if (strncmp(command, 'calibrate', 9)),
    fprintf(1,'Start Liberty calibration...\n')
    LibertyCalibration(hW,hMou,hL,1);

    %elseif (strncmp(command, 'octagon', 7)),
    %fprintf(1,'Creating Octagon Paths...\n')
    %numPath = 10;
    %center = [10 10];
    %vertices = 8;
    %length = 50;  % in mm
    %DrawOctagon(center,vertices,length,numPath);

elseif (strncmp(command, 'on', 2)),

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


    %%% VISSERVER
    VSIP = Params.visServerIP;  % '128.218.64.230';

    if (ishandle(hW)), % Don't do anything
        fprintf(1,'VisServer Already Up and Running! \n');
    else
        fprintf(1,'Start Up VisServer...\n')
        hW = actxserver('VisServer.VisWindow',VSIP);  pause(.1);
    end
    if(isempty(hReachTrg) | ~ishandle(hReachTrg)), % Reach target handle
        fprintf(1,'...2 ')
        hReachTrg = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end
    if(isempty(hStartTrg) | ~ishandle(hStartTrg)), % Start target handle
        fprintf(1,'...3 ')
        hStartTrg = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end
    if(isempty(hFng) | ~ishandle(hFng)),      % Feedback finger handle
        fprintf(1,'...4 ')
        hFng      = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end
    if(isempty(hMou)| ~ishandle(hMou) ),      % Mouse handle
        fprintf(1,'...5 ')
        hMou      = actxserver('VisServer.VisMouse',VSIP);   pause(.1);
    end

    if(isempty(hEyeTrg) | ~ishandle(hEyeTrg)), % Start target handle
        fprintf(1,'...6 ')
        hEyeTrg = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end

    %     fprintf(1,'...7 ')
    %     hFng  = actxserver('VisServer.VisComplexShape',VSIP);   pause(.1);
    %     hFng.show = 0;
    %     hFng.drawMode = 'Polygon';
    %     hFng.color = [1 1 1];

    if(isempty(hBonusTrg) | ~ishandle(hBonusTrg)),
        fprintf(1,'... 8 ')
        hBonusTrg      = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
    end

    if(isempty(hText1) | ~ishandle(hText1)),
        fprintf(1,'... 9 ')
        hText1 = actxserver('VisServer.VisText',VSIP); pause(0.1);
        hText1.show = 0;
        hText1.scale = [1 1].*50;
    end


    %fprintf(1,'...6 ')  %  Right Hand Arrow Field
    %if (ishandle(hRightHandArrowField)), delete(hRightHandArrowField); end

    %     hRightHandArrowField  = actxserver('VisServer.VisComplexShape',VSIP);   pause(.1);
    %     hRightHandArrowField.show = 0;
    %     hRightHandArrowField.drawMode = 'Polygon';
    %     hRightHandArrowField.scale = 1;
    %     hRightHandArrowField.z = -1;
    %     hRightHandArrowField.pos = [0;0];

    %     fprintf(1,'...6 ')  %  Dot Field
    %     if (ishandle(hRightHandDotField)), delete(hRightHandDotField); end
    %     hRightHandDotField  = actxserver('VisServer.VisComplexShape',VSIP);   pause(.1);
    %     hRightHandDotField.show = 0;
    %     hRightHandDotField.drawMode = 'Polygon';
    %     hRightHandDotField.scale = 1;
    %     hRightHandDotField.z = -1;

    ang = [0:30]/30*2*pi;
    pts = [cos(ang); sin(ang)]';
    hReachTrg.points = pts;
    hStartTrg.points = pts;
    hBonusTrg.points = pts;
    hEyeTrg.points   = pts;
    hFng.points = pts;
    fprintf(1,'   Done.\n')

    % if ~NO_ISCAN
    %%% IScan

    fprintf(1,'Initialize IScan...')
    EyeOpen;
    EyeStart;
    fprintf(1,'   Done.\n')
    %end

    %%% TDT
    fprintf(1,'Initialize TDT...\n')
    %tdtInit('128.218.64.118');
    tdtInit('cannonball');
    fprintf(1,'Set TDT in Preview mode...')
    tdtRecOff;
    pause(1);
    fprintf('Tone Test');
    tdtTone(500); pause(1); tdtTone(0);
    fprintf(1,'   Done.\n')

    %     % load Octagon Paths
    %     fname = 'OctagonPaths.mat';
    %     fprintf(1,'\nLoading %s file...\n',fname)
    %     load(sprintf('%s',fname));
    %     fprintf(1,'Octagon properties:\n')
    %     fprintf(1,'Center = [%.2f %.2f]\n',center(1),center(2));

    fprintf(1,'\n\nTo continue the task type in the following\n')
    fprintf(1,' Run(<monkeyName>)\n')

    %%%% turn VisServer off
elseif (strncmp(command, 'off', 2)),
    %     fprintf(1,'Close Down VisServer, IScan and TDT...\n')
    %     if (ishandle(hL)),        release(hL);         end
    %     if (ishandle(hW)),        release(hW);        end
    %     if (ishandle(hStartTrg)),   release(hStartTrg);end
    %     if (ishandle(hReachTrg)), release(hReachTrg);  end
    %     if (ishandle(hFng)),     release(hFng);       end
    %     if (ishandle(hMou)),      release(hMou);       end
    %     if (ishandle(hRightHandDotField)), release(hRightHandDotField);  end

    fprintf(1,'Close Down VisServer, IScan and TDT...\n')
    if (ishandle(hL)),          delete(hL);             end
    if (ishandle(hW)),          delete(hW);             end
    if (ishandle(hStartTrg)),   delete(hStartTrg);      end
    if (ishandle(hReachTrg)),   delete(hReachTrg);      end
    if (ishandle(hEyeTrg)),     delete(hEyeTrg);        end
    if (ishandle(hFng)),        delete(hFng);           end
    if (ishandle(hMou)),        delete(hMou);           end
    if (ishandle(hBonusTrg)),   delete(hBonusTrg);      end
    if (ishandle(hText1)),      delete(hText1);         end
    %     if (ishandle(hRightHandDotField)),delete(hRightHandDotField); end
    %    if (ishandle(hRightHandArrowField)),delete(hRightHandArrowField); end


    %%% TDT
    tdtStop;

    %%% IScan
    EyeStop;
    EyeClose;
    EyeClearCalibration;

else
    fprintf(1,'+++ ERROR: Syntax error.\n')
    fprintf(1,'Possible command options: \n ')
    fprintf(1,' on, off, calibrate\n')
    status = 0;
end