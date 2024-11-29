
// MFCSemiTransparent.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCSemiTransparent.h"
#include "MFCSemiTransparentDlg.h"

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")  // GDI+ 라이브러리를 링크

ULONG_PTR g_gdiplusToken;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSemiTransparentApp

BEGIN_MESSAGE_MAP(CMFCSemiTransparentApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCSemiTransparentApp 생성

CMFCSemiTransparentApp::CMFCSemiTransparentApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCSemiTransparentApp 개체입니다.

CMFCSemiTransparentApp theApp;


// CMFCSemiTransparentApp 초기화

BOOL CMFCSemiTransparentApp::InitInstance()
{

	// GDI+ 초기화
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, nullptr);

	CWinApp::InitInstance();
	CMFCSemiTransparentDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// GDI+ 종료
	Gdiplus::GdiplusShutdown(g_gdiplusToken);

	return FALSE;
}

//int CMFCSemiTransparentApp::ExitInstance()
//{
//	// GDI+ 종료
//	Gdiplus::GdiplusShutdown(g_gdiplusToken);
//
//	return CWinApp::ExitInstance();
//}