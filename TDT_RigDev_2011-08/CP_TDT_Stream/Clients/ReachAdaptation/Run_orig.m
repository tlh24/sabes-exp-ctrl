function Run(name,calibFile,command,adaptStartTarget,tdtTankName)

global Params hMou 
global tdtTankName tdtBlockName 

if (nargin<1),
    fprintf(1,'\n+++ ERROR: Missing Input Parameters! \n')
    fprintf(1,'You must specify the following:\n')
    fprintf(1,' MonkeyName, EyeCalibFile, Experiment\n\n ')
    return
end

if (nargin<2),
    fprintf(1,'\n+++ ERROR: Missing Eye Tracker Calibration File! \n\n')
    return
end

if (nargin<3),
    fprintf(1,'\n+++ ERROR: Missing Experiment Specification! \n')
    fprintf(1,'What do you want to do? Two options: \n')
    fprintf(1,'  tuning or adaptation \n\n')
    return
end

if (nargin<4),
    fprintf(1,'\nWARNING: Start Target for Adaptation Experiment not defined...\n')
    fprintf(1,'Maybe you are Tuning. Setting Start Target to 0. \n')
    adaptStartTarget = 0;
end

if (nargin<5),
    fprintf(1,'\nWARNING: TDT Data Tank not defined...\n')
    fprintf(1,'Setting DataTank name to zero. Is this ok? \n'); pause
    tdtTankName  = 'NA';
    tdtBlockName = 'NA';
    tdtTank      = 0;
else
    tdtTank = 1;
end

if (tdtTank~=0),
    TTX = actxcontrol('ttank.x', [1 1 1 1]);
    servername = 'cannonball';
    clientname = 'Me';
    if (invoke(TTX, 'ConnectServer', servername, clientname) ~= 1)
        fprintf(1, '+++ Error connecting to server.\n'); return
    end
    if (invoke(TTX, 'OpenTank', tdtTankName, 'r') ~= 1)
        fprintf(1, '+++ Error opening tank or tank %s does not exist.\n', tdtTankName)
        return
    end
    
    status = invoke(TTX,'CheckTank',tdtTankName);
    if (status==0), fprintf(1,'Tank %s is currently Closed\n',tdtTankName);
    elseif (status==79), fprintf(1,'Tank %s is currently Open\n',tdtTankName);
    elseif (status==82), fprintf(1,'Tank %s is currently in Preview or Record Mode\n',tdtTankName);
    else fprintf(1,'Unknown Tank %s status\n',tdtTankName);
    end

    blockname = invoke(TTX,'GetHotBlock');
    if(isempty(blockname)),
        fprintf(1,'+++ Error: No block is being recorded or is empty.\n'); return
    else
        if (invoke(TTX, 'SelectBlock', blockname) ~= 1)
            fprintf(1, '+++ Error selecting block or %s does not exist.\n',blockname); return
        else
            fprintf(1, 'Reading data from Tank %s %s\n',tdtTankName,blockname)
        end
        tdtBlockName = blockname;
    end
end

calibDir = 'MonkeyEyeCalib/'; 

%%% Draw Octagon (parameters are chosen depending on monkey)
DrawOctagon(name)


%%% Tuning
if (strncmp(command, 'tuning', 6 ))
    fprintf(1,' \n')
    fprintf(1,'Starting Tuning Experiment...\n')    
    test = 'Tuning';
    
    EyeLoadCalibration(calibFile,calibDir) 
    fprintf(1,'Load Eye Tracker Calibration File: %s%s_EyeCal.mat... \n',...
        calibDir,calibFile);
    
    fprintf(1,'Set Tuning Experiment Parameters... \n');
    Params = ReachAdaptation_Params(name,test);
    
    fprintf(1,'Start Tuning Experiment... \n');
    ReachAdaptation(test, adaptStartTarget);
    
%%% Adaptation    
elseif (strncmp(command, 'adaptation', 10 ))
    fprintf(1,' \n')
    if (adaptStartTarget == 0) 
       fprintf(1,'+++ ERROR: Missing Start Target for Adaptation Experiment! \n')
       return
    end
        
    fprintf(1,'Starting Adaptation Experiment...\n')
    test = 'Adaptation';
    
    EyeLoadCalibration(calibFile,calibDir); 
    fprintf(1,'Load Eye Tracker Calibration File: %s%s_EyeCal.mat... \n',...
        calibDir,calibFile);
    
    fprintf(1,'Set Adaptation Experiment Parameters... \n');
    Params = ReachAdaptation_Params(name,test);
    Params.START_TARGET_NUMBER = adaptStartTarget;
    fprintf(1,'Start Reach Adaptation Experiment... \n')
    ReachAdaptation(test, adaptStartTarget);
    

end

