# Microsoft Developer Studio Generated NMAKE File, Based on CP_OptoTrack.dsp
!IF "$(CFG)" == ""
CFG=CP_OptoTrack - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CP_OptoTrack - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CP_OptoTrack - Win32 Release" && "$(CFG)" != "CP_OptoTrack - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CP_OptoTrack.mak" CFG="CP_OptoTrack - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CP_OptoTrack - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CP_OptoTrack - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\CP_OptoTrack.exe" "$(OUTDIR)\CP_OptoTrackCom.tlb"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\CP_OptoClass.obj"
	-@erase "$(INTDIR)\CP_OptoTrack.obj"
	-@erase "$(INTDIR)\CP_OptoTrack.res"
	-@erase "$(INTDIR)\CP_OptoTrackCom.tlb"
	-@erase "$(INTDIR)\CP_OptoTrackCom_i.obj"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\OptoTrack.obj"
	-@erase "$(INTDIR)\OptoTrackGlob.obj"
	-@erase "$(INTDIR)\ReadingThread.obj"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\SafeArrayLib.obj"
	-@erase "$(INTDIR)\SlideBuf.obj"
	-@erase "$(INTDIR)\TimeStamp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CP_OptoTrack.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\CP_OptoTrack.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_OptoTrack.res" /i "./Release" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_OptoTrack.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Winmm.lib opto\oapi.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_OptoTrack.pdb" /machine:I386 /out:"$(OUTDIR)\CP_OptoTrack.exe" /libpath:"Opto" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_OptoClass.obj" \
	"$(INTDIR)\CP_OptoTrack.obj" \
	"$(INTDIR)\CP_OptoTrackCom_i.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\OptoTrack.obj" \
	"$(INTDIR)\OptoTrackGlob.obj" \
	"$(INTDIR)\ReadingThread.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\SlideBuf.obj" \
	"$(INTDIR)\TimeStamp.obj" \
	"$(INTDIR)\CP_OptoTrack.res" \
	"$(INTDIR)\SafeArrayLib.obj"

"$(OUTDIR)\CP_OptoTrack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CP_OptoTrack.exe" "$(OUTDIR)\CP_OptoTrack.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\CP_OptoClass.obj"
	-@erase "$(INTDIR)\CP_OptoClass.sbr"
	-@erase "$(INTDIR)\CP_OptoTrack.obj"
	-@erase "$(INTDIR)\CP_OptoTrack.res"
	-@erase "$(INTDIR)\CP_OptoTrack.sbr"
	-@erase "$(INTDIR)\CP_OptoTrackCom.tlb"
	-@erase "$(INTDIR)\CP_OptoTrackCom_i.obj"
	-@erase "$(INTDIR)\CP_OptoTrackCom_i.sbr"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\CP_printf.sbr"
	-@erase "$(INTDIR)\OptoTrack.obj"
	-@erase "$(INTDIR)\OptoTrack.sbr"
	-@erase "$(INTDIR)\OptoTrackGlob.obj"
	-@erase "$(INTDIR)\OptoTrackGlob.sbr"
	-@erase "$(INTDIR)\ReadingThread.obj"
	-@erase "$(INTDIR)\ReadingThread.sbr"
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
	-@erase "$(OUTDIR)\CP_OptoTrack.bsc"
	-@erase "$(OUTDIR)\CP_OptoTrack.exe"
	-@erase "$(OUTDIR)\CP_OptoTrack.ilk"
	-@erase "$(OUTDIR)\CP_OptoTrack.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I ".\Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/D "_DEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_OptoTrack.res" /i "./Debug" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_OptoTrack.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\CP_OptoClass.sbr" \
	"$(INTDIR)\CP_OptoTrack.sbr" \
	"$(INTDIR)\CP_OptoTrackCom_i.sbr" \
	"$(INTDIR)\CP_printf.sbr" \
	"$(INTDIR)\OptoTrack.sbr" \
	"$(INTDIR)\OptoTrackGlob.sbr" \
	"$(INTDIR)\ReadingThread.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\SlideBuf.sbr" \
	"$(INTDIR)\TimeStamp.sbr" \
	"$(INTDIR)\SafeArrayLib.sbr"

"$(OUTDIR)\CP_OptoTrack.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Winmm.lib opto\oapi.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CP_OptoTrack.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CP_OptoTrack.exe" /pdbtype:sept /libpath:"Opto" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_OptoClass.obj" \
	"$(INTDIR)\CP_OptoTrack.obj" \
	"$(INTDIR)\CP_OptoTrackCom_i.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\OptoTrack.obj" \
	"$(INTDIR)\OptoTrackGlob.obj" \
	"$(INTDIR)\ReadingThread.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\SlideBuf.obj" \
	"$(INTDIR)\TimeStamp.obj" \
	"$(INTDIR)\CP_OptoTrack.res" \
	"$(INTDIR)\SafeArrayLib.obj"

"$(OUTDIR)\CP_OptoTrack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CP_OptoTrack.dep")
!INCLUDE "CP_OptoTrack.dep"
!ELSE 
!MESSAGE Warning: cannot find "CP_OptoTrack.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CP_OptoTrack - Win32 Release" || "$(CFG)" == "CP_OptoTrack - Win32 Debug"
SOURCE=.\ClassFactory.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\ClassFactory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\ClassFactory.obj"	"$(INTDIR)\ClassFactory.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\Console.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\Console.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\Console.obj"	"$(INTDIR)\Console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CP_OptoClass.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\CP_OptoClass.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\CP_OptoClass.obj"	"$(INTDIR)\CP_OptoClass.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_OptoTrack.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\CP_OptoTrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\CP_OptoTrack.obj"	"$(INTDIR)\CP_OptoTrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_OptoTrackCom.idl

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\CP_OptoTrackCom.tlb" /win32 

"$(INTDIR)\CP_OptoTrackCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"

MTL_SWITCHES=/D "_DEBUG" /tlb "$(OUTDIR)\CP_OptoTrackCom.tlb" /win32 

"$(INTDIR)\CP_OptoTrackCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CP_OptoTrackCom_i.c

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\CP_OptoTrackCom_i.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\CP_OptoTrackCom_i.obj"	"$(INTDIR)\CP_OptoTrackCom_i.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\CP_printf.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\CP_printf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\CP_printf.obj"	"$(INTDIR)\CP_printf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\OptoTrack.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\OptoTrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\OptoTrack.obj"	"$(INTDIR)\OptoTrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\OptoTrackGlob.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\OptoTrackGlob.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\OptoTrackGlob.obj"	"$(INTDIR)\OptoTrackGlob.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ReadingThread.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\ReadingThread.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\ReadingThread.obj"	"$(INTDIR)\ReadingThread.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\RegisterCom.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\RegisterCom.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\RegisterCom.obj"	"$(INTDIR)\RegisterCom.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\SafeArrayLib.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\SafeArrayLib.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\SafeArrayLib.obj"	"$(INTDIR)\SafeArrayLib.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SlideBuf.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\SlideBuf.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\SlideBuf.obj"	"$(INTDIR)\SlideBuf.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TimeStamp.cpp

!IF  "$(CFG)" == "CP_OptoTrack - Win32 Release"


"$(INTDIR)\TimeStamp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_OptoTrack - Win32 Debug"


"$(INTDIR)\TimeStamp.obj"	"$(INTDIR)\TimeStamp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_OptoTrack.rc

"$(INTDIR)\CP_OptoTrack.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

