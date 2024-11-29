
// MFCNotepad.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCNotepad.h"
#include "MFCNotepadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCNotepadApp

BEGIN_MESSAGE_MAP(CMFCNotepadApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCNotepadApp 생성

CMFCNotepadApp::CMFCNotepadApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCNotepadApp 개체입니다.

CMFCNotepadApp theApp;


// CMFCNotepadApp 초기화

BOOL CMFCNotepadApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCNotepadDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}

