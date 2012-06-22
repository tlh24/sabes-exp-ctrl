% strVisServerName = 'VisServer2';
strVisServerName = 'grappelli';

nDisks = 1000;

hW = actxserver('VisServer.VisWindow',strVisServerName); 
hW.calibrated = 0;
fprintf('Creating...\r', i);
for i=1:nDisks
%  fprintf('%3d\r', i);
  hDsk(i) = actxserver('VisServer.VisDisk',strVisServerName); 
end

disk_params = rand(5, nDisks);
scale_vect = [1023 767 1 1 1]';
scale_mat = repmat(scale_vect, [1, nDisks]); 
disk_params = scale_mat .* disk_params; % X,Y-coord, RGB

hW.batchmode = 1;
for i=1:nDisks
  hDsk(i).color = [disk_params(3:5,i)];
  hDsk(i).pos = [disk_params(1:2,i)];
  hDsk(i).show =1;
end
hW.drawnow();

fprintf('Press any key to delete objects\n');
pause;
delOrder = randperm(nDisks);
fprintf('Deleting...\r', i);
for i=delOrder
%  fprintf('%3d\r', i);
  if iscom(hDsk(i))  release(hDsk(i)); end;
end
hW.drawnow();
if iscom(hW)  release(hW); end;

