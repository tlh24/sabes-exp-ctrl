clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('make text');
bmi5_cmd('make text words 256'); % give a name
bmi5_cmd('make text string 32');

eval(bmi5_cmd('mmap'));

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4);

b5.text_v = [double('test') zeros(1,252)]';
b5.text_color = [1 1 1 1];

b5.words_v   = [double('hello world') zeros(1,256-11)]';
b5.words_color = [1 0 0 1];
b5.words_pos   = [0.5 0.5]; 

b5.string_v   = [double('hi') zeros(1,30)]'; %length 32 -- see above. 
b5.string_color = [0 1 0 1];
b5.string_pos   = [-0.5 -0.5]; 

b5 = bmi5_mmap(b5);

% test 'draw' toggle. 
pause(1);

b5.text_draw = 0; 
b5 = bmi5_mmap(b5);
pause(1);

b5.words_draw = 0; 
b5.text_draw = 1; 
b5 = bmi5_mmap(b5);
pause(1);

b5.string_draw = 0; 
b5.words_draw = 1; 
b5 = bmi5_mmap(b5);
pause(1);