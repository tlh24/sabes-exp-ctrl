clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
bmi5_cmd('make tdtudp tdt1 2 tdt_udp_28_3048');      % connect by dns/wins
bmi5_cmd('make tdtudp tdt2 14 169.230.191.127');     % connect by ip

eval(bmi5_cmd('mmap'))

b5.tdt1_udp(1) = 1;     % juice trigger
b5.tdt1_udp(2) = 500;   % juice time (msec)
bmi5_mmap(b5)
b5.tdt1_udp(1) = 0;
bmi5_mmap(b5)

% fields 1-8 are boring scalar stim values
% fields 9-14 each hold 16 bits of the 96-bit stimchan vector
udp{1} = 0;     % StimGo
udp{2} = 0;     % StimAbort
udp{3} = 100;   % StimFreqHz
udp{4} = 100;   % StimPWUs
udp{5} = 0;     % StimAmpUA
udp{6} = 25;    % StimIPIUs
udp{7} = 0;     % StimNumPulses
udp{8} = 1;     % StimMonBank

stimchans = false(1,96);
stimchans(5)  = 1;
stimchans(17) = 1;
stimchans(43) = 1;
stimchans(80) = 1;
stimchans(92:95) = 1;

% pack
tmp     = char(stimchans+48); % char-48 is \0
udp{9}  = bin2dec(tmp(1:16));
udp{10} = bin2dec(tmp(17:32));
udp{11} = bin2dec(tmp(33:48));
udp{12} = bin2dec(tmp(49:64));
udp{13} = bin2dec(tmp(65:80));
udp{14} = bin2dec(tmp(81:96));

for i=1:length(udp),
    b5.tdt2_udp(i) = udp{i};
end
bmi5_mmap(b5)

udp{1} = 1;
for i=1:length(udp),
    b5.tdt2_udp(i) = udp{i};
end
bmi5_mmap(b5)

udp{1} = 0;
for i=1:length(udp),
    b5.tdt2_udp(i) = udp{i};
end
bmi5_mmap(b5)