global bmi5_in bmi5_out;

cd('/home/motorlab/sw/sabes-exp-ctrl/bmi5/matlab');
bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

bmi5_cmd('make labjack isometric 5'); 
eval(bmi5_cmd('mmap'));

n = 8000; 
v = zeros(5, n); 
for i = 1:n
    b5 = bmi5_mmap(b5); 
    v(:, i) = b5.isometric_sensors_o; 
end

plot(v'); 