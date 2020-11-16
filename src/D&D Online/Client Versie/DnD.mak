# Microsoft Developer Studio Generated NMAKE File, Based on DnD.dsp
!IF "$(CFG)" == ""
CFG=DnD - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DnD - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DnD - Win32 Release" && "$(CFG)" != "DnD - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DnD - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\DnD.exe"


CLEAN :
	-@erase "$(INTDIR)\ChatView.obj"
	-@erase "$(INTDIR)\ColorListBox.obj"
	-@erase "$(INTDIR)\ConnView.obj"
	-@erase "$(INTDIR)\DnD.obj"
	-@erase "$(INTDIR)\DnD.pch"
	-@erase "$(INTDIR)\DnD.res"
	-@erase "$(INTDIR)\DnDDoc.obj"
	-@erase "$(INTDIR)\DnDView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MySocket.obj"
	-@erase "$(INTDIR)\PTGameObject.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DnD.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\DnD.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x813 /fo"$(INTDIR)\DnD.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DnD.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\DnD.pdb" /machine:I386 /out:"$(OUTDIR)\DnD.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChatView.obj" \
	"$(INTDIR)\ColorListBox.obj" \
	"$(INTDIR)\ConnView.obj" \
	"$(INTDIR)\DnD.obj" \
	"$(INTDIR)\DnDDoc.obj" \
	"$(INTDIR)\DnDView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MySocket.obj" \
	"$(INTDIR)\PTGameObject.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DnD.res"

"$(OUTDIR)\DnD.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DnD - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Client.exe"


CLEAN :
	-@erase "$(INTDIR)\ChatView.obj"
	-@erase "$(INTDIR)\ColorListBox.obj"
	-@erase "$(INTDIR)\ConnView.obj"
	-@erase "$(INTDIR)\DnD.obj"
	-@erase "$(INTDIR)\DnD.pch"
	-@erase "$(INTDIR)\DnD.res"
	-@erase "$(INTDIR)\DnDDoc.obj"
	-@erase "$(INTDIR)\DnDView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MySocket.obj"
	-@erase "$(INTDIR)\PTGameObject.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Client.exe"
	-@erase "$(OUTDIR)\Client.ilk"
	-@erase "$(OUTDIR)\Client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\DnD.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x813 /fo"$(INTDIR)\DnD.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DnD.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Client.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Client.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChatView.obj" \
	"$(INTDIR)\ColorListBox.obj" \
	"$(INTDIR)\ConnView.obj" \
	"$(INTDIR)\DnD.obj" \
	"$(INTDIR)\DnDDoc.obj" \
	"$(INTDIR)\DnDView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MySocket.obj" \
	"$(INTDIR)\PTGameObject.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\DnD.res"

"$(OUTDIR)\Client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DnD.dep")
!INCLUDE "DnD.dep"
!ELSE 
!MESSAGE Warning: cannot find "DnD.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DnD - Win32 Release" || "$(CFG)" == "DnD - Win32 Debug"
SOURCE=.\ChatView.cpp

"$(INTDIR)\ChatView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\ColorListBox.cpp

"$(INTDIR)\ColorListBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\ConnView.cpp

"$(INTDIR)\ConnView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\DnD.cpp

"$(INTDIR)\DnD.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\DnD.rc

"$(INTDIR)\DnD.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DnDDoc.cpp

"$(INTDIR)\DnDDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\DnDView.cpp

"$(INTDIR)\DnDView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\MySocket.cpp

"$(INTDIR)\MySocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\PTGameObject.cpp

"$(INTDIR)\PTGameObject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DnD.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DnD - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\DnD.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DnD.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DnD - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\DnD.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DnD.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

