clear;
global bmi5_out bmi5_in b5

BASEPATH = '/home/joeyo/';

CalibrationFile = fullfile(BASEPATH,'sw/sabes-exp-ctrl/bmi5/matlab/calibration_polhemus.mat');

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('help')
bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make stars_circle dots 50');
bmi5_cmd('make circle');
bmi5_cmd('make polhemus finger'); 

eval(bmi5_cmd('mmap'));

b5.affine_m44 = eye(4);
b5.quadratic_m44 = zeros(4);
c = load(CalibrationFile);
qp = c.q';
q2 = eye(4);
q2(1:2, 1:2) = qp(1:2, 1:2);
q2(1:2, 4) = qp(1:2, 4);
b5.affine_m44 = q2;
b5 = bmi5_mmap(b5);

pos     = [20 90];
scale 	= 5.*[7 7];

b5.dots_pos         = pos;
b5.dots_scale       = scale;
b5.dots_starsize    = 2;
b5.dots_vel         = [0 0];
b5.dots_coherence   = 1;
b5.dots_color       = [1 0 0 1]; % RED
b5.dots_lifetime    = 0.1;
b5.dots_draw        = 1;

b5.circle_pos       = pos;
b5.circle_scale     = scale;
b5.circle_color     = [1 1 1 0.1]; % white
b5.circle_draw      = 1;

b5 = bmi5_mmap(b5);

while(1)
    tmp = c.pm * [b5.finger_sensors_o(1:3)];
    b5.dots_pos = tmp(1:2);
    b5.circle_pos = tmp(1:2);
    b5 = bmi5_mmap(b5);
end


