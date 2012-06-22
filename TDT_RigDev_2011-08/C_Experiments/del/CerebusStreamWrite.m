function CerebusStreamWrite( strData )

CerebusGlobalsInclude;

if find( strData == 0 )
  warning('Char == 0 found in Cerebus serial data, data were not written!');
  return;
end

fprintf(g_hCerebusSerial, strData, 'async');
