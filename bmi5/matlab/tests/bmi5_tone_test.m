clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('make tone');       % no name
bmi5_cmd('make tone beep');  % with name
eval(bmi5_cmd('mmap'))

b5.tone_freq = 440;     % hz
b5.tone_pan = 0;        % left/right pan
b5.tone_scale = 1;      % arbitrary units?
b5.tone_duration = 1;   % seconds
b5.tone_play_io = 1;    % automatically set to false when a tone is played

b5 = bmi5_mmap(b5);

pause(1.5);


b5.beep_freq = 880;     % hz
b5.beep_pan = 0;        % left/right pan
b5.beep_scale = 1;      % arbitrary units?
b5.beep_duration = 2; % seconds
b5.beep_play_io = 1;    % automatically set to false when a tone is played

b5 = bmi5_mmap(b5);

pause(1.5);

% polyphony
b5.beep_freq = 660;
b5.tone_play_io = 1;
b5.beep_play_io = 1;

b5 = bmi5_mmap(b5);

bmi5_cmd('delete_all')