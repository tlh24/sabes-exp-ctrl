srvname = 'CP_EyeTrack.Application'

hITrack=actxserver(srvname);
% get(hITrack);
% methods(hITrack);
disp(hITrack.strProgramVersion);


iIdx = int32(0);
iLastIdx = int32(0);
nNew = int32(0);
iCounter =int32(0);

iCounter =1;
while 1
  hF = fopen('CP_EyeTrackLog.txt','at');
  hITrack.ConnectISCAN();
  pause(0.1)
 
  dData = [];
  
  iLastIdx = 0;
  hITrack.ResetDataBuffer;
  tic;
  while( iLastIdx < 100 )
    pause(0.1); % approx. 12 new points per update @120Hz
    iIdx  = hITrack.lngLatestDataIndex;
    nNew = iIdx - iLastIdx;
    if nNew > 0
      dData = hITrack.GetDataBuffer(iLastIdx+1, nNew);
      iLastIdx = iIdx;
      t2 = toc;
      for i=1:size(dData,1) 
        strLog = sprintf('%d\t  %d\t  %.3f\t  %.3f\t  %g\t  %g\t  %g\t  %g\n', ...
                          iCounter, i, t2, dData(i,1)/1000, dData(i,2), dData(i,3), dData(i,4), dData(i,5));
        fprintf(hF, '%s', strLog );
        iCounter = iCounter + 1;
      end         
    end
  end
  fclose(hF);
  hITrack.DisconnectISCAN();
  fprintf('%s', strLog );

end 
delete(hITrack);
fclose(hF);



