%% connect to bmi5
global bmi5_in bmi5_out;

cd('/home/motorlab/sabes-exp-ctrl/bmi5/matlab');
bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

bmi5_cmd('make labjack isometric 4 4'); 
eval(bmi5_cmd('mmap'));
%%
b5 = bmi5_mmap(b5); 
b5.isometricAIN_sensors_o

%%
b5.isometricDOUT_channels = [0 0 1 1];
b5 = bmi5_mmap(b5);
%%
b5.isometricDOUT_channels = [1 0 1 1];
b5 = bmi5_mmap(b5);
juiceStart = b5.isometricDOUT_time_o;

while (b5.time_o - juiceStart) < 0.1
    b5 = bmi5_mmap(b5);
end

b5.isometricDOUT_channels = [0 0 1 1];
b5 = bmi5_mmap(b5);
%% define sampling parameters

n = 50000; %number of samples read from labjack
nMean = 250; %number of samples for averaging to remove noise

%% check sampling rate

tic
for ii = 1:nMean
    b5 = bmi5_mmap(b5); 
    initSample = b5.isometricAIN_sensors_o;
end
samplingTime = toc

%% Begin streaming
DlgH = figure(1);
set(gcf, 'position', [1921, 361, 1280, 643])
closeStream = 0;
H = uicontrol('Style', 'PushButton', ...
                    'String', 'Stop', ...
                    'position', [20 10 60 20], ...
                    'Callback', 'streamU6 = 0');
H2 = uicontrol('Style', 'PushButton', ...
                    'String', 'Play', ...
                    'position', [100 10 60 20], ...
                    'Callback', 'streamU6 = 1');
H3 = uicontrol('Style', 'PushButton', ...
                    'String', 'Close', ...
                    'position', [200 10 60 20], ...
                    'Callback', 'closeStream = 1');
H4 = uicontrol('Style', 'PushButton', ...
                    'String', 'Cursor or Plot', ...
                    'position', [20 30 90 20], ...
                    'Callback', 'plotMode = mod(plotMode+1,3)');
axesHandle = axes('position', [0.1,0.1,0.8,0.8]);
insetHandleX = axes('position', [0.65, 0.1, 0.25, 0.25]);

                

rawforce = zeros(2, n/nMean);                
force = zeros(2, n/nMean);
itmp = zeros(4,nMean);
streamU6 = 1;
plotMode = 2;
Vin = 5;
ZeroBalanceTolerance = 0.002;
ZeroBalance = ZeroBalanceTolerance*Vin*2e-3;
plotLimits = Vin*2.2e-3;
points = 0;
bigEffort = Vin*[1e-3, 1e-3];
smallEffort = bigEffort/2;
% smallEffort = Vin*[-0.2e-3, -0.2e-3];
bigRadius = 0.1e-3;
smallRadius = 0.05e-3;

rawSignal = [];

bigReward = 5;
smallReward = 1;
timer = 0;
rewardTime = 10;
makeVideo = 0;

if makeVideo
    clear writerObj
    writerObj = VideoWriter('/home/motorlab/Documents/SUBNETS/VideoTask2_02.avi');

    writerObj.FrameRate = 7;

    open(writerObj)
end

while ~closeStream
    while streamU6 && ~closeStream
%         tic
        for ii = 1:nMean
            b5 = bmi5_mmap(b5); 
            itmp(:,ii) = -b5.isometricAIN_sensors_o;
        end
        
%         rawSignal = [rawSignal, itmp];
%         toc
%         for jj= 1:size(itmp,1)
%             itmp(jj,:) = filtfilt(b1,a1, itmp(jj,:));
% %             itmp(jj,:) = filtfilt(b2,a2, itmp(jj,:));
%         end
%         force(1, n/nMean + 1) = mean((itmp(2,:) - itmp(1,:))./itmp(5,:));
%         force(2, n/nMean + 1) = mean((itmp(4,:) - itmp(3,:))./itmp(5,:));
        newForceX = mean(itmp(1,:));
        newForceY = mean(itmp(3,:));
        if abs(newForceX - force(1,n/nMean)) > ZeroBalance
            force(1, n/nMean + 1) = newForceX;
        elseif abs(newForceX) < ZeroBalance
            force(1, n/nMean + 1) = 0;
        else
            force(1, n/nMean + 1) = force(1,n/nMean);
        end
        
        if abs(newForceY - force(2,n/nMean)) > ZeroBalance
            force(2, n/nMean + 1) = newForceY;
        elseif abs(newForceY) < ZeroBalance
            force(2, n/nMean + 1) = 0;
        else
            force(2, n/nMean + 1) = force(2,n/nMean);
        end
        force(:,1) = [];
