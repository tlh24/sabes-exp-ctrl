clear;
global bmi5_out bmi5_in b5

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('make stars');
bmi5_cmd('make stars dots'); % give a name
bmi5_cmd('make stars asters 100');

eval(bmi5_cmd('mmap'));

b5.affine_m44 = eye(4); 
b5.quadratic_m44 = zeros(4);

b5.stars_scale  = [0.2 0.2];
b5.dots_scale   = [0.2 0.2];
b5.asters_scale = [0.2 0.2];

b5.stars_pos    = [-0.5 -0.5];
b5.dots_pos     = [+0.5 +0.5];
b5.asters_pos   = [+0.5  0.0];

b5.stars_vel    = [1 1];
b5.dots_vel     = [0.2 -0.2];
b5.asters_vel   = [-0.1 sqrt(7)];

b5.stars_coherence  = 0.5;
b5.dots_coherence   = 0.75;
b5.asters_coherence = 0.95;

b5.stars_color = [1 1 1 1]; % white 
b5.dots_color = [0 1 1 1]; % cyan
b5.asters_color = [1 0.2 0.8 1]; % redish-magenta.

b5.stars_draw  = 1;
b5.dots_draw   = 1;
b5.asters_draw = 1;

bmi5_mmap(b5);

