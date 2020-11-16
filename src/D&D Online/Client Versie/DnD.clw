; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDnDMapPlay
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DnD.h"
LastPage=0

ClassCount=16
Class1=CDnDApp
Class2=CDnDDoc
Class3=CDnDView
Class4=CMainFrame

ResourceCount=14
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_DLGCREATEPLAYER
Resource4=IDR_MAINFRAME (English (U.S.))
Resource5=IDD_DLGHEADCHOOSE
Resource6=IDD_CHATVIEW (English (U.S.))
Class6=CConnView
Resource7=IDD_MAPPLAYVIEW (English (U.S.))
Class7=CChatView
Class8=CMySocket
Class9=CColorListBox
Resource8=IDD_CONNVIEW (English (U.S.))
Class10=CDndPlayer
Resource9=IDD_DLGPLAYERSET
Class11=CDndHeadMenu
Resource10=IDD_ABOUTBOX (English (U.S.))
Class12=CCreatePlayer
Resource11=IDD_DND_FORM (English (U.S.))
Class13=CProfManager
Class14=CAddProfile
Resource12=IDD_PROFMANAGERDLG
Class15=CDnDMapPlay
Resource13=IDD_ADDPROFILE
Class16=CChatOptions
Resource14=IDD_CHATOPTIONSDLG

[CLS:CDnDApp]
Type=0
HeaderFile=DnD.h
ImplementationFile=DnD.cpp
Filter=N
LastObject=CDnDApp

[CLS:CDnDDoc]
Type=0
HeaderFile=DnDDoc.h
ImplementationFile=DnDDoc.cpp
Filter=N
LastObject=CDnDDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDnDView]
Type=0
HeaderFile=DnDView.h
ImplementationFile=DnDView.cpp
Filter=D
LastObject=CDnDView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=DnD.cpp
ImplementationFile=DnD.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE

[DLG:IDD_DND_FORM (English (U.S.))]
Type=1
Class=CDnDView
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONNECT
Command10=ID_CHAT
Command11=ID_MAPPLAY
CommandCount=11

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CONNVIEW (English (U.S.))]
Type=1
Class=CConnView
ControlCount=22
Control1=IDC_BUTTONCONNECT,button,1342242817
Control2=IDC_CONNPROFILE,combobox,1344339971
Control3=IDC_PROFMANAGER,button,1342242816
Control4=IDC_IPADDRESS,SysIPAddress32,1342242816
Control5=IDC_EDITUSERNAME,edit,1350631554
Control6=IDC_EDITPASS,edit,1350631586
Control7=IDC_STATIC,button,1342177287
Control8=IDC_EDITPORT,edit,1484849280
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_LISTCONN,listbox,1352728833
Control12=IDC_DEBUGBTN,button,1342242816
Control13=IDC_PLAYERSET,button,1073807360
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1073741831
Control16=IDC_INFO,static,1342177294
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_USERPROFILE,combobox,1075904771
Control20=IDC_STATIC,static,1342308352
Control21=IDC_DEBUGBTN2,button,1073807360
Control22=IDC_STATIC,static,1342177294

[CLS:CConnView]
Type=0
HeaderFile=ConnView.h
ImplementationFile=ConnView.cpp
BaseClass=CFormView
Filter=D
LastObject=CConnView
VirtualFilter=VWC

[DLG:IDD_CHATVIEW (English (U.S.))]
Type=1
Class=CChatView
ControlCount=25
Control1=IDC_BUTTONSEND,button,1342242817
Control2=IDC_EDITCHAT,edit,1350631552
Control3=IDC_HEADME,static,1073742094
Control4=IDC_LISTCHAT,listbox,1352728833
Control5=IDC_SKETCHBLCOK,static,1073741830
Control6=IDC_STATIC,static,1073872896
Control7=IDC_HEAD1,static,1073742094
Control8=IDC_HEAD2,static,1073742094
Control9=IDC_HEAD3,static,1073742094
Control10=IDC_HEAD4,static,1073742094
Control11=IDC_HEAD5,static,1073742094
Control12=IDC_HEAD6,static,1073742094
Control13=IDC_HEAD7,static,1073742094
Control14=IDC_HEAD8,static,1073742094
Control15=IDC_STATIC,button,1342177287
Control16=IDC_CHARN1,static,1342308352
Control17=IDC_CHARN2,static,1342308352
Control18=IDC_CHARN3,static,1342308352
Control19=IDC_CHARN4,static,1342308352
Control20=IDC_CHARN5,static,1342308352
Control21=IDC_CHARN6,static,1342308352
Control22=IDC_CHARN7,static,1342308352
Control23=IDC_CHARN8,static,1342308352
Control24=IDC_STATIC,button,1342177287
Control25=IDC_CHATOPTIONS,button,1342242816

