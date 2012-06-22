function [IDX,varargout] = nearest(list, tgt, varargin)
%  function [idx,varargout] = nearest(list, tgt, varargin)
%
%  Finds the element in 'list' nearest to 'tgt'.  Returns the index value.  Will also return the value of the element.
%
%  An optional argument can be used to specify whether to find the nearest value to 'tgt' (DEFAULT),
%  the nearest value less than or equal to 'tgt',  (use '<')
%  or the nearest value greater than or equal to 'tgt'.  (use '>'). 
%
%  Uses the ascii values for string inputs.
%
%  MF Sept. 30, 2002
%

if nargin < 2, error([mfilename ': need at least 2 input args.']); end

if ~isnumeric(tgt), tgt = str2double(tgt(:)); end
if ~isnumeric(list), list = str2double(list(:)); end
tgt = tgt(:);

IDX = zeros(length(tgt),1); VAL = IDX+nan;
for i = 1:length(tgt)
    
    dist = tgt(i) - list;
    
    if nargin == 2
        idx = find(abs(dist) == min(abs(dist)));
        val = list(idx);
    elseif isequal(varargin{1}, '>')
        if all(dist > 0)
            idx = -1;
            val = nan;
        else
            idx = find(dist == max(dist(find(dist<=0))));
            val = list(idx);
        end
    elseif isequal(varargin{1}, '<')
        if all(dist < 0)
            idx = -1; 
            val = nan;
        else
            idx = find(dist == min(dist(find(dist>=0))));
            val = list(idx);
        end
    else
        error([mfilename ': unknown option']);
    end
    
    IDX(i) = idx(1);
    VAL(i) = val(1);
    
end

if nargout == 2
    varargout{1} = VAL;
end

return