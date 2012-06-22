
% ReadHotBlock
% Read data from a block which is being written into the Tank
% Save data in matlab file for further analysis

function ReadHotBlock(tank)

if(nargin<1),
   fprintf(1,'Use: ReadHotBlock(tank)\n') 
   fprintf(1,'Example: ReadHotBlock(DT3_042705)\n') 
   return
end
%clear all;

%servername = 'cannonball';                   % server
servername = 'Local';                         % server
clientname = 'Me';                            % change this if not Local server
%tankname   = 'ReachAdaptationDAQ_DT3_042705'; % tank name
tankname   =  sprintf('%s',tank); % tank name

%%%
TTX = actxcontrol('ttank.x', [1 1 1 1]);

if (invoke(TTX, 'ConnectServer', servername, clientname) ~= 1)
  fprintf(1, '+++ Error connecting to server.\n')
  return
end

if (invoke(TTX, 'OpenTank', tankname, 'r') ~= 1)
  fprintf(1, '+++ Error opening tank or tank %s does not exist.\n', tankname)
  return
end
status = invoke(TTX,'CheckTank',tankname);
if (status==0), fprintf(1,'Tank %s is currently Closed\n',tankname);
elseif (status==79), fprintf(1,'Tank %s is currently Open\n',tankname);
elseif (status==82), fprintf(1,'Tank %s is currently in Record Mode\n',tankname);
else fprintf(1,'Unknown Tank %s status\n',tankname);
end

blockname = invoke(TTX,'GetHotBlock');
if(isempty(blockname)),
    fprintf(1,'+++ Error: No block is being recorded or is empty.\n')
    return
else
    if (invoke(TTX, 'SelectBlock', blockname) ~= 1)
        fprintf(1, '+++ Error selecting block or %s does not exist.\n',blockname)
        return
    else
        fprintf(1, 'Reading data from Tank %s %s\n',tankname,blockname)
    end
end

% Variables saved into Tank
ev1 = 'TrSt'; % Trial status: 1 = On Trial , 0 = Off Trial
ev2 = 'TrOn';
ev3 = 'TrOf';
ev4 = 'tgID'; % Target identification number
ev5 = 'Strt'; % start target ID
ev6 = 'Stop'; % stop target ID
ev7 = 'Tone';
ev8 = 'Juic';
ev9 = 'Snip'; % snippets: each one contains 30 data points 

ev10 = 'LSyn'; % Liberty Sync signal
ev11 = 'EyeH';
ev12 = 'EyeV';


varTDTNames = {'TrSt' 'TrOn' 'TrOf' 'tgID' 'Strt' 'Stop' 'Tone' 'Juic' 'Snip' 'LSyn' 'EyeH' 'EyeV'}
varNames = {'TrialStatus' 'TrialOn' 'TrialOff' 'moveID' 'startTarget' 'stopTarget' 'Tone' 'Juice' 'Snip' 'LibertySync' 'EyeH' 'EyeV'}
%%% Loop over variables we want to get out from the TDT Tank and save value + time stamps
for ivar = 1:9,

    % Get locally stored all data for 'var'. Nev = number of events read.
    Var       = varTDTNames{ivar};
    maxNev    = 1000000;
    Channel   = 0;
    SortCode  = 0;
    StartTime = 0.0;
    StopTime  = 0.0;

    fprintf(1,'%d - Variable %s \n', ivar, Var)
    Nev = invoke(TTX, 'ReadEventsV', maxNev, Var, Channel, SortCode, StartTime, StopTime, 'ALL');

    if (Nev == 0)
        fprintf(1,'Warning: No events found for variable %s \n', Var)
    else
        fprintf(1,'Number of events in %s = %d \n', blockname, Nev)
    end
    % Parse out elements of the returned data.
    ListOffset = 0;
    W      = invoke(TTX, 'ParseEvV', ListOffset, Nev); plot(W,'bo'); % data
    ts     = invoke(TTX, 'ParseEvInfoV', ListOffset, Nev, 6);        % time stamp
    sf     = invoke(TTX, 'ParseEvInfoV', ListOffset, Nev, 9);        % sampling frequency
    fprintf(1,'Data size: %d %d',size(W));
    fprintf(1,' - Time Stamp size: %d %d \n', size(ts));
    if(sf(1)>0)
       fprintf(1,'Samp. Freq. = %.2f Hz (%.5f usec)',sf(1),(1/sf(1))*10^4)  
    else
        fprintf(1,'Samp. Freq. = %.2f Hz',sf(1))
    end
    fprintf(1,'\n\n')
    eval(sprintf('%s=W;',varNames{ivar}));
    eval(sprintf('%s_TS=ts;',varNames{ivar}));
    eval(sprintf('%s_SF=sf;',varNames{ivar}));
end



if (1)
Snip_SF = Snip_SF(1);
filename = sprintf('A_%s_%s',tankname,blockname);
eval(sprintf('save %s TrialStatus TrialStatus_TS TrialOn TrialOn_TS TrialOff TrialOff_TS moveID moveID_TS startTarget startTarget_TS stopTarget stopTarget_TS Tone Tone_TS Juice Juice_TS Snip Snip_TS Snip_SF', filename)) 
fprintf(1,'Data saved to file %s\n',filename)
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Call to matlab RasterPlots and other stuff
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
TuningPlots(filename)
RasterPlot(filename)
InOutRasterPlot(filename)

%%% Quit
invoke(TTX, 'ReleaseServer');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% The following are valid values for the 3rd parameter of ParseEvInfoV:
%   1  = Amount of waveform data in bytes
%   2  = Record Type (see TCommon.h)
%   3  = Event Code Value
%   4  = Channel No.
%   5  = Sorting No.
%   6  = Time Stamp
%   7  = Scalar Value (only valid if no data is attached)
%   8  = Data format code (see TCommon.h)
%   9  = Data sample rate in Hz. (not value unless data is attached)
%   10 = Not used returns 0.
%   0  = Returns all values above



