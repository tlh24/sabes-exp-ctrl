
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% INBOX %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function in = INBOX(pos,boxpos,win)

if (length(win) == 1),
    in = sqrt( (pos(:,1)-boxpos(1)).^2 + (pos(:,2)-boxpos(2)).^2 ) < win;
else
    in = abs(pos(:,1)-boxpos(:,1)) < win(1) & abs(pos(:,2)-boxpos(:,2)) < win(2);
end


