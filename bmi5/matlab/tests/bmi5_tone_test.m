global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('make tone tone');
eval(bmi5_cmd('mmap structure'));

b5.tone_freq_io = 440; 
b5.tone_pan = 0;
b5.tone_scale = 1;
b5.tone_duration = 1;

bmi5_mmap(b5);
