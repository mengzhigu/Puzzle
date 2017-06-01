; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPicShow
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pictrue1.h"
LastPage=0

ClassCount=6
Class1=CPictrue1App
Class2=CPictrue1Doc
Class3=CPictrue1View
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CPicShow
Resource2=IDD_ABOUTBOX

[CLS:CPictrue1App]
Type=0
HeaderFile=pictrue1.h
ImplementationFile=pictrue1.cpp
Filter=N

[CLS:CPictrue1Doc]
Type=0
HeaderFile=pictrue1Doc.h
ImplementationFile=pictrue1Doc.cpp
Filter=N

[CLS:CPictrue1View]
Type=0
HeaderFile=pictrue1View.h
ImplementationFile=pictrue1View.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=pictrue1.cpp
ImplementationFile=pictrue1.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_START
Command2=ID_GAME_EASY
Command3=ID_GAME_MIDDLE
Command4=ID_GAME_HARD
Command5=ID_APP_EXIT
Command6=ID_PICTURE1
Command7=ID_PICTURE2
Command8=ID_PICTURE3
Command9=ID_PICTURE4
Command10=ID_FILE_OPEN
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_EASY
Command2=ID_GAME_HARD
Command3=ID_GAME_MIDDLE
Command4=ID_GAME_START
Command5=ID_APP_EXIT
CommandCount=5

[TB:IDR_MAINFRAME]
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
CommandCount=8

[CLS:CPicShow]
Type=0
HeaderFile=PicShow.h
ImplementationFile=PicShow.cpp
BaseClass=CFormView
Filter=D

