function [] = bmi5_calibrate_test(mouse)
global m2; 
if(mouse)
	load('calibration_mouse.mat');
else
	load('calibration.mat'); 
end
qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 3); 
m2.Data(1).affine_m44 = q2; 
bmi5_sync(); 

while(1)
	p = pm * m2.Data(1).polhemus_sensors;
	m2.Data(1).target_trans = p(1:2); 
	bmi5_sync(); 
end