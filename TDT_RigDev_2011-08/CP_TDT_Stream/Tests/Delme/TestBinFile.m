strDir = 'D:\tmp\TDT_Tanks\';
strFile = 'Test_20060414_Block-19.i16';
% strFile = 'Test_20060414_Block-15_raw.bin';

strPath = [strDir strFile]
hf=fopen(strPath);
ch_vals = fread(hf, inf, 'int16' );
fclose(hf);

chDiff = diff(ch_vals);

idx = find((chDiff ~= 1) & (chDiff ~= -65535));

length(idx)
