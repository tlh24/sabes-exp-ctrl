

nbits = 4;
frac = 3;

ppoff = nbits*frac + nbits -1;
ppon  = ppoff*frac;

cw = ppon*nbits + ppoff*(nbits-1);


if(mod(cw,4)~=0), cw = cw+4-(cw/4); end

fprintf(1,'ppon=%d, ppoff=%d, cw=%.2f\n',ppon,ppoff,cw)