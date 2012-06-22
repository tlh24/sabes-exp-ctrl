
MeanH2O = 150; SDH2O = MeanH2O/5;
MeanIJI = 60;
RunTime = 3600;

fprintf('\n\n - - - -  Running Stochastic Monkey Sprinkler  - - - - \n');
tic; TotalJ = 0;
while toc < RunTime
  
  IJI = inf;
  while IJI > 3*MeanIJI
  IJI = exprnd(MeanIJI);
  end
  fprintf('Waiting %0.2f secs',IJI);
  pause(IJI);
  Jdur = randn(1).*SDH2O + MeanH2O;
  JuiceStart(Jdur);
  TotalJ = TotalJ + Jdur;
  
  fprintf('  |  Juice: %0.2f secs |  Total Juice Time: %0.2f secs\n',Jdur,TotalJ);
  
end

% 
%     tic
% 
% for i = 1:1000,
%    
%     fprintf(1,'> %d - ',i)
%     if(rand>0.8), 
%         JuiceStart(H2O); 
%         fprintf(1,'H2O = %d\n',H2O)
%         toc
%     end
% 
%     pause(5)
% end