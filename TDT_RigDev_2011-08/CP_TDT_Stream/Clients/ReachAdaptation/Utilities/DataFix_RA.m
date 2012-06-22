function DataFix_RA(name)

namehold = name;
filect    = 1; % Change this if you want to start from a file other than 1
directory = 1;
number    = 1; %Change this if you want the data to save as something other than 1
lastFile  = 0;
lastTrial = 0;

while (directory)
    try,
        fprintf(1,'\n >>> Processing TEMP directory number %d\n',filect)
        cd(sprintf('ReachAdaptation_%s-%d_TEMP',namehold,filect));
        filect=filect+1;
    catch,
        fprintf(1,'Directory not found or no more TEMP dirs available\n',filect)
        lastFile = filect-1;
        break;
    end
    fnames = dir;
    
    %% Load Data
    load VARS
    if(filect-1==1),
        hourStart   = TimeStamp(4);
        minuteStart = TimeStamp(5);
    end
    ct=0; done=0;
    while( ~done )
        fnm = sprintf('DATA_%d.mat',ct+1);
        if(exist(fnm)),
            %fprintf(1,'Load file %s \n',fnm);
            load(fnm);
            lastTrial = ct+1;
            ct=ct+1;
        else
            fprintf(1,'File %s not found or end of list\n',fnm);
            done=1;
        end
    end
    
    cd ..
    
    %% Recombine
    for i=1:ct,
        eval(sprintf('DATA(i) = DATA_%d;',i));
    end


% Save
    if exist('DATA'),
        fprintf(1,'Saving file ReachAdaptation_%s-%d.mat \n\n',name,number)
        eval(sprintf('save ReachAdaptation_%s-%d.mat DATA Params TimeStamp', name,number));
        number = number+1;
        clear DATA;
    else
        fprintf(1,'DATA not found, maybe directory does not exist\n',filect)
    end
    % eval(sprintf('!del /Q %s_TEMP\\*.*',name));      
    % eval(sprintf('!rmdir %s_TEMP',name));
end

% Get stop training info from very last trial file
eval(sprintf('load ReachAdaptation_%s-%d_TEMP/DATA_%d.mat',namehold,lastFile,lastTrial));
eval(sprintf('hourStop   = DATA_%d.trialtime(4);',lastTrial));
eval(sprintf('minuteStop = DATA_%d.trialtime(5);',lastTrial));


fprintf(1,'\n\n')
fprintf(1,'================================================================\n')
fprintf(1,'===============    Adaptation Training Summary    ==============\n')
fprintf(1,'================================================================\n')
fprintf(1,'Start Time = %d:%d\n',hourStart,minuteStart)
fprintf(1,'Stop Time = %d:%d\n\n',hourStop,minuteStop)


TotalTrials_RA(namehold)