%         force = floor(1e4*force)./1e4;
%         for jj = 1:size(force,1)
%             force(jj,:) = filtfilt(b2,a2, force(jj,:));
%         end
        switch plotMode
            case 0
                axes(axesHandle)
                cla
                xlim('auto')
                plot(force(1:2,:)','o');
                ylim([-1 1]*plotLimits);
                
            case 1
                axes(axesHandle)
                cla
                try
                    delete(htext)
                    delete(htext2)
                    delete(htext3)
                end
                hold on
                scatter(force(1,end),force(2,end), 0.5e3,'ro', 'filled');
                scatter(smallEffort(1), smallEffort(2), smallRadius*30e6,'bo');
                text(smallEffort(1), smallEffort(2), '1', 'fontsize', 25)
                scatter(bigEffort(1), bigEffort(2), bigRadius*70e6, 'go');
                text(bigEffort(1), bigEffort(2), '5', 'fontsize', 25)
                htext = text(Vin*1e-3, Vin*2.3e-3, ['Time to reward = ' num2str(rewardTime - timer) '   points = ' num2str(points)], 'fontsize', 20);
                htext2 = text(2.21*Vin*1e-3,-5.5e-3, 'X force');
                htext3 = text(2.21*Vin*1e-3,-8.5e-3, 'Y force');
                xlim([-1 1]*plotLimits);
                if sqrt((force(1,end) - smallEffort(1))^2 + (force(2,end) - smallEffort(2))^2) <  smallRadius*1.8*Vin
                    timer = timer + 1;
                elseif sqrt((force(1,end) - bigEffort(1))^2 + (force(2,end) - bigEffort(2))^2) <  bigRadius*3*Vin
                    timer = timer + 1;
                else
                    timer = 0;
                end
            
                if timer == rewardTime
                    if sqrt((force(1,end) - smallEffort(1))^2 + (force(2,end) - smallEffort(2))^2) >  smallRadius*2.5
                        points = points + 5;
                    else
                        points = points + 1;
                    end
                    timer = 0;
                    bigEffort(1) = randi([500, 1500],1,1)*1e-6*Vin;
                    bigEffort(2) = randi([500, 1500],1,1)*1e-6*Vin;
                    smallEffort(1) = -randi([100, 500],1,1)*1e-6*Vin;
                    smallEffort(2) = -randi([100, 500],1,1)*1e-6*Vin;
                    cla
                    pause(0.5)
                end
                ylim([-1 1]*plotLimits);
                axes(insetHandleX)
                cla
                xlim('auto')
                plot([force(1,:)+5e-3;force(2,:)-5e-3]');
                ylim([-1 1]*plotLimits);
                axis off
                box off
                
            
            case 2
                axes(axesHandle)
                cla
                try
                    delete(htext)
                    delete(htext2)
                    delete(htext3)
                end
                hold on
                scatter(force(1,end),force(2,end),'ro');
                plot(-plotLimits:0.0001:plotLimits, smallEffort(1),'oc')
                plot(-plotLimits:0.0001:plotLimits, bigEffort(1),'oc')
                htext = text(Vin*1e-3, Vin*2.3e-3, ['Time to reward = ' num2str(rewardTime - timer) '   points = ' num2str(points)], 'fontsize', 20);
                htext2 = text(2.21*Vin*1e-3,-5.5e-3, 'X force');
                htext3 = text(2.21*Vin*1e-3,-8.5e-3, 'Y force');xlim([-1 1]*plotLimits);
                
                text(smallEffort(1), smallEffort(2), num2str(smallEffort(1)), 'fontsize', 25)
                text(bigEffort(1), bigEffort(2), num2str(bigEffort(1)), 'fontsize', 25)
                
                if smallEffort(1) > force(2,end)
%                     timer = timer + 1;
                elseif bigEffort(1) < force(2,end)
%                     timer = timer + 1;
                else
                    timer = 0;
                end
            
                if timer == rewardTime
                    if force(2,end) > bigEffort(1)
                        points = points + 5;
                    else
                        points = points + 1;
                    end
                    timer = 0;
%                     bigEffort = randi([500, 1500],1,2)*1e-6*Vin;
%                     smallEffort = -randi([100, 500],1,2)*1e-6*Vin;
                    cla
                    pause(0.5)
                end
                ylim([-1 1]*plotLimits);
                axes(insetHandleX)
                cla
                xlim('auto')
                plot([force(1,:)+5e-3;force(2,:)-5e-3]');
                ylim([-1 1]*plotLimits);
                axis off
                box off
            case 3
                cla
                xlim('auto')
                plot(diff(itmp(1:2,:)),'o')
        end
        
%         set(gca, 'xtick', [])
        if makeVideo
            currFrame = getframe(gcf);
            writeVideo(writerObj, currFrame);
        end
        
        pause(0.005)
%         if size(rawSignal,2) > 250000
%             closeStream = 1;
%         end
%     toc
    end
    if makeVideo
        makeVideo = 0;
        close(writerObj)
    end
    
    pause(0.02)
end
delete(DlgH)

