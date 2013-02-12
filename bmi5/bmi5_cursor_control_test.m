function [] = bmi5_cursor_control_test()
global b5; 
load('calibration.mat'); % load pm & q. 
affine = eye(4); 
affine(1:2, 1:2) = q(1:2, 1:2)'; 
affine(1:2, 4) = q(3, 1:2)'; 
b5.affine_m44 = affine; % so everything is saved in world coords.
b5.stars_scale = [10; 10]; % units: cm!
b5.cursor_scale = [1; 1]; 
b5.target_scale = [1; 1]; 
bmi5_mmap(b5); 

while(1)
    world = pm * b5.polhemus_sensors_o; 
    b5.cursor_trans = world(1:2); 
    bmi5_mmap(b5);
end