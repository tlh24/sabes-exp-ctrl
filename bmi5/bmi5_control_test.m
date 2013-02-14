% test the connection with bmi5 as well. 
global bmi5_in bmi5_out b5;

b5 = [];

cd('/home/joeyo/sw/sabes-exp-ctrl/bmi5');

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

% initial settings -- setup a cursor and a starfield.
bmi5_cmd('store float 3 trial'); 
bmi5_cmd('make circle cursor_'); 
bmi5_cmd('make stars stars_'); 
bmi5_cmd('make circle target_'); 
bmi5_cmd('make tone tone_');  % tone object, not actual tone.
eval(bmi5_cmd('mmap structure')); 

b5.tone_freq = 440; 
b5.tone_pan = 0;
b5.tone_scale = 1;
b5.tone_duration = 1;

b5.cursor_scale = [0.1; 0.1]; 
b5.cursor_color = [1; 0.6; 1; 1]; 
b5.cursor_trans = [0.5; 0.5];
b5.target_scale = [0.1; 0.1]; 
b5.target_color = [1; 1; 0.6; 1]; 
b5.target_trans = [-0.5; -0.5];

b5.cursor_draw = 1; 
b5.target_draw = 1;  
b5.stars_draw = 1; 

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4); 

b5.stars_coherence = 0.5; 
b5.stars_scale = [1 ; 1]; %necessary! -- defaults to 0.
b5.stars_vel = [0.5 ; 0.5];

code = bmi5_mmap(b5); 

bmi5_cmd('start_recording'); 


% fwrite(bmi5_in, 'save serial_test.mat');
% code = fread(bmi5_out, 1, 'int');
% msg = char(fread(bmi5_out, code, 'char')')
% 
% fclose(bmi5_in); 
% fclose(bmi5_out); 
% 
% clear all
% load serial_test.mat
% trial