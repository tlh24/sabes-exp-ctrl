function saveIntermediateTrialData(savedData)
%
%
%
%

global Params


save(sprintf('%s_TEMP/savedData',Params.FILENAME),'savedData');
