clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('make store int 1 scalar');
eval(bmi5_cmd('mmap'));

for i=1:(100*60*60)
    b5.scalar_v = i; 
    b5 = bmi5_mmap(b5);
    pause(0.01); 
end

bmi5_cmd('save ticks_test.mat')

load('ticks_test.mat');
figure;
plot(time_o, ticks_o); 

figure; 
a = ones(numel(ticks_o), 2);
a(:,1) = time_o; 
x = a \ ticks_o';
pred = a * x;
plot(time_o, ticks_o - pred'); 
title('Tick error vs. time estimated against global linear regression')

% ----
bmi5_cmd('delete_all')
% ----