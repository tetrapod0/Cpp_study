
// MFCListControlTest.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCListControlTest.h"
#include "MFCListControlTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCListControlTestApp

BEGIN_MESSAGE_MAP(CMFCListControlTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCListControlTestApp 생성

CMFCListControlTestApp::CMFCListControlTestApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCListControlTestApp 개체입니다.

CMFCListControlTestApp theApp;


// CMFCListControlTestApp 초기화

BOOL CMFCListControlTestApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCListControlTestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}

