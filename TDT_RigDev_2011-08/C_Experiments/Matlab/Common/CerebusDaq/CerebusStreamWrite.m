function CerebusStreamWrite( strData )

DaqConfigInclude;

if find( strData == 0 )
  warning('Char == 0 found in Cerebus serial data, data were not written!');
  return;
end

hCerebusSerial = serial(strCerebusComPort, 'BaudRate', 115200, 'Terminator', 0 );
fopen(hCerebusSerial);
fprintf(hCerebusSerial, strData);
fclose(hCerebusSerial);
