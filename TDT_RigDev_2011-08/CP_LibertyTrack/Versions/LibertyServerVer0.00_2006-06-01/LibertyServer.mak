# Microsoft Developer Studio Generated NMAKE File, Based on LibertyServer.dsp
!IF "$(CFG)" == ""
CFG=LibertyServer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LibertyServer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LibertyServer - Win32 Debug" && "$(CFG)" != "LibertyServer - Win32 Unicode Debug" && "$(CFG)" != "LibertyServer - Win32 Release MinSize" && "$(CFG)" != "LibertyServer - Win32 Release MinDependency" && "$(CFG)" != "LibertyServer - Win32 Unicode Release MinSize" && "$(CFG)" != "LibertyServer - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibertyServer.mak" CFG="LibertyServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibertyServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "LibertyServer - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "LibertyServer - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "LibertyServer - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "LibertyServer - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "LibertyServer - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "LibertyServer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LibertyServer.exe" "$(OUTDIR)\LibertyServer.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComUtils.obj"
	-@erase "$(INTDIR)\ComUtils.sbr"
	-@erase "$(INTDIR)\Liberty.obj"
	-@erase "$(INTDIR)\Liberty.sbr"
	-@erase "$(INTDIR)\LibertyServer.obj"
	-@erase "$(INTDIR)\LibertyServer.pch"
	-@erase "$(INTDIR)\LibertyServer.res"
	-@erase "$(INTDIR)\LibertyServer.sbr"
	-@erase "$(INTDIR)\nrutil_for_regression.obj"
	-@erase "$(INTDIR)\nrutil_for_regression.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LibertyServer.bsc"
	-@erase "$(OUTDIR)\LibertyServer.exe"
	-@erase "$(OUTDIR)\LibertyServer.ilk"
	-@erase "$(OUTDIR)\LibertyServer.pdb"
	-@erase ".\LibertyServer.h"
	-@erase ".\LibertyServer.tlb"
	-@erase ".\LibertyServer_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /I "C:\Program Files\Polhemus\PDI\Inc" /I "..\common" /I "..\numrec" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LibertyServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LibertyServer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibertyServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Liberty.sbr" \
	"$(INTDIR)\LibertyServer.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\ComUtils.sbr" \
	"$(INTDIR)\nrutil_for_regression.sbr"

"$(OUTDIR)\LibertyServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib PDID.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LibertyServer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LibertyServer.exe" /pdbtype:sept /libpath:"PDI" /libpath:"c:\lab\src\numrec\release" 
LINK32_OBJS= \
	"$(INTDIR)\Liberty.obj" \
	"$(INTDIR)\LibertyServer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibertyServer.res" \
	"$(INTDIR)\ComUtils.obj" \
	"$(INTDIR)\nrutil_for_regression.obj"

"$(OUTDIR)\LibertyServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\LibertyServer.exe
InputPath=.\Debug\LibertyServer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\LibertyServer.exe" ".\LibertyServer.tlb" ".\LibertyServer.h" ".\LibertyServer_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComUtils.obj"
	-@erase "$(INTDIR)\Liberty.obj"
	-@erase "$(INTDIR)\LibertyServer.obj"
	-@erase "$(INTDIR)\LibertyServer.pch"
	-@erase "$(INTDIR)\LibertyServer.res"
	-@erase "$(INTDIR)\nrutil_for_regression.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LibertyServer.exe"
	-@erase "$(OUTDIR)\LibertyServer.ilk"
	-@erase "$(OUTDIR)\LibertyServer.pdb"
	-@erase ".\LibertyServer.h"
	-@erase ".\LibertyServer.tlb"
	-@erase ".\LibertyServer_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\LibertyServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LibertyServer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibertyServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LibertyServer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LibertyServer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Liberty.obj" \
	"$(INTDIR)\LibertyServer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibertyServer.res" \
	"$(INTDIR)\ComUtils.obj" \
	"$(INTDIR)\nrutil_for_regression.obj"

