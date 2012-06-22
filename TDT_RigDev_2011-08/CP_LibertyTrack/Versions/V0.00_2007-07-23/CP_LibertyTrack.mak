# Microsoft Developer Studio Generated NMAKE File, Based on CP_LibertyTrack.dsp
!IF "$(CFG)" == ""
CFG=CP_LibertyTrack - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CP_LibertyTrack - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CP_LibertyTrack - Win32 Release" && "$(CFG)" != "CP_LibertyTrack - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CP_LibertyTrack.mak" CFG="CP_LibertyTrack - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CP_LibertyTrack - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CP_LibertyTrack - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\CP_LibertyTrack.exe"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\CP_LibertyClass.obj"
	-@erase "$(INTDIR)\CP_LibertyTrack.obj"
	-@erase "$(INTDIR)\CP_LibertyTrack.res"
	-@erase "$(INTDIR)\CP_LibertyTrackCom.tlb"
	-@erase "$(INTDIR)\CP_LibertyTrackCom_i.obj"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\LibertyTrack.obj"
	-@erase "$(INTDIR)\LibertyTrackGlob.obj"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\SafeArrayLib.obj"
	-@erase "$(INTDIR)\SlideBuf.obj"
	-@erase "$(INTDIR)\TimeStamp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CP_LibertyTrack.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\CP_LibertyTrack.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_LibertyTrack.res" /i "./Release" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_LibertyTrack.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib pdi.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_LibertyTrack.pdb" /machine:I386 /out:"$(OUTDIR)\CP_LibertyTrack.exe" /libpath:"Liberty" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_LibertyClass.obj" \
	"$(INTDIR)\CP_LibertyTrack.obj" \
	"$(INTDIR)\CP_LibertyTrackCom_i.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\LibertyTrack.obj" \
	"$(INTDIR)\LibertyTrackGlob.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\SafeArrayLib.obj" \
	"$(INTDIR)\SlideBuf.obj" \
	"$(INTDIR)\TimeStamp.obj" \
	"$(INTDIR)\CP_LibertyTrack.res"

"$(OUTDIR)\CP_LibertyTrack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CP_LibertyTrack.exe" "$(OUTDIR)\CP_LibertyTrack.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\CP_LibertyClass.obj"
	-@erase "$(INTDIR)\CP_LibertyClass.sbr"
	-@erase "$(INTDIR)\CP_LibertyTrack.obj"
	-@erase "$(INTDIR)\CP_LibertyTrack.res"
	-@erase "$(INTDIR)\CP_LibertyTrack.sbr"
	-@erase "$(INTDIR)\CP_LibertyTrackCom.tlb"
	-@erase "$(INTDIR)\CP_LibertyTrackCom_i.obj"
	-@erase "$(INTDIR)\CP_LibertyTrackCom_i.sbr"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\CP_printf.sbr"
	-@erase "$(INTDIR)\LibertyTrack.obj"
	-@erase "$(INTDIR)\LibertyTrack.sbr"
	-@erase "$(INTDIR)\LibertyTrackGlob.obj"
	-@erase "$(INTDIR)\LibertyTrackGlob.sbr"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\RegisterCom.sbr"
	-@erase "$(INTDIR)\SafeArrayLib.obj"
	-@erase "$(INTDIR)\SafeArrayLib.sbr"
	-@erase "$(INTDIR)\SlideBuf.obj"
	-@erase "$(INTDIR)\SlideBuf.sbr"
	-@erase "$(INTDIR)\TimeStamp.obj"
	-@erase "$(INTDIR)\TimeStamp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CP_LibertyTrack.bsc"
	-@erase "$(OUTDIR)\CP_LibertyTrack.exe"
	-@erase "$(OUTDIR)\CP_LibertyTrack.ilk"
	-@erase "$(OUTDIR)\CP_LibertyTrack.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I ".\Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/D "_DEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_LibertyTrack.res" /i "./Debug" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_LibertyTrack.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\CP_LibertyClass.sbr" \
	"$(INTDIR)\CP_LibertyTrack.sbr" \
	"$(INTDIR)\CP_LibertyTrackCom_i.sbr" \
	"$(INTDIR)\CP_printf.sbr" \
	"$(INTDIR)\LibertyTrack.sbr" \
	"$(INTDIR)\LibertyTrackGlob.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\SafeArrayLib.sbr" \
	"$(INTDIR)\SlideBuf.sbr" \
	"$(INTDIR)\TimeStamp.sbr"

"$(OUTDIR)\CP_LibertyTrack.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib pdi.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CP_LibertyTrack.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CP_LibertyTrack.exe" /pdbtype:sept /libpath:"Liberty" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_LibertyClass.obj" \
	"$(INTDIR)\CP_LibertyTrack.obj" \
	"$(INTDIR)\CP_LibertyTrackCom_i.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\LibertyTrack.obj" \
	"$(INTDIR)\LibertyTrackGlob.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\SafeArrayLib.obj" \
	"$(INTDIR)\SlideBuf.obj" \
	"$(INTDIR)\TimeStamp.obj" \
	"$(INTDIR)\CP_LibertyTrack.res"

"$(OUTDIR)\CP_LibertyTrack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CP_LibertyTrack.dep")
!INCLUDE "CP_LibertyTrack.dep"
!ELSE 
!MESSAGE Warning: cannot find "CP_LibertyTrack.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CP_LibertyTrack - Win32 Release" || "$(CFG)" == "CP_LibertyTrack - Win32 Debug"
SOURCE=.\ClassFactory.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\ClassFactory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\ClassFactory.obj"	"$(INTDIR)\ClassFactory.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\Console.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\Console.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\Console.obj"	"$(INTDIR)\Console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CP_LibertyClass.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\CP_LibertyClass.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\CP_LibertyClass.obj"	"$(INTDIR)\CP_LibertyClass.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_LibertyTrack.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\CP_LibertyTrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\CP_LibertyTrack.obj"	"$(INTDIR)\CP_LibertyTrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_LibertyTrackCom.idl

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\CP_LibertyTrackCom.tlb" /win32 

"$(INTDIR)\CP_LibertyTrackCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"

MTL_SWITCHES=/D "_DEBUG" /tlb "$(OUTDIR)\CP_LibertyTrackCom.tlb" /win32 

"$(INTDIR)\CP_LibertyTrackCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CP_LibertyTrackCom_i.c

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\CP_LibertyTrackCom_i.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\CP_LibertyTrackCom_i.obj"	"$(INTDIR)\CP_LibertyTrackCom_i.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\CP_printf.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\CP_printf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\CP_printf.obj"	"$(INTDIR)\CP_printf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\LibertyTrack.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\LibertyTrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\LibertyTrack.obj"	"$(INTDIR)\LibertyTrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\LibertyTrackGlob.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\LibertyTrackGlob.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\LibertyTrackGlob.obj"	"$(INTDIR)\LibertyTrackGlob.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\RegisterCom.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\RegisterCom.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\RegisterCom.obj"	"$(INTDIR)\RegisterCom.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\SafeArrayLib.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\SafeArrayLib.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\SafeArrayLib.obj"	"$(INTDIR)\SafeArrayLib.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SlideBuf.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\SlideBuf.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\SlideBuf.obj"	"$(INTDIR)\SlideBuf.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TimeStamp.cpp

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"


"$(INTDIR)\TimeStamp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"


"$(INTDIR)\TimeStamp.obj"	"$(INTDIR)\TimeStamp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_LibertyTrack.rc

"$(INTDIR)\CP_LibertyTrack.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CP_LibertyTrackCom.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

