

% strFileName = 'D:\DataTmp\RecTime03\RecTime001.nev';
% strFileName = 'D:\DataTmp\RecTime00\RecTime001.nev';
strFileName = 'D:\DataTmp\E071031_M1001.nev'

[dRP2_SyncUpTS dRP2_SyncDwnTS ...
dRecOnTS dRecOffTS ...
dPauseOnTS dPauseOffTS ...
dRecSyncTS ]  =  NevGetParsedDigInEvents( strFileName );
