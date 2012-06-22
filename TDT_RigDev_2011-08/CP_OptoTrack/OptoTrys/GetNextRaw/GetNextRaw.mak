# Microsoft Developer Studio Generated NMAKE File, Based on GetNextRaw.dsp
!IF "$(CFG)" == ""
CFG=GetNextRaw - Win32 Debug
!MESSAGE No configuration specified. Defaulting to GetNextRaw - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GetNextRaw - Win32 Release" && "$(CFG)" != "GetNextRaw - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GetNextRaw.mak" CFG="GetNextRaw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GetNextRaw - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "GetNextRaw - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "GetNextRaw - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\GetNextRaw.exe"


CLEAN :
	-@erase "$(INTDIR)\GetNextRaw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\GetNextRaw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "../Opto" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\GetNextRaw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GetNextRaw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ../Opto/oapi.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\GetNextRaw.pdb" /machine:I386 /out:"$(OUTDIR)\GetNextRaw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GetNextRaw.obj"

"$(OUTDIR)\GetNextRaw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GetNextRaw - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\GetNextRaw.exe"


CLEAN :
	-@erase "$(INTDIR)\GetNextRaw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\GetNextRaw.exe"
	-@erase "$(OUTDIR)\GetNextRaw.ilk"
	-@erase "$(OUTDIR)\GetNextRaw.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../Opto" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\GetNextRaw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GetNextRaw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ../Opto/oapi.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\GetNextRaw.pdb" /debug /machine:I386 /out:"$(OUTDIR)\GetNextRaw.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\GetNextRaw.obj"

"$(OUTDIR)\GetNextRaw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("GetNextRaw.dep")
!INCLUDE "GetNextRaw.dep"
!ELSE 
!MESSAGE Warning: cannot find "GetNextRaw.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GetNextRaw - Win32 Release" || "$(CFG)" == "GetNextRaw - Win32 Debug"
SOURCE=.\GetNextRaw.c

"$(INTDIR)\GetNextRaw.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