[CLS:CChatView]
Type=0
HeaderFile=ChatView.h
ImplementationFile=ChatView.cpp
BaseClass=CFormView
Filter=D
LastObject=CChatView
VirtualFilter=VWC

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CSocket
Filter=N

[CLS:CColorListBox]
Type=0
HeaderFile=ColorListBox.h
ImplementationFile=ColorListBox.cpp
BaseClass=CAnimateCtrl
Filter=W

[DLG:IDD_DLGPLAYERSET]
Type=1
Class=CDndPlayer
ControlCount=33
Control1=IDC_COMBOCHARS,combobox,1344340035
Control2=IDOK,button,1342242817
Control3=IDC_NEWCHAR,button,1342242816
Control4=IDC_EDITUNCHAR,edit,1350631552
Control5=IDC_UNOWNED,button,1342242816
Control6=IDC_HEAD,static,1342177294
Control7=IDC_STATIC,button,1073741831
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATNAME,static,1342308352
Control10=IDC_STATCLASS,static,1342308352
Control11=IDC_STATGENDER,static,1342308352
Control12=IDC_STATRACE,static,1342308352
Control13=IDC_STATDEITY,static,1342308352
Control14=IDC_STATAGE,static,1342308352
Control15=IDC_STATALIGNMENT,static,1342308352
Control16=IDC_STATDESCRIPTION,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATSTR,static,1342308352
Control20=IDC_STATDEX,static,1342308352
Control21=IDC_STATCON,static,1342308352
Control22=IDC_STATINT,static,1342308352
Control23=IDC_STATWIS,static,1342308352
Control24=IDC_STATCHA,static,1342308352
Control25=IDC_INFO,static,1342177294
Control26=IDC_STATIC,static,1342308352
Control27=IDC_INFO2,static,1342177294
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,static,1342308352

[CLS:CDndPlayer]
Type=0
HeaderFile=DndPlayer.h
ImplementationFile=DndPlayer.cpp
BaseClass=CDialog
Filter=D
LastObject=CDndPlayer
VirtualFilter=dWC

[DLG:IDD_DLGHEADCHOOSE]
Type=1
Class=CDndHeadMenu
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDC_PREVHEAD,button,1476460544
Control3=IDC_NEXTHEAD,button,1476460544
Control4=IDCANCEL,button,1342242816
Control5=IDC_HEAD1,static,1342177550
Control6=IDC_HEAD2,static,1342177550
Control7=IDC_HEAD3,static,1342177550
Control8=IDC_HEAD4,static,1342177550
Control9=IDC_HEAD5,static,1342177550
Control10=IDC_HEAD6,static,1342177550
Control11=IDC_HEAD7,static,1342177550
Control12=IDC_HEAD8,static,1342177550
Control13=IDC_HEAD9,static,1342177550
Control14=IDC_HEAD10,static,1342177550
Control15=IDC_INFO,static,1342177294
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_HEADCHOSEN,static,1342177550

[CLS:CDndHeadMenu]
Type=0
HeaderFile=DndHeadMenu.h
ImplementationFile=DndHeadMenu.cpp
BaseClass=CDialog
Filter=D
LastObject=CDndHeadMenu
VirtualFilter=dWC

