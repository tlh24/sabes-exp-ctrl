function CerebusStreamWriteTimesync( dTimesyncTS )

StreamTagsInclude;

CerebusStreamWrite( sprintf( '%s%s%f', strStreamTimesyncTag, strStreamSeparator, dTimesyncTS ));