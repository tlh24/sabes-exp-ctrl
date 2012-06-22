
OptoServerps.dll: dlldata.obj OptoServer_p.obj OptoServer_i.obj
	link /dll /out:OptoServerps.dll /def:OptoServerps.def /entry:DllMain dlldata.obj OptoServer_p.obj OptoServer_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del OptoServerps.dll
	@del OptoServerps.lib
	@del OptoServerps.exp
	@del dlldata.obj
	@del OptoServer_p.obj
	@del OptoServer_i.obj
