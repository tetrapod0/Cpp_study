
// ExamODBC.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ExamODBC.h"
#include "ExamODBCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamODBCApp

BEGIN_MESSAGE_MAP(CExamODBCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExamODBCApp 생성

CExamODBCApp::CExamODBCApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExamODBCApp 개체입니다.

CExamODBCApp theApp;


// CExamODBCApp 초기화

BOOL CExamODBCApp::InitInstance()
{
	CWinApp::InitInstance();
	CExamODBCDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

