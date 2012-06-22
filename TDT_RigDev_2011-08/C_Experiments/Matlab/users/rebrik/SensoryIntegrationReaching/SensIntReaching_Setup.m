%%
%% Setup VisServer with command options:
%% 'on', 'off', 'calibrate' 'octagon'
%% Return 1 if successful, 0 otherwise

function status = SensIntReaching_Setup(command)

global hL hW hEye NO_ISCAN
global hStartTrg hReachTrg hFng hRightHandArrowField hBonusTrg hText1 hEyeTrg
global eyeStruct

global DEBUG
global BUFFERTIME PREDTIME FRAMERATE
global Path V center % octagon properties

ServerNamesInclude;

randn('state',sum(100*clock));
rand('state',sum(100*clock));

Params = SensIntReaching_Params(0);

%%% Liberty parameters

status = 1;

if(nargin<1)
    fprintf('+++ ERROR: No command was selected\n')
    fprintf(' Options: on, off\n')
    return
end

if (strncmp(command, 'on', 2)),

    %%% LIBERTY
    if iscom(hL)        % check if handle exist
        fprintf('Tracker is already running! \n');
    else
        fprintf('Connecting to the Tracker\n');
        hL = actxserver(strTrackerName, strTrackerComputer);
    end


    %%% VISSERVER

    if (iscom(hW)), % Don't do anything
        fprintf('VisServer is already running! \n');
    else
        fprintf('CP_Display...\n');
        hW = actxserver('CP_Display.VMain', strDisplayComputer); 
    end
    if(isempty(hReachTrg) | ~iscom(hReachTrg)), % Reach target handle
        fprintf('...2 ')
        hReachTrg = actxserver('CP_Display.VDisk',strDisplayComputer); 
    end
    if(isempty(hStartTrg) | ~iscom(hStartTrg)), % Start target handle
        fprintf('...3 ')
        hStartTrg = actxserver('CP_Display.VDisk',strDisplayComputer); 
    end
    if(isempty(hFng) | ~iscom(hFng)),      % Feedback finger handle
        fprintf('...4 ')
        hFng      = actxserver('CP_Display.VDisk',strDisplayComputer); 
    end
%    if(isempty(hMou)| ~iscom(hMou) ),      % Mouse handle
%        fprintf('...5 ')
%        hMou      = actxserver('VisServer.VisMouse',strDisplayComputer);
%    end

    if(isempty(hEyeTrg) | ~iscom(hEyeTrg)), % Start target handle
        fprintf('...6 ')
        hEyeTrg = actxserver('CP_Display.VDisk',strDisplayComputer);
    end

    %     fprintf('...7 ')
    %     hFng  = actxserver('VisServer.VisComplexShape',strDisplayComputer);
    %     hFng.Hide;
    %     hFng.drawMode = 'Polygon';
    %     hFng.SetColor([1 1 1]);

    if(isempty(hBonusTrg) | ~iscom(hBonusTrg)),
        fprintf('... 8 ')
        hBonusTrg      = actxserver('CP_Display.VDisk',strDisplayComputer); 
    end

%     if(isempty(hText1) | ~iscom(hText1)),
%         fprintf('... 9 ')
%         hText1 = actxserver('CP_Display.VText',strDisplayComputer); 
%         hText1.Hide;
%         hText1.SetScale( [1 1].*50);
%     end


    %fprintf('...6 ')  %  Right Hand Arrow Field
    %if (iscom(hRightHandArrowField)), delete(hRightHandArrowField); end

    %     hRightHandArrowField  = actxserver('VisServer.VisComplexShape',strDisplayComputer);
    %     hRightHandArrowField.show = 0;
    %     hRightHandArrowField.drawMode = 'Polygon';
    %     hRightHandArrowField.scale = 1;
    %     hRightHandArrowField.z = -1;
    %     hRightHandArrowField.pos = [0;0];

    %     fprintf('...6 ')  %  Dot Field
    %     if (iscom(hRightHandDotField)), delete(hRightHandDotField); end
    %     hRightHandDotField  = actxserver('VisServer.VisComplexShape',strDisplayComputer);
    %     hRightHandDotField.show = 0;
    %     hRightHandDotField.drawMode = 'Polygon';
    %     hRightHandDotField.scale = 1;
    %     hRightHandDotField.z = -1;

    fprintf('   Done.\n')

    %%% IScan
    if(isempty(hEye) | ~iscom(hEye)),
      fprintf('Connecting to IScan \n')
      hEye = actxserver('CP_EyeTrack.Application',strEyeTrackComputer); 
    end


    fprintf('   Done.\n')
    %end

    fprintf('Tone Test');
    ToneStart(500, 1); 
    fprintf('   Done.\n')

    %     % load Octagon Paths
    %     fname = 'OctagonPaths.mat';
    %     fprintf('\nLoading %s file...\n',fname)
    %     load(sprintf('%s',fname));
    %     fprintf('Octagon properties:\n')
    %     fprintf('Center = [%.2f %.2f]\n',center(1),center(2));

    fprintf('\n\nTo continue the task type in the following\n')
    fprintf(' Run(<monkeyName>)\n')

    %%%% turn VisServer off
elseif (strncmp(command, 'off', 2)),
    %     fprintf('Close Down VisServer, IScan and TDT...\n')
    %     if (iscom(hL)),        release(hL);         end
    %     if (iscom(hW)),        release(hW);        end
    %     if (iscom(hStartTrg)),   release(hStartTrg);end
    %     if (iscom(hReachTrg)), release(hReachTrg);  end
    %     if (iscom(hFng)),     release(hFng);       end
    %     if (iscom(hMou)),      release(hMou);       end
    %     if (iscom(hRightHandDotField)), release(hRightHandDotField);  end

    fprintf('Close Down VisServer, IScan and TDT...\n')
    if (iscom(hL)),          delete(hL);             end
    if (iscom(hW)),          delete(hW);             end
    if (iscom(hStartTrg)),   delete(hStartTrg);      end
    if (iscom(hReachTrg)),   delete(hReachTrg);      end
    if (iscom(hEyeTrg)),     delete(hEyeTrg);        end
    if (iscom(hFng)),        delete(hFng);           end
    if (iscom(hBonusTrg)),   delete(hBonusTrg);      end
    if (iscom(hText1)),      delete(hText1);         end
    if (iscom(hEye)),      delete(hEye);         end

    %     if (iscom(hRightHandDotField)),delete(hRightHandDotField); end
    %    if (iscom(hRightHandArrowField)),delete(hRightHandArrowField); end


else
    fprintf('+++ ERROR: Syntax error.\n')
    fprintf('Possible command options: \n ')
    fprintf(' on, off\n')
    status = 0;
end