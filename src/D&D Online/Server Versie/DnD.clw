; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProgressDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DnD.h"
LastPage=0

ClassCount=13
Class1=CDnDApp
Class2=CDnDDoc
Class3=CDnDView
Class4=CMainFrame

ResourceCount=15
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_DND_FORM
Resource4=CG_IDD_PROGRESS (English (U.S.))
Resource5=CG_IDR_POPUP_CHAT_VIEW
Resource6=IDD_MAPVIEW (English (U.S.))
Class6=CConnView
Resource7=IDD_CONNVIEW (English (U.S.))
Class7=CChatView
Resource8=IDD_MAPPLAY (English (U.S.))
Resource9=IDD_SKETCHVIEW (English (U.S.))
Resource10=IDD_CHATVIEW (English (U.S.))
Class8=DndSketchView
Resource11=IDD_DND_FORM (English (U.S.))
Class9=DnDMapView
Class10=MapSettings
Resource12=IDD_ABOUTBOX (English (U.S.))
Class11=CDnDMapPlay
Resource13=IDD_MAPSETDLG
Class12=CStatsDialog
Resource14=IDR_MAINFRAME (English (U.S.))
Class13=CProgressDlg
Resource15=IDD_STATSDIALOG

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
LastObject=ID_MAPPLAY




[CLS:CAboutDlg]
Type=0
HeaderFile=DnD.cpp
ImplementationFile=DnD.cpp
Filter=D

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

[DLG:IDD_DND_FORM]
Type=1
Class=CDnDView

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
Command10=ID_SKETCH
Command11=ID_MAP
Command12=ID_MAPPLAY
Command13=ID_CHAT
CommandCount=13

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_ABOUT
CommandCount=1

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
ControlCount=15
Control1=IDC_BTN_STARTSVR,button,1342242816
Control2=IDC_SVRSTATLIST,listbox,1352728929
Control3=IDC_PORT,edit,1216422016
Control4=IDC_STATIC,static,1073872896
Control5=IDC_BTIMEOUT,button,1073807363
Control6=IDC_BUTTON1,button,1073807360
Control7=IDC_STATIC,static,1342179342
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_IP1,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_CONHOST,static,1342308352
Control14=IDC_Link,static,1342308352
Control15=IDC_STATIC,static,1342308352

[CLS:CConnView]
Type=0
HeaderFile=ConnView.h
ImplementationFile=ConnView.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_Link
VirtualFilter=VWC

[DLG:IDD_CHATVIEW (English (U.S.))]
Type=1
Class=CChatView
ControlCount=17
Control1=IDC_BTNSEND,button,1342242816
Control2=IDC_EDITTOSENDCHAT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_HEAD7,static,1073742094
Control7=IDC_COMMANDBOX,combobox,1075904771
Control8=IDC_USERLIST,listbox,1084295521
Control9=IDC_CHATBOX,listbox,1353777505
Control10=IDC_HEAD1,static,1073742094
Control11=IDC_HEAD2,static,1073742094
Control12=IDC_HEAD3,static,1073742094
Control13=IDC_HEAD4,static,1073742094
Control14=IDC_HEAD5,static,1073742094
Control15=IDC_HEAD6,static,1073742094
Control16=IDC_HEAD8,static,1073742094
Control17=IDC_STATIC,static,1342177294

[CLS:CChatView]
Type=0
HeaderFile=ChatView.h
ImplementationFile=ChatView.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_EDITTOSENDCHAT
VirtualFilter=VWC

[MNU:CG_IDR_POPUP_CHAT_VIEW]
Type=1
Class=CChatView
Command1=ID_POPUP_PLAYERSTATS
Command2=ID_POPUP_BAN
Command3=ID_POPUP_KICK
CommandCount=3

[DLG:IDD_SKETCHVIEW (English (U.S.))]
Type=1
Class=DndSketchView
ControlCount=18
Control1=IDC_SKETCHBLOCK,static,1073741830
Control2=IDC_LINETOOL,button,1342242944
Control3=IDC_CIRCLETOOL,button,1342242944
Control4=IDC_SELECTTOOL,button,1208025216
Control5=IDC_LOADIMAGEBTN,button,1342242944
Control6=IDC_SENDIMAGE,button,1342242816
Control7=IDC_COLPICKOUT,button,1342242816
Control8=IDC_COLPICKIN,button,1342242816
Control9=IDC_CLEAR,button,1342242816
Control10=IDC_LIVEUPDATE,button,1342242819
Control11=IDC_SKETCHBLOCK2,static,1073741830
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342177294
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_COLIN,static,1073741828
Control18=IDC_COLOUT,static,1073741828

[CLS:DndSketchView]
Type=0
HeaderFile=DndSketchView.h
ImplementationFile=DndSketchView.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_SKETCHBLOCK2
VirtualFilter=VWC

