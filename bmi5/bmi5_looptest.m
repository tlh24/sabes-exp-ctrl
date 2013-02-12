function [] = bmi5_looptest()
global b5; 
n = 20000;
tic
for i=1:n
	b5.cursor_trans = sin(toc()/4)*[sin(toc()); cos(toc())]; 
	b5.target_trans = -1* b5.cursor_trans; 
	b5.stars_vel = 0.1*[sin(toc()); cos(toc())]; 
	b5.trial = [i; floor(i/10); floor(i/100)]; 
	% tell bmi5 to set these parameters -- synchronization is internal. 
	code = bmi5_mmap(b5);
% 	if(code ~= 0)
% 		disp('unexpected response from bmi5_out pipe'); 
% 	end
% 	disp(['frame ' num2str(b5.frame_o)]); 
% 	disp(['ticks ' num2str(b5.ticks_o)]); 
end
d = toc();
frame_rate = n/d
