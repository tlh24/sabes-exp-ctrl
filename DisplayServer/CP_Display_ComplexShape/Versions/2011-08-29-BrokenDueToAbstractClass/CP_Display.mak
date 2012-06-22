# Microsoft Developer Studio Generated NMAKE File, Based on CP_Display.dsp
!IF "$(CFG)" == ""
CFG=CP_Display - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CP_Display - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CP_Display - Win32 Debug" && "$(CFG)" != "CP_Display - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CP_Display.mak" CFG="CP_Display - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CP_Display - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CP_Display - Win32 Release MinDependency" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "CP_Display - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CP_Display.exe" ".\CP_Display.tlb" ".\CP_Display.h" ".\CP_Display_i.c" "$(OUTDIR)\CP_Display.bsc"


CLEAN :
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\CP_Display.obj"
	-@erase "$(INTDIR)\CP_Display.res"
	-@erase "$(INTDIR)\CP_Display.sbr"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\CP_printf.sbr"
	-@erase "$(INTDIR)\FrameCounter.obj"
	-@erase "$(INTDIR)\FrameCounter.sbr"
	-@erase "$(INTDIR)\GL_Engine.obj"
	-@erase "$(INTDIR)\GL_Engine.sbr"
	-@erase "$(INTDIR)\GL_Font.obj"
	-@erase "$(INTDIR)\GL_Font.sbr"
	-@erase "$(INTDIR)\PointerArray.obj"
	-@erase "$(INTDIR)\PointerArray.sbr"
	-@erase "$(INTDIR)\PortTalkGrantIO.obj"
	-@erase "$(INTDIR)\PortTalkGrantIO.sbr"
	-@erase "$(INTDIR)\SafeArrayLib.obj"
	-@erase "$(INTDIR)\SafeArrayLib.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VDisk.obj"
	-@erase "$(INTDIR)\VDisk.sbr"
	-@erase "$(INTDIR)\VMain.obj"
	-@erase "$(INTDIR)\VMain.sbr"
	-@erase "$(INTDIR)\VMouse.obj"
	-@erase "$(INTDIR)\VMouse.sbr"
	-@erase "$(INTDIR)\VObject.obj"
	-@erase "$(INTDIR)\VObject.sbr"
	-@erase "$(INTDIR)\VPolygon.obj"
	-@erase "$(INTDIR)\VPolygon.sbr"
	-@erase "$(INTDIR)\VText.obj"
	-@erase "$(INTDIR)\VText.sbr"
	-@erase "$(OUTDIR)\CP_Display.bsc"
	-@erase "$(OUTDIR)\CP_Display.exe"
	-@erase "$(OUTDIR)\CP_Display.ilk"
	-@erase "$(OUTDIR)\CP_Display.pdb"
	-@erase ".\CP_Display.h"
	-@erase ".\CP_Display.tlb"
	-@erase ".\CP_Display_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_Display.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_Display.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\CP_Display.sbr" \
	"$(INTDIR)\CP_printf.sbr" \
	"$(INTDIR)\FrameCounter.sbr" \
	"$(INTDIR)\GL_Engine.sbr" \
	"$(INTDIR)\GL_Font.sbr" \
	"$(INTDIR)\PointerArray.sbr" \
	"$(INTDIR)\PortTalkGrantIO.sbr" \
	"$(INTDIR)\SafeArrayLib.sbr" \
	"$(INTDIR)\VDisk.sbr" \
	"$(INTDIR)\VMain.sbr" \
	"$(INTDIR)\VMouse.sbr" \
	"$(INTDIR)\VObject.sbr" \
	"$(INTDIR)\VPolygon.sbr" \
	"$(INTDIR)\VText.sbr"

"$(OUTDIR)\CP_Display.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CP_Display.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CP_Display.exe" /pdbtype:sept /libpath:"../nr/release" 
LINK32_OBJS= \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_Display.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\FrameCounter.obj" \
	"$(INTDIR)\GL_Engine.obj" \
	"$(INTDIR)\GL_Font.obj" \
	"$(INTDIR)\PointerArray.obj" \
	"$(INTDIR)\PortTalkGrantIO.obj" \
	"$(INTDIR)\SafeArrayLib.obj" \
	"$(INTDIR)\VDisk.obj" \
	"$(INTDIR)\VMain.obj" \
	"$(INTDIR)\VMouse.obj" \
	"$(INTDIR)\VObject.obj" \
	"$(INTDIR)\VPolygon.obj" \
	"$(INTDIR)\VText.obj" \
	"$(INTDIR)\CP_Display.res"

"$(OUTDIR)\CP_Display.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CP_Display - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\CP_Display.exe" "$(OUTDIR)\CP_Display.bsc"


