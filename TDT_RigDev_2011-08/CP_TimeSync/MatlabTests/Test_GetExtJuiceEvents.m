          
nExtJuiceOnEvents = hTS.GetTagVal('ExtJuiceOnCnt');
dExtJuiceOnTicks = hTS.ReadTagVEX('ExtJuiceOnTimes',...
       0, nExtJuiceOnEvents,'I32','F64',1);
nExtJuiceOffEvents = hTS.GetTagVal('ExtJuiceOffCnt');
dExtJuiceOffTicks = hTS.ReadTagVEX('ExtJuiceOffTimes',...
       0, nExtJuiceOffEvents,'I32','F64',1);

dExtJuiceOnTimes = dExtJuiceOnTicks * dTsTicksToMs
dExtJuiceOffTimes = dExtJuiceOffTicks * dTsTicksToMs

% hTS.SoftTrg(1);