"$(OUTDIR)\LibertyServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\LibertyServer.exe
InputPath=.\DebugU\LibertyServer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LibertyServer.exe" ".\LibertyServer.tlb" ".\LibertyServer.h" ".\LibertyServer_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComUtils.obj"
	-@erase "$(INTDIR)\Liberty.obj"
	-@erase "$(INTDIR)\LibertyServer.obj"
	-@erase "$(INTDIR)\LibertyServer.pch"
	-@erase "$(INTDIR)\LibertyServer.res"
	-@erase "$(INTDIR)\nrutil_for_regression.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LibertyServer.exe"
	-@erase ".\LibertyServer.h"
	-@erase ".\LibertyServer.tlb"
	-@erase ".\LibertyServer_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LibertyServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibertyServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LibertyServer.pdb" /machine:I386 /out:"$(OUTDIR)\LibertyServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Liberty.obj" \
	"$(INTDIR)\LibertyServer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibertyServer.res" \
	"$(INTDIR)\ComUtils.obj" \
	"$(INTDIR)\nrutil_for_regression.obj"

"$(OUTDIR)\LibertyServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\LibertyServer.exe
InputPath=.\ReleaseMinSize\LibertyServer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LibertyServer.exe" ".\LibertyServer.tlb" ".\LibertyServer.h" ".\LibertyServer_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComUtils.obj"
	-@erase "$(INTDIR)\Liberty.obj"
	-@erase "$(INTDIR)\LibertyServer.obj"
	-@erase "$(INTDIR)\LibertyServer.pch"
	-@erase "$(INTDIR)\LibertyServer.res"
	-@erase "$(INTDIR)\nrutil_for_regression.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LibertyServer.exe"
	-@erase ".\LibertyServer.h"
	-@erase ".\LibertyServer.tlb"
	-@erase ".\LibertyServer_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LibertyServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibertyServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LibertyServer.pdb" /machine:I386 /out:"$(OUTDIR)\LibertyServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Liberty.obj" \
	"$(INTDIR)\LibertyServer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibertyServer.res" \
	"$(INTDIR)\ComUtils.obj" \
	"$(INTDIR)\nrutil_for_regression.obj"

"$(OUTDIR)\LibertyServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\LibertyServer.exe
InputPath=.\ReleaseMinDependency\LibertyServer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LibertyServer.exe" ".\LibertyServer.tlb" ".\LibertyServer.h" ".\LibertyServer_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComUtils.obj"
	-@erase "$(INTDIR)\Liberty.obj"
	-@erase "$(INTDIR)\LibertyServer.obj"
	-@erase "$(INTDIR)\LibertyServer.pch"
	-@erase "$(INTDIR)\LibertyServer.res"
	-@erase "$(INTDIR)\nrutil_for_regression.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LibertyServer.exe"
	-@erase ".\LibertyServer.h"
	-@erase ".\LibertyServer.tlb"
	-@erase ".\LibertyServer_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LibertyServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibertyServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LibertyServer.pdb" /machine:I386 /out:"$(OUTDIR)\LibertyServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Liberty.obj" \
	"$(INTDIR)\LibertyServer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibertyServer.res" \
	"$(INTDIR)\ComUtils.obj" \
	"$(INTDIR)\nrutil_for_regression.obj"

"$(OUTDIR)\LibertyServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\LibertyServer.exe
InputPath=.\ReleaseUMinSize\LibertyServer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LibertyServer.exe" ".\LibertyServer.tlb" ".\LibertyServer.h" ".\LibertyServer_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComUtils.obj"
	-@erase "$(INTDIR)\Liberty.obj"
	-@erase "$(INTDIR)\LibertyServer.obj"
	-@erase "$(INTDIR)\LibertyServer.pch"
	-@erase "$(INTDIR)\LibertyServer.res"
	-@erase "$(INTDIR)\nrutil_for_regression.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LibertyServer.exe"
	-@erase ".\LibertyServer.h"
	-@erase ".\LibertyServer.tlb"
	-@erase ".\LibertyServer_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LibertyServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibertyServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LibertyServer.pdb" /machine:I386 /out:"$(OUTDIR)\LibertyServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Liberty.obj" \
	"$(INTDIR)\LibertyServer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibertyServer.res" \
	"$(INTDIR)\ComUtils.obj" \
	"$(INTDIR)\nrutil_for_regression.obj"

