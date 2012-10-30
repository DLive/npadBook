//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#include "stdafx.h"

#include "PluginDefinition.h"
#include "menuCmdID.h"

#include "propertyDlg.h"
#include "DockingFeature/Docking.h"

// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;
HANDLE m_dllHandle;
ClocalSearchResult* pBookDlg=NULL;
tTbData mydlg;
//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
	m_dllHandle=hModule;
	if(!pBookDlg)
		pBookDlg=new ClocalSearchResult();

	createDlg();
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here


ShortcutKey showCut;
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
	showCut._isCtrl=true;
	showCut._isShift=true;
	showCut._isAlt=false;
	showCut._key='C';
    setCommand(0, TEXT("显示ITBook"), &menuShowDlg, &showCut, true);
    setCommand(1, TEXT("建议与BUG"), &DLive, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void menuShowDlg()
{
    // Open a new document
    //::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    //// Get the current scintilla
    //int which = -1;
    //::SendMessage(nppData._nppHandle,NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    //if (which == -1)
    //    return;
    //HWND curScintilla = (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;

    //// Say hello now :
    //// Scintilla control has no Unicode mode, so we use (char *) here
    //::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");
	//::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");
	CnpadBookApp::getApp()->showDlg();
	//::SendMessage(nppData._nppHandle,NPPM_DMMSHOW, 0, (LPARAM)mydlg.hClient);//
	/*CMenu show;

	show.Attach(funcItem[0]._cmdID);
	UINT isNeedShow=show.GetMenuState(funcItem[0]._cmdID,MF_CHECKED);*/
	//test
}

void DLive(){
	//MessageBox(NULL,_T("http://weibo.com/doublelive"),_T("问题反映"),NULL);
}
void createDlg()
{
	//CpropertyDlg m_propertyBar;
	
	//if (!m_propertyBar.Create(NULL,IDD_PROPERTY,CBRS_TOP|CBRS_FLYBY|CBRS_SIZE_DYNAMIC,IDD_PROPERTY))
	//{
	//	TRACE0("Failed to create dialog bar\n");
	//	return;      // fail to create
	//}/
	if(!pBookDlg->m_hWnd)
		pBookDlg->Create(IDD_LOCALRESULT);
	
	/*mydlg.dlgID=IDD_LOCALRESULT;
	mydlg.hClient=pBookDlg->m_hWnd;
	mydlg.hIconTab=NULL;
	mydlg.uMask=DWS_DF_CONT_LEFT;
	mydlg.pszModuleName=TEXT("npadBook.dll");
	mydlg.pszName=TEXT("asdfasdf");
	mydlg.pszAddInfo=TEXT("afsd");*/
	//test.ShowWindow(SW_SHOW);
	//::SendMessage(nppData._nppHandle,NPPM_DMMREGASDCKDLG, 0, (LPARAM)&mydlg);
	//::SendMessage(nppData._nppHandle,NPPM_DMMSHOW, 0, (LPARAM)test.m_hWnd);
	
	//m_propertyBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_propertyBar);

	//::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("Notepad++ Plugin Template"), MB_OK);
}
