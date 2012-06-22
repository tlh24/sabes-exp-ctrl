# Microsoft Developer Studio Project File - Name="CP_Display" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CP_Display - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CP_Display.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/CP_Display", PBAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CP_Display - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../nr/release"

!ELSEIF  "$(CFG)" == "CP_Display - Win32 Release MinDependency"

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
# ADD CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "CP_Display - Win32 Debug"
# Name "CP_Display - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\!readme.txt"
# End Source File
# Begin Source File

SOURCE=.\Util\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_Display.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_Display.idl
# ADD MTL /tlb ".\CP_Display.tlb" /h "CP_Display.h" /iid "CP_Display_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\CP_Display.rc
# End Source File
# Begin Source File

SOURCE=.\Util\CP_printf.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\GL_Engine.cpp
# End Source File
# Begin Source File

SOURCE=.\GL_Font.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\PointerArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\PortTalkGrantIO.c
# End Source File
# Begin Source File

SOURCE=.\Util\SafeArrayLib.cpp
# End Source File
# Begin Source File

SOURCE=.\VDisk.cpp
# End Source File
# Begin Source File

SOURCE=.\VMain.cpp
# End Source File
# Begin Source File

SOURCE=.\VMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\VObject.cpp
# End Source File
# Begin Source File

SOURCE=.\VObject.idl
# ADD MTL /tlb ""
# End Source File
# Begin Source File

SOURCE=.\VPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\VText.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ATL_Defs.h
# End Source File
# Begin Source File

SOURCE=.\BuildOptions.h
# End Source File
# Begin Source File

SOURCE=.\Util\Console.h
# End Source File
# Begin Source File

SOURCE=.\CP_Display.h
# End Source File
# Begin Source File

SOURCE=.\Util\CP_printf.h
# End Source File
# Begin Source File

SOURCE=.\FrameCounter.h
# End Source File
# Begin Source File

SOURCE=.\GL_Engine.h
# End Source File
# Begin Source File

SOURCE=.\GL_Font.h
# End Source File
# Begin Source File

SOURCE=.\Util\PointerArray.h
# End Source File
# Begin Source File

SOURCE=.\Util\PortTalkGrantIO.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Util\SafeArrayLib.h
# End Source File
# Begin Source File

SOURCE=.\VDisk.h
# End Source File
# Begin Source File

SOURCE=.\VMain.h
# End Source File
# Begin Source File

SOURCE=.\VMouse.h
# End Source File
# Begin Source File

SOURCE=.\VObject.h
# End Source File
# Begin Source File

SOURCE=.\VObjectMethodsDecl.h
# End Source File
# Begin Source File

SOURCE=.\VObjectMethodsImpl.h
# End Source File
# Begin Source File

SOURCE=.\VPolygon.h
# End Source File
# Begin Source File

SOURCE=.\VText.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CP_Display.rgs
# End Source File
# Begin Source File

SOURCE=.\VDisk.rgs
# End Source File
# Begin Source File

SOURCE=.\VMain.rgs
# End Source File
# Begin Source File

SOURCE=.\VMouse.rgs
# End Source File
# Begin Source File

SOURCE=.\VPolygon.rgs
# End Source File
# Begin Source File

SOURCE=.\VText.rgs
# End Source File
# Begin Source File

SOURCE=.\VWindow.rgs
# End Source File
# End Group
# End Target
# End Project
