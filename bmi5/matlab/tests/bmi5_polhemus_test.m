global bmi5_in bmi5_out;

cd('/home/motorlab/sabes-exp-ctrl/bmi5/matlab');
bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r'); 
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w'); 

bmi5_cmd('make polhemus finger'); 
eval(bmi5_cmd('mmap'));

n = 8000; 
p = zeros(3, n); 
v = p; 
for i = 1:n
    b5 = bmi5_mmap(b5); 
    p(:, i) = b5.finger_sensors_o; 
    v(:, i) = b5.finger_sensorvel_o; 
end