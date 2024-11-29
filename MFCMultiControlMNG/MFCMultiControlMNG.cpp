
// MFCMultiControlMNG.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCMultiControlMNG.h"
#include "MFCMultiControlMNGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMultiControlMNGApp

BEGIN_MESSAGE_MAP(CMFCMultiControlMNGApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCMultiControlMNGApp 생성

CMFCMultiControlMNGApp::CMFCMultiControlMNGApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCMultiControlMNGApp 개체입니다.

CMFCMultiControlMNGApp theApp;


// CMFCMultiControlMNGApp 초기화

BOOL CMFCMultiControlMNGApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCMultiControlMNGDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}

