function [] = bmi5_calibrate_test(mouse)
global bmi5_in bmi5_out;

cd('/home/joeyo/sw/sabes-exp-ctrl/bmi5/matlab');
bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

bmi5_cmd('make circle cursor');
if(mouse)
	load('calibration_mouse.mat');
    bmi5_cmd('make mouse finger');
else
    load('calibration_polhemus.mat');
    bmi5_cmd('make polhemus finger');
end
bmi5_cmd('mmap')
eval(bmi5_cmd('mmap'));

if mouse
    b5.cursor_scale = [0.1; 0.1]; % in mm
else
    b5.cursor_scale = [5; 5]; % in mm
end
b5.cursor_color = [1; 1; 1; 1]; 
b5.cursor_pos   = [0; 0];
b5.cursor_draw  = 1;

qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 3); 
b5.affine_m44 = q2; 
b5 = bmi5_mmap(b5);

while(1)
	p = pm * b5.finger_sensors_o;
	b5.cursor_pos = p(1:2); 
	b5 = bmi5_mmap(b5);
end