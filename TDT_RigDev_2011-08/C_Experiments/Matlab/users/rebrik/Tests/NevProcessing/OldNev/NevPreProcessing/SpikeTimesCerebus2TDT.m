function status = SpikeTimesCerebus2TDT
%
%
%  MF Sept. 20, 2007.  Modified from the Neuroshare API, EXAMPLE.m code.
%
TDTSampleFreq = 12207.03125;      %  Hz
TDTSamplesPerTick = 1024;   %  How often, in terms of TDT samples, a tick gets sent to Cerebus
DLLName = 'C:\bin\nsNEVLibrary';


TDTSamplePeriod = 1/TDTSampleFreq;
TDTTickPeriod = TDTSamplesPerTick*TDTSamplePeriod;

% Load the appropriate DLL
[nsresult] = ns_SetLibrary(DLLName);
if (nsresult ~= 0)
    disp('DLL was not found!');
    return
end

% Find out the data file from user
%filename = input('Data file: ', 's');
[FileNeural, PathNeural] = uigetfile({'*.nev', 'Cerebus NEV Files (*.nev)'; '*.mat','Pre-converted Nev2Mat file'},'Choose a Data File');

[status,statusmsg,nev2matfilename] = CerebusNev2Mat(PathNeural, FileNeural);
if status ~= -1
    fprintf('\n%s\n',statusmsg);
else
    error('Problem converting to .mat');
end
Data = load(nev2matfilename);

if isempty(Data.RecordingStartTimeTDT)

    %  Get the Recording Start Time (in TDT time)
    Qbutt = questdlg(mfilename,'Specify Recording Start time (TDT)','Choose File','Enter Manually','Cancel','Choose File');
    switch Qbutt
        case 'Choose File'
            [FileBehavioral, PathBehavioral] = uigefile('*.mat','Choose *.mat file');
            S = load(fullfile(PathBehavioral,FileBehavioral),'RecordingStart');
            Data.RecordingStartTimeTDT = S.RecordingStart;
        case 'Enter Manually'
            answer = inputdlg('Enter Recording Start Time (TDT; secs)',mfilename,1);
            if isempty(answer)
                fprintf('\nCancelling\n\n');
                status = -1;
                return;
            end
            Data.RecordingStartTimeTDT = answer{1};
        case 'Cancel'
            fprintf('\nCancelling\n\n');
            status = -1;
            return;
        otherwise

    end
end


NewSpikeTimes = ConvertTimeCerebus2TDT(Data.RecordingStartTimeTDT,Data.RecordingStartTimeCerebus,Data.TDTTickTimesCerebus,Data.SpikeTimesCerebus(:,3),TDTTickPeriod);
SpikeTimesTDT = [Data.SpikeTimesCerebus(:,[1 2]) NewSpikeTimes(:)];

rmvstr = '_CerebusSpikeTimes';
rei = regexp(FileNeural,rmvstr);
FileNeural2 = FileNeural;
if ~isempty(rei)
    kidx = setdiff([1:length(FileNeural)],[rei:rei+length(rmvstr)-1]);
   FileNeural2 = FileNeural(kidx);
end
outfile = [strtok(FileNeural2,'.') '_SpikeTimesTDT.mat'];
NevFile = fullfile(PathNeural,FileNeural2);
OutputFileDate = datestr(datevec(now));

%keyboard;

save(fullfile(PathNeural,outfile),'SpikeTimesTDT','NevFile','OutputFileDate');

return;


%%  - - - - - - -  Subroutines  - - - - - - - - -

function newsptimes = ConvertTimeCerebus2TDT(startoffset, starttime, ticktimes,sptimes,tickperiod)
diagplotflag = 0;
startoffset = str2num(startoffset);

%  We already know the offset, so use these times to find the slope only.
tdtticktimes = [0:length(ticktimes)-1].*tickperiod;
ticktimes = ticktimes - ticktimes(1);
%  Use interp to fit the function locally between each pair of ticks.
%  Average 2 fits, with each fit using every other data point.  Hopefully
%  this averages out any effects of irregularity in the TDT clock cycle.
%  Which should be minuscule in any case.
% % pp = interp1(ticktimes(1:2:end),tdtticktimes(1:2:end),'linear','pp');
% % newsptimes1 = ppval(pp,sptimes);
% % pp = interp1(ticktimes(2:2:end),tdtticktimes(2:2:end),'linear','pp');
% % newsptimes2 = ppval(pp,sptimes);
% % 
% % newsptimes = (newsptimes1 + newsptimes2)./2 + startoffset;


Gain = tdtticktimes(end)/ticktimes(end);
newsptimes = startoffset + (sptimes - starttime)*Gain;

if diagplotflag
    figure;
    plot(tdtticktimes,ticktimes,'.');
    hold on;
    plot([0; max(ticktimes)],[0;max(ticktimes)],'k--');
    xlabel('TDT time');
    ylabel('Cerebus time');
    %    keyboard

    figure;
    hist(tdtticktimes-ticktimes',70);
    title('TDT ticktimes - Cerebus ticktimes (offset removed)');
    ylabel('Counts');

   % m=(tdtticktimes(end)-tdtticktimes(1))/(ticktimes(end)-ticktimes(1));
    %y=m.*sptimes + startoffset;
    %err = newsptimes - y;
    err = newsptimes - (sptimes+startoffset);
    figure;
    subplot(2,1,1);
    hist(err,75);
    title('Spike Time Residuals (Offset removed)');
    xlabel('Fitted TDT - Cerebus');
    subplot(2,1,2);    
    plot(sptimes,err,'.');
    xlabel('Cerebus Time');
    ylabel('Residual');
end

