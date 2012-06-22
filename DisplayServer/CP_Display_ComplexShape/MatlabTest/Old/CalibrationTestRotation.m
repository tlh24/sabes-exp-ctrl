strVisServerName ='grappelli';

dFi = (pi/180)*30;  % 30 deg

sinFi = sin(dFi);
cosFi = cos(dFi);
X_shift = 10;
Y_shift = -20;

X_min = 0.25;
X_max = 0.75;
nX = 5;
Y_min = 0.15;
Y_max = 0.7;
nY = 4;

X_pix = 1024;
Y_pix = 768;

x_v = [X_min: (X_max - X_min)/(nX - 1):X_max];
x_mat = repmat(x_v, [nY, 1]);
x_pos = x_mat(:) * X_pix - X_shift;
y_v = [Y_min: (Y_max - Y_min)/(nY - 1):Y_max]';
y_mat = repmat(y_v, [1, nX]);
y_pos = y_mat(:) * Y_pix - Y_shift;
xy_pos = [(x_pos * cosFi)-(y_pos * sinFi), (y_pos * cosFi)+(x_pos * sinFi)];

% figure;
% plot(x,y,'r.');
% axis equal;
% xlim([0 X_pix]);
% ylim([0 Y_pix]);

% return;

hW = actxserver('VisServer.VisWindow',strVisServerName);  pause(.1);
hC = actxserver('VisServer.VisCalibrate',strVisServerName);

for( iPoint = 1:length(x_pos))
  pause(0.1);
  fprintf('Point # %d\n', iPoint );
  while(~hC.ready), end  % wait for ready
  hC.pos = xy_pos(iPoint,:); % put new position
end

if iscom(hC)  release(hC); end;
if iscom(hW)  release(hW); end;
