clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

target_size = 0.05;       % Size of the target to reach
target_dist = 0.7;      % Maximum distance of target from the pointer
annulus_size = 0.1;      % Maximum distance of the pointer from the target distance
max_trials  = [12 10 15 15 20 20 20 15 5 5]; 
nlines      = 1000;     % number of lines
line_len    = 0.04;        % length of lines
state       = 0;

bmi5_cmd('clear_all');
bmi5_cmd('delete_all');
bmi5_cmd('make square background');
bmi5_cmd('make magnets mag 1000');
bmi5_cmd('make circle target');
bmi5_cmd('make circle state');

%bmi5_cmd('make polhemus finger'); 
bmi5_cmd('make mouse finger'); 

eval(bmi5_cmd('mmap'));
b5 = bmi5_mmap(b5);

b5.affine_m44 = eye(4);
b5.quadratic_m44 = zeros(4);

b5.background_draw = 1;
b5.background_color = [1 1 1 1]; % white
b5.background_pos = [0 0]; 
b5.background_scale = [2 2];

b5.mag_draw = 1;
b5.mag_color = [0 0 0 1]; % white
b5.mag_pos = [0 0]; 
b5.mag_scale = [1 1];
b5.mag_coherence = 1;
b5.mag_compassL = line_len;

b5.target_draw = 1;
b5.target_color = [1 0 0 1]; % red
b5.target_pos = [0 0]; 
b5.target_scale = [target_size target_size];

b5.state_draw = 1;
b5.state_color = [0 1 0 1]; % blue
b5.state_pos = [0 0]; 
b5.state_scale = [0.01 0.01];

b5 = bmi5_mmap(b5);


% Each loop decrease the coherence by 10% 
for step = 0:0.1:1
    coherence = 0.5 - step;
    % for each
    for numberoftrials = 1:max_trials(round(step*10 + 1))
        b5.mag_coherence = 1;
        b5 = bmi5_mmap(b5);
        b5.mag_coherence = coherence;
        b5 = bmi5_mmap(b5);
        
        % set the position of the pointer in the annulus
        x_pos = target_dist - rand(1) * target_dist * 2;
        y_pos = target_dist - rand(1) * target_dist * 2;
        r = sqrt(x_pos^2 + y_pos^2);
        while (r > target_dist) || (r < target_dist - annulus_size)
            x_pos = target_dist - rand(1) * target_dist * 2;
            y_pos = target_dist - rand(1) * target_dist * 2;
            r = sqrt(x_pos^2 + y_pos^2);
        end
        state = [x_pos, y_pos];
        
        trial_done = false;
        inside = false;
        tic;
        t1 = toc;
        
        while t1 < 1
            t1 = toc;
        end
        b5.state_draw   = 1;
        b5.target_draw  = 1;
        b5.mag_draw     = 1;
        b5 = bmi5_mmap(b5);
        tic;
        t2 = 0;
        t3 = 0;
        while ~trial_done
            t1 = toc;
            if(t1 > 7)
                trial_done = true;
            end
            dist = sqrt(state(1).^2 + state(2).^2); 
            if(dist < target_size && ~inside)
                inside = true;
                t2 = toc;
            elseif (dist > target_size)
                inside = false;
                t2 = toc;
            elseif(dist < target_size && inside && t1 - t2 > 0.3)
                trial_done = true;
                success = true;
            end
            
            %tmp = c.pm * [b5.finger_sensors_o(1:3)];
            tmp = b5.finger_sensors_o(1:2);
            state = state + [tmp(1)*(t1 - t3), tmp(2)*(t1 - t3)];
            b5.mag_target = state;
            b5.state_pos = state; 
            b5 = bmi5_mmap(b5);
            t3 = t1;
        end
        b5.state_draw   = 0;
        b5.target_draw  = 0;
        b5.mag_draw     = 0;
        b5 = bmi5_mmap(b5);
        
    end
end
    

% ----
bmi5_cmd('delete_all')
% ----