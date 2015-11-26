clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make square');
bmi5_cmd('make circle');
bmi5_cmd('make magnets mag 1000');

eval(bmi5_cmd('mmap'));

%b5.affine_m44 = eye(4);
%b5.quadratic_m44 = zeros(4);


c = load('calibration_polhemus.mat'); 
qp = c.q';
q2 = eye(4); 
q2(1:2, 1:2) = qp(1:2, 1:2); 
q2(1:2, 4) = qp(1:2, 4); 
b5.affine_m44 = q2;
%}

ctr = [0 50];

b5.square_draw = 1;
b5.square_scale = [250 250];
b5.square_color = [0 0 1 0.2]; %blue
b5.square_pos = ctr;

b5.circle_draw = 1;
b5.circle_scale = [5 5];
b5.circle_color = [1 0 0 0.75]; % red
b5.circle_pos = [10 0] + ctr;

b5.mag_draw = 1;
b5.mag_color = [1 1 1 1]; % white
b5.mag_pos = [0 50]; 
b5.mag_scale = [250 250];
b5.mag_coherence = 0.6;
b5.mag_compassL = 5;
b5.mag_target = [10 0] + ctr;

b5 = bmi5_mmap(b5);

%% test with an animation
Ax = 50;
fx = 3/8;
Ay = 50;
fy = 4/8;
phi = 0;
t0 = b5.time_o;
t = t0;
while ((t-t0) < 10) 
    t = b5.time_o;
    x = Ax * sin(2*pi*fx*t+phi) + ctr(1);
    y = Ay * sin(2*pi*fy*t+phi) + ctr(2);
    b5.mag_target = [x y];
    b5.circle_pos = [x y];
    b5 = bmi5_mmap(b5);
end

% ----
%bmi5_cmd('delete_all')
% ----

% b5 = bmi5_mmap(b5); % nb if you call mmap after delete, you get a crash!

