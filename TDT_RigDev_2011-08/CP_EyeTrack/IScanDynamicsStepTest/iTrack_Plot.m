strDir = '';
strFile1 = 'iTrack_00.F32';
strFile2 = 'iTrack_01.F32';

strPath = [strDir strFile1]
hf=fopen(strPath);
ch_vals1 = fread(hf, inf, 'float32' );
fclose(hf);

strPath = [strDir strFile2]
hf=fopen(strPath);
ch_vals2 = fread(hf, inf, 'float32' );
fclose(hf);
len = length(ch_vals1)
len2 = length(ch_vals2)

if len2~=len 
  error('File lengths do not match!');
end

x=(1:len)/6.103;

figure
plot( x, ch_vals2, 'r')
hold on;
plot( x, ch_vals1, 'b')

xlabel('msec')

% ch_diff = ch_vals1(x) - ch_vals2(x);
% % hist(ch_diff);
% plot(ch_diff);
% 
% ch_vals1(1:10)
% ch_vals2(1:10)