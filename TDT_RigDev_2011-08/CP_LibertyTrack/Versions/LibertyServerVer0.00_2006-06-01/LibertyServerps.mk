
LibertyServerps.dll: dlldata.obj LibertyServer_p.obj LibertyServer_i.obj
	link /dll /out:LibertyServerps.dll /def:LibertyServerps.def /entry:DllMain dlldata.obj LibertyServer_p.obj LibertyServer_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del LibertyServerps.dll
	@del LibertyServerps.lib
	@del LibertyServerps.exp
	@del dlldata.obj
	@del LibertyServer_p.obj
	@del LibertyServer_i.obj
