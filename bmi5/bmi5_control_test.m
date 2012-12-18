% test the connection with bmi5 as well. 
global bmi5_in bmi5_out b5; 
cd('/home/tlh24/sabes-exp-ctrl/bmi5');

bmi5_out = fopen('/home/tlh24/sabes-exp-ctrl/bmi5/bmi5_out', 'r'); 
bmi5_in = fopen('/home/tlh24/sabes-exp-ctrl/bmi5/bmi5_in', 'w'); 

% initial settings -- setup a cursor and a starfield.
bmi5_cmd('store float 3 trial'); 
bmi5_cmd('make circle cursor_'); 
bmi5_cmd('make stars stars_'); 
bmi5_cmd('make circle target_'); 
bmi5_cmd('tone');  % tone object, not actual tone.
eval(bmi5_cmd('mmap structure')); 

b5.tone_freq = 440; 
b5.tone_pan = 0;
b5.tone_scale = 1;
b5.tone_duration = 5;

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
b5.stars_scale = [1; 1]; %necessary! -- defaults to 0.

bmi5_mmap(b5); 
bmi5_cmd('go.'); 

bmi5_cmd('start_recording'); 

n = 20000
tic
for i=1:n
	b5.cursor_trans = sin(toc()/4)*[sin(toc()); cos(toc())]; 
	b5.target_trans = -1* b5.cursor_trans; 
	b5.stars_vel = 0.1*[sin(toc()); cos(toc())]; 
	b5.trial = [i; floor(i/10); floor(i/100)]; 
	% tell bmi5 to set these parameters -- it's read is blocking.
	bmi5_mmap(b5);
	fwrite(bmi5_in, 'go.'); 
	% if bmi5 has to do anything, it will block on this read. 
	% could e.g. wait for vsync.
	code = fread(bmi5_out, 1, 'int');
% 	if(code ~= 0)
% 		disp('unexpected response from bmi5_out pipe'); 
% 	end
% 	disp(['frame ' num2str(b5.frame_o)]); 
% 	disp(['ticks ' num2str(b5.ticks_o)]); 
end
d = toc()
frame_rate = n/d

fwrite(bmi5_in, 'save serial_test.mat');
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')

fclose(bmi5_in); 
fclose(bmi5_out); 

clear all
load serial_test.mat
trial