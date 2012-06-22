% strVisServerName = 'VisServer1';
strVisServerName = 'grappelli';


nFrames = 1000;
nDisks = 20;

fprintf('Starting VisServer...\n')
fprintf('VisWindow\n')
hW = actxserver('VisServer.VisWindow',strVisServerName); 
hW.calibrated = 0;
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

tic
for j=1:nFrames
  hW.batchmode = 1;
  for i = 1:nDisks
    hDsk(i).pos = [disk_params(1:2,i,j)];
  end
  hW.drawnow();
end
toc/nFrames

fprintf('Finished\n');
for i=1:nDisks
  if iscom(hDsk(i))  release(hDsk(i)); end;
end
if iscom(hW)  release(hW); end;

