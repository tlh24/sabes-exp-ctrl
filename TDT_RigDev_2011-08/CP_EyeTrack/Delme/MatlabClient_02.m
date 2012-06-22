srvname = 'CP_EyeTrack.Application'

hITrack=actxserver(srvname);
% get(hITrack);
% methods(hITrack);
disp(hITrack.strProgramVersion);

hITrack.ConnectISCAN();
pause(0.1)

iIdx = int32(0);
iLastIdx = int32(0);
nNew = int32(0);

dData = [];

iLastIdx = 0;
hITrack.ResetBuffer;
while( iLastIdx < 400 )
  
  iIdx  = hITrack.lngLatestDataIndex;
  nNew = iIdx - iLastIdx;
  if nNew > 0
    dData = hITrack.GetDataBuffer(iLastIdx+1, nNew);
    fprintf('%d\t%d\t%.1f\t%g\t%g\t%g\t%g\r', ... 
            iIdx, nNew, dData(end,1), dData(end,2), dData(end,3), dData(end,4), dData(end,5) );
    iLastIdx = iIdx;
  end
  pause(0.1);
end
hITrack.DisconnectISCAN();

delete(hITrack)



