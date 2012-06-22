function pos = getonePoint()

global BUFFERTIME FRAMERATE PREDTIME
global hL
global DEBUG

BUFFERTIME = 600;
PREDTIME = 1/75;
FRAMERATE = 240;
IP  = [4,3]; % latest index for position

if (isnumeric(hL)) delete(hL); end
hL = actxserver('LibertyServer.Liberty');


invoke(hL,'setup',BUFFERTIME,PREDTIME);
hL.active = 1;
point = hL.latest;       %% mm
pos = point(1,IP);
hL.active = 0;
release(hL);