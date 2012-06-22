% EyeTest 2
% Test Iscan data collection

dt = .05; 
n  = 100;

global eyeStruct
fprintf(1,'EyeOpen...\n')
EyeOpen 

tic;
fprintf(1,'EyeStart...\n')
EyeStart; 
% tic;
tm1=toc;
fprintf(1,'Updating\n')
for i=1:n, 
    fprintf(1,'... %d \n',i)
    pause(dt); 
    [a,b,c] = EyeUpdate;
    fprintf(1,'%d \n',a)
end
tm2=toc;
ctm = tm2-tm1;

tm1=toc;
fprintf(1,'EyeStop...\n')
[t,e,eR,err]=EyeStop;
tm2=toc;
dtm = tm2-tm1;

fprintf(1,'nominal time = %.2f\nclock time = %.2f\ndownload time = %.2f\nerror = %d\n\n',...
    dt*n,ctm,dtm,err) %% eye time = %.2f\n t(end)-t(1)

clf; 
subplot(311); plot(t,e(:,1))
subplot(312); plot(t,e(:,2))
subplot(3,3,7); hold on;
plot(e(:,1),e(:,2),'.'); 
subplot(3,3,8);hist(e(:,1),30); 
subplot(3,3,9);hist(e(:,2),30);

meanH = mean(e(:,1)); stdH = std(e(:,1));
meanV = mean(e(:,2)); stdV = std(e(:,2));

fprintf(1,'Mean H = %.2f +/- %.2f - Mean H = %.2f +/- %.2f \n', meanH,stdH,meanV,stdV)


fprintf(1,'EyeClose...\n')
EyeClose