# Microsoft Developer Studio Generated NMAKE File, Based on Sample1.dsp
!IF "$(CFG)" == ""
CFG=Sample1 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Sample1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Sample1 - Win32 Release" && "$(CFG)" != "Sample1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sample1.mak" CFG="Sample1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sample1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Sample1 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sample1 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Sample1.exe"


CLEAN :
	-@erase "$(INTDIR)\sample1.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Sample1.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\Opto" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Sample1.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Sample1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib advapi32.lib ../Opto/oapi.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Sample1.pdb" /machine:I386 /out:"$(OUTDIR)\Sample1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\sample1.obj"

"$(OUTDIR)\Sample1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Sample1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Sample1.exe"


CLEAN :
	-@erase "$(INTDIR)\sample1.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Sample1.exe"
	-@erase "$(OUTDIR)\Sample1.ilk"
	-@erase "$(OUTDIR)\Sample1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\Opto" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Sample1.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Sample1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../Opto/oapi.lib kernel32.lib user32.lib advapi32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Sample1.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Sample1.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\sample1.obj"

"$(OUTDIR)\Sample1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Sample1.dep")
!INCLUDE "Sample1.dep"
!ELSE 
!MESSAGE Warning: cannot find "Sample1.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Sample1 - Win32 Release" || "$(CFG)" == "Sample1 - Win32 Debug"
SOURCE=.\sample1.c

"$(INTDIR)\sample1.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

