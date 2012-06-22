% 
%--- Update Time coefficients
function ExperimentTimingUpdate( )

ExperimentGlobalsInclude;
DaqConfigInclude;

FrameMismatchMax = 5;
hVMain = g_ExpData.hVMain;
hTracker = g_ExpData.hTracker;
hEyeTrack = g_ExpData.hEyeTrack;

%--- Display
% TODO: append new vals to the global var
[dFrameCnt dFrameTimeMs ] = DisplayGetTiming( );
dSrvFrameCnt = hVMain.GetFrameCount();
if abs(dSrvFrameCnt - dFrameCnt) > FrameMismatchMax
  warning('Mismatch in frame count for the Display! RP2: %d,  Display: %d, Diff: %d', ...
                                                        dFrameCnt, dSrvFrameCnt, dFrameCnt-dSrvFrameCnt );
end

[C0 C1] = ExperimentCalcLinCoeffs(dFrameCnt, g_ExpData.dDisplayFrameCnt, ...
                      dFrameTimeMs, g_ExpData.dDisplayFrameTimeMs);
hVMain.SetTimeScale(C0, C1);
g_ExpData.dDisplayFrameCnt = dFrameCnt;
g_ExpData.dDisplayFrameTimeMs = dFrameTimeMs;

%--- Tracker
% TODO: append new vals to the global var
[dFrameCnt dFrameTimeMs ] = TrackerGetTiming( ); % Time Server (RZ2)
dSrvFrameCnt = hTracker.GetFrameCount(); % Tracker Server
if abs(dSrvFrameCnt - dFrameCnt) > FrameMismatchMax
  warning('Mismatch in frame count for the Tracker! RP2: %d,  Tracker: %d, Diff: %d', ...
                                                        dFrameCnt, dSrvFrameCnt, dFrameCnt-dSrvFrameCnt );
end

[C0 C1] = ExperimentCalcLinCoeffs(dFrameCnt, g_ExpData.dTrackerFrameCnt, ...
                      dFrameTimeMs, g_ExpData.dTrackerFrameTimeMs);
hTracker.SetTimeScale(C0, C1);
g_ExpData.dTrackerFrameCnt = dFrameCnt;
g_ExpData.dTrackerFrameTimeMs = dFrameTimeMs;

%--- EyeTrack
% TODO: append new vals to the global var
[dFrameCnt dFrameTimeMs ] = EyeTrackGetTiming( );
dSrvFrameCnt = hEyeTrack.GetFrameCount();
if abs(dSrvFrameCnt - dFrameCnt) > FrameMismatchMax
  fprintf('\n==>> Mismatch in frame count for the EyeTrack! RP2: %d,  EyeTrack: %d, Diff: %d\n', ... 
                                                        dFrameCnt, dSrvFrameCnt, dFrameCnt-dSrvFrameCnt );
end

[C0 C1] = ExperimentCalcLinCoeffs(dFrameCnt, g_ExpData.dEyeTrackFrameCnt, ...
                      dFrameTimeMs, g_ExpData.dEyeTrackFrameTimeMs);
hEyeTrack.SetTimeScale(C0, C1);
g_ExpData.dEyeTrackFrameCnt = dFrameCnt;
g_ExpData.dEyeTrackFrameTimeMs = dFrameTimeMs;

% Write timesync to the daq streams 
if blnUseCerebusDaq 
  dTimesyncTS = GenerateSyncPulse();  % sends TTL pulse, returns its timestamp on RP2
  CerebusStreamWriteTimesync( dTimesyncTS );  % write to the serial interface
end
