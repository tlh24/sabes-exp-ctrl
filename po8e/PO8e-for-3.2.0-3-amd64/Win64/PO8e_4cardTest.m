close all; clear all; clear classes; clear fun; clc;

if exist('PO8')
    clear PO8
end

PO8 = PO8e_4card();

count = PO8.cardCount();
fprintf('Found %d card(s) in the system.\n', count)
if (0 == count)
    error('  exiting\n');
end

for x = 1:count
    fprintf(' Connecting to card %d\n', x)
    PO8 = PO8.connectToCard(x);
    if (PO8.isNull(x))
        disp('  connection failed');
    else
        fprintf('  established connection to card %d\n', x)
        if ~PO8.startCollecting(x, 1);
           fprintf('  startCollecting() failed with: %d\n', PO8.getLastError(x))
           PO8.releaseCard(x);
        else
           disp('  card is collecting incoming data.');
        end
    end
end

fprintf('Waiting for the stream to start on card 1\n')
numSamples = 0;
while numSamples < 1
    [numSamples, PO8] = PO8.samplesReady(1);
    pause(.05);
end	

stoppedCount = 0;           
timeout = intmax;
while stoppedCount < count
    
    if (count == 1)
        PO8.waitForDataReady(1, timeout); %timeout is in milliseconds
    end
    waitCount = 0;
    stoppedCount = 0;
        
    for x = 1:count
        [numSamples, PO8] = PO8.samplesReady(x);
        if PO8.isStopped(x)
            stoppedCount = stoppedCount + 1;
        elseif numSamples > 0
            %fprintf('numSamples = %d\n', numSamples)
            PO8 = PO8.readBlock(x, numSamples);
            if (PO8.Status(x) == 0)
                disp('  reading block failed; no samples returned');
            else
                PO8.flushBufferedData(x, numSamples, 0);
                % each row of PO8.Data{x} is 1 channel
                % do something with the data here
                % ...
                % ...
                
                size(PO8.Data{x});
                xd = max(max(PO8.Data{x}));
                nd = min(min(PO8.Data{x}));
                xo = max(max(PO8.Offsets{x}));
                no = min(min(PO8.Offsets{x}));
                fprintf('numSamples = %d, %.2f %.2f %d %d\n', numSamples, nd, xd, no, xo)
            end
         else
            waitCount = waitCount + 1;
        end
    end
    pause(.025)
end

for x = 1:count
    fprintf('Releasing card %d\n', x)
    PO8.releaseCard(x);
end

clear PO8
