function [] = bmi5_calibrate_test(mouse)
global bmi5_in bmi5_out b5;

cd('/home/joeyo/sw/sabes-exp-ctrl/bmi5');

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

b5 = [];

if(mouse)
	load('calibration_mouse.mat');
else
	load('calibration.mat'); 
end
qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 3); 
b5.affine_m44 = q2; 
bmi5_sync(); 

while(1)
	p = pm * b5.polhemus_sensors_o;
	b5.target_pos = p(1:2); 
	bmi5_sync(); 
end