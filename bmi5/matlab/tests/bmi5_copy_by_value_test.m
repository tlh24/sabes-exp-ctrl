clear;
global bmi5_out bmi5_in

bmi5_out = fopen('/tmp/bmi5_out.fifo', 'r');
bmi5_in  = fopen('/tmp/bmi5_in.fifo',  'w');
eval(bmi5_cmd('mmap'));

foo(1).time = 0;

fprintf('*** fill structure ***\n');
for i=1:5
	%bmi5_mmap(b5);             % update in-place. old semantics.
    b5 = bmi5_mmap(b5);         % return a new structure. new semantics.
    foo(i).time = b5.time_o;    % save the time
    fprintf('foo(%d).time: %0.2f\n',i,foo(i).time);
    pause(1);
end

fprintf('\n\n');

fprintf('*** print structure ***\n');
for i=1:5
    fprintf('foo(%d).time: %0.2f\n',i,foo(i).time);
end