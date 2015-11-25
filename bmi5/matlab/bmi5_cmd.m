function msg = bmi5_cmd(cmd)
global bmi5_in bmi5_out; 
count = fwrite(bmi5_in, cmd); 
code = fread(bmi5_out, 1, 'int');
msg = char(fread(bmi5_out, code, 'char')');
end