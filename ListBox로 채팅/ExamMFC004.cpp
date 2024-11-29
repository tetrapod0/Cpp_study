
// ExamMFC004.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ExamMFC004.h"
#include "ExamMFC004Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamMFC004App

BEGIN_MESSAGE_MAP(CExamMFC004App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExamMFC004App 생성

CExamMFC004App::CExamMFC004App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExamMFC004App 개체입니다.

CExamMFC004App theApp;


// CExamMFC004App 초기화

BOOL CExamMFC004App::InitInstance()
{
	CWinApp::InitInstance();

	CExamMFC004Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	return FALSE;
}

