% strVisServerName = 'VisServer2';
strVisServerName = 'grappelli';


nFrames = 10;
nDisks = 3;



fprintf('Starting VisServer...\n')
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
  hDsk(i).color = [i i i]*(1.0/nDisks);
  hDsk(i).pos = [500+ 10*i; 300 + 10*i];
  hDsk(i).z = [0.7-i/10];
  hDsk(i).radius = 20;
  hDsk(i).show =1;
end
hW.drawnow();
fprintf('Press any key to continue\n');
pause();

% 
% tic
% for j=1:nFrames
%   hW.batchmode = 1;
%   for i = 1:nDisks
%     hDsk(i).pos = [disk_params(1:2,i,j)];
%   end
%   hW.drawnow();
% end
% toc/nFrames

fprintf('Finished\n');
for i=1:nDisks
  if iscom(hDsk(i))  release(hDsk(i)); end;
end
hW.drawnow();

if iscom(hW)  release(hW); end;

