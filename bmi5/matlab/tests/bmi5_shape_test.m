clear;

global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('delete_all')

bmi5_cmd('make circle cursor');
bmi5_cmd('make ring ring 0.5');
bmi5_cmd('make square square'); 
bmi5_cmd('make open_square os 0.5'); 
eval(bmi5_cmd('mmap'));

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4);

b5.cursor_draw = 1;
b5.cursor_scale = [0.5 0.5];
b5.cursor_color = [1 0 0 1]; % red
b5.cursor_pos = [-0.5 -0.5]; 

b5 = bmi5_mmap(b5);

pause;

b5.ring_draw = 1;
b5.ring_scale = [0.5 0.5];
b5.ring_color = [0 1 0 1]; %green
b5.ring_pos = [0.5 -0.5]; 

b5.square_draw = 1;
b5.square_scale = [0.5 0.5];
b5.square_color = [0 0 1 1]; %blue
b5.square_pos = [0.5 0.5]; 

b5.os_draw = 1;
b5.os_scale = [0.5 0.5];
b5.os_color = [1 1 0 1]; %yellow
b5.os_pos = [-0.5 0.5]; 

b5 = bmi5_mmap(b5);

pause;

% these should only be on the experiment display (1)
% put on both displays. 
b5.cursor_draw = 3; 
b5.ring_draw = 3; 
b5.square_draw = 3; 

b5.os_draw = 3; 

b5 = bmi5_mmap(b5);

pause;

% and now only on the experimenter display. 
b5.cursor_draw = 2; 
b5.ring_draw = 2; 
b5.square_draw = 2; 
b5.os_draw = 2; 

b5 = bmi5_mmap(b5);

pause;

% ----
bmi5_cmd('delete_all')
% ----

%bmi5_cmd('make polhemus finger')
%bmi5_cmd('make optotrak finger 3')
bmi5_cmd('make mouse finger')
bmi5_cmd('make circle cursor');
bmi5_cmd('make ring ring 0.5');
eval(bmi5_cmd('mmap'));
b5 = bmi5_mmap(b5);

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4);

b5.cursor_draw = 3;
b5.cursor_scale = [0.5 0.5];
b5.cursor_color = [1 0 0 1]; % red
b5.cursor_pos = [-0.5 -0.5]; 

b5.ring_draw = 3;
b5.ring_scale = [0.5 0.5];
b5.ring_color = [0 1 0 1]; %green
b5.ring_pos = [0.5 -0.5]; 

b5 = bmi5_mmap(b5);

while(1)
    b5.cursor_pos = b5.finger_sensors_o(1:2); 
    b5 = bmi5_mmap(b5);
end