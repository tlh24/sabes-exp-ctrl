# Microsoft Developer Studio Project File - Name="CP_LibertyTrack" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CP_LibertyTrack - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CP_LibertyTrack.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CP_LibertyTrack - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "./Release" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib pdi.lib /nologo /subsystem:windows /machine:I386 /libpath:"Liberty"

!ELSEIF  "$(CFG)" == "CP_LibertyTrack - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /W3 /Gm /GX /ZI /Od /I ".\Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /D "_DEBUG" /win32
# SUBTRACT MTL /nologo /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "./Debug" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib pdi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"Liberty"

!ENDIF 

# Begin Target

# Name "CP_LibertyTrack - Win32 Release"
# Name "CP_LibertyTrack - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\!readme.txt"
# End Source File
# Begin Source File

SOURCE=.\ClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyClass.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyTrack_TODO.txt
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyTrackCom.idl
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyTrackCom_i.c
# End Source File
# Begin Source File

SOURCE=.\Util\CP_printf.cpp
# End Source File
# Begin Source File

SOURCE=.\LibertyTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\LibertyTrackGlob.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterCom.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\SafeArrayLib.cpp
# End Source File
# Begin Source File

SOURCE=.\SlideBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeStamp.cpp
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

SOURCE=.\CP_ET_Class.h
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyClass.h
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyTrackCom.h
# End Source File
# Begin Source File

SOURCE=.\Util\CP_printf.h
# End Source File
# Begin Source File

SOURCE=.\LibertyTrack.h
# End Source File
# Begin Source File

SOURCE=.\LibertyTrackGlob.h
# End Source File
# Begin Source File

SOURCE=.\RegisterCom.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Util\SafeArrayLib.h
# End Source File
# Begin Source File

SOURCE=.\SlideBuf.h
# End Source File
# Begin Source File

SOURCE=.\TimeStamp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CP_LibertyTrack.ico
# End Source File
# Begin Source File

SOURCE=.\CP_LibertyTrack.rc
# End Source File
# Begin Source File

SOURCE=.\Debug\CP_LibertyTrackCom.tlb
# End Source File
# End Group
# End Target
# End Project
