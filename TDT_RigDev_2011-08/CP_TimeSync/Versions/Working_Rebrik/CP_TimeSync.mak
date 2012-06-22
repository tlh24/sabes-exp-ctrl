# Microsoft Developer Studio Generated NMAKE File, Based on CP_TimeSync.dsp
!IF "$(CFG)" == ""
CFG=CP_TimeSync - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CP_TimeSync - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CP_TimeSync - Win32 Debug" && "$(CFG)" != "CP_TimeSync - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CP_TimeSync.mak" CFG="CP_TimeSync - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CP_TimeSync - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CP_TimeSync - Win32 Release MinDependency" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CP_TimeSync - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CP_TimeSync.exe" "$(OUTDIR)\CP_TimeSync.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\cp_printf.obj"
	-@erase "$(INTDIR)\cp_printf.sbr"
	-@erase "$(INTDIR)\CP_TimeSync.obj"
	-@erase "$(INTDIR)\CP_TimeSync.res"
	-@erase "$(INTDIR)\CP_TimeSync.sbr"
	-@erase "$(INTDIR)\CP_TimeSyncClass.obj"
	-@erase "$(INTDIR)\CP_TimeSyncClass.sbr"
	-@erase "$(INTDIR)\CP_TimeSyncCom_i.obj"
	-@erase "$(INTDIR)\CP_TimeSyncCom_i.sbr"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\RegisterCom.sbr"
	-@erase "$(INTDIR)\TimeSyncGlob.obj"
	-@erase "$(INTDIR)\TimeSyncGlob.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CP_TimeSync.bsc"
	-@erase "$(OUTDIR)\CP_TimeSync.exe"
	-@erase "$(OUTDIR)\CP_TimeSync.pdb"
	-@erase ".\CP_TimeSyncCom.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /Zi /Od /I ".\Util" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /D "_ATL_DLL_IMPL" /D _WIN32_WINDOWS=0x0500 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_TimeSync.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_TimeSync.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\cp_printf.sbr" \
	"$(INTDIR)\CP_TimeSync.sbr" \
	"$(INTDIR)\CP_TimeSyncClass.sbr" \
	"$(INTDIR)\CP_TimeSyncCom_i.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\TimeSyncGlob.sbr"

"$(OUTDIR)\CP_TimeSync.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=libcmtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib comsupp.lib atl.lib shlwapi.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_TimeSync.pdb" /debug /machine:I386 /nodefaultlib /out:"$(OUTDIR)\CP_TimeSync.exe" /pdbtype:sept /libpath:"VisualLeakDetector\\" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\cp_printf.obj" \
	"$(INTDIR)\CP_TimeSync.obj" \
	"$(INTDIR)\CP_TimeSyncClass.obj" \
	"$(INTDIR)\CP_TimeSyncCom_i.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\TimeSyncGlob.obj" \
	"$(INTDIR)\CP_TimeSync.res"

"$(OUTDIR)\CP_TimeSync.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CP_TimeSync - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\CP_TimeSync.exe" "$(OUTDIR)\CP_TimeSync.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\cp_printf.obj"
	-@erase "$(INTDIR)\cp_printf.sbr"
	-@erase "$(INTDIR)\CP_TimeSync.obj"
	-@erase "$(INTDIR)\CP_TimeSync.res"
	-@erase "$(INTDIR)\CP_TimeSync.sbr"
	-@erase "$(INTDIR)\CP_TimeSyncClass.obj"
	-@erase "$(INTDIR)\CP_TimeSyncClass.sbr"
	-@erase "$(INTDIR)\CP_TimeSyncCom_i.obj"
	-@erase "$(INTDIR)\CP_TimeSyncCom_i.sbr"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\RegisterCom.sbr"
	-@erase "$(INTDIR)\TimeSyncGlob.obj"
	-@erase "$(INTDIR)\TimeSyncGlob.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CP_TimeSync.bsc"
	-@erase "$(OUTDIR)\CP_TimeSync.exe"
	-@erase ".\CP_TimeSyncCom.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MT /W3 /GR /O2 /I ".\Util" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /D "_ATL_DLL_IMPL" /D _WIN32_WINDOWS=0x0500 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_TimeSync.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_TimeSync.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\cp_printf.sbr" \
	"$(INTDIR)\CP_TimeSync.sbr" \
	"$(INTDIR)\CP_TimeSyncClass.sbr" \
	"$(INTDIR)\CP_TimeSyncCom_i.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\TimeSyncGlob.sbr"

"$(OUTDIR)\CP_TimeSync.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=libcmt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib comsupp.lib atl.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_TimeSync.pdb" /machine:I386 /nodefaultlib /out:"$(OUTDIR)\CP_TimeSync.exe" /libpath:".\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\cp_printf.obj" \
	"$(INTDIR)\CP_TimeSync.obj" \
	"$(INTDIR)\CP_TimeSyncClass.obj" \
	"$(INTDIR)\CP_TimeSyncCom_i.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\TimeSyncGlob.obj" \
	"$(INTDIR)\CP_TimeSync.res"

"$(OUTDIR)\CP_TimeSync.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CP_TimeSync.dep")
!INCLUDE "CP_TimeSync.dep"
!ELSE 
!MESSAGE Warning: cannot find "CP_TimeSync.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CP_TimeSync - Win32 Debug" || "$(CFG)" == "CP_TimeSync - Win32 Release MinDependency"
SOURCE=.\ClassFactory.cpp

"$(INTDIR)\ClassFactory.obj"	"$(INTDIR)\ClassFactory.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Util\Console.cpp

"$(INTDIR)\Console.obj"	"$(INTDIR)\Console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Util\cp_printf.cpp

"$(INTDIR)\cp_printf.obj"	"$(INTDIR)\cp_printf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CP_TimeSync.cpp

"$(INTDIR)\CP_TimeSync.obj"	"$(INTDIR)\CP_TimeSync.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CP_TimeSync.rc

"$(INTDIR)\CP_TimeSync.res" : $(SOURCE) "$(INTDIR)" ".\CP_TimeSyncCom.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CP_TimeSyncClass.cpp

"$(INTDIR)\CP_TimeSyncClass.obj"	"$(INTDIR)\CP_TimeSyncClass.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CP_TimeSyncCom.idl
MTL_SWITCHES=/tlb "CP_TimeSyncCom.tlb" 

".\CP_TimeSyncCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\CP_TimeSyncCom_i.c

"$(INTDIR)\CP_TimeSyncCom_i.obj"	"$(INTDIR)\CP_TimeSyncCom_i.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegisterCom.cpp

"$(INTDIR)\RegisterCom.obj"	"$(INTDIR)\RegisterCom.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TimeSyncGlob.cpp

"$(INTDIR)\TimeSyncGlob.obj"	"$(INTDIR)\TimeSyncGlob.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

