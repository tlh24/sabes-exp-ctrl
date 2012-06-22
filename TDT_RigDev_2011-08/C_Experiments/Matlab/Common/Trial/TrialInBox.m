function in = TrialInBox(pos,boxpos,win)
%
%  This used to be called INBOX
%
%
pos = pos';
boxpos = boxpos';

if (length(win) == 1),
    in = sqrt( (pos(1,:)-boxpos(1)).^2 + (pos(2,:)-boxpos(2)).^2 ) < win;
else
    in = abs(pos(1,:)-boxpos(1,:)) < win(1) & abs(pos(2,:)-boxpos(2,:)) < win(2);
end


