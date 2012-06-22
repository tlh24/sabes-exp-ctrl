srvname = 'CP_EyeTrack.Application';

hEye=actxserver(srvname);

[ dCoeff0, dCoeff1 ] = hEye.GetTimeScale;

hEye.SetTimeScale( 0, 1);
 
[dC0, dC1]  = hEye.GetTimeScale;
% delete(hEye)