[DLG:IDD_MAPVIEW (English (U.S.))]
Type=1
Class=DnDMapView
ControlCount=33
Control1=IDC_SETTINGS,button,1342242816
Control2=IDC_SAVEMAP,button,1342242816
Control3=IDC_LOADMAP,button,1342242816
Control4=IDC_MAPNAME,edit,1350631552
Control5=IDC_MAP,static,1073741830
Control6=IDC_ROOMTOOL,button,1342242816
Control7=IDC_TOOLCORRIDOR,button,1342242816
Control8=IDC_ROOMCOMBO,combobox,1344339971
Control9=IDC_CURRENTTOOL,static,1342308352
Control10=IDC_TOOLDOOR,button,1342242816
Control11=IDC_DOORCOMBO,combobox,1344339971
Control12=IDC_UNDO,button,1073807360
Control13=IDC_STATIC,button,1342177287
Control14=IDC_ERASER,button,1342242816
Control15=IDC_ITEMS,button,1342242816
Control16=IDC_ITEMSCOMBO,combobox,1344339970
Control17=IDC_CLEARMAP,button,1342242816
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_PLAYERS,button,1342242816
Control21=IDC_COMBOPLAYERS,combobox,1344339970
Control22=IDC_TOOLSELECT,button,1342242816
Control23=IDC_MONSTER,button,1342242816
Control24=IDC_COMBOMONSTER,combobox,1344340226
Control25=IDC_STATIC,button,1342177287
Control26=IDC_DELETESM,button,1476460544
Control27=IDC_STATINFOBL,static,1342308352
Control28=IDC_STATINFOBL2,static,1342308352
Control29=IDC_STATINFOBL3,static,1342308352
Control30=IDC_LAYERCOMBO,combobox,1344339970
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1073872896
Control33=IDC_STATDEB,static,1342308352

[CLS:DnDMapView]
Type=0
HeaderFile=DnDMapView1.h
ImplementationFile=DnDMapView1.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=DnDMapView

[DLG:IDD_MAPSETDLG]
Type=1
Class=MapSettings
ControlCount=12
Control1=IDC_BLOCKS,edit,1350639744
Control2=IDC_SPIN1,msctls_updown32,1342177334
Control3=IDC_DISPGRID,button,1342242819
Control4=IDC_CHECKHIRES,button,1342242819
Control5=IDC_CHECKCP,button,1342242819
Control6=IDC_CLEARBUTTON,button,1342242816
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342177294
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287

[CLS:MapSettings]
Type=0
HeaderFile=MapSettings.h
ImplementationFile=MapSettings.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECKCP
VirtualFilter=dWC

[DLG:IDD_MAPPLAY (English (U.S.))]
Type=1
Class=CDnDMapPlay
ControlCount=21
Control1=IDC_CHATSEND,button,1342242816
Control2=IDC_CHATMAP,edit,1350631552
Control3=IDC_Start,button,1342242816
Control4=IDC_LOADMAP,button,1342242816
Control5=IDC_VISCOMBO,combobox,1344339970
Control6=IDC_UNHIDE,button,1073807360
Control7=IDC_CHECKNAME,button,1342242819
Control8=IDC_CHECKNAME2,button,1342242819
Control9=IDC_UP,button,1342242816
Control10=IDC_RIGHT,button,1342242816
Control11=IDC_DOWN,button,1342242816
Control12=IDC_LEFT,button,1342242816
Control13=IDC_MAP,static,1073741830
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATMAPTITLE,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_COMBOAREA,combobox,1478557698
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342177294
Control21=IDC_CHATINMAP,listbox,1353777408

[CLS:CDnDMapPlay]
Type=0
HeaderFile=DnDMapPlay.h
ImplementationFile=DnDMapPlay.cpp
BaseClass=CFormView
Filter=D
LastObject=CDnDMapPlay
VirtualFilter=VWC

[DLG:IDD_STATSDIALOG]
Type=1
Class=CStatsDialog
ControlCount=28
Control1=IDOK,button,1342242817
Control2=IDC_ARMOR,edit,1350631552
Control3=IDC_ITEMS,edit,1350631552
Control4=IDC_STRENGTH,edit,1350631552
Control5=IDC_DEXTERITY,edit,1350631552
Control6=IDC_CONSTITUTION,edit,1350631552
Control7=IDC_INTELLIGENCE,edit,1350631552
Control8=IDC_WISDOM,edit,1350631552
Control9=IDC_CHARISMA,edit,1350631552
Control10=IDC_USERNAME,edit,1350633602
Control11=IDC_CHARNAME,edit,1350633602
Control12=IDDOCHANGES,button,1342242816
Control13=IDBAN,button,1342242816
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308354
Control19=IDC_STATIC,static,1342308354
Control20=IDC_STATIC,static,1342308354
Control21=IDC_STATIC,static,1342308354
Control22=IDC_STATIC,static,1342308354
Control23=IDC_STATIC,static,1342308354
Control24=IDC_STATIC,static,1342308354
Control25=IDC_STATIC,static,1342308354
Control26=IDC_GIF1,static,1342177284
Control27=IDC_GIF2,static,1342177284
Control28=IDKICK,button,1342242816

[CLS:CStatsDialog]
Type=0
HeaderFile=StatsDialog.h
ImplementationFile=StatsDialog.cpp
BaseClass=CAniDialog
Filter=D
LastObject=CStatsDialog
VirtualFilter=dWC

[DLG:CG_IDD_PROGRESS (English (U.S.))]
Type=1
Class=CProgressDlg
ControlCount=3
Control1=CG_IDC_PROGDLG_PROGRESS,msctls_progress32,1350565888
Control2=CG_IDC_PROGDLG_PERCENT,static,1342308352
Control3=CG_IDC_PROGDLG_STATUS,static,1342308352

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgDlg.h
ImplementationFile=ProgDlg.cpp
BaseClass=CDialog

