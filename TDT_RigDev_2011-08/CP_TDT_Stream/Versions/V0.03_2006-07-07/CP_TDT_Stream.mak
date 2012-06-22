# Microsoft Developer Studio Generated NMAKE File, Based on CP_TDT_Stream.dsp
!IF "$(CFG)" == ""
CFG=CP_TDT_Stream - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CP_TDT_Stream - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CP_TDT_Stream - Win32 Debug" && "$(CFG)" != "CP_TDT_Stream - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CP_TDT_Stream.mak" CFG="CP_TDT_Stream - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CP_TDT_Stream - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CP_TDT_Stream - Win32 Release MinDependency" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CP_TDT_Stream - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CP_TDT_Stream.exe" "$(OUTDIR)\CP_TDT_Stream.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\cp_printf.obj"
	-@erase "$(INTDIR)\cp_printf.sbr"
	-@erase "$(INTDIR)\CP_TDT_Stream.obj"
	-@erase "$(INTDIR)\CP_TDT_Stream.res"
	-@erase "$(INTDIR)\CP_TDT_Stream.sbr"
	-@erase "$(INTDIR)\CP_TDT_StreamCom_i.obj"
	-@erase "$(INTDIR)\CP_TDT_StreamCom_i.sbr"
	-@erase "$(INTDIR)\CP_TS_Class.obj"
	-@erase "$(INTDIR)\CP_TS_Class.sbr"
	-@erase "$(INTDIR)\DataFile.obj"
	-@erase "$(INTDIR)\DataFile.sbr"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\RegisterCom.sbr"
	-@erase "$(INTDIR)\Stream_Glob.obj"
	-@erase "$(INTDIR)\Stream_Glob.sbr"
	-@erase "$(INTDIR)\TDT_Stream.obj"
	-@erase "$(INTDIR)\TDT_Stream.sbr"
	-@erase "$(INTDIR)\TimerThread.obj"
	-@erase "$(INTDIR)\TimerThread.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CP_TDT_Stream.bsc"
	-@erase "$(OUTDIR)\CP_TDT_Stream.exe"
	-@erase "$(OUTDIR)\CP_TDT_Stream.pdb"
	-@erase ".\CP_TDT_StreamCom.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /Zi /Od /I ".\Util" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /D "_ATL_DLL_IMPL" /D _WIN32_WINDOWS=0x0500 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_TDT_Stream.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_TDT_Stream.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\cp_printf.sbr" \
	"$(INTDIR)\CP_TDT_Stream.sbr" \
	"$(INTDIR)\CP_TDT_StreamCom_i.sbr" \
	"$(INTDIR)\CP_TS_Class.sbr" \
	"$(INTDIR)\DataFile.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\Stream_Glob.sbr" \
	"$(INTDIR)\TDT_Stream.sbr" \
	"$(INTDIR)\TimerThread.sbr"

"$(OUTDIR)\CP_TDT_Stream.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=libcmtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib comsupp.lib atl.lib shlwapi.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_TDT_Stream.pdb" /debug /machine:I386 /nodefaultlib /out:"$(OUTDIR)\CP_TDT_Stream.exe" /pdbtype:sept /libpath:"VisualLeakDetector\\" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\cp_printf.obj" \
	"$(INTDIR)\CP_TDT_Stream.obj" \
	"$(INTDIR)\CP_TDT_StreamCom_i.obj" \
	"$(INTDIR)\CP_TS_Class.obj" \
	"$(INTDIR)\DataFile.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\Stream_Glob.obj" \
	"$(INTDIR)\TDT_Stream.obj" \
	"$(INTDIR)\TimerThread.obj" \
	"$(INTDIR)\CP_TDT_Stream.res"

