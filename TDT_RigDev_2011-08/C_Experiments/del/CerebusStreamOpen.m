function CerebusStreamOpen

DaqConfigInclude;
CerebusGlobalsInclude;

CerebusStreamClose;

g_hCerebusSerial = serial(strCerebusComPort, 'BaudRate', 115200, 'Terminator', 0 );
set( g_hCerebusSerial, 'Tag', strCerebusComTag );

fopen(g_hCerebusSerial);
