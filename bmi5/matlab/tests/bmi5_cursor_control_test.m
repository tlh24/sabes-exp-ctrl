clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make circle cursor');
bmi5_cmd('make polhemus finger');
eval(bmi5_cmd('mmap'))

b5.cursor_scale = [5; 5];       % in mm
b5.cursor_color = [1; 1; 1; 1]; % white
b5.cursor_pos   = [0; 0];
b5.cursor_draw  = 1;

%load('../calibration_opto.mat'); % load pm & q. 
%load('../calibration_mouse.mat'); % load pm & q. 
load('~/sw/sabes-exp-ctrl/bmi5/matlab/calibration_polhemus.mat'); % load pm & q. 

qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2; 

b5 = bmi5_mmap(b5); 

t = b5.time_o;

while(1)
    
    p = pm * b5.finger_sensors_o; 
%    p = b5.finger_sensors_o; 
    b5.cursor_pos = p(1:2);
    b5 = bmi5_mmap(b5);
    
    if ((b5.time_o - t) > 30)
        fprintf('-> saving BMI5 data\n');
        bmi5_cmd('save /tmp/bmi5_cursor_control_test.mat');
        t = b5.time_o;
    end
end