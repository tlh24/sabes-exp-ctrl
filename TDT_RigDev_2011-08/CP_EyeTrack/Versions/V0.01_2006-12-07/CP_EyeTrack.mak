# Microsoft Developer Studio Generated NMAKE File, Based on CP_EyeTrack.dsp
!IF "$(CFG)" == ""
CFG=CP_EyeTrack - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CP_EyeTrack - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CP_EyeTrack - Win32 Release" && "$(CFG)" != "CP_EyeTrack - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CP_EyeTrack.mak" CFG="CP_EyeTrack - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CP_EyeTrack - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CP_EyeTrack - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\CP_EyeTrack.exe" "$(OUTDIR)\CP_EyeTrackCom.tlb"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\CP_ET_Class.obj"
	-@erase "$(INTDIR)\CP_EyeTrack.obj"
	-@erase "$(INTDIR)\CP_EyeTrack.res"
	-@erase "$(INTDIR)\CP_EyeTrackCom.tlb"
	-@erase "$(INTDIR)\CP_EyeTrackCom_i.obj"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\EyeTrack.obj"
	-@erase "$(INTDIR)\EyeTrackGlob.obj"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\SerialThread.obj"
	-@erase "$(INTDIR)\SlideBuf.obj"
	-@erase "$(INTDIR)\TimeStamp.obj"
	-@erase "$(INTDIR)\tserial.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CP_EyeTrack.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\CP_EyeTrack.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_EyeTrack.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_EyeTrack.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_EyeTrack.pdb" /machine:I386 /out:"$(OUTDIR)\CP_EyeTrack.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_ET_Class.obj" \
	"$(INTDIR)\CP_EyeTrack.obj" \
	"$(INTDIR)\CP_EyeTrackCom_i.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\EyeTrack.obj" \
	"$(INTDIR)\EyeTrackGlob.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\SerialThread.obj" \
	"$(INTDIR)\SlideBuf.obj" \
	"$(INTDIR)\TimeStamp.obj" \
	"$(INTDIR)\tserial.obj" \
	"$(INTDIR)\CP_EyeTrack.res"

"$(OUTDIR)\CP_EyeTrack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CP_EyeTrack.exe" "$(OUTDIR)\CP_EyeTrackCom.tlb" "$(OUTDIR)\CP_EyeTrack.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClassFactory.obj"
	-@erase "$(INTDIR)\ClassFactory.sbr"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\CP_ET_Class.obj"
	-@erase "$(INTDIR)\CP_ET_Class.sbr"
	-@erase "$(INTDIR)\CP_EyeTrack.obj"
	-@erase "$(INTDIR)\CP_EyeTrack.res"
	-@erase "$(INTDIR)\CP_EyeTrack.sbr"
	-@erase "$(INTDIR)\CP_EyeTrackCom.tlb"
	-@erase "$(INTDIR)\CP_EyeTrackCom_i.obj"
	-@erase "$(INTDIR)\CP_EyeTrackCom_i.sbr"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\CP_printf.sbr"
	-@erase "$(INTDIR)\EyeTrack.obj"
	-@erase "$(INTDIR)\EyeTrack.sbr"
	-@erase "$(INTDIR)\EyeTrackGlob.obj"
	-@erase "$(INTDIR)\EyeTrackGlob.sbr"
	-@erase "$(INTDIR)\RegisterCom.obj"
	-@erase "$(INTDIR)\RegisterCom.sbr"
	-@erase "$(INTDIR)\SerialThread.obj"
	-@erase "$(INTDIR)\SerialThread.sbr"
	-@erase "$(INTDIR)\SlideBuf.obj"
	-@erase "$(INTDIR)\SlideBuf.sbr"
	-@erase "$(INTDIR)\TimeStamp.obj"
	-@erase "$(INTDIR)\TimeStamp.sbr"
	-@erase "$(INTDIR)\tserial.obj"
	-@erase "$(INTDIR)\tserial.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CP_EyeTrack.bsc"
	-@erase "$(OUTDIR)\CP_EyeTrack.exe"
	-@erase "$(OUTDIR)\CP_EyeTrack.ilk"
	-@erase "$(OUTDIR)\CP_EyeTrack.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I ".\Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/D "_DEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_EyeTrack.res" /i "./Debug" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_EyeTrack.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClassFactory.sbr" \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\CP_ET_Class.sbr" \
	"$(INTDIR)\CP_EyeTrack.sbr" \
	"$(INTDIR)\CP_EyeTrackCom_i.sbr" \
	"$(INTDIR)\CP_printf.sbr" \
	"$(INTDIR)\EyeTrack.sbr" \
	"$(INTDIR)\EyeTrackGlob.sbr" \
	"$(INTDIR)\RegisterCom.sbr" \
	"$(INTDIR)\SerialThread.sbr" \
	"$(INTDIR)\SlideBuf.sbr" \
	"$(INTDIR)\TimeStamp.sbr" \
	"$(INTDIR)\tserial.sbr"

