# Microsoft Developer Studio Project File - Name="CP_TDT_Stream" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CP_TDT_Stream - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CP_TDT_Stream.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CP_TDT_Stream - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CP_TDT_Stream___Win32_Debug"
# PROP BASE Intermediate_Dir "CP_TDT_Stream___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /W3 /Gm /GX /Zi /Od /I ".\Util" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /D "_ATL_DLL_IMPL" /D _WIN32_WINDOWS=0x0500 /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libcmtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib comsupp.lib atl.lib shlwapi.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib /pdbtype:sept /libpath:"VisualLeakDetector\\"

!ELSEIF  "$(CFG)" == "CP_TDT_Stream - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MT /W3 /GR /O2 /I ".\Util" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /D "_ATL_DLL_IMPL" /D _WIN32_WINDOWS=0x0500 /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 libcmt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib comsupp.lib atl.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /libpath:".\Lib"

!ENDIF 

# Begin Target

# Name "CP_TDT_Stream - Win32 Debug"
# Name "CP_TDT_Stream - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\cp_printf.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_TDT_Stream.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_TDT_Stream.rc
# End Source File
# Begin Source File

SOURCE=.\CP_TDT_StreamCom.idl
# ADD MTL /tlb "CP_TDT_StreamCom.tlb"
# End Source File
# Begin Source File

SOURCE=.\CP_TDT_StreamCom_i.c
# End Source File
# Begin Source File

SOURCE=.\CP_TS_Class.cpp
# End Source File
# Begin Source File

SOURCE=.\DataFile.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterCom.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream_Glob.cpp
# End Source File
# Begin Source File

SOURCE=.\TDT_Stream.cpp
# End Source File
# Begin Source File

SOURCE=.\TimerThread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ClassFactory.h
# End Source File
# Begin Source File

SOURCE=.\Util\Console.h
# End Source File
# Begin Source File

SOURCE=.\Util\CP_printf.h
# End Source File
# Begin Source File

SOURCE=.\CP_TDT_Err.h
# End Source File
# Begin Source File

SOURCE=.\CP_TDT_StreamCom.h
# End Source File
# Begin Source File

SOURCE=.\CP_TS_Class.h
# End Source File
# Begin Source File

SOURCE=.\DataFile.h
# End Source File
# Begin Source File

SOURCE=.\RegisterCom.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Stream_Glob.h
# End Source File
# Begin Source File

SOURCE=.\TDT_Stream.h
# End Source File
# Begin Source File

SOURCE=.\TimerThread.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CP_TDT_Stream.ico
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CP_TDT_Streamps.mk
# End Source File
# End Group
# End Target
# End Project
# Section CP_TDT_Stream : {00000000-0000-0000-0000-800000800000}
# 	1:13:IDD_VIDDIALOG:101
# End Section
