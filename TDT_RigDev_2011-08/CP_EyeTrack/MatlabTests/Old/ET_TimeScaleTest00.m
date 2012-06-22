srvname = 'CP_EyeTrack.Application';

hITrack=actxserver(srvname);

[ dCoeff0, dCoeff1 ] = hITrack.GetTimeScale;

hITrack.SetTimeScale( 0, 1);
 
[dC0, dC1]  = hITrack.GetTimeScale;
% delete(hITrack)



