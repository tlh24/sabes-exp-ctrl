global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('tdtudp tdt1 2 tdt_udp_28_3048');      % connect by dns/wins
bmi5_cmd('tdtudp tdt2 32 169.230.191.127');     % connect by ip

eval(bmi5_cmd('mmap structure'))

bmi5_mmap(b5)
