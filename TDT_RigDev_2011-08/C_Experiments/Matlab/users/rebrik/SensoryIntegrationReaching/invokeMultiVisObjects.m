function invokeMultiVisObjects(H,varargin)
%
%
%
%  MF Jan. 5, 2007
%
%tic
for i = 1:length(H)
    
   invoke(H(i),varargin{:}); 
    
end
%toc