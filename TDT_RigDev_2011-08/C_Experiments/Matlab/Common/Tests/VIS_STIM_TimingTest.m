% VIS_STIM_TimingTest
%
% Try sending CP_Display and Stim commands simultaneously
% and check for relative timing
RERUN = 0;


ExperimentGlobalsInclude;
ServerNamesInclude;



if(RERUN),
  
  %% SETUP
  ExperimentStart
  
  hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer);
  hVDisk.SetColor([1 1 1]);
  hVDisk.SetXY([0 100]);
  hVDisk.SetScale(300);
  hVDisk.Hide
  pause(1);
  
  
  
  %% LOOP
  STIM_N   = 200;
  STIM_PER = 0.5; % SEC
  
  TIME=nan(STIM_N,2);
  for i=1:STIM_N,
    % Start Time
    TIME(i,1)= TimeSyncGetTimeMs();
    % Put Up Disk
    hVDisk.Show
    % Call Stim
    g_ExpData.hDev.SetTargetVal(['RZ2_3','.StimTrig'],1);
    g_ExpData.hDev.SetTargetVal(['RZ2_3','.StimTrig'],0);
    % Finish Time
    TIME(i,2)= TimeSyncGetTimeMs();
    pause(0.2)
    % Hide Disk
    hVDisk.Hide
    % Wait
    pause(STIM_PER);
  end
  %% END
  
  save VIS_STIM_TimingTest TIME
  
  ExperimentStop
  
else
  
  
  %% Analysis
  % Load
  load Pixl.csv
  Pixl = 1000*Pixl(:,1);
  load Stim.csv
  Stim = 1000*Stim(:,1);
  
  % FixPix
  for i=1:length(TIME(:,1)),
    [dt idt] = min(abs(TIME(i,1)-Pixl));
    if(abs(dt)<200) PIX(i,1)=Pixl(idt);
    else PIX(i,1)=NaN;
    end
  end
  
  ATIMES = [TIME(:,1) Stim PIX TIME(:,2)];
  STR = {'Time1' 'Stim' 'Pixl' 'Time2'};
  
  figure(1); clf; ct=0;
  clear ADT SDT
  for i=1:4,
    for j=(i+1):4
      %subplot(4,4,i+4*(j-1)); hold on
      ct=ct+1;
      subplot(2,3,ct); hold on
      dT = ATIMES(:,i)-ATIMES(:,j);
      title(sprintf('%s - %s = %f (%f) [%f]',...
        STR{i},STR{j},nanmean(dT),nanstd(dT),max(dT)-min(dT)))
      plot(dT,'marker','o')
      ADT(:,ct)=dT;
      SDT{ct} = [STR{i},'-',STR{j}];
    end
  end
  
  %%
  figure(2); clf; ct=0;
  DTIMES = ATIMES(:,[2:4])-ATIMES(:,1)*[1 1 1];
  
  for i=1:3,
    for j=(i+1):3,
      ct=ct+1;
      subplot(1,3,ct); hold on
      
      d1 = DTIMES(:,i);
      d2 = DTIMES(:,j);
      c = corrcoef(d1,d2); c=c(1,2);
      
      title(sprintf('%s vs %s:  r = %f',...
        STR{j+1},STR{i+1},c))
      xlabel(STR{i+1});
      ylabel(STR{j+1});
      plot(d1,d2,'o')
      lim=[min([d1]) max([d1])];
      plot(lim,lim,'k:')
    end
  end
  
  % The wind up appears to be that everything is pretty fast, except that there is a variable delay in calling/returning from a DCOM call -- it's either fast or about 20 msec
  
end
