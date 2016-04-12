clear;

global bmi5_out bmi5_in b5

BASEPATH = '/home/joeyo/';

CalibrationFile = fullfile(BASEPATH,'sw/sabes-exp-ctrl/bmi5/matlab/calibration_polhemus.mat');

cd(fullfile(BASEPATH,'sw/sabes-exp-ctrl/bmi5/matlab'));

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make polhemus finger'); 
bmi5_cmd('make circle cursor');
eval(bmi5_cmd('mmap structure'));

b5 = bmi5_mmap(b5);

c = load(CalibrationFile); 
qp = c.q';
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2;
b5 = bmi5_mmap(b5);

b5.cursor_draw = 3;
b5.cursor_scale = [5 5];
b5.cursor_color = [1 0 0 1]; % red

b5 = bmi5_mmap(b5);

while(1)
    pos = c.pm * [b5.finger_sensors_o(1:3)];
    b5.cursor_pos = pos(1:2);
    b5 = bmi5_mmap(b5);
end
