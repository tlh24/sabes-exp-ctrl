strFileName = 'IScanTestFile.txt';

chSync = hex2dec('44');

wSync = chSync + chSync * 256;

x1 = 500;
x2 = 4500;
y1 = 200;
y2 = 2200;

n1 = 400;
n2 = 500;
n3 = 450;
n4 = 600;

% vals = ones(3, n1+n2+n3+n4);
vals = [];

s = 1;
e = n1;
vals (2, s:e) = ones (1, n1) * x1;
vals (3, s:e) = ones (1, n1) * y1;

s = n1 + 1;
e = n1 + n2;
vals (2, s:e) = ones (1, n2) * x1;
vals (3, s:e) = ones (1, n2) * y2;

s = n1 + n2 + 1;
e = n1 + n2 + n3;
vals (2, s:e) = ones (1, n3) * x2;
vals (3, s:e) = ones (1, n3) * y1;

s = n1 + n2 + n3 + 1;
e = n1 + n2 + n3 + n4;
vals (2, s:e) = ones (1, n4) * x2;
vals (3, s:e) = ones (1, n4) * y2;


vals(1, :) = ones(1, n1+n2+n3+n4) * wSync;


wVals = int16(vals);
hf=fopen( strFileName, 'wb' );
fwrite(hf, vals, 'int16' );
fclose(hf);
 


