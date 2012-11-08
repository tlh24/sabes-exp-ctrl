% make a connection with gtkclient.
m = memmapfile('/tmp/binned', 'Format', {'uint16' [10 194] 'x'}); 
A = m.Data(1).x;

pipe_out = fopen('~/myopen/gtkclient_tdt/gtkclient_out', 'r'); 
pipe_in = fopen('~/myopen/gtkclient_tdt/gtkclient_in', 'w'); 

% test the connection with bmi5 as well. 
m2 = memmapfile('/tmp/bmi5_control', 'Format', {...
        'double' [1 1] 'time';...
        'double' [1 1] 'ticks';...
        'double' [1 1] 'frame';...
        'double' [4 1] 'shape_color';...
        'double' [2 1] 'shape_scale';...
        'double' [2 1] 'shape_trans';...
        'double' [4 1] 'stars_color';...
        'double' [2 1] 'stars_scale';...
        'double' [2 1] 'stars_trans';...
        'double' [2 1] 'stars_vel';...
        'double' [1 1] 'stars_coherence';...
        'double' [3 1] 'polhemus_sensors';...
        'double' [1 1] 'polhemus_time';...
        'double' [1 1] 'polhemus_ticks';...
        });

m2.Writable = true; 

bmi5_out = fopen('~/sabes-exp-ctrl/bmi5/bmi5_out', 'r'); 
bmi5_in = fopen('~/sabes-exp-ctrl/bmi5/bmi5_in', 'w'); 

skip = 0;
prev = 0;

% initial settings. 
m2.Data(1).shape_scale = [0.1; 0.1]; 
m2.Data(1).shape_color = [1; 0.7; 1; 1]; 
m2.Data(1).stars_coherence = 0.5; 
fwrite(bmi5_in, 'go.'); 
msg = fread(bmi5_out, 3, 'uchar');

n = 5000; 
tic
skip = 0; 
prev = 0; 
for i=1:n
	% first, ping gtkclient to sample the binned spike data. 
	disp('writing to pipe_in') 
	fwrite(pipe_in, 'go.'); 
	disp('reading from pipe_out'); 
	msg = fread(pipe_out, 3, 'uchar'); % uncertain if this interlock is strictly necessary.
	% disp([num2str(i) ' ' num2str(A(1,193))]); 
	if A(1,193) - prev ~= 1
		skip = skip + 1; 
	end
	prev = A(1,193); 
	% now interact with the display (bmi5).
	m2.Data(1).stars_shape_vel = 0.1*[sin(toc()); cos(toc())]; 
	m2.Data(1).shape_trans =  0.5*[sin(toc()); cos(toc())]; 
	% tell bmi5 to set these parameters -- its read is blocking.
	fwrite(bmi5_in, 'go.'); 
	% if bmi5 has to do anything, it will block on this read. 
	% could e.g. wait for vsync.
	msg = fread(bmi5_out, 3, 'uchar');
	disp(['frame ' num2str(m2.Data(1).frame)]); 
	disp(['ticks ' num2str(m2.Data(1).ticks)]); 
	if 0
		image(A(:,1:192)/300); 
		ylabel('lag')
		xlabel('neuron'); 
		colormap gray
		drawnow
	end
end
d = toc()
frame_rate = n/d
skip

fclose(pipe_in); 
fclose(pipe_out); 
fclose(bmi5_in); 
fclose(bmi5_out); 
