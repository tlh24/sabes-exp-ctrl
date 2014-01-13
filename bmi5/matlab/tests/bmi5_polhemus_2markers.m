clear;

global bmi5_out bmi5_in b5

CalibrationFile = '/home/motorlab/sw/sabes-exp-ctrl/bmi5/matlab/calibration_polhemus.mat';

cd('/home/motorlab/sw/sabes-exp-ctrl/bmi5/matlab');
bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make polhemus finger 2'); 
bmi5_cmd('make circle cursorA');
bmi5_cmd('make circle cursorB');
eval(bmi5_cmd('mmap structure'));

c = load(CalibrationFile); 
qp = c.q';
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2;
b5 = bmi5_mmap(b5);

b5.cursorA_draw = 3;
b5.cursorA_scale = [5 5];
b5.cursorA_color = [1 0 0 1]; % red

b5.cursorB_draw = 3;
b5.cursorB_scale = [5 5];
b5.cursorB_color = [0 0 1 1]; % blue

b5 = bmi5_mmap(b5);

while(1)
    posA = c.pm * [b5.finger_sensors_o(1:3)];
    posB = c.pm * [b5.finger_sensors_o(4:6)];
    b5.cursorA_pos = posA(1:2);
    b5.cursorB_pos = posB(1:2);
    b5 = bmi5_mmap(b5);
end
