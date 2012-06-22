%  TimsArrows.m

ARROW_CORNER = Params.ARROW_CENTER - Params.ARROW_SPACE*[Params.NARROWX-1...
           Params.NARROWY-1]/2 + 2*(.5-rand(1,2)) .* ...
   Params.ARROW_RANDBOX;

for i=1:Params.NARROWX,
   for j=1:Params.NARROWY;
       hArrows{(i-1)*Params.NARROWY + j}.show  = 0;
       hArrows{(i-1)*Params.NARROWY + j}.pos   = ARROW_CORNER + ...
       Params.ARROW_SPACE*[i-1, j-1];
       hArrows{(i-1)*Params.NARROWY + j}.fill  = 1;
   end
end
