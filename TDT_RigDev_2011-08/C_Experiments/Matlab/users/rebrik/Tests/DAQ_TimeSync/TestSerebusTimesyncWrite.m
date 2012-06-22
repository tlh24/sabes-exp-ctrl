
CerebusOpenSerial;

nTimes = 10;

for i = 1: nTimes
  dTimesyncTS = now();
  CerebusWriteTimesync( dTimesyncTS )
  pause(1);
end

CerebusCloseSerial;

