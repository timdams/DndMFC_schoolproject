# Microsoft Developer Studio Project File - Name="DnD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DnD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DnD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DnD.mak" CFG="DnD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DnD - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DnD - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DnD - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DnD - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DnD - Win32 Release"
# Name "DnD - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AniDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Barrel.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatView.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnView.cpp
# End Source File
# Begin Source File

SOURCE=.\DnD.cpp
# End Source File
# Begin Source File

SOURCE=.\DnD.rc
# End Source File
# Begin Source File

SOURCE=.\DnDDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DnDMapPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\DnDMapView1.cpp
# End Source File
# Begin Source File

SOURCE=.\DndSketchView.cpp
# End Source File
# Begin Source File

SOURCE=.\DnDView.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\MySocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PTGameObject.cpp
# End Source File
# Begin Source File

SOURCE=.\StatsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ACCESS.H
# End Source File
# Begin Source File

SOURCE=.\AniDialog.h
# End Source File
# Begin Source File

SOURCE=.\Barrel.h
# End Source File
# Begin Source File

SOURCE=.\ChatView.h
# End Source File
# Begin Source File

SOURCE=.\ColorListBox.h
# End Source File
# Begin Source File

SOURCE=.\ConnView.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\DnD.h
# End Source File
# Begin Source File

SOURCE=.\DnDDoc.h
# End Source File
# Begin Source File

SOURCE=.\DnDMapPlay.h
# End Source File
# Begin Source File

SOURCE=.\DnDMapView1.h
# End Source File
# Begin Source File

SOURCE=.\DndSketchView.h
# End Source File
# Begin Source File

SOURCE=.\DnDView.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapSettings.h
# End Source File
# Begin Source File

SOURCE=.\MySocket.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\PlayerInfo.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\PTGameObject.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StatsDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blankroo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\corridortile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DnD.ico
# End Source File
# Begin Source File

SOURCE=.\res\DnD.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DnDDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Tiles\doorhortile.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\doorverttile.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\fireorig.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\furnituretile.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\herotile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\info.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\partytile.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\pittile.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\roomtile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\Tiles\treasuretile.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DnD.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section DnD : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:22:CG_IDR_POPUP_CHAT_VIEW:105
# End Section