"$(OUTDIR)\CP_EyeTrack.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CP_EyeTrack.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CP_EyeTrack.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ClassFactory.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_ET_Class.obj" \
	"$(INTDIR)\CP_EyeTrack.obj" \
	"$(INTDIR)\CP_EyeTrackCom_i.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\EyeTrack.obj" \
	"$(INTDIR)\EyeTrackGlob.obj" \
	"$(INTDIR)\RegisterCom.obj" \
	"$(INTDIR)\SerialThread.obj" \
	"$(INTDIR)\SlideBuf.obj" \
	"$(INTDIR)\TimeStamp.obj" \
	"$(INTDIR)\tserial.obj" \
	"$(INTDIR)\CP_EyeTrack.res"

"$(OUTDIR)\CP_EyeTrack.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CP_EyeTrack.dep")
!INCLUDE "CP_EyeTrack.dep"
!ELSE 
!MESSAGE Warning: cannot find "CP_EyeTrack.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CP_EyeTrack - Win32 Release" || "$(CFG)" == "CP_EyeTrack - Win32 Debug"
SOURCE=.\ClassFactory.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\ClassFactory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\ClassFactory.obj"	"$(INTDIR)\ClassFactory.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\Console.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\Console.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\Console.obj"	"$(INTDIR)\Console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CP_ET_Class.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\CP_ET_Class.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\CP_ET_Class.obj"	"$(INTDIR)\CP_ET_Class.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_EyeTrack.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\CP_EyeTrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\CP_EyeTrack.obj"	"$(INTDIR)\CP_EyeTrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CP_EyeTrackCom.idl

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\CP_EyeTrackCom.tlb" /win32 

"$(INTDIR)\CP_EyeTrackCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"

MTL_SWITCHES=/D "_DEBUG" /tlb "$(OUTDIR)\CP_EyeTrackCom.tlb" /win32 

"$(INTDIR)\CP_EyeTrackCom.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CP_EyeTrackCom_i.c

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\CP_EyeTrackCom_i.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\CP_EyeTrackCom_i.obj"	"$(INTDIR)\CP_EyeTrackCom_i.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\CP_printf.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\CP_printf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\CP_printf.obj"	"$(INTDIR)\CP_printf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\EyeTrack.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\EyeTrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\EyeTrack.obj"	"$(INTDIR)\EyeTrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\EyeTrackGlob.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\EyeTrackGlob.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\EyeTrackGlob.obj"	"$(INTDIR)\EyeTrackGlob.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\RegisterCom.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\RegisterCom.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\RegisterCom.obj"	"$(INTDIR)\RegisterCom.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SerialThread.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\SerialThread.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\SerialThread.obj"	"$(INTDIR)\SerialThread.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SlideBuf.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\SlideBuf.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\SlideBuf.obj"	"$(INTDIR)\SlideBuf.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TimeStamp.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\TimeStamp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\TimeStamp.obj"	"$(INTDIR)\TimeStamp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Util\tserial.cpp

!IF  "$(CFG)" == "CP_EyeTrack - Win32 Release"


"$(INTDIR)\tserial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CP_EyeTrack - Win32 Debug"


"$(INTDIR)\tserial.obj"	"$(INTDIR)\tserial.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CP_EyeTrack.rc

"$(INTDIR)\CP_EyeTrack.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

