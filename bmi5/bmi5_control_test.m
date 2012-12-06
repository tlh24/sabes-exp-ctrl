% test the connection with bmi5 as well. 
cd('/home/tlh24/sabes-exp-ctrl/bmi5');

bmi5_out = fopen('/home/tlh24/sabes-exp-ctrl/bmi5/bmi5_out', 'r'); 
bmi5_in = fopen('/home/tlh24/sabes-exp-ctrl/bmi5/bmi5_in', 'w'); 

% initial settings -- setup a cursor and a starfield.
fwrite(bmi5_in, 'store float 3 trial')
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')

fwrite(bmi5_in, 'make circle cursor_');
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')

fwrite(bmi5_in, 'make stars stars_');
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')

fwrite(bmi5_in, 'make circle target_');
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')

fwrite(bmi5_in, 'tone'); % tone object, not actual tone.
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')

fwrite(bmi5_in, 'mmap structure');
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')')
eval(msg); 

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

m2.Data(1).stars_coherence = 0.5; 
m2.Data(1).stars_scale = [1; 1]; %necessary! -- defaults to 0.
fwrite(bmi5_in, 'go.'); 
code = fread(bmi5_out, 1, 'int');

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