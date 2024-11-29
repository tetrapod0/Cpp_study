
// MyCalculator.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MyCalculator.h"
#include "MyCalculatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCalculatorApp

BEGIN_MESSAGE_MAP(CMyCalculatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyCalculatorApp 생성

CMyCalculatorApp::CMyCalculatorApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMyCalculatorApp 개체입니다.

CMyCalculatorApp theApp;


// CMyCalculatorApp 초기화

BOOL CMyCalculatorApp::InitInstance()
{
	//



	CWinApp::InitInstance();
	CMyCalculatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

