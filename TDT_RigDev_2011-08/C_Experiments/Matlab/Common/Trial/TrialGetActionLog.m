function Log = TrialGetActionLog(Arg1,EventCodes,OtherEventLog)
%
%  Builds an action log which is N x 2.
%  The first column contains event codes and the 2nd column the timestamp
%  for each event.
%
%  Note that this converts all timestamps into secs.  If you pass in
%  OtherEventLog this function expects the timestamps in OtherEventLog(:,2)
%  to be in msecs.
%
%
%

persistent NJOnPrev  NTOnPrev NJOffPrev  NTOffPrev

if nargin ==0 | isequal(lower(Arg1),'init')
  NJOnPrev = 0;
  NTOnPrev = 0;
  NJOffPrev = 0;
  NTOffPrev = 0;
else
  if ~iscom(Arg1)
    error('Argument must be either ''init'', or a handle to a COM object');
  end

  % % Get events from CP_Display
  [veid,veT] = Arg1.GetEventLog;
  vlog = [double(veid(:)) veT(:)];

  [NJOn,JOnT, NJOff, JOffT] = JuiceGetEvents;
  [NTOn,TOnT, NTOff, TOffT] = ToneGetEvents;
  [NRecOn,ROnT, NRecOff, ROffT, NRecPause, RPauseOnT, NRecResume, RPauseOffT] = RecordingGetEvents;

  jlog = [];
  if (NJOn - NJOnPrev) > 0
    %  (NJOn - NJOnPrev) can be 0 even though JOnT is not empty because if
    %  no juice ON events have yet occurred JuiceGetEvents() returns a Nan
    %  for the time.
    jlog = [zeros(NJOn-NJOnPrev,1)+EventCodes.Juice_On   JOnT(NJOnPrev+1:end)'];
  end
  if (NJOff - NJOffPrev) > 0
    jlog = [jlog; [zeros(NJOff-NJOffPrev,1)+EventCodes.Juice_Off 	JOffT(NJOffPrev+1:end)']];
  end

  tlog = [];
  if (NTOn-NTOnPrev) > 0
    tlog =  [zeros(NTOn-NTOnPrev,1)+EventCodes.Tone_On  TOnT(NTOnPrev+1:end)'];
  end
  if (NTOff-NTOffPrev) > 0
    tlog = [tlog; [zeros(NTOff-NTOffPrev,1)+EventCodes.Tone_Off TOffT(NTOffPrev+1:end)']];
  end

  %  Note that all recording events are kept for safety purposes.
  rlog =  [ [zeros(length(ROnT),1)+EventCodes.Recording_Start            ROnT']; ...
    [zeros(length(ROffT),1)+EventCodes.Recording_Stop            ROffT']; ...
    [zeros(length(RPauseOnT),1)+EventCodes.Recording_Pause         RPauseOnT']; ...
    [zeros(length(RPauseOffT),1)+EventCodes.Recording_Resume       RPauseOffT'] ...
    ];

  Log = [jlog; tlog; rlog; vlog];
  if nargin == 3
    Log = [Log; OtherEventLog];
  end
  
  %  Sort by timestamp
  [dum,sidx] = sort(Log(:,2));
  Log = Log(sidx,:);
  
  %  Convert all timestamps into secs.
  Log(:,2) = Log(:,2)./1000;

  NJOnPrev = NJOn;
  NTOnPrev = NTOn;
  NJOffPrev = NJOff;
  NRecOffPrev = NRecOff;
  NTOffPrev = NTOff;

end

return