# Microsoft Developer Studio Generated NMAKE File, Based on OptoInfo.dsp
!IF "$(CFG)" == ""
CFG=OptoInfo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OptoInfo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OptoInfo - Win32 Release" && "$(CFG)" != "OptoInfo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OptoInfo.mak" CFG="OptoInfo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OptoInfo - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "OptoInfo - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "OptoInfo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\OptoInfo.exe"


CLEAN :
	-@erase "$(INTDIR)\OptoInfo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OptoInfo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "../Opto" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\OptoInfo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OptoInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ../Opto/oapi.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\OptoInfo.pdb" /machine:I386 /out:"$(OUTDIR)\OptoInfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\OptoInfo.obj"

"$(OUTDIR)\OptoInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OptoInfo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\OptoInfo.exe" "$(OUTDIR)\OptoInfo.bsc"


CLEAN :
	-@erase "$(INTDIR)\OptoInfo.obj"
	-@erase "$(INTDIR)\OptoInfo.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OptoInfo.bsc"
	-@erase "$(OUTDIR)\OptoInfo.exe"
	-@erase "$(OUTDIR)\OptoInfo.ilk"
	-@erase "$(OUTDIR)\OptoInfo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../Opto" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OptoInfo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OptoInfo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\OptoInfo.sbr"

"$(OUTDIR)\OptoInfo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ../Opto/oapi.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\OptoInfo.pdb" /debug /machine:I386 /out:"$(OUTDIR)\OptoInfo.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\OptoInfo.obj"

"$(OUTDIR)\OptoInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("OptoInfo.dep")
!INCLUDE "OptoInfo.dep"
!ELSE 
!MESSAGE Warning: cannot find "OptoInfo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OptoInfo - Win32 Release" || "$(CFG)" == "OptoInfo - Win32 Debug"
SOURCE=.\OptoInfo.c

!IF  "$(CFG)" == "OptoInfo - Win32 Release"


"$(INTDIR)\OptoInfo.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OptoInfo - Win32 Debug"


"$(INTDIR)\OptoInfo.obj"	"$(INTDIR)\OptoInfo.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

