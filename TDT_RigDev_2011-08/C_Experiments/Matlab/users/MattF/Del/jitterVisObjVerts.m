function jitterVisObjVerts(jitter,eyeLoc,hList)
%  function jitterVisObjVerts(jitter,eyeLoc,hList)
%
%  Jitter vis object locations so mimic eye position noise.  Jitter should
%  be a 2-vector in radians.
%
%
%  MF April 19, 2007.
%

for hi = 1:length(hList)

    if get(hList(hi),'show')
        pts = get(hList(hi),'points');

        [th,r] = cart2pol(pts(:,1)-eyeLoc(1),pts(:,2)-eyeLoc(2));
        dx = r.*cos(jitter(1));
        
        dy = eyeLoc(3).*sin(jitter(2))./cos(-jitter(2));
        %dy = r.*sin(jitter(2));

        set(hList(hi),'points',[pts + [dx dy]]);
    end
end