
// MFCSliderControl.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCSliderControl.h"
#include "MFCSliderControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSliderControlApp

BEGIN_MESSAGE_MAP(CMFCSliderControlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCSliderControlApp 생성

CMFCSliderControlApp::CMFCSliderControlApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCSliderControlApp 개체입니다.

CMFCSliderControlApp theApp;


// CMFCSliderControlApp 초기화

BOOL CMFCSliderControlApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCSliderControlDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}

