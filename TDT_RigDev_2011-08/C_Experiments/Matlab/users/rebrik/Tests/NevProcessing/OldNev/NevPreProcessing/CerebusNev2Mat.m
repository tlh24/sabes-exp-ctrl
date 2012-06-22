function [status,statusmsg,outfile] = CerebusNev2Mat(path,fname)
%
%  Output file:
%           NevFile     :       Filename of original Nev file
%           FileDate        :       Date converted
%           NChannels   :       Number of channels
%           RecordingStartTimeTDT :     Time of Recording start in TDT time.
%           SpikeTimesCerebus <n x 3> : [Channel Unit Timestamp]
%           TDTTickTimesCerebus :  Cerebus timestamps for incoming TDT ticks
%
%  MF Sept. 20, 2007
%


filename = fullfile(path,fname);
outfile = [];


[dum,ext] = strtok(fname,'.');
switch lower(ext)

    case '.mat'
        fprintf('\n%s: Loading pre-converted file\n',mfilename);
        S = load(filename);
        if isfield(S,'SpikeTimesCerebus')
            if size(S.SpikeTimesCerebus,2) == 3
                ok = 1;
            else
                ok = 0;
            end
        end
        ok = and(ok,isfield(S,'NChannels'));
        ok = and(ok,isfield(S,'NevFile'));
        ok = and(ok,isfield(S,'TDTTickTimesCerebus'));

        if ok
            status = 2;
            statusmsg = sprintf('%s: %s looks ok',mfilename,filename);
            outfile = filename;
            return;
        else
            status = -1;
            statusmsg = sprintf('%s: %s does not look like the correct file',mfilename,filename);
            return;
        end
    case '.nev'

        fprintf('\n%s: Loading NEV file and converting\n',mfilename);

        % Open data file
        [nsresult, hfile] = ns_OpenFile(filename);
        if (nsresult ~= 0)
            disp('Data file did not open!');
            return
        end

        % Get file information
        [nsresult, FileInfo] = ns_GetFileInfo(hfile);
        % Gives you EntityCount, TimeStampResolution and TimeSpan
        if (nsresult ~= 0)
            disp('Data file information did not load!');
            return
        end


        % Build catalogue of entities
        [nsresult, EntityInfo] = ns_GetEntityInfo(hfile, [1 : 1 : FileInfo.EntityCount]);

        NeuralList = find([EntityInfo.EntityType] == 4);    % List of EntityIDs needed to retrieve the information and data
        SegmentList = find([EntityInfo.EntityType] == 3);
        AnalogList = find([EntityInfo.EntityType] == 2);
        EventList = find([EntityInfo.EntityType] == 1);

        % How many of a particular entity do we have
        cNeural = length(NeuralList);
        cSegment = length(SegmentList);
        cAnalog = length(AnalogList);
        cEvent = length(EventList);

        %clear FileInfo;

        if (cNeural == 0)
            status = -1;
            statusmsg = sprintf('%s: No neural events available in %s',mfilename,filename);
            return;
        end

        if (cSegment == 0)
            %disp('No segment entities available!');
            %return;     % It does not make sense to continue in this particular analysis
            % if there are no segment entities.
        end

        if (cAnalog == 0)
            %disp('No analog entities available!');
        end

        if (cEvent == 0)
            status = -1;
            statusmsg = sprintf('%s: No Timing Events available in %s',mfilename,filename);
            return;
        end


        %

        % These three functions are for demonstration purposes
        %% [nsresult, nsSegmentInfo] = ns_GetSegmentInfo(hfile, SegmentList(channel));
        %% [nsresult, nsSegmentSourceInfo] = ns_GetSegmentSourceInfo(hfile, SegmentList(channel), 1);

        % %         %%%%%  THIS DOESN'T WORK EITHER, IT SEEMS TO ASSUME THE WRONG FILE
        % %         %%%%%  FORMAT ....
        % %         %  I'm using old NEV to Matlab functions here because the new ones
        % %         %  don't seem to work.
        % %         nevObject = openNEV(filename);
        % %         NPackets = nevObject.FileInfo.packetCount;  %  This will be a little larger than the number of spike packets.
        % %
        % %         CerebusSamplePeriod = 1./nevObject.HeaderBasic.sampleResolution;
        % %         SpikeTimesCerebus = zeros(NPackets,3);
        % %         Nper = 50000; packetStart = 1;done=0;%PacketsLeft = NPackets; packetStart = 1;
        % %         while ~done %(PacketsLeft > 0)
        % %             %            grabN = min(Nper,PacketsLeft);
        % %             spikes = getNEVSpikes(nevObject, Nper, packetStart);
        % %             gotN = length(spikes.electrode);
        % %             if gotN
        % %                 SpikeTimesCerebus(packetStart:packetStart+gotN-1,:) = [double(spikes.electrode(:)) double(spikes.unit(:)) ...
        % %                     CerebusSamplePeriod.*double(spikes.timeStamp(:))];
        % %                 packetStart = packetStart+gotN;
        % %             else
        % %                 done = 1;
        % %             end
        % %         end
        % %         SpikeTimesCerebus = SpikeTimesCerebus(1:packetStart-1,:);  %  Get rid of the padding on the end.

        SpikeTimesCerebus = [];
        prefix = 'elec';
        for eleci= 1:cSegment%1:cNeural
            %                nSpikes = EntityInfo(NeuralList(eleci)).ItemCount;
            nSpikes = EntityInfo(SegmentList(eleci)).ItemCount;
            if nSpikes
                [nsresult, timestamps_wf, waveforms, sampleCount, unitIDs] = ns_GetSegmentData(hfile, SegmentList(eleci), [1:nSpikes]);
                %%%


                clear waveforms sampleCount;

                Label = EntityInfo(SegmentList(eleci)).EntityLabel;
                if ~isequal(Label(1:4),prefix)
                    error('Unknown Neural Channel Label');
                end
                ChannelNum = str2num(strtok(Label,prefix));

                SpikeTimesCerebus = [SpikeTimesCerebus; [repmat(ChannelNum,nSpikes,1) unitIDs(:) timestamps_wf(:)]];
                %clear nsSegmentInfo;
                %clear nsSegmentSourceInfo;
            end
        end

        %  GET THE TDT TICKS FROM THE EVENT DATA HERE
        %  PUT IN TDTTickTimesCerebus
        EventLabels = strvcat(EntityInfo(EventList).EntityLabel);
        didx = strmatch('digin',EventLabels);
        if isempty(didx), error('No digin events found'); end
        NDigitalEvents = EntityInfo(EventList(didx)).ItemCount;
        [nsr,nsEI] = ns_GetEventInfo(hfile,EventList(didx));
        if ~isequal(nsEI.EventType,'ns_EVENT_WORD'), error('Not the correct type of digin data'); end
        [nsr,EventTimeStamps,EventValue] = ns_GetEventData(hfile,EventList(didx),[1:NDigitalEvents]);

        ns_CloseFile(hfile);
        
        dMaskedEvents =  bitand(EventValue, 1);  % keep the TimeSync bit only
        TickEventIdx = find(abs(diff(dMaskedEvents))==1);   % abs() - we are using both up and down transitions
        TDTTickTimesCerebus = EventTimeStamps(TickEventIdx+1); % diif indexes are shifted by 1, correcting

        dMaskedEvents =  bitand(EventValue, 8);  % keep the RecSync bit only
        RecEventIdx = find(diff(dMaskedEvents)==8);   
        RecordingStartTimeCerebus = EventTimeStamps(RecEventIdx+1); % diif indexes are shifted by 1, correcting
       
        if( length(RecEventIdx) ~= 1) 
          warning('Incorrect number of Recording Start events: %d', length(RecEventIdx));
        end
        
        %        keyboard

        RecordingStartTimeTDT = [];
        NevFile = filename;
        FileDate = datestr(datevec(now));
        NChannels = length(unique(SpikeTimesCerebus(:,1)));
        %        TDTTickTimesCerebus =

        outfile = [strtok(filename,'.') '_CerebusSpikeTimes.mat'];
        save(outfile,'NevFile','FileDate','NChannels','SpikeTimesCerebus','TDTTickTimesCerebus','RecordingStartTimeTDT', 'RecordingStartTimeCerebus' );

        status = 1;
        statusmsg = sprintf('%s: %s Saved Successfully',mfilename,outfile);
        %         %
        %         % Reduce the data set to only the first 150 seconds of data
        %         %
        %
        %         NeuralLabels = strvcat(EntityInfo(NeuralList).EntityLabel);
        %
        %         for cChannel = 1 : 1 : length(channel),
        %             % Have to figure out which Neural entities correspond with the selected segment entities
        %             list = strmatch(EntityInfo(SegmentList(channel(cChannel))).EntityLabel, NeuralLabels, 'exact');
        %
        %             % Retrieve the data
        %             [nsresult, NeuralInfo] = ns_GetNeuralInfo(hfile, NeuralList(list));
        %             [nsresult, NeuralData] = ns_GetNeuralData(hfile, NeuralList(list), 1, max([EntityInfo(NeuralList(list)).ItemCount]));
        %
        %             if (totaltime == 150)
        %                 ind = find(NeuralData <= 150);
        %             else
        %                 ind = [1:1:size(NeuralData, 1) * size(NeuralData, 2)];
        %             end
        %
        %             % Get the neural timestamps
        %             NeuralData = reshape(NeuralData, size(NeuralData, 1) * size(NeuralData, 2), 1);
        %             timestamps(cChannel) = {NeuralData(ind)};
        %             % Match the neural events with their unit ID
        %             temp = ones(length(ind) / length(list), 1) * [NeuralInfo(:).SourceUnitID];
        %             units(cChannel) = {temp(:)};
        %             % Remember how many neural events were found
        %             ItemCount(cChannel) = length(timestamps{cChannel});
        %
        %             NeuralData(:) = [];
        %         end
        %         clear NeuralData SegmentLabels NeuralLabels NeuralInfo;
        %         EntityInfo = rmfield(EntityInfo, 'ItemCount');
        %
        %         % Close data file. Should be done by the library but just in case.
        %         ns_CloseFile(hfile);
        %
        %         % Unload DLL
        %         clear mexprog;
        %
        %         for cChannel = 1 : 1 : length(channel),
        %             % Plot neural activity on that channel
        %             figure;
        %             subplot(4, 1, 1);
        %             % Plot the first 100 waveforms on that channel and apply different
        %             % colors for different unitIDs
        %             % Unclassified units
        %             ind = find(unitIDs(:, cChannel) == 0);
        %             if (~isempty(ind))
        %                 plot(waveforms(:, ind, cChannel), 'Color', [.8 .8 .8]); % in grey
        %                 hold on;
        %             end
        %             % Classified Units
        %             Colors = ['y' 'm' 'c' 'r' 'g'];
        %
        %             for cUnit = 1 : 1 : 5,
        %                 ind = find(unitIDs(:, cChannel) == cUnit);
        %                 if (~isempty(ind))
        %                     plot(waveforms(:, ind, cChannel), Colors(cUnit));
        %                     hold on;
        %                 end
        %             end
        %
        %             axis tight;
        %             title(['Waveforms - ' EntityInfo(SegmentList(channel(cChannel))).EntityLabel]);
        %             ylabel('Voltage (uV)');
        %
        %             subplot(4, 1, 2);
        %             % This creates lines for the unit
        %             a = repmat(timestamps{cChannel}', 2, 1);          % X Values don't change so just two rows with the same values
        %             b = repmat([0.6; 1.4], 1, ItemCount(cChannel));   % Start and end points of each line
        %             % This plots the lines for each unit
        %             % Unclassified units
        %             ind = find(units{cChannel} == 0);
        %             hold on;
        %             if (~isempty(ind))
        %                 plot(a(:, ind), b(:, ind), 'Color', [.8 .8 .8]); % in grey
        %             end
        %
        %             % Classified Units
        %             for cUnit = 1 : 1 : 5,
        %                 ind = find(unitIDs(:, cChannel) == cUnit);
        %                 if (~isempty(ind))
        %                     plot(a(:, ind), b(:, ind), Colors(cUnit));
        %                 end
        %             end
        %
        %             title(['Raster plot - ' EntityInfo(SegmentList(channel(cChannel))).EntityLabel]);
        %             xlabel('Time [s]');
        %             set(gca, 'ytick', []);
        %             xlim([0 round(totaltime)]);
        %             clear a b;
        %
        %             % Use a sliding window 100 ms (delta t) long (equivalent to linear kernel)
        %             dt = 0.1; % ms
        %             for i = totaltime : -stepsize : 0,
        %                 gaussdata(round(i / stepsize + 1)) = sum(exp(-(i - timestamps{cChannel}(find((timestamps{cChannel} > i - 4 * dt) & (timestamps{cChannel} < i + 4 * dt)))').^2 / (2 * dt^2))) / sqrt(2 * 3.1415) / dt;
        %             end
        %
        %             % Throw away firing rates higher than 200 because they are not real and show up at the beginning
        %             gaussdata(find(gaussdata > 200)) = 0;
        %
        %             subplot(4, 1, 3);
        %             plot(time, gaussdata(1 : length(time)));
        %             title(['Approximated firing rate (Gaussian) - ' EntityInfo(SegmentList(channel(cChannel))).EntityLabel]);
        %             xlabel('Time [s]');
        %             ylabel('Rate [Hz]');
        %             clear gaussdata;
        %
        %             % Interspike Interval Distribution (1 ms resolution)
        %             if (length(timestamps{cChannel}) > 1)  % Have to make sure that we have at least two data points
        %                 nbins = 500; % ms
        %                 dtime = (timestamps{cChannel}(2 : end) - timestamps{cChannel}(1 : end - 1)) * 1000;
        %
        %                 subplot(4, 1, 4);
        %                 bar(histc(dtime, 1 : 1 : nbins));
        %                 axis tight;
        %                 title(['Interspike Interval Histogram - ' EntityInfo(SegmentList(channel(cChannel))).EntityLabel]);
        %                 xlabel('Time [ms]');
        %                 ylabel('# Spikes');
        %                 clear dtime;
        %             end
        %         end

    otherwise
        status = -1;
        statusmsg = sprintf('%s: %s is an unknown file type',mfilename,ext);
        return;
end
