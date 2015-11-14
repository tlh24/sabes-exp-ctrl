clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('delete_all')

bmi5_cmd('make tone');       % no name
bmi5_cmd('make tone beep');  % with name
eval(bmi5_cmd('mmap'))

%% play tone for 1 second
b5.tone_freq = 440;     % hz
b5.tone_pan = 0;        % left/right pan
b5.tone_scale = 1;      % arbitrary units?
b5.tone_duration = 1;   % seconds
b5.tone_play_io = 1;    % automatically set to false when a tone is played

b5 = bmi5_mmap(b5);

pause(2.5);

%% play tone for 2 seconds
b5.beep_freq = 880;     % hz
b5.beep_pan = 0;        % left/right pan
b5.beep_scale = 1;      % arbitrary units?
b5.beep_duration = 2;   % seconds
b5.beep_play_io = 1;    % automatically set to false when a tone is played

b5 = bmi5_mmap(b5);

pause(2.5);

%% play polyphony tones
b5.beep_freq = 660;
b5.beep_duration = 1;
b5.tone_play_io = 1;
b5.beep_play_io = 1;

b5 = bmi5_mmap(b5);

pause(2.5);

%% play blip volume ramp
dt = 0.1;
for i=0.1:0.1:1
    b5.tone_duration = dt;
    b5.tone_scale = i;
    b5.tone_play_io = 1;
    b5 = bmi5_mmap(b5);
    pause(2*dt);
end

%% play blip left-right pan ramp
dt = 0.1;
for i=-1:0.1:1
    b5.tone_duration = dt;
    b5.tone_scale = 1;
    b5.tone_pan = i;
    b5.tone_play_io = 1;
    b5 = bmi5_mmap(b5);
    pause(2*dt);
end

pause

bmi5_cmd('delete_all')