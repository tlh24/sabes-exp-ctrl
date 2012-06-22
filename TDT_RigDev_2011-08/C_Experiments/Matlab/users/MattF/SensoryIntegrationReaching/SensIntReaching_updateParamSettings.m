function SensIntReaching_updateParamSettings(pstruct, trial)
%
%
%
%
%  MF May 30, 2008.
%

global Params Data

if ~isfield(pstruct,'Settings')
    error('%s: No ''Settings'' field found',mfilename);
end

pcell = pstruct.Settings;
for i = 1:length(pcell)
    if ~ischar(pcell{i})
        error('Settings entries must be evaluatable strings');
    end
    try
       eval(pcell{i}); 
    catch
        fprintf('\n\n\n- - - %s - - -\n\tCouldn''t evaluate the following:\n\n\t"%s".\n\nSkipping.\n\n',mfilename,pcell{i});        
    end    
end

return