clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make square');
bmi5_cmd('make circle bigcircle');
bmi5_cmd('make circle');
bmi5_cmd('make magnets mag 100');

eval(bmi5_cmd('mmap'));

%b5.affine_m44 = eye(4);
%b5.quadratic_m44 = zeros(4);


c = load('calibration_polhemus.mat'); 
qp = c.q';
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2;
%}

b5.square_draw = 1;
b5.square_scale = [200 200];
b5.square_color = [0 0 1 1]; %blue
b5.square_pos = [0 50];

b5.bigcircle_draw = 1;
b5.bigcircle_scale = [200 200];
b5.bigcircle_color = [0 1 0 1]; %green
b5.bigcircle_pos = [0 50];

b5.circle_draw = 1;
b5.circle_scale = [5 5];
b5.circle_color = [1 0 0 1]; % red
b5.circle_pos = [10 50];

b5.mag_draw = 1;
b5.mag_color = [1 1 1 1]; % white
b5.mag_pos = [0 50]; 
b5.mag_scale = [200 200];
b5.mag_coherence = 0.5;
b5.mag_compassL = 10;
b5.mag_target = [10 50];

b5 = bmi5_mmap(b5);

return;

% ----
bmi5_cmd('delete_all')
% ----

b5 = bmi5_mmap(b5);

