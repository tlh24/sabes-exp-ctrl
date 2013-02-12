timing = dlmread('timing.txt', ' ', 0,0);

a = timing(:,1);
a(:,2) = 1;
b = timing(:,2);
w = a\b
bp = a*w;
w(1);
% plot(b-bp)

res = b-bp;
plot(x,histc(res, x), 'r')
hold on