"$(OUTDIR)\CP_TDT_Stream.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CP_TDT_Stream - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\CP_TDT_Stream.exe" ".\CP_TDT_StreamCom.tlb" "$(OUTDIR)\CP_TDT_Stream.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\cp_printf.obj"
	-@erase "$(INTDIR)\cp_printf.sbr"
	-@erase "$(INTDIR)\CP_TDT_Stream.obj"
	-@erase "$(INTDIR)\CP_TDT_Stream.res"
	-@erase "$(INTDIR)\CP_TDT_Stream.sbr"
	-@erase "$(INTDIR)\CP_TDT_StreamCom_i.obj"
	-@erase "$(INTDIR)\CP_TDT_StreamCom_i.sbr"
	-@erase "$(INTDIR)\CP_TS_Class.obj"
	-@erase "$(INTDIR)\CP_TS_Class.sbr"
	-@erase "$(INTDIR)\DataFile.obj"
	-@erase "$(INTDIR)\DataFile.sbr"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\RegisterCom.sbr"
	-@erase "$(INTDIR)\Stream_Glob.obj"
	-@erase "$(INTDIR)\Stream_Glob.sbr"
	-@erase "$(INTDIR)\TDT_Stream.obj"
	-@erase "$(INTDIR)\TDT_Stream.sbr"
	-@erase "$(INTDIR)\TimerThread.obj"
	-@erase "$(INTDIR)\TimerThread.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CP_TDT_Stream.bsc"
	-@erase "$(OUTDIR)\CP_TDT_Stream.exe"
	-@erase ".\CP_TDT_StreamCom.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MT /W3 /GR /O2 /I ".\Util" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /D "_ATL_DLL_IMPL" /D _WIN32_WINDOWS=0x0500 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_TDT_Stream.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_TDT_Stream.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\cp_printf.sbr" \
	"$(INTDIR)\CP_TDT_Stream.sbr" \
	"$(INTDIR)\CP_TDT_StreamCom_i.sbr" \
	"$(INTDIR)\CP_TS_Class.sbr" \
	"$(INTDIR)\DataFile.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\Stream_Glob.sbr" \
	"$(INTDIR)\TDT_Stream.sbr" \
	"$(INTDIR)\TimerThread.sbr"

"$(OUTDIR)\CP_TDT_Stream.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=libcmt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib comsupp.lib atl.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_TDT_Stream.pdb" /machine:I386 /nodefaultlib /out:"$(OUTDIR)\CP_TDT_Stream.exe" /libpath:".\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\cp_printf.obj" \
	"$(INTDIR)\CP_TDT_Stream.obj" \
	"$(INTDIR)\CP_TDT_StreamCom_i.obj" \
	"$(INTDIR)\CP_TS_Class.obj" \
	"$(INTDIR)\DataFile.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\Stream_Glob.obj" \
	"$(INTDIR)\TDT_Stream.obj" \
	"$(INTDIR)\TimerThread.obj" \
	"$(INTDIR)\CP_TDT_Stream.res"

"$(OUTDIR)\CP_TDT_Stream.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CP_TDT_Stream.dep")
!INCLUDE "CP_TDT_Stream.dep"
!ELSE 
!MESSAGE Warning: cannot find "CP_TDT_Stream.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CP_TDT_Stream - Win32 Debug" || "$(CFG)" == "CP_TDT_Stream - Win32 Release MinDependency"
SOURCE=.\ClassFactory.cpp

"$(INTDIR)\ClassFactory.obj"	"$(INTDIR)\ClassFactory.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Util\Console.cpp

"$(INTDIR)\Console.obj"	"$(INTDIR)\Console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Util\cp_printf.cpp

"$(INTDIR)\cp_printf.obj"	"$(INTDIR)\cp_printf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CP_TDT_Stream.cpp

"$(INTDIR)\CP_TDT_Stream.obj"	"$(INTDIR)\CP_TDT_Stream.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CP_TDT_Stream.rc

"$(INTDIR)\CP_TDT_Stream.res" : $(SOURCE) "$(INTDIR)" ".\CP_TDT_StreamCom.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CP_TDT_StreamCom.idl
MTL_SWITCHES=/tlb "CP_TDT_StreamCom.tlb" 

".\CP_TDT_StreamCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\CP_TDT_StreamCom_i.c

"$(INTDIR)\CP_TDT_StreamCom_i.obj"	"$(INTDIR)\CP_TDT_StreamCom_i.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CP_TS_Class.cpp

"$(INTDIR)\CP_TS_Class.obj"	"$(INTDIR)\CP_TS_Class.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DataFile.cpp

"$(INTDIR)\DataFile.obj"	"$(INTDIR)\DataFile.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegisterCom.cpp

"$(INTDIR)\RegisterCom.obj"	"$(INTDIR)\RegisterCom.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Stream_Glob.cpp

"$(INTDIR)\Stream_Glob.obj"	"$(INTDIR)\Stream_Glob.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TDT_Stream.cpp

"$(INTDIR)\TDT_Stream.obj"	"$(INTDIR)\TDT_Stream.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TimerThread.cpp

"$(INTDIR)\TimerThread.obj"	"$(INTDIR)\TimerThread.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

