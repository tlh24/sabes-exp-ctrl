function [screen,world] = bmi5_calibrate()
global m2; 
% first ask for a set of points. 
w = linspace(-0.8, 0.8, 4); 
screen = zeros(16, 4); 
world = zeros(16, 3); 
i=1;
for yi = 1:4
	for xi = 1:4
		x = w(xi); 
		y = w(yi); 
		m2.Data(1).target_trans = [x ; y]; 
		screen(i,1) = x; 
		screen(i,2) = y; 
		bmi5_sync(); 
		pause(1); 
		world(i,:) = m2.Data(1).polhemus_sensors'; 
		i=i+1;
	end
end

q = world\screen;
m2.affine