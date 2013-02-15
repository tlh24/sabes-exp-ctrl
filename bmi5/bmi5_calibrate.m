function [] = bmi5_calibrate(mouse)
global bmi5_in bmi5_out b5;

cd('/home/joeyo/sw/sabes-exp-ctrl/bmi5');

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

b5 = [];

num_targets = 9;

for j=1:num_targets
 bmi5_cmd(strcat('make circle target',num2str(j)));
end
bmi5_cmd('make tone tone');
bmi5_cmd('make circle cursor');

eval(bmi5_cmd('mmap structure'));

% first ask for a set of points. 
w = linspace(-0.8, 0.8, 4); 
screen = zeros(num_targets, 4); 
world = zeros(num_targets, 4); 
screen(:,4) = 1; 
world(:,4) = 1; 
pm = zeros(3); 
% in tim's desk setup: (will differ in other setups).
if(mouse)
	pm = eye(3);% mouse control.
else
	%pm(1,2) = -1; % y -> x
	%pm(2,3) = -1; % z -> y
	%pm(3,1) = 0; % x -> 0
    
    %pm = [   0   0  +1
    %        -1   0   0   
    %         0  -1   0  ];
         
    pm = [   0  -1   0
             0   0  -1   
            +1   0   0  ];
         
end

snt = sqrt(num_targets); 
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

b5.cursor_scale = [0.1; 0.1]; 
b5.cursor_color = [1; 1; 1; 1]; 
b5.cursor_pos   = [0; 0];
b5.cursor_draw  = 0;

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4); 

bmi5_mmap(b5);

b5.tone_freq_io = 440; 
b5.tone_pan = 0;
b5.tone_scale = 1;
b5.tone_duration = 0.25;

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
        b5.tone_freq_io = 440;
		bmi5_mmap(b5); 
		pause(2);
        b5.tone_freq = 0; % need to add a 'play' flag.
        bmi5_mmap(b5); % update sensors.
		p = (pm * b5.polhemus_sensors_o)'; 
		world(i,1:3) = p(1:3);
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

% turn off all targets
for j=1:num_targets
    s = strcat('target',num2str(j),'_');
    b5.(strcat(s,'draw')) = 0;
end
bmi5_mmap(b5);

% set up affine matrix
qp = q'; 
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 3); 
b5.affine_m44 = q2; 
b5.cursor_draw = 1;
bmi5_mmap(b5); 

while(1)
	p = pm * b5.polhemus_sensors_o;
	b5.cursor_pos = p(1:2); 
	bmi5_mmap(b5); 
end

end

