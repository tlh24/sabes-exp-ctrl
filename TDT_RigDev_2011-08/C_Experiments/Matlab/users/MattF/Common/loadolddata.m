%  loadolddata.m

dir
pwd

loadN =(input('load DATA_1:DATA_? : '));

if ~isempty(loadN) & loadN > 0
 clear savedData;%% = struct([]);

  for i = 1:loadN
    load(sprintf('DATA_%i.mat',i));
    eval(sprintf('savedData(%i) = DATA_%i;',i,i));
  end

  save('savedData', 'savedData');

end