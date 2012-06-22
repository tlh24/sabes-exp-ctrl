function [TransformMtx] = CalcTransformMtx( v1, v2, v3);

% v1 = [49.616 -285.50 -1579.75]';
% v2 = [51.1085 284.197 -1574.20]';
% v3 = [126.626 -393.422 -1887.76]';

% directional vector of X - axis
% goes through points 1 and 2
dirX = (v2-v1)/norm(v2-v1);   %normalize to length 1

% directional vector of Y - axis
% subtract X-component from v3->v1 vector
% The remainder is the Y - component
vY = (v1 - v3) - dirX * dot( dirX, (v1 - v3));
dirY = vY/norm(vY);  %normalize to length 1

% directional vector of Z - axis
% subtract X and Y components from v1 vector
% the remainder is the Z - component
vZ = -v1 + dirX * dot(dirX, v1) + dirY * dot( dirY, v1);
dirZ = vZ/norm(vZ);   %normalize to length 1


rotMtx = [dirX dirY dirZ];
vTrans = -rotMtx' * v1;

TransformMtx = [rotMtx 
                vTrans' ];


% Sanity checks
% dot(dirX, dirY)  % should be 0
% dot(dirX, dirZ)  % should be 0
% dot(dirY, dirZ)  % should be 0
% det(rotMtx)      % should be 1
% 
% v1p = [v1; 1]' * TransformMtx   % should be 0 0 0 
% v2p = [v2; 1]' * TransformMtx  % should be x2 0 0
% v3p = [v3; 1]' * TransformMtx  % should be x3 y3 0