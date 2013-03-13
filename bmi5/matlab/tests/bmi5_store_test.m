clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('make store int 1 scalar');
bmi5_cmd('make store int 2 vector');
eval(bmi5_cmd('mmap'));

b5.scalar_v = 1;
b5 = bmi5_mmap(b5);
b5.scalar_v = 200;
b5 = bmi5_mmap(b5);
b5.vector_v = [5 5];
b5 = bmi5_mmap(b5);
b5.vector_v = [6 9];
b5 = bmi5_mmap(b5);

% DOES THIS CORRUPT DATA?
%b5.vector = [1 2 3 4 5];
%b5 = bmi5_mmap(b5);

bmi5_cmd('save test.mat')

% ----
bmi5_cmd('delete_all')
% ----
