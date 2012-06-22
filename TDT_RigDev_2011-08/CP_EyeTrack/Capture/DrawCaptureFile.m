hf=fopen('ISCAN_00.TXT');
vals = fread(hf, inf, 'uint16' );
fclose(hf);

columns = reshape(vals, 3, length(vals)/3);
x = columns(2,:);
y = columns(3,:);
min(x(find(x>0)))
max(x)
min(y(find(y>0)))
max(y)
figure
plot(x,y, '.');
figure
plot(x, '.');
figure
plot(y, '.');
