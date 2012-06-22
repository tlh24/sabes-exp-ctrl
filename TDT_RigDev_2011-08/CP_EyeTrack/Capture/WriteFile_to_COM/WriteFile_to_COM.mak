# Microsoft Developer Studio Generated NMAKE File, Based on WriteFile_to_COM.dsp
!IF "$(CFG)" == ""
CFG=WriteFile_to_COM - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WriteFile_to_COM - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WriteFile_to_COM - Win32 Release" && "$(CFG)" != "WriteFile_to_COM - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WriteFile_to_COM.mak" CFG="WriteFile_to_COM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WriteFile_to_COM - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "WriteFile_to_COM - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WriteFile_to_COM - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WriteFile_to_COM.exe"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WriteFile_to_COM.obj"
	-@erase "$(OUTDIR)\WriteFile_to_COM.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\WriteFile_to_COM.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WriteFile_to_COM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\WriteFile_to_COM.pdb" /machine:I386 /out:"$(OUTDIR)\WriteFile_to_COM.exe" 
LINK32_OBJS= \
	"$(INTDIR)\WriteFile_to_COM.obj"

"$(OUTDIR)\WriteFile_to_COM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WriteFile_to_COM - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WriteFile_to_COM.exe"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WriteFile_to_COM.obj"
	-@erase "$(OUTDIR)\WriteFile_to_COM.exe"
	-@erase "$(OUTDIR)\WriteFile_to_COM.ilk"
	-@erase "$(OUTDIR)\WriteFile_to_COM.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\WriteFile_to_COM.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WriteFile_to_COM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\WriteFile_to_COM.pdb" /debug /machine:I386 /out:"$(OUTDIR)\WriteFile_to_COM.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\WriteFile_to_COM.obj"

"$(OUTDIR)\WriteFile_to_COM.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WriteFile_to_COM.dep")
!INCLUDE "WriteFile_to_COM.dep"
!ELSE 
!MESSAGE Warning: cannot find "WriteFile_to_COM.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WriteFile_to_COM - Win32 Release" || "$(CFG)" == "WriteFile_to_COM - Win32 Debug"
SOURCE=.\WriteFile_to_COM.c

"$(INTDIR)\WriteFile_to_COM.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