"$(OUTDIR)\LibertyServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\LibertyServer.exe
InputPath=.\ReleaseUMinDependency\LibertyServer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
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
!IF EXISTS("LibertyServer.dep")
!INCLUDE "LibertyServer.dep"
!ELSE 
!MESSAGE Warning: cannot find "LibertyServer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LibertyServer - Win32 Debug" || "$(CFG)" == "LibertyServer - Win32 Unicode Debug" || "$(CFG)" == "LibertyServer - Win32 Release MinSize" || "$(CFG)" == "LibertyServer - Win32 Release MinDependency" || "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize" || "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"
SOURCE=.\common\ComUtils.cpp

!IF  "$(CFG)" == "LibertyServer - Win32 Debug"


"$(INTDIR)\ComUtils.obj"	"$(INTDIR)\ComUtils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Debug"


"$(INTDIR)\ComUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinSize"


"$(INTDIR)\ComUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinDependency"


"$(INTDIR)\ComUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize"


"$(INTDIR)\ComUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"


"$(INTDIR)\ComUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Liberty.cpp

!IF  "$(CFG)" == "LibertyServer - Win32 Debug"


"$(INTDIR)\Liberty.obj"	"$(INTDIR)\Liberty.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch" ".\LibertyServer.h"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Debug"


"$(INTDIR)\Liberty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinSize"


"$(INTDIR)\Liberty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinDependency"


"$(INTDIR)\Liberty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize"


"$(INTDIR)\Liberty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"


"$(INTDIR)\Liberty.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ENDIF 

SOURCE=.\LibertyServer.cpp

!IF  "$(CFG)" == "LibertyServer - Win32 Debug"


"$(INTDIR)\LibertyServer.obj"	"$(INTDIR)\LibertyServer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch" ".\LibertyServer.h" ".\LibertyServer_i.c"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Debug"


"$(INTDIR)\LibertyServer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinSize"


"$(INTDIR)\LibertyServer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinDependency"


"$(INTDIR)\LibertyServer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize"


"$(INTDIR)\LibertyServer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"


"$(INTDIR)\LibertyServer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"


!ENDIF 

SOURCE=.\LibertyServer.idl
MTL_SWITCHES=/tlb ".\LibertyServer.tlb" /h "LibertyServer.h" /iid "LibertyServer_i.c" /Oicf 

".\LibertyServer.tlb"	".\LibertyServer.h"	".\LibertyServer_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\LibertyServer.rc

"$(INTDIR)\LibertyServer.res" : $(SOURCE) "$(INTDIR)" ".\LibertyServer.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\common\nrutil_for_regression.cpp

!IF  "$(CFG)" == "LibertyServer - Win32 Debug"


"$(INTDIR)\nrutil_for_regression.obj"	"$(INTDIR)\nrutil_for_regression.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Debug"


"$(INTDIR)\nrutil_for_regression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinSize"


"$(INTDIR)\nrutil_for_regression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinDependency"


"$(INTDIR)\nrutil_for_regression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize"


"$(INTDIR)\nrutil_for_regression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"


"$(INTDIR)\nrutil_for_regression.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibertyServer.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LibertyServer - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /I "C:\Program Files\Polhemus\PDI\Inc" /I "..\common" /I "..\numrec" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LibertyServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LibertyServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\LibertyServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibertyServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibertyServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibertyServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibertyServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibertyServer - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LibertyServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibertyServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

