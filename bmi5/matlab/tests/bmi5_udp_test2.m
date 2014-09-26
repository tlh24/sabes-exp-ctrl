clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');

bmi5_cmd('make tdtudp tdt2 12 tdt_udp_28_3043');

eval(bmi5_cmd('mmap'))


% fields 1-6  are for the first channel of stimulation
% fields 7-12 are for the second
udp{1}  = 0;     % StimEnabled1
udp{2}  = 20;   % StimFreqHz1
udp{3}  = 100;   % StimPWUs1
udp{4}  = 50;    % StimAmpUA1
udp{5}  = 25;    % StimIPIUs1
udp{6}  = 3;     % StimChan1

udp{7}  = 0;     % StimEnabled2
udp{8}  = 20;   % StimFreqHz2
udp{9}  = 100;   % StimPWUs2
udp{10} = 50;    % StimAmpUA2
udp{11} = 25;    % StimIPIUs2
udp{12} = 7;     % StimChan2

% send initial values
for i=1:length(udp)
    b5.tdt2_udp(i) = udp{i};
end
b5 = bmi5_mmap(b5)

%{
b5.tdt2_udp(1) = 1;
b5.tdt2_udp(7) = 1;
b5 = bmi5_mmap(b5)
%pause(10);
%}


b5.tdt2_udp(1) = 1;
b5.tdt2_udp(7) = 1;
b5 = bmi5_mmap(b5)
for i=10:100
    b5.tdt2_udp(2) = i;
    b5.tdt2_udp(8) = i;
    b5 = bmi5_mmap(b5)
    pause(1);
end
%}

%{
b5.tdt2_udp(1) = 0;
b5.tdt2_udp(7) = 0;
b5 = bmi5_mmap(b5)
%}