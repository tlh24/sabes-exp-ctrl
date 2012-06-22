function setMultiVisObjects(H,varargin)
%
%
%
%  MF Jan. 5, 2007
%
%tic
for i = 1:length(H)
    
   set(H(i),varargin{:}); 
    
end
%toc