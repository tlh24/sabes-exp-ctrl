function [] = bmi5_calibrate(mouse)
pause(10); 
global b5; 
% reset the affine transform.
b5.affine_m44 = eye(4); 
bmi5_sync(); 
% first ask for a set of points. 
w = linspace(-0.8, 0.8, 4); 
screen = zeros(16, 3); 
world = zeros(16, 3); 
screen(:,3) = 1; 
world(:,3) = 1; 
pm = zeros(3); 
% in tim's desk setup: (will differ in other setups).
if(mouse)
	pm = eye(3);% mouse control.
else
	pm(1,2) = -1; % y -> x
	pm(2,3) = -1; % z -> y
	pm(3,1) = 0; % x -> 0
end
i=1;
for yi = 1:4
	for xi = 1:4
		x = w(xi); 
		y = w(yi); 
		b5.target_trans = [x ; y]; 
		screen(i,1) = x; 
		screen(i,2) = y; 
		bmi5_mmap(b5); 
		pause(2); 
        for h=1:30
            bmi5_mmap(b5); % update sensors.
        end
		p = (pm * b5.polhemus_sensors_o)'; 
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
if(mouse)
	save('calibration_mouse.mat','q','pm'); 
else
	save('calibration.mat','q','pm'); 
end
