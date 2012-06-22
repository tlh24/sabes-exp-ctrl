%%
%% TestLibertyBuffer
%% compare Liberty buffer catched from matlab code via the Libert software
%% and the pulses of the Liberty Sync Signal seen by the TDT code

hL = actxserver('LibertyServer.Liberty');
invoke(hL,'setup',0,0.015);

TDTdev = actxcontrol('TDevAcc.X',[5 5 26 26]);
invoke(TDTdev,'ConnectServer','cannonball')
invoke(TDTdev,'SetSysMode',0);
 
%% System Settings
%  0 = idle
%  1 = standby 
%  2 = preview 
%  3 = record


BufferTime = 0.1; % sec 
hL.activeSensors=[1 0 0 0];
invoke(TDTdev,'SetSysMode',3);  %record
fprintf(1,'Buffer length in nb of frames - matlab vs TDT \n')
for k = 1:10,
 invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',1);  
 invoke(TDTdev,'SetTargetVal','RP2(1).TrialEnable',0); pause(0.1); % reset counters to zero 
 invoke(hL,'startBuffer'); pause(BufferTime); invoke(hL,'stopBuffer')
 B=invoke(hL,'getBuffer',1);
 pause(0.1);
 LSyn = invoke(TDTdev,'GetTargetVal','RP2(1).LibertySync');
 fprintf(1,'%d - Buffer length = %d   %d\n',k,length(B),LSyn)
end
invoke(TDTdev,'SetSysMode',0);
