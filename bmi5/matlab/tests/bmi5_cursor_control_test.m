clear;

global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('make circle cursor');
bmi5_cmd('make polhemus finger');
eval(bmi5_cmd('mmap'));

b5.cursor_scale = [5; 5];       % in mm
b5.cursor_color = [1; 1; 1; 1]; % white
b5.cursor_pos   = [0; 0];
b5.cursor_draw  = 1;

load('../calibration.mat'); % load pm & q. 

qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2; 

bmi5_mmap(b5); 

while(1)
    p = pm * b5.finger_sensors_o; 
    b5.cursor_pos = p(1:2); 
    bmi5_mmap(b5);
end