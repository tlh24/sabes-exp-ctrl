global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('tdtudp tdt1 2 tdt_udp_28_3048');      % connect by dns/wins
bmi5_cmd('tdtudp tdt2 32 169.230.191.127');     % connect by ip

eval(bmi5_cmd('mmap structure'))


b5.tdt1_udp(1) = 1;     % juice trigger
b5.tdt1_udp(2) = 300;   % juice time (msec)
bmi5_mmap(b5)
b5.tdt1_udp(1) = 0;
bmi5_mmap(b5)
