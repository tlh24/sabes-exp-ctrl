function status = updateVisBlurObject(H,prop,vals)
%
%  Send in vals as 1xm or Nxm.  N is number of handles, m is the 
%  length of the property value vector.
%
%
%  MF Feb. 26, 2007
%

if size(vals,1) == 1
    for i = 1:numel(H)
        set(H(i),prop,vals);
    end
elseif size(vals,1) == numel(H)
    for i = 1:numel(H)
        set(H(i),prop,vals(i,:));
    end
else
    error('vals 1xm, or Nxm, where N is the number of handles, and m is the length of the prop value vector');
end