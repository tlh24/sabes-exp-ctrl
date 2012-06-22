 % EyeCalibration 
 
 %% DEP VARIABLES - Table Coordinates
 NX = 8;
 NY = 3;
 N  = 0;
 
 GridX = [-97.5 -68.93 -40.36 -11.79 16.79 45.36 73.93 102.5];
 GridY = [-13.6 21.4 56.4];
 
 for i = 1:NY,
     for j = 1:NX,
         N = N + 1;
         Grid(N,:) = [GridX(j), GridY(i)];
     end
 end
 
 

 %% INDEP VARIABLES - Iscan Coords
 EyeH =[ 356 345 341 312 303 286 275 260 ...
         357 351 344 312 301 291 278 272 ...
         362 351 343 312 301 293 282 273 ];

 EyeV =[ 161 162 163 160 161 158 159 157 ...
         158 159 159 157 156 156 155 154 ...
         158 156 155 156 152 151 151 150 ];

 EyeH =[ 356 351 343 312 301 291 278 270 ...
         356 351 343 312 301 291 278 270 ...
         356 351 343 312 301 291 278 270 ];

 EyeV =[ 160 160 160 160 160 160 160 160 ...
         156 156 156 156 156 156 156 156 ...
         151 151 151 151 151 151 151 151 ];

 EY = [EyeH ; EyeV]';
 
 meanEY = mean(EY);
 stdEY  = std(EY);
 Npts    = size(EY,1);

 nEY = [ (EY(:,1)-meanEY(1))./stdEY(1)  (EY(:,2)-meanEY(2))./stdEY(2)];
 DAT = [ones(Npts,1), nEY, nEY(:,1).^2, nEY(:,1).*nEY(:,2), nEY(:,2).^2];         

 regCoef = (DAT'*DAT)\(DAT'*Grid);     %%  get regression coeffiecients 
 dist    = Grid - DAT*regCoef;         %%  model fit
 calibEY = DAT*regCoef;              %%  calibrated data   
 RMSEcal = sqrt(mean( sum(dist.^2,2) )); %% Root Mean Cartesian Distance Error

  % plot results
  plot(Grid(:,1),Grid(:,2),'o'); hold on;
  plot(calibEY(:,1),calibEY(:,2),'r*'); hold off; 
  axis ([-120 125 -35 80]);
  
  