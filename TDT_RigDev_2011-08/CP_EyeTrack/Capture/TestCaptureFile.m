hf=fopen('IScanTestFile.txt');
ch_vals = fread(hf, inf, 'uchar' );
fclose(hf);
chSync = hex2dec('44');
iSyncChar = find(ch_vals == chSync);

iSyncChIntervals = diff(iSyncChar);

% array index containing first frame char
iSyncFrames = iSyncChar(find(iSyncChIntervals==1));

%% Sanity check
% ii =168;
% ch_vals(iSyncFrames(ii))
% ch_vals(iSyncFrames(ii)+1)

iSyncFramesIntervals = diff(iSyncFrames);
iMaxIntewrval = max(iSyncFramesIntervals)
hist(iSyncFramesIntervals, 1:iMaxIntewrval);