CLEAN :
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Console.sbr"
	-@erase "$(INTDIR)\CP_Display.obj"
	-@erase "$(INTDIR)\CP_Display.res"
	-@erase "$(INTDIR)\CP_Display.sbr"
	-@erase "$(INTDIR)\CP_printf.obj"
	-@erase "$(INTDIR)\CP_printf.sbr"
	-@erase "$(INTDIR)\FrameCounter.obj"
	-@erase "$(INTDIR)\FrameCounter.sbr"
	-@erase "$(INTDIR)\GL_Engine.obj"
	-@erase "$(INTDIR)\GL_Engine.sbr"
	-@erase "$(INTDIR)\GL_Font.obj"
	-@erase "$(INTDIR)\GL_Font.sbr"
	-@erase "$(INTDIR)\PointerArray.obj"
	-@erase "$(INTDIR)\PointerArray.sbr"
	-@erase "$(INTDIR)\PortTalkGrantIO.obj"
	-@erase "$(INTDIR)\PortTalkGrantIO.sbr"
	-@erase "$(INTDIR)\SafeArrayLib.obj"
	-@erase "$(INTDIR)\SafeArrayLib.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VDisk.obj"
	-@erase "$(INTDIR)\VDisk.sbr"
	-@erase "$(INTDIR)\VMain.obj"
	-@erase "$(INTDIR)\VMain.sbr"
	-@erase "$(INTDIR)\VMouse.obj"
	-@erase "$(INTDIR)\VMouse.sbr"
	-@erase "$(INTDIR)\VObject.obj"
	-@erase "$(INTDIR)\VObject.sbr"
	-@erase "$(INTDIR)\VPolygon.obj"
	-@erase "$(INTDIR)\VPolygon.sbr"
	-@erase "$(INTDIR)\VText.obj"
	-@erase "$(INTDIR)\VText.sbr"
	-@erase "$(OUTDIR)\CP_Display.bsc"
	-@erase "$(OUTDIR)\CP_Display.exe"
	-@erase ".\CP_Display.h"
	-@erase ".\CP_Display.tlb"
	-@erase ".\CP_Display_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CP_Display.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CP_Display.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Console.sbr" \
	"$(INTDIR)\CP_Display.sbr" \
	"$(INTDIR)\CP_printf.sbr" \
	"$(INTDIR)\FrameCounter.sbr" \
	"$(INTDIR)\GL_Engine.sbr" \
	"$(INTDIR)\GL_Font.sbr" \
	"$(INTDIR)\PointerArray.sbr" \
	"$(INTDIR)\PortTalkGrantIO.sbr" \
	"$(INTDIR)\SafeArrayLib.sbr" \
	"$(INTDIR)\VDisk.sbr" \
	"$(INTDIR)\VMain.sbr" \
	"$(INTDIR)\VMouse.sbr" \
	"$(INTDIR)\VObject.sbr" \
	"$(INTDIR)\VPolygon.sbr" \
	"$(INTDIR)\VText.sbr"

"$(OUTDIR)\CP_Display.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CP_Display.pdb" /machine:I386 /out:"$(OUTDIR)\CP_Display.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\CP_Display.obj" \
	"$(INTDIR)\CP_printf.obj" \
	"$(INTDIR)\FrameCounter.obj" \
	"$(INTDIR)\GL_Engine.obj" \
	"$(INTDIR)\GL_Font.obj" \
	"$(INTDIR)\PointerArray.obj" \
	"$(INTDIR)\PortTalkGrantIO.obj" \
	"$(INTDIR)\SafeArrayLib.obj" \
	"$(INTDIR)\VDisk.obj" \
	"$(INTDIR)\VMain.obj" \
	"$(INTDIR)\VMouse.obj" \
	"$(INTDIR)\VObject.obj" \
	"$(INTDIR)\VPolygon.obj" \
	"$(INTDIR)\VText.obj" \
	"$(INTDIR)\CP_Display.res"

"$(OUTDIR)\CP_Display.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CP_Display.dep")
!INCLUDE "CP_Display.dep"
!ELSE 
!MESSAGE Warning: cannot find "CP_Display.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CP_Display - Win32 Debug" || "$(CFG)" == "CP_Display - Win32 Release MinDependency"
SOURCE=.\Util\Console.cpp

"$(INTDIR)\Console.obj"	"$(INTDIR)\Console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CP_Display.cpp

"$(INTDIR)\CP_Display.obj"	"$(INTDIR)\CP_Display.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CP_Display.idl
MTL_SWITCHES=/tlb ".\CP_Display.tlb" /h "CP_Display.h" /iid "CP_Display_i.c" /Oicf 

".\CP_Display.tlb"	".\CP_Display.h"	".\CP_Display_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\CP_Display.rc

"$(INTDIR)\CP_Display.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Util\CP_printf.cpp

"$(INTDIR)\CP_printf.obj"	"$(INTDIR)\CP_printf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\FrameCounter.cpp

"$(INTDIR)\FrameCounter.obj"	"$(INTDIR)\FrameCounter.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GL_Engine.cpp

"$(INTDIR)\GL_Engine.obj"	"$(INTDIR)\GL_Engine.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GL_Font.cpp

"$(INTDIR)\GL_Font.obj"	"$(INTDIR)\GL_Font.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Util\PointerArray.cpp

"$(INTDIR)\PointerArray.obj"	"$(INTDIR)\PointerArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Util\PortTalkGrantIO.c

"$(INTDIR)\PortTalkGrantIO.obj"	"$(INTDIR)\PortTalkGrantIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Util\SafeArrayLib.cpp

"$(INTDIR)\SafeArrayLib.obj"	"$(INTDIR)\SafeArrayLib.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\VDisk.cpp

"$(INTDIR)\VDisk.obj"	"$(INTDIR)\VDisk.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VMain.cpp

"$(INTDIR)\VMain.obj"	"$(INTDIR)\VMain.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VMouse.cpp

"$(INTDIR)\VMouse.obj"	"$(INTDIR)\VMouse.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VObject.cpp

"$(INTDIR)\VObject.obj"	"$(INTDIR)\VObject.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VObject.idl
MTL_SWITCHES=

	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\VPolygon.cpp

"$(INTDIR)\VPolygon.obj"	"$(INTDIR)\VPolygon.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VText.cpp

"$(INTDIR)\VText.obj"	"$(INTDIR)\VText.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

