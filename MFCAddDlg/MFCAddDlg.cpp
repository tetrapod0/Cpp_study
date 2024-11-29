
// MFCAddDlg.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCAddDlg.h"
#include "MFCAddDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAddDlgApp

BEGIN_MESSAGE_MAP(CMFCAddDlgApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCAddDlgApp 생성

CMFCAddDlgApp::CMFCAddDlgApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCAddDlgApp 개체입니다.

CMFCAddDlgApp theApp;


// CMFCAddDlgApp 초기화

BOOL CMFCAddDlgApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCAddDlgDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}

