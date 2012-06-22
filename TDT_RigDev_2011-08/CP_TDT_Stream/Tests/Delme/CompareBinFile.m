strDir = 'D:\tmp\TDT_Tanks\';
% strFile1 = 'Test_20060414_Block-21.i16';
% strFile2 = 'Test_20060414_Block-21_raw.bin';

% strFile1 = 'Abe_DT1_061206_Block-1_raw.bin';
% strFile2 = 'Abe_DT1_061206_Block-1.i16';
strFile1 = 'Abe_DT1_061206_Block-4_raw.bin';
strFile2 = 'Abe_DT1_061206_Block-4.i16';
% strFile1 = 'Abe_DT1_061206_Block-7_raw.bin';
% strFile2 = 'Abe_DT1_061206_Block-7.i16';
% strFile1 = '';
% strFile2 = '';

strPath = [strDir strFile1]
hf=fopen(strPath);
ch_vals1 = fread(hf, inf, 'int16' );
fclose(hf);

strPath = [strDir strFile2]
hf=fopen(strPath);
ch_vals2 = fread(hf, inf, 'int16' );
fclose(hf);
len1 = length(ch_vals1)
len2 = length(ch_vals2)
len = min( len1, len2)
len = min( len, 10000000)
%len = 2000
ch_vals1 = ch_vals1( 2:len);
ch_vals2 = ch_vals2(1:len-1);

ch_diff = ch_vals1 - ch_vals2;
%plot(ch_diff(1:1000));
figure;

non0diff = find(ch_diff~=0);
hist(ch_diff(non0diff));

ch_vals1(1:10)
ch_vals2(1:10)