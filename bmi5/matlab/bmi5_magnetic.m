clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make line line');
%bmi5_cmd('make square square'); 
bmi5_cmd('make circle cursor');
eval(bmi5_cmd('mmap'));
b5 = bmi5_mmap(b5);

b5.affine_m44 = eye(4);
b5.quadratic_m44 = zeros(4);

b5.cursor_draw = 1;
b5.cursor_scale = [0.5 0.5];
b5.cursor_color = [1 0 0 1]; % red
b5.cursor_pos = [-0.5 -0.5]; 

b5.line_draw = 1;
b5.line_color = [1 1 1 1]; % red
b5.line_pos = [0 0]; 
b5.line_scale = [1 1];

% b5.square_draw = 1;
% b5.square_scale = [0.1 0.01];
% b5.square_color = [0 0 1 1]; %blue
% b5.square_pos = [0.5 0.5]; 

b5 = bmi5_mmap(b5);

% ----
%bmi5_cmd('delete_all')
% ----