% strVisServerName = 'VisServer2';
strVisServerName = 'grappelli';


nFrames = 1000;
nDisks = 5;

% Position and size are in fractions of the screen size 
CounterH   =.02;
CounterW   =.3;
CounterOff =.1;

fprintf('Starting VisServer...\n')
fprintf('VisWindow\n')
hW = actxserver('VisServer.VisWindow',strVisServerName); 
hW.calibrated = 0;
hW.counterpos=[1-CounterW-CounterOff 1-CounterH]; 
hW.countersize=[CounterW CounterH];

fprintf('Creating VisDisks\n')
for i=1:nDisks
  hDsk(i) = actxserver('VisServer.VisDisk',strVisServerName); 
end
disk_params = rand(5, nDisks, nFrames);
scale_vect = [1023 767 1 1 1]';
scale_mat = repmat(scale_vect, [1, nDisks, nFrames]); 
disk_params = scale_mat .* disk_params; % X,Y-coord, RGB

hW.batchmode = 1;
for i=1:nDisks
  hDsk(i).color = [disk_params(3:5,i,1)];
  hDsk(i).show =1;
end

FrameTimes = zeros(1, nFrames);
hW.batchmode = 1;
hW.logmode = 1;
for iFrame=1:nFrames
  tic
  for i = 1:nDisks
    hDsk(i).pos = [disk_params(1:2,i,iFrame)];
%     hDsk(i).color = [disk_params(3:5,i,iFrame)]; % log something
  end
  if ~rem(iFrame, 10 )
    hDsk(1).color = [disk_params(3:5,1,iFrame)]; % log something
  end
  hW.drawnow();
  % wait for VisServer to finish drawing and change the mode
  dummy = hW.logmode; 
  FrameTimes(iFrame) = toc;
end

fprintf('Finished\n');
for i=1:nDisks
  if iscom(hDsk(i))  release(hDsk(i)); end;
end
if iscom(hW)  release(hW); end;

mean(FrameTimes)
plot(FrameTimes, '-+');
% ft1=FrameTimes(1:2:nFrames);
% ft4=FrameTimes(1:2:nFrames);
% hist(ft1);
% hist(ft2);
