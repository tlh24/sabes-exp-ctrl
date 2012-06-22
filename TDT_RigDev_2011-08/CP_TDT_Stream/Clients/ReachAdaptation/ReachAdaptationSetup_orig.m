 %%
%% Setup VisServer with command options: 
%% 'on', 'off', 'calibrate' 'octagon'
%% Return 1 if successful, 0 otherwise

function status = ReachAdaptationSetup(command)

global hL hW hMou hEye
global hStartTrg hReachTrg hEyeFix hFng 

global DEBUG
global BUFFERTIME PREDTIME FRAMERATE
global eyeStruct
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
    LibertyCalibrateMouse(hW,hMou,hL,1); 

elseif (strncmp(command, 'octagon', 7)),
    fprintf(1,'Creating Octagon Paths...\n')
    DrawOctagon(name);

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
            fprintf(1,'No errors to report from Liberty.\n')
        end
        invoke(hL,'stopBuffer');
    end
        fprintf(1,'   Done.\n')


    
    %%% VISSERVER    
    VSIP = '128.218.64.230';
    
    if (ishandle(hW)), % Don't do anything
        fprintf(1,'VisServer Already Up and Running! \n');
    else
        fprintf(1,'Start Up VisServer...\n')
        hW = actxserver('VisServer.VisWindow',VSIP);  pause(.1);
%         h   =.02;
%         w   =.05;
%         off =.1;         
%         % Big pixel array (with ONOFF_FRAC = 0.5)
%         h   =.05;
%         w   =.3;
%         off =.1;

        % Big pixel array (with ONOFF_FRAC = 1.5)
        h   =.02;
        w   =.3;
        off =.1;

        hW.logmode =1;
        hW.counterpos=[1-w-off 1-h]; hW.countersize=[w h];
        hW.counter=2^8-1;
        fprintf(1,'Check photodiodes array position and if OK give Enter... \n')
        pause
        hW.counter =0;
    end
    
    if(~ishandle(hEyeFix)),  % Fixation target handle
        fprintf(1,'...1 ')
        hEyeFix      = actxserver('VisServer.VisPolygon',VSIP); pause(.1);
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
    if(~ishandle(hMou)),      % Mouse handle 
        fprintf(1,'...5 ')
        hMou      = actxserver('VisServer.VisMouse',VSIP);   pause(.1);
    end
    
    ang = [0:30]/30*2*pi;
    pts = [cos(ang); sin(ang)]';
    hReachTrg.points = pts;
    hStartTrg.points = pts;
    hEyeFix.points = pts;
    hFng.points = pts;
    fprintf(1,'   Done.\n')
    
    
    %%% IScan 
    fprintf(1,'Initialize IScan...')
    EyeOpen;
    EyeStart;
    fprintf(1,'   Done.\n')
    

    %%% TDT
    fprintf(1,'Initialize TDT...\n')
    tdtInit('cannonball');
    fprintf(1,'Set TDT in Preview mode...')
    tdtRecOff;
    fprintf(1,'   Done.\n')

    % load Octagon Paths
    fname = 'OctagonPaths.mat';
    fprintf(1,'\nLoading %s file...\n',fname)
    load(sprintf('%s',fname));
    fprintf(1,'Octagon properties:\n')
    fprintf(1,'Center = [%.2f %.2f]\n',center(1),center(2));
    
    fprintf(1,'\n\nTo continue the task type in one of the two following Run possibilities:\n')
    fprintf(1,' 1) tuning     -> Run(<monkeyName>,<eyeCalibration>,tuning,0,<tdtTankName>) \n')
    fprintf(1,' 2) adaptation -> Run(<monkeyName>,<eyeCalibration>,adaptation,<startTargetNB>,<tdtTankName>) \n\n')
    
%%%% turn VisServer off
elseif (strncmp(command, 'off', 2)),
    fprintf(1,'Close Down VisServer, IScan and TDT...\n')
    if (ishandle(hL)),        release(hL);        end
    if (ishandle(hW)),        release(hW);        end
    if (ishandle(hStartTrg)), release(hStartTrg); end
    if (ishandle(hReachTrg)), release(hReachTrg); end
    if (ishandle(hEyeFix)),   release(hEyeFix);   end
    if (ishandle(hFng)),      release(hFng);      end
    if (ishandle(hMou)),      release(hMou);      end
 
    %%% TDT
    tdtStop;

    %%% IScan  
    EyeStop;
    EyeClose;
    EyeClearCalibration;
    

else
    fprintf(1,'+++ ERROR: Syntax error.\n') 
    fprintf(1,'Possible command options: \n ')
    fprintf(1,' on, off, calibrate, octagon \n')
    status = 0;
end