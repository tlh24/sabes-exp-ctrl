function [screen,world] = bmi5_calibrate()
global m2; 
% reset the affine transform.
m2.Data(1).affine_m44 = eye(4); 
bmi5_sync(); 
% first ask for a set of points. 
w = linspace(-0.8, 0.8, 4); 
screen = zeros(16, 3); 
world = zeros(16, 3); 
screen(:,3) = 1; 
world(:,3) = 1; 
pm = zeros(3); 
% in tim's desk setup: (will differ in other setups).
pm(1,3) = 1; % z -> x
pm(2,2) = 1; % y -> y
pm(3,1) = 0; % x -> 0
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
		bmi5_sync(); % update sensors.
		p = (pm * m2.Data(1).polhemus_sensors)'; 
		world(i,1:2) = p(1:2);
		i=i+1;
	end
end

q = world\screen; % screen = world * q (transposed from opengl)

hold off
plot(screen(:,1), screen(:,2), 'bo'); 
hold on
pred = world * q; 
plot(pred(:,1), pred(:,2), 'ro'); 

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