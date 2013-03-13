% function [] = bmi5_calibrate(type)
% function [] = bmi5_calibrate(type)
% type = 1 -> mouse control. 
% type = 2 -> optotrak (downstairs)
% anything else -> polhemus. 
global bmi5_in bmi5_out b5;

if(type == 2)
	cd('/home/tlh24/sabes-exp-ctrl/bmi5/matlab');
else
	cd('/home/joeyo/sw/sabes-exp-ctrl/bmi5/matlab');
end

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

num_targets = 16;
snt = sqrt(num_targets);

for j=1:num_targets
 bmi5_cmd(strcat('make circle target',num2str(j)));
end
bmi5_cmd('make tone tone');
bmi5_cmd('make circle cursor');

if(type == 1)
	bmi5_cmd('make mouse finger');
elseif(type == 2)
    bmi5_cmd('make optotrak finger 3'); %three sensors.
else
	bmi5_cmd('make polhemus finger'); 
end

% visibility rectangle. 
bmi5_cmd('make square opto_visible');

eval(bmi5_cmd('mmap'));

% first ask for a set of points. 
w = linspace(-0.6, 0.6, snt);

screen = zeros(num_targets, 4); 
world = zeros(num_targets, 4); 
screen(:,4) = 1; 
world(:,4) = 1; 
pm = zeros(3); 

if(type == 1)
	pm = eye(3);% mouse control.
elseif(type == 2)
	% this matrix was arrived at by moving an optotrak emitter 
	% randomly in the experimental plane, 
	% then taking the PCA.  
	pm = zeros(3); 
	pm(1,:) = [1 0 1] * -0.5390; % positive to right.
	pm(2,:) = [-1 0 1] * 3.4396; % positive forward. 
	pm(3,:) = [0 -1 0]; % positive up (uncalibrated)
else 
    % In addition to permuting from the native polhemus
    % axes to a more reasonable set of axes, this matrix
    % handles the conversion to mm from cm (polhemus native units)
    pm = [    0  -10    0
              0    0  -10  
            +10    0    0  ];
end

i=1; 
for yi = 1:snt
    for xi = 1:snt
		x = w(xi); 
		y = w(yi);
        s = strcat('target',num2str(i),'_');
        b5.(strcat(s,'scale')) = [0.1 ; 0.1];
        b5.(strcat(s,'color')) = [0; 1; 0; 1];
        b5.(strcat(s,'pos')) = [x ; y];
        b5.(strcat(s,'draw'))  = 1;
        i=i+1;
    end
end

b5.cursor_scale = [5; 5]; % in mm
b5.cursor_color = [1; 1; 1; 1]; 
b5.cursor_pos   = [0; 0];
b5.cursor_draw  = 0;

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4); 

b5 = bmi5_mmap(b5);

b5.tone_freq = 440; 
b5.tone_pan = 0;
b5.tone_scale = 1;
b5.tone_duration = 0.25;

b5.opto_visible_scale = [1.8 1.8]; 
b5.opto_visible_color = [1 0 0 0.3];
b5.opto_visible_draw = 0; 

pause(10);

i=1;
for yi = 1:snt
	for xi = 1:snt
        for j=1:num_targets
            s = strcat('target',num2str(j),'_');
            b5.(strcat(s,'color')) = [0 1 0 1]; % green
        end
		screen(i,1) = w(xi); 
		screen(i,2) = w(yi);
        s = strcat('target',num2str(i),'_');
        b5.(strcat(s,'color')) = [1 0 0 1]; % red
        b5.tone_play_io = 1;
		b5 = bmi5_mmap(b5); 
		time_start = b5.time_o; 
		while(b5.time_o - time_start < 2.5 || b5.opto_visible_draw == 1)
			b5 = bmi5_mmap(b5); 
			% update visibility.
			if(sum(abs(b5.finger_sensors_o(1:3))) > 1e6)
				b5.opto_visible_draw = 1; 
			else
				b5.opto_visible_draw = 0; 
			end
		end
		b5 = bmi5_mmap(b5); 
        if(type == 1)
            p = (pm * [b5.finger_o;0])'; 
		elseif(type == 2)
			p = (pm * [b5.finger_sensors_o(1:3)])'; 
		else
            p = (pm * [b5.finger_sensors_o])'; 
		end
		world(i,1:3) = p(1:3);
		i=i+1;
	end
end

world2 = world; 
world2(:,3) = 0; 
q = world2\screen; % screen = world * q (q will be transposed from opengl)

hold off
plot(screen(:,1), screen(:,2), 'bo'); 
hold on
pred = world * q; 
plot(pred(:,1), pred(:,2), 'ro'); 
if(type == 1)
	save('calibration_mouse.mat','q','pm'); 
elseif(type == 2)
	save('calibration_opto.mat','q','pm'); 
else
	save('calibration.mat','q','pm'); 
end

% turn off all targets
for j=1:num_targets
    s = strcat('target',num2str(j),'_');
    b5.(strcat(s,'draw')) = 0;
end
b5 = bmi5_mmap(b5);

% set up affine matrix
qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2; 
b5.cursor_draw = 1;
b5 = bmi5_mmap(b5); 

while(1)
	p = pm * [b5.finger_sensors_o(1:3)];
	b5.cursor_pos = p(1:2); 
	b5 = bmi5_mmap(b5); 
end

%end
b5.opto_visible_draw = 1;
b5 = bmi5_mmap(b5); 
pause(4); 
b5.opto_visible_draw = 0;
b5 = bmi5_mmap(b5); 
n = 600; 
data = zeros(3,n); 
for(i=1:n)
	b5 = bmi5_mmap(b5); 
	data(:,i) = b5.finger_sensors_o(1:3);
	pause(0.1); 
end
b5.opto_visible_draw = 1;
b5 = bmi5_mmap(b5); 
