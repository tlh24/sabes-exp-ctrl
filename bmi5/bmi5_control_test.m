% test the connection with bmi5 as well. 
global bmi5_in bmi5_out m2; 
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

m2.Data(1).tone_freq = 440; 
m2.Data(1).tone_pan = 0;
m2.Data(1).tone_scale = 1;
m2.Data(1).tone_duration = 5;

m2.Data(1).cursor_scale = [0.1; 0.1]; 
m2.Data(1).cursor_color = [1; 0.6; 1; 1]; 
m2.Data(1).cursor_trans = [0.5; 0.5];
m2.Data(1).target_scale = [0.1; 0.1]; 
m2.Data(1).target_color = [1; 1; 0.6; 1]; 
m2.Data(1).target_trans = [-0.5; -0.5];

m2.Data(1).cursor_draw = 1; 
m2.Data(1).target_draw = 1;  
m2.Data(1).stars_draw = 1; 

m2.Data(1).affine_m44 = eye(4); 
m2.Data(1).quadratic_m44 = zeros(4); 

m2.Data(1).stars_coherence = 0.5; 
m2.Data(1).stars_scale = [1; 1]; %necessary! -- defaults to 0.

bmi5_cmd('go.'); 

n = 200
tic
for i=1:n
	m2.Data(1).cursor_trans = sin(toc()/4)*[sin(toc()); cos(toc())]; 
	m2.Data(1).target_trans = -1* m2.Data(1).cursor_trans; 
	m2.Data(1).stars_vel = 0.1*[sin(toc()); cos(toc())]; 
	m2.Data(1).trial = [i; floor(i/10); floor(i/100)]; 
	% tell bmi5 to set these parameters -- it's read is blocking.
	fwrite(bmi5_in, 'go.'); 
	% if bmi5 has to do anything, it will block on this read. 
	% could e.g. wait for vsync.
	code = fread(bmi5_out, 1, 'int');
	if(code ~= 0)
		disp('unexpected response from bmi5_out pipe'); 
	end
	disp(['frame ' num2str(m2.Data(1).frame)]); 
	disp(['ticks ' num2str(m2.Data(1).ticks)]); 
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