[DLG:IDD_DLGCREATEPLAYER]
Type=1
Class=CCreatePlayer
ControlCount=69
Control1=IDOK,button,1342242817
Control2=IDC_GENRAND,button,1342242816
Control3=IDC_CHARNAME,edit,1350631552
Control4=IDC_GENDER,combobox,1344339971
Control5=IDC_RACE,combobox,1344340227
Control6=IDC_CLASS,combobox,1344340227
Control7=IDC_DEITY,combobox,1344340227
Control8=IDC_ALIGNMENT,combobox,1344340227
Control9=IDC_AGE,edit,1350639744
Control10=IDC_FAMILIAR,combobox,1478557955
Control11=IDC_BTNPORTRAIT,button,1342242816
Control12=IDC_DESC,edit,1351684292
Control13=IDC_GENSTATS,button,1476460544
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_HEAD,static,1342177294
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STR,edit,1350641794
Control27=IDC_DEX,edit,1350641794
Control28=IDC_CON,edit,1350641794
Control29=IDC_INT,edit,1350641794
Control30=IDC_WIS,edit,1350641794
Control31=IDC_CHA,edit,1350641794
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STRMOD,static,1342308352
Control34=IDC_DEXMOD,static,1342308352
Control35=IDC_CONMOD,static,1342308352
Control36=IDC_INTMOD,static,1342308352
Control37=IDC_WISMOD,static,1342308352
Control38=IDC_CHAMOD,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATFAM,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_LANGUAGES,button,1342177287
Control45=IDC_LANG,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_HITPOINTS,edit,1350641792
Control48=IDC_STATIC,static,1342308352
Control49=IDC_AC,edit,1350633600
Control50=IDC_STATIC,button,1342177287
Control51=IDC_STATIC,static,1342308352
Control52=IDC_STATIC,static,1342308352
Control53=IDC_STATIC,static,1342308352
Control54=IDC_FORT,edit,1350641794
Control55=IDC_REFLEX,edit,1350641794
Control56=IDC_WILL,edit,1350641794
Control57=IDC_STATIC,button,1342177287
Control58=IDC_STATIC,static,1342308352
Control59=IDC_STATIC,static,1342308352
Control60=IDC_STATIC,static,1342308352
Control61=IDC_INITIATIVE,edit,1350641794
Control62=IDC_MELEE,edit,1350641794
Control63=IDC_RANGED,edit,1350641794
Control64=IDC_INFO,static,1342177294
Control65=IDC_STATIC,static,1342308352
Control66=IDC_STATIC,button,1342177287
Control67=IDC_STATIC,button,1342177287
Control68=IDC_STATIC,button,1342177287
Control69=IDC_STATIC,button,1342177287

[CLS:CCreatePlayer]
Type=0
HeaderFile=CreatePlayer.h
ImplementationFile=CreatePlayer.cpp
BaseClass=CDialog
Filter=D
LastObject=CCreatePlayer
VirtualFilter=dWC

[DLG:IDD_PROFMANAGERDLG]
Type=1
Class=CProfManager
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDC_ADD,button,1342242816
Control3=IDC_CHANGE,button,1342242816
Control4=IDC_DELETE,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_FILE,edit,1484849280
Control7=IDC_BROWSEFILE,button,1476460544
Control8=IDC_PROFILES,listbox,1353777409
Control9=IDC_STATFILE,static,1476526080
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_SAVECHANGES,button,1208025088
Control13=IDC_INFO,static,1342177294
Control14=IDC_STATIC,static,1342308352
Control15=IDC_CHANGEPATH,button,1342242819

[CLS:CProfManager]
Type=0
HeaderFile=ProfManager.h
ImplementationFile=ProfManager.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHANGE
VirtualFilter=dWC

[DLG:IDD_ADDPROFILE]
Type=1
Class=CAddProfile
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_PROFNAME,edit,1350631552
Control3=IDC_SERVIP,SysIPAddress32,1342242816
Control4=IDC_USERNAME,edit,1350631552
Control5=IDC_PASS,edit,1350631584
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[CLS:CAddProfile]
Type=0
HeaderFile=AddProfile.h
ImplementationFile=AddProfile.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAddProfile

[DLG:IDD_MAPPLAYVIEW (English (U.S.))]
Type=1
Class=CDnDMapPlay
ControlCount=4
Control1=IDC_BTNCHAT,button,1342242816
Control2=IDC_MAPCHAT,edit,1350631552
Control3=IDC_MAPAREA,static,1073741830
Control4=IDC_LIST1,listbox,1352728833

[CLS:CDnDMapPlay]
Type=0
HeaderFile=DnDMapPlay.h
ImplementationFile=DnDMapPlay.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_MAPCHAT
VirtualFilter=VWC

[DLG:IDD_CHATOPTIONSDLG]
Type=1
Class=CChatOptions
ControlCount=7
Control1=IDC_RES,edit,1350639744
Control2=IDC_SPINRES,msctls_updown32,1342177334
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_INFO,static,1342177294
Control7=IDC_STATIC,static,1342308352

[CLS:CChatOptions]
Type=0
HeaderFile=ChatOptions.h
ImplementationFile=ChatOptions.cpp
BaseClass=CDialog
Filter=D
LastObject=CChatOptions
VirtualFilter=dWC

