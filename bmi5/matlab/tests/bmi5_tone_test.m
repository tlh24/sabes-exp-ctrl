global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('make tone tone');
eval(bmi5_cmd('mmap structure'));

b5.tone_freq = 440;     % hz
b5.tone_pan = 0;        % left/right pan
b5.tone_scale = 1;      % arbitrary units?
b5.tone_duration = 1;   % seconds
b5.tone_play_io = 1;    % automatically set to false when a tone is played

bmi5_mmap(b5);
