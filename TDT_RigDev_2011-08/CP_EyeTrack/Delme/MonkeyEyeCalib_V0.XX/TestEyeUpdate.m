% TestEyeUpdate.m

EyeOpen;
EyeStart;
fprintf('Pausing for 20 seconds\n');
pause(20);
for i = 1:5;
  EyeUpdate;
  pause(1);
  fprintf('%d\n', i);
end
fprintf('Pausing for 20 seconds\n');
pause(20);
for i = 1:5;
  EyeUpdate;
  pause(1);
  fprintf('%d\n', i);
end
EyeStop;
EyeClose;