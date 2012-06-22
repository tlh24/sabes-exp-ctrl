function CerebusStreamClose

DaqConfigInclude;

hCerebusSerial = instrfind('Tag',strCerebusComTag);
if( length(hCerebusSerial))
  fprintf('Cerebus serial port object found. Closing COM port.\n');
  fclose( hCerebusSerial );
  delete( hCerebusSerial );
end

