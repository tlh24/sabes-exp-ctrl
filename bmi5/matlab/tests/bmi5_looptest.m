clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('make stars');
bmi5_cmd('make circle cursor');
bmi5_cmd('make circle target');
eval(bmi5_cmd('mmap'));

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4); 

b5.stars_draw = 1; 
b5.stars_scale = [1 1]; 
b5.stars_pos = [0 0]; 
b5.stars_color = [1 1 1 1]; 
b5.stars_coherence = 0.5; 
b5.stars_vel = [0.1; 0.1]; 

b5.cursor_draw = 1; 
b5.cursor_color = [1 0 0 1]; 
b5.cursor_scale = [0.2 0.2]; 
b5.target_draw = 1; 
b5.target_color = [0 1 0 1]; 
b5.target_scale = [0.2 0.2]; 

bmi5_mmap(b5);

n = 20000;
tic
for i=1:n
	b5.cursor_pos = sin(toc()/4)*[sin(toc()); cos(toc())]; 
	b5.target_pos = -1* b5.cursor_pos; 
	b5.stars_vel = 0.1*[sin(toc()); cos(toc())]; 

	bmi5_mmap(b5);
% 	if(code ~= 0)
% 		disp('unexpected response from bmi5_out pipe'); 
% 	end
% 	disp(['frame ' num2str(b5.frame_o)]); 
% 	disp(['ticks ' num2str(b5.ticks_o)]); 
end
d = toc();
frame_rate = n/d
